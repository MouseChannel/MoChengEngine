/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-19 18:37:26
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-21 12:28:58
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderManager.hpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "FrameWork/Core/Rendering/RenderContext.h"
 
#include "FrameWork/Core/Rendering/Render_Target/Render_target_base.h"
#include "FrameWork/Wrapper/Image.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "vulkan/vulkan_core.h"
#include <stdint.h>
#include <tuple>
#include <vector>
namespace MoChengEngine::FrameWork::Core::Rendering {
using namespace MoChengEngine::FrameWork::Wrapper;

static void Set_image_layout(RenderContext &render_context,
                             Wrapper::Image::Ptr  image,
                             VkImageLayout newLayout,
                             VkPipelineStageFlags srcStageMask,
                             VkPipelineStageFlags dstStageMask,
                             VkImageAspectFlags aspect_mask) {
  VkImageSubresourceRange region{};
  region.aspectMask = aspect_mask;
  region.baseMipLevel = 0;
  region.levelCount = 1;
  region.baseArrayLayer = 0;
  region.layerCount = 1;
  auto command_buffer = render_context.request_command_buffer();
  image->SetImageLayout(newLayout, srcStageMask, dstStageMask, region,
                        command_buffer);
  render_context.Add_Prepare_command_buffers({command_buffer});
}
static std::tuple<std::vector<Wrapper::Image::Ptr>, VkAttachmentDescription>
Create_Image_and_description(Device::Ptr &device, SwapChain::Ptr &swapChain,
                             VkSampleCountFlagBits samples,
                             VkAttachmentLoadOp loadOp,
                             VkAttachmentStoreOp storeOp,
                             VkAttachmentLoadOp stencilloadOp,
                             VkAttachmentStoreOp stencilstoreOp) {

  Wrapper::Image::Ptr image;
  VkAttachmentDescription descriptions;

  VkExtent3D extent{swapChain->Get_extent2D().height,
                    swapChain->Get_extent2D().width, 1};
  auto imageType = VK_IMAGE_TYPE_2D;
  auto tiling = VK_IMAGE_TILING_OPTIMAL;
  auto image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  auto properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  auto aspectFlags = VK_IMAGE_ASPECT_COLOR_BIT;
  auto memory_usage = VMA_MEMORY_USAGE_GPU_ONLY;
  VkSampleCountFlagBits sample_count;
  device->getMaxUsableSampleCount(sample_count);
  image = Wrapper::Image::Create(device, extent, swapChain->Get_format(),
                                 imageType, tiling, image_usage, sample_count,
                                 properties, aspectFlags, memory_usage);
  VkAttachmentDescription attachment_des;
  attachment_des.format = swapChain->Get_format();
  attachment_des.samples = samples;
  attachment_des.loadOp = loadOp;
  attachment_des.storeOp = storeOp;
  attachment_des.stencilLoadOp = stencilloadOp;
  attachment_des.stencilStoreOp = stencilstoreOp;
  attachment_des.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  attachment_des.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
}

static RenderTarget Create_render_target(Device::Ptr &device,
                                         SwapChain::Ptr &swapChain,
                                         VkSampleCountFlagBits samples,
                                         VkAttachmentLoadOp loadOp,
                                         VkAttachmentStoreOp storeOp,
                                         VkAttachmentLoadOp stencilloadOp,
                                         VkAttachmentStoreOp stencilstoreOp) {}
 

} // namespace MoChengEngine::FrameWork::Core::Rendering