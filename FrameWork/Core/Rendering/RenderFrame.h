/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:46:21
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-16 15:08:08
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderFrame.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

// RenderTarget contains three vectors for:  Image, ImageView and Attachment.
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Core/Rendering/RenderTarget.h"
#include "FrameWork/Wrapper/Command/CommandPool.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/FrameBuffer.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/Semaphore.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Core::Rendering {

class RenderFrame : public ObjectBase<RenderFrame> {
private:
  Wrapper::Device::Ptr m_device;
  RenderTarget::Ptr m_render_target;
  Wrapper::CommandPool::Ptr m_command_pool;

  RenderTarget::Ptr m_swapchain_render_target;

  Wrapper::Semaphore::Ptr m_render_finish_semaphore;
  Wrapper::Semaphore::Ptr m_present_finish_semaphore;

public:
  RenderFrame(Wrapper::Device::Ptr &device, RenderTarget::Ptr &renderTarget);
  ~RenderFrame();
  [[nodiscard]] auto Get_command_pool(VkQueueFlagBits bit) {
    return m_command_pool;
  }
  [[nodiscard]] auto Get_render_finish_semaphore() {
    return m_render_finish_semaphore;
  }

  [[nodiscard]] auto Get_present_finish_semaphore() {
    return m_present_finish_semaphore;
  }
};
} // namespace MoChengEngine::FrameWork::Core::Rendering
