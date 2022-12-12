/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-30 11:39:57
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-09 14:32:29
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Final_Render_Target.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Final_Render_Target.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Final_Render_Target.h
 * \MoChengEngine\FrameWork\Core\Rendering\Render_Target\Final_Render_Target.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Core/Rendering/Render_Target/Render_target_base.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "Render_target_base.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Core::Rendering
{

    class Final_RenderTarget : public RenderTarget
    {

    public:
        Final_RenderTarget(Wrapper::Image::Ptr images_ptr,
                           VkAttachmentDescription attachments_description)
            : RenderTarget{images_ptr, attachments_description} {}
        //   ~Final_RenderTarget() {}

        inline static const RenderTarget::ConvertFunc DEFAULT_FINAL_CREATE_FUNC =
            [](Wrapper::Image::Ptr swap_chain_image)
        {
            VkAttachmentDescription attachment_Des{};
            attachment_Des.format = swap_chain_image->Get_format();
            attachment_Des.samples = VK_SAMPLE_COUNT_1_BIT;
            attachment_Des.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
            attachment_Des.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
            attachment_Des.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            attachment_Des.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            attachment_Des.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            attachment_Des.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            return std::make_unique<Final_RenderTarget>(swap_chain_image,
                                                        attachment_Des);
        };
        // Create_ATTACHMENT_Reference CREATE_ATTACHMENT_REFERENCE_FUNC = [](int index)
        // {
        //     VkAttachmentReference finalAttachmentRef;
        //     finalAttachmentRef.attachment = index;
        //     finalAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        //     return finalAttachmentRef;
        // };

        [[nodiscard]] VkImageLayout Get_layout() override
        {
            return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        }
        [[nodiscard]] Wrapper::SubPass::attachment_type
        Get_attachment_type() override
        {
            return Wrapper::SubPass::ResolveAttachment;
        }
        [[nodiscard]] VkAttachmentReference Get_Attachement_Reference(int index) override
        {
            VkAttachmentReference finalAttachmentRef;
            finalAttachmentRef.attachment = index;
            finalAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            return finalAttachmentRef;
        }
    };
} // namespace MoChengEngine::FrameWork::Core::Rendering