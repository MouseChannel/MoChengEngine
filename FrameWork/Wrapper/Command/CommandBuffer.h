/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 14:36:52
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-16 13:45:41
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandBuffer.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "CommandPool.h"
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/FrameBuffer.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"

namespace MoChengEngine::FrameWork::Wrapper {
struct RenderPassBinding {
  const Wrapper::RenderPass::Ptr render_pass;

  const Wrapper::FrameBuffer::Ptr framebuffer;
  static RenderPassBinding Create(Wrapper::Device::Ptr &device,
                                  const Wrapper::RenderPass::Ptr &render_pass,
                                  VkExtent2D extent,
                                  std::vector<VkImageView> &attachments) {
    return RenderPassBinding{
        .render_pass = render_pass,
        .framebuffer = Wrapper::FrameBuffer::Create(
            device->Get_handle(), extent, attachments, render_pass)};
  }
};
class CommandBuffer : public WrapperBase<VkCommandBuffer, CommandBuffer> {
private:
  Device::Ptr m_device;
  RenderPassBinding current_render_pass;
  CommandPool::Ptr m_commandPool;

public:
  CommandBuffer(Device::Ptr device, CommandPool::Ptr commandPool,
                bool asSecondary = false);
  ~CommandBuffer();
  void Begin(VkCommandBufferUsageFlags flag = 0,
             const VkCommandBufferInheritanceInfo &inheritance = {});
  void End();
  void BeginRenderPass(
      const VkRenderPassBeginInfo &renderPassBeginInfo,
      const VkSubpassContents &subPassContents = VK_SUBPASS_CONTENTS_INLINE);
  void EndRenderPass();
  void CopyBufferToBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer,
                          uint32_t copyInfoCount,
                          const std::vector<VkBufferCopy> &copyInfos);
  void CopyBufferToImage(VkBuffer srcBuffer, VkImage dstImage,
                         VkImageLayout dstImageLayout, uint32_t width,
                         uint32_t height);
  //   [[nodiscard]] VkCommandBuffer Get_handle() { return m_handle; }
};
} // namespace MoChengEngine::FrameWork::Wrapper