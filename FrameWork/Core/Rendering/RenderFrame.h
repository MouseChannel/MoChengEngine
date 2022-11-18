/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:46:21
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-18 14:32:46
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderFrame.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

// RenderTarget contains three vectors for:  Image, ImageView and Attachment.
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Core/ObjectPool.hpp"
#include "FrameWork/Core/Rendering/RenderTarget.h"
#include "FrameWork/Wrapper/Command/CommandBuffer.h"
#include "FrameWork/Wrapper/Command/CommandPool.h"
#include "FrameWork/Wrapper/Command/CommandQueue.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/FrameBuffer.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/Semaphore.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Core::Rendering {

class RenderFrame : public ObjectBase<RenderFrame> {
private:
  Wrapper::Device::Ptr m_device{nullptr};
  RenderTarget::Ptr m_render_target;

  std::vector<Wrapper::CommandPool::Ptr> m_command_pool ;

  RenderTarget::Ptr m_swapchain_render_target;

  std::vector<Wrapper::CommandBuffer::Ptr> m_command_buffers;

  Wrapper::Semaphore::Ptr m_render_finish_semaphore;
  Wrapper::Semaphore::Ptr m_present_finish_semaphore;

  ObjectPool<Wrapper::CommandBuffer::Ptr> command_buffers ;

public:
  RenderFrame(Wrapper::Device::Ptr &device, RenderTarget::Ptr &renderTarget);
  ~RenderFrame();
  Wrapper::CommandBuffer::Ptr request_command_buffer(Wrapper::CommandQueue::Ptr command_queue);
  [[nodiscard]] Wrapper::CommandPool::Ptr Get_command_pool(Wrapper::CommandQueue::Ptr command_queue);
  [[nodiscard]] auto Get_render_finish_semaphore() {
    return m_render_finish_semaphore;
  }

  [[nodiscard]] auto Get_present_finish_semaphore() {
    return m_present_finish_semaphore;
  }
 
};
} // namespace MoChengEngine::FrameWork::Core::Rendering
