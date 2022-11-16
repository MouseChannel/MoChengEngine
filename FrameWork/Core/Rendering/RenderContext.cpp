

#include "RenderContext.h"
#include "FrameWork/Core/Rendering/RenderContext.h"
#include "FrameWork/Core/Rendering/RenderTarget.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Glfw_Window.h"
#include "FrameWork/Wrapper/Image.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "FrameWork/Wrapper/WindowSurface.h"
#include "vulkan/vulkan_core.h"
namespace MoChengEngine::FrameWork::Core::Rendering {
RenderContext::RenderContext(Wrapper::Device::Ptr device,
                             Wrapper::Glfw_Window::Ptr window,
                             Wrapper::WindowSurface::Ptr surface)
    : m_device{device}, m_window{window}, m_surface{surface} {
  m_swap_chain = Wrapper::SwapChain::Create(m_device, surface);
}
RenderContext::~RenderContext() {}
void RenderContext::Prepare() {
  auto &swapchain_images = m_swap_chain->Get_images();
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
      m_swap_chain->Get_extent2D(), swapchain_images, swapchain_images_view);
  render_frames.emplace_back(
      std::make_unique<RenderFrame>(m_device, render_target));
}

Wrapper::CommandBuffer::Ptr RenderContext::Begin() { Begin_frame(); }

void RenderContext::Begin_frame() {
  auto &prev_frame = render_frames[active_frame_index];

  auto present_finish_semaphore = prev_frame->Get_present_finish_semaphore();
  m_swap_chain->Acquire_next_image(
      active_frame_index, present_finish_semaphore->Get_handle(), nullptr);
}
void RenderContext::Submit(Wrapper::CommandBuffer::Ptr commandBuffer) {}

auto RenderContext::Get_commandQueue_by_flag(VkQueueFlagBits bit) {
  if (m_command_queue == nullptr) {
    auto family_index = m_device->Get_Queue_Index_By_Flag(bit);
    m_command_queue = Wrapper::CommandQueue::Create(m_device, family_index);
  }
  return m_command_queue;
}
} // namespace MoChengEngine::FrameWork::Core::Rendering