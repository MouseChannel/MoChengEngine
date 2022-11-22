/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-08 12:13:24
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-22 20:44:30
 * @FilePath: \MoChengEngine\G_Example\app.hpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

#include "FrameWork/Core/Rendering/Graphic_pipeline.h"
#include "FrameWork/Core/Rendering/RenderContext.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Glfw_Window.h"
#include "FrameWork/Wrapper/Instance/Instance.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/WindowSurface.h"

namespace MoChengEngine {
using namespace FrameWork::Wrapper;
class App {
private:
  Device::Ptr m_Device{nullptr};
  FrameWork::Core::Rendering::RenderContext::Ptr render_context;
  FrameWork::Core::Rendering::GraphicPipeline::Ptr m_pipeline;
  int m_Width{800};
  int m_Height{600};
  Glfw_Window_my::Ptr m_Window{nullptr};
  Instance::Ptr m_Instance{nullptr};

  WindowSurface::Ptr m_Surface{nullptr};
  RenderPass::Ptr m_Renderpass{nullptr};

public:
  void Init();
  void InitVulkan();

  void MainLoop();

  void CleanUp();
  void Run();

  void Prepare();
  App() = default;
  ~App() = default;
};
void App::Run() {
  Init();
  Prepare();
  //   MainLoop();
  //   CleanUp();
}

void App::Init() {

  m_Window = Glfw_Window_my::Create();
  m_Instance = Instance::Create();

  m_Surface = WindowSurface::Create(m_Instance, m_Window);

  m_Device = Device::Create(m_Instance, m_Instance->Get_gpus()[0], m_Surface);
}

void App::Prepare() {
  render_context = FrameWork::Core::Rendering::RenderContext::Create(
      m_Device, m_Window, m_Surface);

  m_Renderpass = RenderPass::Create(m_Device);
  //   m_pipeline = FrameWork::Core::Rendering::GraphicPipeline::Create(auto
  //   args...)
}

} // namespace MoChengEngine