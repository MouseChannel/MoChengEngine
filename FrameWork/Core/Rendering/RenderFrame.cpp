/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:46:25
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-18 14:53:54
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderFrame.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "RenderFrame.h"
#include "FrameWork/Core/ObjectPool.hpp"
#include "FrameWork/Core/Rendering/RenderFrame.h"
#include "FrameWork/Wrapper/Command/CommandBuffer.h"
#include "FrameWork/Wrapper/Command/CommandPool.h"
#include "FrameWork/Wrapper/Semaphore.h"
#include <algorithm>
namespace MoChengEngine::FrameWork::Core::Rendering {
RenderFrame::RenderFrame(Wrapper::Device::Ptr &device,
                         RenderTarget::Ptr &renderTarget)
    : m_device{device}, m_render_target{renderTarget},
      m_swapchain_render_target{renderTarget},
      m_render_finish_semaphore{Wrapper::Semaphore::Create(m_device)},
      m_present_finish_semaphore{Wrapper::Semaphore::Create(m_device)},
      command_buffers{[this]() {
        return Wrapper::CommandBuffer::Create(m_device, m_command_pool[0]);
      }} {}

RenderFrame::~RenderFrame() {}

Wrapper::CommandPool::Ptr
RenderFrame::Get_command_pool(Wrapper::CommandQueue::Ptr command_queue) {
  auto target_command_pool =
      std::find_if(m_command_pool.begin(), m_command_pool.end(),
                   [command_queue](auto command_pool) {
                     return command_pool->Get_queue_family_index() ==
                            command_queue->Get_family_index();
                   });
  if (target_command_pool == m_command_pool.end()) {
    // did not contains suitable command_pool, create one
    m_command_pool.emplace_back(Wrapper::CommandPool::Create(
        m_device, command_queue->Get_family_propertie().queueFlags));
    return m_command_pool.back();
  }
  return *target_command_pool;
}
Wrapper::CommandBuffer::Ptr
RenderFrame::request_command_buffer(Wrapper::CommandQueue::Ptr command_queue) {
  auto command_pool = Get_command_pool(command_queue);
  command_buffers.request_object([this, command_pool]() {
    return Wrapper::CommandBuffer::Create(m_device, command_pool);
  });
}

} // namespace MoChengEngine::FrameWork::Core::Rendering