/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 14:36:55
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 11:27:13
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandBuffer.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "CommandBuffer.h"
#include "vulkan/vulkan_core.h"
namespace MoChengEngine::FrameWork::Wrapper {

CommandBuffer::CommandBuffer(Device::Ptr device, CommandPool::Ptr commandPool,
                             bool asSecondary)
    : m_device{device}, m_commandPool{commandPool} {

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandBufferCount = 1;
  allocInfo.commandPool = m_commandPool->Get_handle();
  allocInfo.level = asSecondary ? VK_COMMAND_BUFFER_LEVEL_SECONDARY
                                : VK_COMMAND_BUFFER_LEVEL_PRIMARY;

  VK_CHECK_SUCCESS(
      vkAllocateCommandBuffers(m_device->Get_handle(), &allocInfo, &m_handle),
      "falied to create commandBuffer");
}
CommandBuffer::~CommandBuffer() {
  vkFreeCommandBuffers(m_device->Get_handle(), m_commandPool->Get_handle(), 1,
                       &m_handle);
}
void CommandBuffer::Begin(VkCommandBufferUsageFlags flag,
                          const VkCommandBufferInheritanceInfo &inheritance) {
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = flag;
  beginInfo.pInheritanceInfo = &inheritance;
  VK_CHECK_SUCCESS(vkBeginCommandBuffer(m_handle, &beginInfo),
                   "failed to begin commandBuffer");
}
void CommandBuffer::End() {
  VK_CHECK_SUCCESS(vkEndCommandBuffer(m_handle),
                   "failed to end Command Buffer");
}
void CommandBuffer::BeginRenderPass(
    const VkRenderPassBeginInfo &renderPassBeginInfo,
    const VkSubpassContents &subPassContents) {
  vkCmdBeginRenderPass(m_handle, &renderPassBeginInfo, subPassContents);
}
void CommandBuffer::EndRenderPass() { vkCmdEndRenderPass(m_handle); }

void CommandBuffer::CopyBufferToBuffer(
    VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t copyInfoCount,
    const std::vector<VkBufferCopy> &copyInfos) {
  vkCmdCopyBuffer(m_handle, srcBuffer, dstBuffer, copyInfoCount,
                  copyInfos.data());
}
void CommandBuffer::CopyBufferToImage(VkBuffer srcBuffer, VkImage dstImage,
                                      VkImageLayout dstImageLayout,
                                      uint32_t width, uint32_t height) {
  VkBufferImageCopy region{};

  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = 0;
  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;
  region.imageOffset = {0, 0, 0};
  region.imageExtent = {width, height, 1};

  vkCmdCopyBufferToImage(m_handle, srcBuffer, dstImage, dstImageLayout, 1,
                         &region);
}

} // namespace MoChengEngine::FrameWork::Wrapper