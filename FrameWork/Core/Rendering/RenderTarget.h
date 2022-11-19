/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:56:50
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-18 21:23:43
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderTarget.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Core/ObjectBase.hpp"
#include "FrameWork/Wrapper/Image.h"
#include "vulkan/vulkan_core.h"
#include <algorithm>

namespace MoChengEngine::FrameWork::Core::Rendering {
struct Attachment {
  VkFormat format{VK_FORMAT_UNDEFINED};

  VkSampleCountFlagBits samples{VK_SAMPLE_COUNT_1_BIT};

  VkImageLayout initial_layout{VK_IMAGE_LAYOUT_UNDEFINED};

  Attachment() = default;

  Attachment(VkFormat format, VkSampleCountFlagBits samples);
};
class RenderTarget : public ObjectBase<RenderTarget> {
private:
  VkExtent2D extent{0, 0};
  std::vector<Wrapper::Image::Ptr> images_ptr;
  std::vector<VkImage> images;
  std::vector<VkImageView> Image_views;

    std::vector<Attachment> attachments;

public:
  RenderTarget(std::vector<Wrapper::Image::Ptr> &images_ptr);
  RenderTarget(std::vector<VkImage> &images,
               std::vector<VkImageView> &images_view, VkExtent2D &extent);
  ~RenderTarget();
  [[nodiscard]] auto Get_extent() { return extent; }
  [[nodiscard]] auto Get_image() { return images; }
  [[nodiscard]] auto Get_image_view() { return Image_views; }
  [[nodiscard]] auto Get_attachment() { return attachments; }
};
} // namespace MoChengEngine::FrameWork::Core::Rendering