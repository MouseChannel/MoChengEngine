/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 17:00:17
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-16 10:48:50
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Image.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "Device.h"
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Command/CommandBuffer.h"
#include "FrameWork/Wrapper/Resource.hpp"
#include "FrameWork/Wrapper/WrapperBase.hpp"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Wrapper {
class Image : public Resource<VkImage, Image> {
private:
  VkImageView m_view;

  VkFormat m_format;
  VkImageLayout m_layout{VK_IMAGE_LAYOUT_UNDEFINED};
  VkImageType m_imageType;

  VkExtent3D m_extent;

  VkImageViewCreateInfo Make_View_Info(const VkImageAspectFlags aspectFlags);

public:
  Image(const Device::Ptr device, const VkExtent3D &extent,
        const VkFormat &format, const VkImageType &imageType,
        const VkImageTiling &tiling, const VkImageUsageFlags &usage,
        const VkSampleCountFlagBits &sample,
        const VkMemoryPropertyFlags &properties,
        const VkImageAspectFlags &aspectFlags,
        const VmaMemoryUsage &memory_usage);
  Image(const Device::Ptr &device, VkImage image_handle,
        const VkExtent3D &extent, VkFormat format,
        const VkImageUsageFlags &usage,
        VkSampleCountFlagBits sample_count = VK_SAMPLE_COUNT_1_BIT);
  ~Image();
  Image() = delete;
  static VkImageView CreateView(VkImageViewCreateInfo viewInfo,
                                Device::Ptr &device);

  void FillImageData(size_t size, void *pData);
  // 使用barrier修改image格式
  void SetImageLayout(VkImageLayout newLayout,
                      VkPipelineStageFlags srcStageMask,
                      VkPipelineStageFlags dstStageMask,
                      VkImageSubresourceRange subresrouceRange,
                      CommandBuffer::Ptr commandBuffer);
  void FillImageData(size_t size, void *pData,
                     CommandBuffer::Ptr commandBuffer);

  [[nodiscard]] auto Get_view() const { return m_view; }
  [[nodiscard]] auto Get_extent() { return m_extent; }
  [[nodiscard]] auto Get_extent2D() {
    return VkExtent2D{.height = m_extent.height, .width = m_extent.width};
  }
};
} // namespace MoChengEngine::FrameWork::Wrapper