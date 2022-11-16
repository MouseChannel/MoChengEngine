/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-14 21:37:39
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-16 13:42:23
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\FrameBuffer.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "FrameBuffer.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Wrapper {
FrameBuffer::FrameBuffer(Device::Ptr &device, VkExtent2D extent,
                         std::vector<VkImageView> &attachments,
                         RenderPass::Ptr &renderPass)
    : m_device{device} {

  VkFramebufferCreateInfo frameBufferCreateInfo{};
  frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  frameBufferCreateInfo.renderPass = renderPass->Get_handle();
  frameBufferCreateInfo.attachmentCount =
      static_cast<uint32_t>(attachments.size());
  frameBufferCreateInfo.pAttachments = attachments.data();
  frameBufferCreateInfo.width = extent.width;
  frameBufferCreateInfo.height = extent.height;
  frameBufferCreateInfo.layers = 1;

  vkCreateFramebuffer(device->Get_handle(), &frameBufferCreateInfo, nullptr,
                      &m_handle);
}
FrameBuffer::~FrameBuffer() {
  vkDestroyFramebuffer(m_device->Get_handle(), m_handle, nullptr);
}
} // namespace MoChengEngine::FrameWork::Wrapper