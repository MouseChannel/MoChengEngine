/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-30 09:51:44
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-12 15:09:20
 * @FilePath: \MoChengEngine\G_Example\app.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "app.h"
#include "FrameWork/Core/UniformManager/UniformManager.h"
#include "FrameWork/Wrapper/ShaderModule.h"
#include "vulkan/vulkan_core.h"

#include <algorithm>
#include <vector>
namespace MoChengEngine {

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
  m_model->loadModel("D:\\cpp\\vk\\assets\\jqm.obj", m_Device);

  m_render_context =
      std::make_unique<Rendering::RenderContext>(m_Device, m_Window, m_Surface);
}
void App::Prepare() {
  m_render_context->Prepare();

  Prepare_UniformManager();
  Prepare_shader_module();

  Prepare_Pipeline();
}

void App::Prepare_UniformManager() {
  // prepare uniformManager
  m_uniformManager = std::make_unique<FrameWork::UniformManager>();
  //   auto command_buffer =
  //   std::vector<FrameWork::Wrapper::CommandBuffer::Ptr> command_buffers;

  m_uniformManager->Prepare(
      m_Device,
      FrameWork::COMMAND{
          .request_command_buffer =
              [this]() { return m_render_context->request_command_buffer(); },
          .queue = m_render_context->Get_command_queue()},
      m_render_context->Get_swap_chain()->Get_image_count());

  //   m_render_context->Add_Prepare_command_buffers({command_buffer});
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
  auto render_pass = m_render_context->Get_Render_Pass();
  m_pipeline = std::make_unique<Rendering::GraphicPipeline>(
      m_Device, m_model->getVertexInputBindingDescriptions(),
      m_model->getAttributeDescriptions(), render_pass,
      m_uniformManager->GetDescriptorLayout()->Get_handle(),
      m_Device->getMaxUsableSampleCount());
  auto shaders = std::vector<VkPipelineShaderStageCreateInfo>();

  for (const auto &i : shader_modules) {

    shaders.emplace_back(i->Make_Createinfo_in_pipeline());
  }
  //   std::transform(shader_modules.begin(), shader_modules.end(),
  //   shaders.end(),
  //                  [](auto &shader_ptr) {
  //                    return ;
  //                  });

  m_pipeline->Build_pipeline(shaders);
}

void App::Record(FrameWork::Wrapper::CommandBuffer::Ptr command_buffer) {
  VkRenderPassBeginInfo renderBeginInfo{};
  renderBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

  renderBeginInfo.renderPass =
      m_render_context->Get_Render_Pass()->Get_handle();
  renderBeginInfo.framebuffer =
      m_render_context->Get_active_frame()->Get_framebuffer()->Get_handle();
  renderBeginInfo.renderArea.offset = {0, 0};
  renderBeginInfo.renderArea.extent =
      m_render_context->Get_swap_chain()->Get_extent2D();
  std::vector<VkClearValue> clearColors{};
  VkClearValue finalClearColor{};
  finalClearColor.color = {0.0f, 0.0f, 0.0f, 1.0f};
  clearColors.push_back(finalClearColor);

  VkClearValue mutiClearColor{};
  mutiClearColor.color = {0.0f, 0.0f, 0.0f, 1.0f};
  clearColors.push_back(mutiClearColor);

  VkClearValue depthClearColor{};
  depthClearColor.depthStencil = {1.0f, 0};
  clearColors.push_back(depthClearColor);
  renderBeginInfo.clearValueCount = clearColors.size();
  renderBeginInfo.pClearValues = clearColors.data();
  command_buffer->Begin();
  command_buffer->BeginRenderPass(renderBeginInfo);
  command_buffer->BindGraphicPipeline(m_pipeline->Get_handle());
  //   auto sdfs = m_uniformManager->GetDescriptorSet(
  //       );
  command_buffer->BindDescriptorSet(
      m_pipeline->Get_Layout(),
      m_uniformManager
          ->GetDescriptorSet()[m_render_context->Get_active_frame_index()]);

  command_buffer->BindVertexBuffer(m_model->getVertexBuffers());
  command_buffer->BindIndexBuffer(m_model->getIndexBuffer()->Get_handle());
  // command_buffer->Draw(3);
  command_buffer->DrawIndex(m_model->getIndexCount());

  command_buffer->EndRenderPass();

  command_buffer->End();
}
void App::Rendering() {

  auto command_buffer = m_render_context->Begin();
  Record(command_buffer);

  m_render_context->Submit({command_buffer});
}
void App::MainLoop() {
  while (!m_Window->ShouldClose()) {
    m_Window->PollEvent();
    Rendering();
  }
}
} // namespace MoChengEngine