/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-13 12:34:10
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 13:20:21
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderContext.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "RenderContext.h"
#include "FrameWork/Core/Rendering/RenderContext.h"
#include "FrameWork/Wrapper/Device.h"
namespace MoChengEngine::FrameWork::Core::Rendering {
RenderContext::RenderContext() {}
RenderContext::~RenderContext() {}

auto RenderContext::Get_commandQueue_by_flag(VkQueueFlagBits bit) {
  if (m_command_queue == nullptr) {
    auto family_index = m_device->Get_Queue_Index_By_Flag(bit);
    m_command_queue = Wrapper::CommandQueue::Create(m_device, family_index);
  }
  return m_command_queue;
}
} // namespace MoChengEngine::FrameWork::Core::Rendering