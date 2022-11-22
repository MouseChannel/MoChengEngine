/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-13 12:34:08
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-21 16:12:58
 * @FilePath: \MoChengEngine\FrameWork\Core\Rendering\RenderContext.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Core/Rendering/RenderFrame.h"
#include "FrameWork/Core/Rendering/Render_Target/Render_target_base.h"
#include "FrameWork/Wrapper/Command/CommandBuffer.h"
#include "FrameWork/Wrapper/Command/CommandQueue.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/FrameBuffer.h"
#include "FrameWork/Wrapper/Glfw_Window.h"
#include "FrameWork/Wrapper/Semaphore.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include "FrameWork/Wrapper/WindowSurface.h"
#include "vulkan/vulkan_core.h"
#include <memory>
#include <vector>
#include "FrameWork/Core/ObjectBase.hpp"

namespace MoChengEngine::FrameWork::Core::Rendering {

class RenderContext :public ObjectBase<RenderContext>{
private:
  Wrapper::Instance::Ptr m_instance;

private:
  Wrapper::Device::Ptr m_device;
  Wrapper::Glfw_Window_my::Ptr m_window;
  Wrapper::WindowSurface::Ptr m_surface;
  std::vector<std::unique_ptr<RenderFrame>> render_frames;
  /// Current active frame index
  uint32_t active_frame_index{0};
  Wrapper::CommandQueue::Ptr m_command_queue{nullptr};
  Wrapper::SwapChain::Ptr m_swap_chain;

  Wrapper::Semaphore::Ptr current_frame_present_finish_semaphore;
  Wrapper::Semaphore::Ptr current_frame_render_finish_semaphore;

  std::vector<Wrapper::CommandBuffer::Ptr> prepared_command_buffers;

  void Wait_all_prepared_command_buffers_finish();

public:
  RenderContext(Wrapper::Device::Ptr device,
                Wrapper::Glfw_Window_my::Ptr window,
                Wrapper::WindowSurface::Ptr surface);
  ~RenderContext();

  void Prepare();
  void Add_Prepare_command_buffers(
      std::vector<Wrapper::CommandBuffer::Ptr> command_buffers);
  Wrapper::CommandBuffer::Ptr Begin();
  /**
   * @description: Acquire_next_image
   */
  void Begin_frame();
  /**
   * @description: present current image(framebuffer)
   */
  void End_frame(VkSemaphore submit_finish_semaphone);
  /**
   * @description: using in render,submit every frame command_buffer
   * @param {Ptr} commandBuffer = a command_buffer which has been recorded
   * already
   */
  void Submit(Wrapper::CommandBuffer::Ptr commandBuffer);

  RenderTarget Create_render_target(VkAttachmentDescription attachment_des);

  [[nodiscard]] auto &Get_command_queue() { return m_command_queue; }
  [[nodiscard]] auto &Get_swap_chain() { return m_swap_chain; }
  [[nodiscard]] auto &Get_active_frame() {
    return render_frames[active_frame_index];
  }
  [[nodiscard]] auto request_command_buffer() {
    return Get_active_frame()->request_command_buffer(m_command_queue);
  }
};
} // namespace MoChengEngine::FrameWork::Core::Rendering