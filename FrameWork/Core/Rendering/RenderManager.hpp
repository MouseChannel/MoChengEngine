/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-19 18:37:26
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-19 20:36:45
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderManager.hpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "FrameWork/Core/Rendering/RenderPassBinding.h"
#include "FrameWork/Wrapper/Image.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "vulkan/vulkan_core.h"
#include <stdint.h>
#include <tuple>
#include <vector>
namespace MoChengEngine::FrameWork::Core::Rendering {
using namespace MoChengEngine::FrameWork::Wrapper;

/**
 * @description: create renderpass include :
 * 1. bind renderPass attachment_descriptions to FrameBuffer attachments
 * 2. bind subpass attachment_reference to  renderPass attachment_descriptions
 *
 * @param {Ptr} &device
 * @param {VkExtent2D &} extent
 * @return {*}
 */
static RenderPassBinding &Create_Render_Pass(Device::Ptr &device,
                                             SwapChain::Ptr &swapChain) {

  VkAttachmentDescription finalAttachmentDes{};
  finalAttachmentDes.format = swapChain->Get_format();
  finalAttachmentDes.samples = VK_SAMPLE_COUNT_1_BIT;
  finalAttachmentDes.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  finalAttachmentDes.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  finalAttachmentDes.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  finalAttachmentDes.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  finalAttachmentDes.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  finalAttachmentDes.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  // 采样attachment
  VkAttachmentDescription MutiAttachmentDes{};
  MutiAttachmentDes.format = swapChain->Get_format();
  MutiAttachmentDes.samples = device->getMaxUsableSampleCount();
  MutiAttachmentDes.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  MutiAttachmentDes.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  MutiAttachmentDes.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  MutiAttachmentDes.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  MutiAttachmentDes.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  MutiAttachmentDes.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  // 深度 attachment
  // 生成深度图
  //   std::vector<Wrapper::Image::Ptr>
  //   depthImages(swapChain->Get_image_count());

  //   VkImageSubresourceRange region{};
  //   region.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
  //   region.baseMipLevel = 0;
  //   region.levelCount = 1;
  //   region.baseArrayLayer = 0;
  //   region.layerCount = 1;

  //   for (int i = 0; i < imageCount; ++i) {
  //     depthImages[i] = Image::createDepthImage(
  //         m_Device, m_SwapChainExtent.width, m_SwapChainExtent.height,
  //         m_Device->getMaxUsableSampleCount());

  //     depthImages[i]->SetImageLayout(
  //         VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
  //         VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
  //         VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT, region, commandPool);
  //   }
  //   auto depth_format = device->findSupportedFormat(
  //       {
  //           VK_FORMAT_D32_SFLOAT,
  //           VK_FORMAT_D32_SFLOAT_S8_UINT,
  //           VK_FORMAT_D24_UNORM_S8_UINT,
  //       },
  //       VK_IMAGE_TILING_OPTIMAL,
  //       VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
  //   VkAttachmentDescription depthAttachmentDes{};
  //   depthAttachmentDes.format = depth_format;
  //   depthAttachmentDes.samples = device->getMaxUsableSampleCount();
  //   depthAttachmentDes.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  //   depthAttachmentDes.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  //   depthAttachmentDes.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  //   depthAttachmentDes.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  //   depthAttachmentDes.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  //   depthAttachmentDes.finalLayout =
  //       VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  auto renderpass = Wrapper::RenderPass::Create(device);
  RenderPassBinding renderpass_bind{device, renderpass,
                                    swapChain->Get_extent2D()};

  //   renderpass_bind.Add_attachment_and_description(
  //       std::make_tuple())
  return renderpass_bind;
}

static std::tuple<std::vector<Wrapper::Image::Ptr>, VkAttachmentDescription>
Create_Images_and_description(uint32_t image_count, VkImageAspectFlags aspect,
                              Device::Ptr &device, SwapChain::Ptr &swapChain) {

  std::vector<Wrapper::Image::Ptr> images;
  VkImageSubresourceRange region{};
  region.aspectMask = aspect;
  region.baseMipLevel = 0;
  region.levelCount = 1;
  region.baseArrayLayer = 0;
  region.layerCount = 1;
  for (int i = 0; i < image_count; ++i) {
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
    images[i] = Wrapper::Image::Create(
        device, extent, swapChain->Get_format(), imageType, tiling, image_usage,
        sample_count, properties, aspectFlags, memory_usage);
  }
}

} // namespace MoChengEngine::FrameWork::Core::Rendering