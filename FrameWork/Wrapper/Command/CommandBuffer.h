/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 14:36:52
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-12 13:22:15
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandBuffer.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "CommandPool.h"
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Base/Component.hpp"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/FrameBuffer.h"
#include "FrameWork/Wrapper/RenderPass.h"

#include <functional>

namespace MoChengEngine::FrameWork {
namespace Wrapper {

class CommandBuffer : public Component<VkCommandBuffer, CommandBuffer> {
private:
  CommandPool::Ptr m_commandPool;
  //   bool is_recording{false};

public:
  enum { primary = 0, second = 1 };
  CommandBuffer(Device::Ptr device, CommandPool::Ptr commandPool,
                bool asSecondary = false);
  ~CommandBuffer();
  void Add_Task(std::function<void()> task, VkCommandBufferUsageFlags flag = 0);
  static void Wait_All(CommandQueue::Ptr command_queue,
                       std::vector<CommandBuffer::Ptr> command_buffers);
  void Wait(CommandQueue::Ptr command_queue);
  void Begin(VkCommandBufferUsageFlags flag = 0,
             const VkCommandBufferInheritanceInfo &inheritance = {});
  void End();
  void BeginRenderPass(
      const VkRenderPassBeginInfo &renderPassBeginInfo,
      const VkSubpassContents &subPassContents = VK_SUBPASS_CONTENTS_INLINE);
  void EndRenderPass();
  void BindGraphicPipeline(const VkPipeline &pipeline);
  void BindVertexBuffer(const std::vector<VkBuffer> &buffers);
  void BindDescriptorSet(const VkPipelineLayout layout,
                         const VkDescriptorSet &descriptorSet);
  void BindIndexBuffer(const VkBuffer &buffer);
  void DrawIndex(size_t indexCount);
  void CopyBufferToBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer,
                          uint32_t copyInfoCount,
                          const std::vector<VkBufferCopy> &copyInfos);
  void CopyBufferToImage(VkBuffer srcBuffer, VkImage dstImage,
                         VkImageLayout dstImageLayout, uint32_t width,
                         uint32_t height);
  void TransferImageLayout(VkImageMemoryBarrier &imageMemoryBarrier,
                           VkPipelineStageFlags srcStageMask,
                           VkPipelineStageFlags dstStageMask);
  //   [[nodiscard]] VkCommandBuffer Get_handle() { return m_handle; }
};
} // namespace Wrapper
struct COMMAND {
  std::function<Wrapper::CommandBuffer::Ptr()> request_command_buffer;
  Wrapper::CommandQueue::Ptr queue;
};

} // namespace MoChengEngine::FrameWork