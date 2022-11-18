/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:56:50
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-17 18:42:09
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
class RenderTarget : public ObjectBase<RenderTarget> {
private:
  VkExtent2D extent{0,0};
  std::vector<Wrapper::Image::Ptr> images_ptr;
  std::vector<VkImage> images;
  std::vector<VkImageView> Image_views;

  //   std::vector<Attachment> attachments;

public:
  RenderTarget(std::vector<Wrapper::Image::Ptr> &images_ptr);
  RenderTarget(std::vector<VkImage> &images, std::vector<VkImageView>& images_view ,VkExtent2D &extent);
  ~RenderTarget();
  [[nodiscard]] auto Get_extent() { return extent; }
  [[nodiscard]] auto Get_image() { return images; }
  [[nodiscard]] auto Get_image_view() { return Image_views; }
};
} // namespace MoChengEngine::FrameWork::Core::Rendering