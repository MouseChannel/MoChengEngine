/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:57:25
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-14 11:38:42
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
namespace MoChengEngine::FrameWork::Core::Rendering
{
    RenderTarget::RenderTarget(Wrapper::Image::Ptr images_p,
                               VkAttachmentDescription attachment_description)
        : image_ptr{images_p},
          attachment_description{attachment_description}, image{images_p->m_handle},
          image_view{images_p->Get_view()}, extent{images_p->Get_extent2D()}
    {
        
        //   for (auto i : image_ptr) {
        //     if (i->Get_extent().height != extent.height &&
        //         i->Get_extent().width != extent.width) {
        //       throw std::runtime_error("RenderTarget images are in different
        //       extent");
        //     }
        //   }
        //   std::transform(image_ptr.begin(), image_ptr.end(), image.end(),
        //                  [](Wrapper::Image::Ptr ptr) { return ptr->Get_handle();
        //                  });
        //   std::transform(image_ptr.begin(), image_ptr.end(), Image_views.end(),
        //                  [](Wrapper::Image::Ptr ptr) { return ptr->Get_view(); });
    }

    VkFormat RenderTarget::FindSupportedFormat(const Wrapper::Device::Ptr &device,
                                               const std::vector<VkFormat> &candidates,
                                               VkImageTiling tiling,
                                               VkFormatFeatureFlags features)
    {
        for (auto format : candidates)
        {
            VkFormatProperties props{};

            vkGetPhysicalDeviceFormatProperties(device->Get_gpu()->Get_handle(), format,
                                                &props);

            if (tiling == VK_IMAGE_TILING_LINEAR &&
                (props.linearTilingFeatures & features) == features)
            {
                return format;
            }

            if (tiling == VK_IMAGE_TILING_OPTIMAL &&
                (props.optimalTilingFeatures & features) == features)
            {
                return format;
            }
        }

        throw std::runtime_error("Error: can not find proper format");
    }
   
} // namespace MoChengEngine::FrameWork::Core::Rendering