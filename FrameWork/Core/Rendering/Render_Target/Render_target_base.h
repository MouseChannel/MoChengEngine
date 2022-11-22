/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:56:50
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-21 12:03:30
 * @FilePath:
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Render_target_base.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Render_target_base.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Render_target_base.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Core/ObjectBase.hpp"
#include "FrameWork/Wrapper/Image.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "functional"
#include "vulkan/vulkan_core.h"
#include <algorithm>

namespace MoChengEngine::FrameWork::Core::Rendering {

/**
 * @description: contains three object，to bind framebuffer and renderpass
 * 1. image_handle
 * 2. image_view using in framebuffer
 * 3. attachment using in renderpass
 *
 *  actually only need 2 and 3
 */
class RenderTarget {
private:
  VkExtent2D extent{0, 0};
  Wrapper::Image::Ptr images_ptr;
  VkImage image;
  VkImageView image_view;

  VkAttachmentDescription attachment_description;

public:
  /**
   * @description: convert a image Ptr to a complete render_target
   */
  using ConvertFunc =
      std::function<std::unique_ptr<RenderTarget>(Wrapper::Image::Ptr)>;
  /**
   * @description: default convert swapchain images to final present images
   */
  static const ConvertFunc DEFAULT_Convert_FUNC;
  /**
   * @description: create a image Ptr
   */
  using Create_Image_Func =
      std::function<Wrapper::Image::Ptr(Wrapper::SwapChain::Ptr)>;

  RenderTarget(Wrapper::Image::Ptr images_ptr,
               VkAttachmentDescription attachments_description);
  RenderTarget(VkImage images, VkImageView images_view, VkExtent2D extent,
               VkAttachmentDescription attachments_description);
  ~RenderTarget();
 
  [[nodiscard]] auto Get_extent() { return extent; }
  [[nodiscard]] auto Get_image() { return image; }
  [[nodiscard]] auto Get_image_view() { return image_view; }
  [[nodiscard]] auto Get_attachments_description() {
    return attachment_description;
  }
};
} // namespace MoChengEngine::FrameWork::Core::Rendering