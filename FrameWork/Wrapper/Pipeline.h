/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-19 11:36:26
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-19 16:33:59
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Pipeline.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Base/Component.hpp"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/RenderPass.h"

namespace MoChengEngine::FrameWork::Wrapper {
class Pipeline : public Component<VkPipeline, Pipeline> {
private:
  VkPipelineLayout m_layout;
  VkPipelineCache m_cache;

  std::vector<VkViewport> m_Viewports{};
  std::vector<VkRect2D> m_Scissors{};

public:
  Pipeline(Device::Ptr &device);
  ~Pipeline();
  void Set_Viewports_and_Scissors(const std::vector<VkViewport> &viewports,
                                  const std::vector<VkRect2D> &scissors) {
    m_Viewports = viewports;
    m_Scissors = scissors;
  }
  void Set_pipeline_state(
      std::vector<VkVertexInputBindingDescription> &vertexbindindDes,
      std::vector<VkVertexInputAttributeDescription> &attributeDes,
      VkDescriptorSetLayout &layout);
  void
  Build_pipeline(RenderPass::Ptr renderpass,
                 std::vector<VkPipelineShaderStageCreateInfo> &shaders_stage);

private:
  VkPipelineVertexInputStateCreateInfo m_VertexInputInfo{};

  void Make_VertexInput_Info(
      std::vector<VkVertexInputBindingDescription> &vertexbindindDes,
      std::vector<VkVertexInputAttributeDescription> &attributeDes);

  VkPipelineInputAssemblyStateCreateInfo m_InputAssembly{};
  void Make_AssemblyInput_Info();

  VkPipelineViewportStateCreateInfo m_Viewport{};
  void Make_ViewPort_Info();
  VkPipelineRasterizationStateCreateInfo m_Rasterizer{};
  void Make_Raster_Info();
  VkPipelineMultisampleStateCreateInfo m_Multisampling{};
  void Make_MultiSample_Info();
  std::vector<VkPipelineColorBlendAttachmentState> m_BlendAttachments{};
  void Make_BlendAttachment_Info();
  VkPipelineColorBlendStateCreateInfo m_BlendState{};
  void Make_BlendState_Info();
  VkPipelineDepthStencilStateCreateInfo m_DepthStencilState{};
  void Make_DepthStecil_Info();
  VkPipelineLayoutCreateInfo m_LayoutState{};
  void Make_LayoutCreate_Info(VkDescriptorSetLayout &layout);
};
} // namespace MoChengEngine::FrameWork::Wrapper