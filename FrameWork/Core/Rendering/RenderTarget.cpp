/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:57:25
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-17 18:42:36
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderTarget.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "RenderTarget.h"
#include "FrameWork/Core/Rendering/RenderTarget.h"
#include "vulkan/vulkan_core.h"
#include <stdexcept>
namespace MoChengEngine::FrameWork::Core::Rendering {
RenderTarget::RenderTarget(std::vector<Wrapper::Image::Ptr> &images_p)
    : images_ptr{images_p} {
  assert(images_ptr.empty());
  extent = images_ptr[0]->Get_extent2D();
  for (auto i : images_ptr) {
    if (i->Get_extent().height != extent.height &&
        i->Get_extent().width != extent.width) {
      throw std::runtime_error("RenderTarget images are in different extent");
    }
  }

  std::transform(images_ptr.begin(), images_ptr.end(), images.end(),
                 [](Wrapper::Image::Ptr ptr) { return ptr->Get_handle(); });
  std::transform(images_ptr.begin(), images_ptr.end(), Image_views.end(),
                 [](Wrapper::Image::Ptr ptr) { return ptr->Get_view(); });
}

RenderTarget::RenderTarget(std::vector<VkImage> &images,
                           std::vector<VkImageView> &images_view,
                           VkExtent2D &extent)
    : images{images}, Image_views{images_view}, extent{extent} {}
RenderTarget::~RenderTarget() {}

} // namespace MoChengEngine::FrameWork::Core::Rendering