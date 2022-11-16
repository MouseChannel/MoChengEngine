/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:46:25
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-16 14:31:50
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderFrame.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "RenderFrame.h"
#include "FrameWork/Core/Rendering/RenderFrame.h"
#include "FrameWork/Wrapper/Semaphore.h"
namespace MoChengEngine::FrameWork::Core::Rendering {
RenderFrame::RenderFrame(Wrapper::Device::Ptr &device,
                         RenderTarget::Ptr &renderTarget)
    : m_device{device}, m_render_target{renderTarget},
      m_swapchain_render_target{renderTarget},

      m_semaphore{Wrapper::Semaphore::Create(device)} {}

RenderFrame::~RenderFrame() {}
// auto RenderFrame::Get_command_pool(VkQueueFlagBits bit) {
//   if (m_command_pool == nullptr) {
//     m_command_pool = Wrapper::CommandPool::Create(m_device, bit);
//   }
//   return m_command_pool;
// }
} // namespace MoChengEngine::FrameWork::Core::Rendering