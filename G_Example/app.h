/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-08 12:13:24
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-01 09:25:41
 * @FilePath: \MoChengEngine\G_Example\app.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Core/Rendering/Graphic_pipeline.h"
#include "FrameWork/Core/Rendering/RenderContext.h"
#include "FrameWork/Core/UniformManager/UniformManager.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Glfw_Window.h"
#include "FrameWork/Wrapper/Instance/Instance.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/ShaderModule.h"
#include "FrameWork/Wrapper/WindowSurface.h"
#include "G_Example/model.hpp"

 
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
  void Record();
  App() = default;
  ~App() = default;
};

void App::Run() {
  Init();
  Prepare();
    MainLoop();
  //   CleanUp();
}

void App::Init() {

  m_Window = Glfw_Window_my::Create();
  m_Instance = Instance::Create();

  m_Surface = WindowSurface::Create(m_Instance, m_Window);

  m_Device = Device::Create(m_Instance, m_Instance->Get_gpus()[0], m_Surface);

  m_model = FrameWork::Model::Create(m_Device);

  m_render_context =
      std::make_unique<Rendering::RenderContext>(m_Device, m_Window, m_Surface);
}
void App::Prepare() {
  m_render_context->Prepare();

  Prepare_UniformManager();

  Prepare_Pipeline();
}

void App::Prepare_UniformManager() {
  // prepare uniformManager
  m_uniformManager = std::make_unique<FrameWork::UniformManager>();
  auto command_buffer = m_render_context->request_command_buffer();
  command_buffer->Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
  m_uniformManager->Prepare(
      m_Device, command_buffer,
      m_render_context->Get_swap_chain()->Get_image_count());
  command_buffer->End();
  m_render_context->Add_Prepare_command_buffers({command_buffer});
}
void App::Prepare_shader_module() {
  //   std::vector<FrameWork::Wrapper::ShaderModule::Ptr> shader_modules{};

  auto shaderVertex = FrameWork::Wrapper::ShaderModule::CreateR(
      m_Device, "D:\\cpp\\vk\\shaders/vs.spv", VK_SHADER_STAGE_VERTEX_BIT,
      "main");
  shader_modules.push_back(shaderVertex);

  auto shaderFragment = FrameWork::Wrapper::ShaderModule::CreateR(
      m_Device, "D:\\cpp\\vk\\shaders/fs.spv", VK_SHADER_STAGE_FRAGMENT_BIT,
      "main");
  shader_modules.push_back(shaderFragment);
}
void App::Prepare_Pipeline() {

  // prepare pipeline
  m_pipeline = std::make_unique<Rendering::GraphicPipeline>(
      m_Device, m_model->getVertexInputBindingDescriptions(),
      m_model->getAttributeDescriptions(), m_render_context->Get_Render_Pass(),
      m_uniformManager->GetDescriptorLayout()->Get_handle(),
      m_Device->getMaxUsableSampleCount());
  auto shaders = std::vector<VkPipelineShaderStageCreateInfo>();

  std::transform(shader_modules.begin(), shader_modules.end(), shaders.end(),
                 [](auto shader_ptr) {
                   return shader_ptr->Make_Createinfo_in_pipeline();
                 });

  m_pipeline->Build_pipeline(shaders);
}

void App::Record() { auto command_buffer = m_render_context->Begin(); }
void App::MainLoop() {
  while (!m_Window->ShouldClose()) {
    m_Window->PollEvent();
  }
}

} // namespace MoChengEngine