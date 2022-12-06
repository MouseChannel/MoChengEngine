/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-13 12:34:10
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-01 09:07:10
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderContext.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

#include "RenderContext.h"
#include "FrameWork/Core/Rendering/RenderContext.h"
#include "FrameWork/Core/Rendering/RenderFrame.h"
#include "FrameWork/Core/Rendering/Render_Target/Muti_Sampler_RenderTarget.h"

#include "FrameWork/Core/Rendering/Render_Target/Depth_RenderTarget.h"

#include "FrameWork/Core/Rendering/Render_Target/Final_Render_Target.h"

#include "FrameWork/Wrapper/Command/CommandBuffer.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Glfw_Window.h"
#include "FrameWork/Wrapper/Image.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/Semaphore.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "FrameWork/Wrapper/WindowSurface.h"
#include "vulkan/vulkan_core.h"
#include <algorithm>
#include <memory>
#include <vector>
namespace MoChengEngine::FrameWork::Core::Rendering {
RenderContext::RenderContext(Wrapper::Device::Ptr device,
                             Wrapper::Glfw_Window_my::Ptr window,
                             Wrapper::WindowSurface::Ptr surface)
    : m_device{device}, m_window{window}, m_surface{surface},
      m_command_queue{m_device->Get_suitable_graphics_queue()} {
  m_swap_chain = Wrapper::SwapChain::Create(m_device, surface);
}
RenderContext::~RenderContext() {}
void RenderContext::Prepare() {

  // make render_targets and fill render_frames

  for (auto i = 0; i < m_swap_chain->Get_image_count(); i++) {
    std::vector<std::unique_ptr<RenderTarget>> current_frame_render_targets;
    // first: origin swap_chain_image
    current_frame_render_targets.emplace_back(
        Final_RenderTarget::DEFAULT_FINAL_CREATE_FUNC(
            m_swap_chain->Get_images()[i]));

    // second: Muti_Sampler_RenderTarget
    current_frame_render_targets.emplace_back(
        Muti_Sampler_RenderTarget::DEFAULT_MUTI_CREATE_FUNC(
            Muti_Sampler_RenderTarget::DEFAULT_IMAGE_CREATE_FUNC(
                m_swap_chain)));
    // third: depth_RenderTarget
    current_frame_render_targets.emplace_back(
        Depth_RenderTarget::DEFAULT_DEPTH_CREATE_FUNC(
            Depth_RenderTarget::DEFAULT_IMAGE_CREATE_FUNC(m_swap_chain)));

    Prepare_RenderPass(current_frame_render_targets);
    render_frames.emplace_back(std::make_unique<RenderFrame>(
        m_device, std::move(current_frame_render_targets)));
    render_frames.back()->Prepare(m_render_pass);
  }
}

void RenderContext::Prepare_RenderPass(
    std::vector<std::unique_ptr<RenderTarget>> &render_targets) {
  if (m_render_pass)
    return;
  m_render_pass = Wrapper::RenderPass::Create(m_device);
  // 做一个subpass
  Wrapper::SubPass subPass{};
  std::vector<VkAttachmentDescription> descriptions;
  for (int index = 0; index < render_targets.size(); index++) {
    auto &render_target = render_targets[index];
    descriptions.emplace_back(render_target->Get_attachments_description());
    // add subpass attachment reference
    auto attachment_reference =
        render_target->CREATE_ATTACHMENT_REFERENCE_FUNC(index);
    auto attachment_type = render_target->Get_attachment_type();
    subPass.Add_attachment_reference(attachment_reference, attachment_type);
  }
  m_render_pass->Set_attachment_description(descriptions);
  // colorAttachment = 多重采样图片
  //  ResolveAttachment，对colorAttachment的每个像素内的采样点做平均值
  subPass.Build_SubPass_Description();
  VkSubpassDependency dependency{};
  dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass = 0;
  // 上一个pass在哪一个stage的哪一个操作完成
  dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.srcAccessMask = 0;
  // P一个pass在哪一个stage的哪一个操作阻塞
  dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT |
                             VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

  m_render_pass->AddSubPass(subPass, dependency);
  m_render_pass->BuildRenderPass();
}

Wrapper::CommandBuffer::Ptr RenderContext::Begin() {
  Begin_frame();
  return Get_active_frame()->request_command_buffer(m_command_queue);
}

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
void RenderContext::Add_Prepare_command_buffers(
    std::vector<Wrapper::CommandBuffer::Ptr> command_buffers) {
  std::transform(command_buffers.begin(), command_buffers.end(),
                 prepared_command_buffers.end(),
                 [](Wrapper::CommandBuffer::Ptr command_buffer_ptr) {
                   return command_buffer_ptr;
                 });
}

void RenderContext::Wait_all_prepared_command_buffers_finish() {
  std::vector<VkCommandBuffer> command_buffer_handles;
  std::transform(prepared_command_buffers.begin(),
                 prepared_command_buffers.end(), command_buffer_handles.end(),
                 [](Wrapper::CommandBuffer::Ptr command_buffer_ptr) {
                   return command_buffer_ptr->Get_handle();
                 });
  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  submitInfo.commandBufferCount = prepared_command_buffers.size();
  submitInfo.pCommandBuffers = command_buffer_handles.data();
  vkQueueSubmit(m_command_queue->Get_handle(), 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(m_command_queue->Get_handle());
  prepared_command_buffers.clear();
}

} // namespace MoChengEngine::FrameWork::Core::Rendering