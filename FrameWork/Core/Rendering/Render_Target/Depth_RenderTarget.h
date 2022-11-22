/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-21 10:59:50
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-21 11:58:45
 * @FilePath:
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Depth_RenderTarget.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Depth_RenderTarget.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Depth_RenderTarget.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Depth_RenderTarget.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Depth_RenderTarget.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Depth_RenderTarget.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Depth_RenderTarget.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Core/Rendering/Render_Target/Render_target_base.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "Render_target_base.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Core::Rendering {

class Depth_RenderTarget : public RenderTarget {

public:
  inline static const ConvertFunc DEFAULT_DEPTH_CREATE_FUNC =
      [](Wrapper::Image::Ptr depth_image) {
        VkAttachmentDescription attachment_Des;
        attachment_Des.format = depth_image->Get_format();
        attachment_Des.samples =
            depth_image->Get_device()->getMaxUsableSampleCount();
        attachment_Des.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachment_Des.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachment_Des.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachment_Des.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachment_Des.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        attachment_Des.finalLayout =
            VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        return std::make_unique<RenderTarget>(depth_image, attachment_Des);
      };

  inline static const Create_Image_Func DEFAULT_IMAGE_CREATE_FUNC =
      [](Wrapper::SwapChain::Ptr swapchain) {
        return Wrapper::Image::Create(
            swapchain->Get_device(),
            VkExtent3D{swapchain->Get_extent2D().height,
                       swapchain->Get_extent2D().width, 1},
            swapchain->Get_format(), VK_IMAGE_TYPE_2D, VK_IMAGE_TILING_OPTIMAL,
            VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
            swapchain->Get_device()->getMaxUsableSampleCount(),
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VK_IMAGE_ASPECT_DEPTH_BIT,
            VMA_MEMORY_USAGE_GPU_ONLY);
      };
};
} // namespace MoChengEngine::FrameWork::Core::Rendering