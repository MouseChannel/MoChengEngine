/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-29 19:22:31
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-30 21:45:27
 * @FilePath: \MoChengEngine\FrameWork\Core\UniformManager\UniformManager.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "description.h"
#include "FrameWork/Wrapper/Command/CommandBuffer.h"
#include "FrameWork/Wrapper/DescriptorSetLayout.h"
#include "FrameWork/Wrapper/descriptorPool.h"
#include "FrameWork/Wrapper/descriptorSet.h"

namespace MoChengEngine::FrameWork {

class UniformManager {

private:
  std::vector<Wrapper::UniformParameter::Ptr> m_UniformParams;

  Wrapper::DescriptorSetLayout::Ptr m_DescriptorSetLayout{nullptr};
  Wrapper::DescriptorPool::Ptr m_DescriptorPool{nullptr};
  Wrapper::DescriptorSet::Ptr m_DescriptorSet;
  Wrapper::Device::Ptr m_Device{nullptr};

public:
  UniformManager() = default;
  ~UniformManager() = default;
  void Prepare(const Wrapper::Device::Ptr device,
               const Wrapper::CommandBuffer::Ptr command_buffer,
               int frame_count);
  [[nodiscard]] auto &GetDescriptorLayout() const {
    return m_DescriptorSetLayout;
  }

  [[nodiscard]] auto GetDescriptorSet(int frameCount) const {
    return m_DescriptorSet->Get_handle()[frameCount];
  }
};
struct VPMatrices {
  glm::mat4 mViewMatrix;
  glm::mat4 mProjectionMatrix;

  VPMatrices() {
    mViewMatrix = glm::mat4(1.0f);
    mProjectionMatrix = glm::mat4(1.0f);
  }
};

struct ObjectUniform {
  glm::mat4 mModelMatrix;

  ObjectUniform() { mModelMatrix = glm::mat4(1.0f); }
};
} // namespace MoChengEngine::FrameWork