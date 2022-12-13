/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-08 12:13:24
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-13 16:05:41
 * @FilePath: \MoChengEngine\G_Example\app.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Core/Rendering/Graphic_pipeline.h"
#include "FrameWork/Core/Rendering/RenderContext.h"
#include "FrameWork/Core/UniformManager/UniformManager.h"
#include "FrameWork/Wrapper/Command/CommandBuffer.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Glfw_Window.h"
#include "FrameWork/Wrapper/Instance/Instance.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/Semaphore.h"
#include "FrameWork/Wrapper/ShaderModule.h"
#include "FrameWork/Wrapper/WindowSurface.h"
#include "G_Example/model.h"
#include <vector>

namespace MoChengEngine {
using namespace FrameWork::Wrapper;
using namespace FrameWork::Core;
class App {
private:
  Device::Ptr m_Device{nullptr};
  std::unique_ptr<Rendering::RenderContext> m_render_context;
  std::unique_ptr<Rendering::GraphicPipeline> m_pipeline;
  std::unique_ptr<FrameWork::UniformManager> m_uniformManager;
  int m_Width{800};
  int m_Height{600};
  Glfw_Window_my::Ptr m_Window{nullptr};
  FrameWork::Model::Ptr m_model{nullptr};
  Instance::Ptr m_Instance{nullptr};
  std::vector<FrameWork::Wrapper::ShaderModule::Ptr> shader_modules;
  WindowSurface::Ptr m_Surface{nullptr};
  std::vector<CommandBuffer::Ptr> command_buffers;
  // test
  uint32_t  image_index{0};
  uint32_t  current_frame{0};
  std::vector<Semaphore::Ptr> present_finish_semaphore;

  std::vector<Semaphore::Ptr> render_finish_semaphore;
  std::vector<Fence::Ptr> fences;

public:
  void Init();
  void InitVulkan();

  void MainLoop();

  void CleanUp();
  void Run();

  void Prepare();
  void Prepare_shader_module();
  void Prepare_UniformManager();
  void Prepare_Pipeline();
  void Record(FrameWork::Wrapper::CommandBuffer::Ptr& command_buffer);
  void Rendering();
  App() = default;
  ~App() = default;
};

} // namespace MoChengEngine