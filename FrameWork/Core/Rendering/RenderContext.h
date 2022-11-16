/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-13 12:34:08
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-16 20:45:06
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderContext.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Core/Rendering/RenderFrame.h"
#include "FrameWork/Wrapper/Command/CommandBuffer.h"
#include "FrameWork/Wrapper/Command/CommandQueue.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Glfw_Window.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "FrameWork/Wrapper/WindowSurface.h"
#include <memory>


namespace MoChengEngine::FrameWork::Core::Rendering {

class RenderContext {
private:
  Wrapper::Instance::Ptr m_instance;

private:
  Wrapper::Device::Ptr m_device;
  Wrapper::Glfw_Window::Ptr m_window;
  Wrapper::WindowSurface::Ptr m_surface;
  std::vector<std::unique_ptr<RenderFrame>> render_frames;
  /// Current active frame index
  uint32_t active_frame_index{0};
  Wrapper::CommandQueue::Ptr m_command_queue{nullptr};
  Wrapper::SwapChain::Ptr m_swap_chain;

public:
  RenderContext(Wrapper::Device::Ptr device, Wrapper::Glfw_Window::Ptr window,
                Wrapper::WindowSurface::Ptr surface);
  ~RenderContext();

  void Prepare();
  Wrapper::CommandBuffer::Ptr Begin();
  void Begin_frame();
  void End_frame();
  void Submit(Wrapper::CommandBuffer::Ptr commandBuffer);
  auto &Get_swap_chain() { return m_swap_chain; }
  auto &Get_active_frame() { return render_frames[active_frame_index]; }
  auto Get_commandQueue_by_flag(VkQueueFlagBits bit);
};
} // namespace MoChengEngine::FrameWork::Core::Rendering