/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 17:00:17
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-22 20:42:50
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Image.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

#pragma once
#include "Device.h"
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Base/Resource.hpp"
#include "FrameWork/Wrapper/Base/WrapperBase.hpp"
#include "FrameWork/Wrapper/Command/CommandBuffer.h"
#include "vulkan/vulkan_core.h"


namespace MoChengEngine::FrameWork::Wrapper {
class Image : public Resource<VkImage, Image> {
private:
  VkImageView m_view{nullptr};

  VkFormat m_format;
  VkImageLayout m_layout{VK_IMAGE_LAYOUT_UNDEFINED};
  VkImageType m_imageType;

  VkExtent3D m_extent;
    bool auto_destroy;
  VkImageViewCreateInfo Make_View_Info(const VkImageAspectFlags aspectFlags);

public:
  Image(const Device::Ptr device, const VkExtent3D extent,
        const VkFormat format, const VkImageType imageType,
        const VkImageTiling tiling, const VkImageUsageFlags usage,
        const VkSampleCountFlagBits sample,
        const VkMemoryPropertyFlags properties,
        const VkImageAspectFlags aspectFlags,
        const VmaMemoryUsage memory_usage);
  Image(const Device::Ptr &device, VkImage image_handle,
        const VkExtent3D extent, VkFormat format  , bool auto_destroy = false);
  ~Image();
  Image() = delete;
  static VkImageView CreateView(VkImageViewCreateInfo viewInfo,
                                Device::Ptr  device);

  void FillImageData(size_t size, void *pData);
  // 使用barrier修改image格式
  void SetImageLayout(VkImageLayout newLayout,
                      VkPipelineStageFlags srcStageMask,
                      VkPipelineStageFlags dstStageMask,
                      VkImageSubresourceRange subresrouceRange,
                      CommandBuffer::Ptr &commandBuffer);
  void FillImageData(size_t size, void *pData,
                     CommandBuffer::Ptr commandBuffer);

  [[nodiscard]] auto Get_view() const { return m_view; }
  [[nodiscard]] auto Get_extent() { return m_extent; }
  [[nodiscard]] auto Get_extent2D() {
    return VkExtent2D{.height = m_extent.height, .width = m_extent.width};
  }
  [[nodiscard]] auto Get_format() { return m_format; }
};
} // namespace MoChengEngine::FrameWork::Wrapper