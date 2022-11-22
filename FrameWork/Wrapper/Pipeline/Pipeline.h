/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-19 11:36:26
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-22 10:53:19
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Pipeline\Pipeline.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Base/Component.hpp"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Pipeline/Pipeline_state.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include <memory>

namespace MoChengEngine::FrameWork::Wrapper {
class Pipeline : public Component<VkPipeline, Pipeline> {

protected:
  std::unique_ptr<PipelineState> pipeline_state;
VkPipelineLayout m_layout;
  VkPipelineCache m_cache;
public:
  Pipeline(Device::Ptr device);
  ~Pipeline();
  void Set_Viewports_and_Scissors(const std::vector<VkViewport> &viewports,
                                  const std::vector<VkRect2D> &scissors) {
    pipeline_state->Set_Viewports_and_Scissors(viewports, scissors);
  }
   
  virtual void
  Build_pipeline( 
                 std::vector<VkPipelineShaderStageCreateInfo> &shaders_stage) = 0;
};
} // namespace MoChengEngine::FrameWork::Wrapper