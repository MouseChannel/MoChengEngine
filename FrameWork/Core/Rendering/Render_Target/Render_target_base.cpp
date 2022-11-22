/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:57:25
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-21 12:26:00
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Render_target_base.cpp
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Render_target_base.cpp
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Render_target_base.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "Render_target_base.h"

#include "FrameWork/Core/Rendering/Render_Target/Render_target_base.h"
#include "vulkan/vulkan_core.h"
#include <stdexcept>
namespace MoChengEngine::FrameWork::Core::Rendering {
RenderTarget::RenderTarget(Wrapper::Image::Ptr images_p,
                           VkAttachmentDescription attachment_description)
    : images_ptr{images_p},
      attachment_description{attachment_description}, image{images_p->m_handle},
      image_view{images_p->Get_view()}, extent{images_ptr->Get_extent2D()} {
  //   for (auto i : images_ptr) {
  //     if (i->Get_extent().height != extent.height &&
  //         i->Get_extent().width != extent.width) {
  //       throw std::runtime_error("RenderTarget images are in different
  //       extent");
  //     }
  //   }
  //   std::transform(images_ptr.begin(), images_ptr.end(), image.end(),
  //                  [](Wrapper::Image::Ptr ptr) { return ptr->Get_handle();
  //                  });
  //   std::transform(images_ptr.begin(), images_ptr.end(), Image_views.end(),
  //                  [](Wrapper::Image::Ptr ptr) { return ptr->Get_view(); });
}

RenderTarget::RenderTarget(VkImage image, VkImageView image_view,
                           VkExtent2D extent,
                           VkAttachmentDescription attachment_description)
    : image{image}, image_view{image_view}, extent{extent},
      attachment_description{attachment_description} {}
RenderTarget::~RenderTarget() {
    images_ptr.reset();
}

 
const RenderTarget::ConvertFunc RenderTarget::DEFAULT_Convert_FUNC =
    [](Wrapper::Image::Ptr swap_chain_image) {
      VkAttachmentDescription attachment_Des;
      attachment_Des.format = swap_chain_image->Get_format();
      attachment_Des.samples = VK_SAMPLE_COUNT_1_BIT;
      attachment_Des.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
      attachment_Des.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
      attachment_Des.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
      attachment_Des.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
      attachment_Des.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
      attachment_Des.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
      return std::make_unique<RenderTarget>(swap_chain_image, attachment_Des);
    };
} // namespace MoChengEngine::FrameWork::Core::Rendering