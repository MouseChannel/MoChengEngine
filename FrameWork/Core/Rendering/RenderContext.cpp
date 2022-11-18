/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-13 12:34:10
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-18 14:23:46
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderContext.cpp
 * @Description: nullptr
 * 
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved. 
 */


#include "RenderContext.h"
#include "FrameWork/Core/Rendering/RenderContext.h"
#include "FrameWork/Core/Rendering/RenderTarget.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Glfw_Window.h"
#include "FrameWork/Wrapper/Image.h"
#include "FrameWork/Wrapper/Semaphore.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "FrameWork/Wrapper/WindowSurface.h"
#include "vulkan/vulkan_core.h"
namespace MoChengEngine::FrameWork::Core::Rendering {
RenderContext::RenderContext(Wrapper::Device::Ptr device,
                             Wrapper::Glfw_Window::Ptr window,
                             Wrapper::WindowSurface::Ptr surface)
    : m_device{device}, m_window{window}, m_surface{surface},
      m_command_queue{m_device->Get_suitable_graphics_queue()} {
  m_swap_chain = Wrapper::SwapChain::Create(m_device, surface);
}
RenderContext::~RenderContext() {}
void RenderContext::Prepare() {
  auto swapchain_images = m_swap_chain->Get_images();
  std::vector<VkImageView> swapchain_images_view;
  std::transform(
      swapchain_images.begin(), swapchain_images.end(),
      swapchain_images_view.end(), [this](VkImage image_handle) {
        VkImageViewCreateInfo imageViewCreateInfo{};
        imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        imageViewCreateInfo.format = m_swap_chain->Get_format();
        imageViewCreateInfo.image = image_handle;
        imageViewCreateInfo.subresourceRange.aspectMask =
            VK_IMAGE_ASPECT_COLOR_BIT;
        imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
        imageViewCreateInfo.subresourceRange.levelCount = 1;
        imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
        imageViewCreateInfo.subresourceRange.layerCount = 1;
        return Wrapper::Image::CreateView(imageViewCreateInfo, m_device);
      });

  auto render_target = RenderTarget::Create(
      swapchain_images, swapchain_images_view, m_swap_chain->Get_extent2D());
  render_frames.emplace_back(
      std::make_unique<RenderFrame>(m_device, render_target));
}

Wrapper::CommandBuffer::Ptr RenderContext::Begin() { Begin_frame(); return Get_current_frame()->request_command_buffer(m_command_queue);}

void RenderContext::Begin_frame() {
  auto &prev_frame = render_frames[active_frame_index];

  current_frame_present_finish_semaphore =
      prev_frame->Get_present_finish_semaphore();
  current_frame_render_finish_semaphore =
      prev_frame->Get_render_finish_semaphore();
  m_swap_chain->Acquire_next_image(
      active_frame_index, current_frame_present_finish_semaphore->Get_handle(),
      nullptr);
}
void RenderContext::Submit(Wrapper::CommandBuffer::Ptr commandBuffer) {

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  // 设置同步信息

  VkPipelineStageFlags waitStages[] = {
      VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores =
      &current_frame_render_finish_semaphore->Get_handle();
  submitInfo.pWaitDstStageMask = waitStages;

  // 提交哪些命令

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffer->Get_handle();

  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores =
      &current_frame_present_finish_semaphore->Get_handle();

  m_command_queue->Submit({submitInfo}, VK_NULL_HANDLE);
}
void RenderContext::End_frame(VkSemaphore submit_finish_semaphone) {
  VkPresentInfoKHR present_info;
  present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

  present_info.waitSemaphoreCount = 1;
  present_info.pWaitSemaphores = &submit_finish_semaphone;
  present_info.swapchainCount = 1;
  present_info.pSwapchains = &m_swap_chain->Get_handle();
  present_info.pImageIndices = &active_frame_index;
  m_command_queue->Present(&present_info);
}

} // namespace MoChengEngine::FrameWork::Core::Rendering