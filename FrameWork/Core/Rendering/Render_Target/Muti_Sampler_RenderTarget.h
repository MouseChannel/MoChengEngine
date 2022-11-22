#pragma once
#include "FrameWork/Core/Rendering/Render_Target/Render_target_base.h"
#include "Render_target_base.h"

namespace MoChengEngine::FrameWork::Core::Rendering {

class Muti_Sampler_RenderTarget : public RenderTarget {

public:
  inline static const ConvertFunc DEFAULT_CREATE_FUNC =
      [](Wrapper::Image::Ptr sampler_image) {
        VkAttachmentDescription attachment_Des{};
        attachment_Des.format = sampler_image->Get_format();
        attachment_Des.samples =
            sampler_image->Get_device()->getMaxUsableSampleCount();
        attachment_Des.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        attachment_Des.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        attachment_Des.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        attachment_Des.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        attachment_Des.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        attachment_Des.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        return std::make_unique<RenderTarget>(sampler_image, attachment_Des);
      };
  inline static const Create_Image_Func DEFAULT_IMAGE_CREATE_FUNC =
      [](Wrapper::SwapChain::Ptr swapchain) {
        return Wrapper::Image::Create(
            swapchain->Get_device(),
            VkExtent3D{swapchain->Get_extent2D().height,
                       swapchain->Get_extent2D().width, 1},
            swapchain->Get_format(), VK_IMAGE_TYPE_2D, VK_IMAGE_TILING_OPTIMAL,
            VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
            swapchain->Get_device()->getMaxUsableSampleCount(),
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VK_IMAGE_ASPECT_COLOR_BIT,VMA_MEMORY_USAGE_GPU_ONLY);
      };
};
} // namespace MoChengEngine::FrameWork::Core::Rendering