/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 14:36:52
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 11:25:43
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandBuffer.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

 
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"
#include "CommandPool.h"

namespace MoChengEngine::FrameWork::Wrapper {
class CommandBuffer : WrapperBase<VkCommandBuffer, CommandBuffer> {
private:
  VkCommandBuffer m_handle;
  Device::Ptr m_device;
  CommandPool::Ptr m_commandPool;
 

public:
  CommandBuffer(Device::Ptr device,    CommandPool::Ptr commandPool,
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
  [[nodiscard]] VkCommandBuffer Get_handle() { return m_handle; }
};
} // namespace MoChengEngine::FrameWork::Wrapper