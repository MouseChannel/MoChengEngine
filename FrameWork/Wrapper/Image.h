/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 17:00:17
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 13:28:25
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Image.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"
#include "Device.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Wrapper {
class Image : public WrapperBase<VkImage, Image> {
private:
  VkImage m_handle;
  Device::Ptr m_device;
  VkFormat m_format;

public:
  Image(const Device::Ptr  device, const int &width, const int &height,
        const VkFormat &format, const VkImageType &imageType,
        const VkImageTiling &tiling, const VkImageUsageFlags &usage,
        const VkSampleCountFlagBits &sample,
        const VkMemoryPropertyFlags &properties,
        const VkImageAspectFlags &aspectFlags);
  ~Image();
  void SetImageLayout(VkImageLayout newLayout,
                      VkPipelineStageFlags srcStageMask,
                      VkPipelineStageFlags dstStageMask,
                      VkImageSubresourceRange subresrouceRange);

  void FillImageData(size_t size, void *pData);
  [[nodiscard]] VkImage Get_handle() { return m_handle; }
};
} // namespace MoChengEngine::FrameWork::Wrapper