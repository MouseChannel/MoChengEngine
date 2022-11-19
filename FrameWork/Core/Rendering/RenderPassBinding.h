/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-19 10:53:01
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-19 20:24:01
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderPassBinding.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/FrameBuffer.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include <tuple>
 

namespace MoChengEngine::FrameWork::Core::Rendering {

/**
 * @description: bind render_pass and framebuffer
 * make sure attachments(in framebuffer ) match description(in render_pass)
 */
class RenderPassBinding {
    public:
  using Device = Wrapper::Device;
  using RenderPass = Wrapper::RenderPass;
  using FrameBuffer = Wrapper::FrameBuffer;
  Device::Ptr m_device;
  VkExtent2D m_extent;
  RenderPass::Ptr m_render_pass;
  std::vector<VkAttachmentDescription> descriptions;
  std::vector<VkImageView> attachments;
  std::vector<std::tuple<VkAttachmentDescription, VkImageView>>
      description_and_attachments;
  FrameBuffer::Ptr framebuffer;

  RenderPassBinding() = delete;
  RenderPassBinding(Device::Ptr &device, RenderPass::Ptr &renderPass,
                    VkExtent2D &extent);
  ~RenderPassBinding();
  void Add_attachment_and_description(
      std::tuple<VkImageView, VkAttachmentDescription> &bind,
      Wrapper::SubPass::attachment_type attachment_type);

  void Build(); 
};
} // namespace MoChengEngine::FrameWork::Core::Rendering