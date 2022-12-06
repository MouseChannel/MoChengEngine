/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-29 19:22:34
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-30 21:47:07
 * @FilePath: \MoChengEngine\FrameWork\Core\UniformManager\UniformManager.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "UniformManager.h"
namespace MoChengEngine::FrameWork {
void UniformManager::Prepare(const Wrapper::Device::Ptr device,
                          const Wrapper::CommandBuffer::Ptr command_buffer,
                          int frame_count) {
  m_Device = device;
  auto vpParam = Wrapper::UniformParameter::create();
  vpParam->mBinding = 0;
  vpParam->mCount = 1;
  vpParam->mDescriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  vpParam->mSize = sizeof(VPMatrices);
  vpParam->mStage = VK_SHADER_STAGE_VERTEX_BIT;

  for (int i = 0; i < frame_count; ++i) {

    auto buffer = Wrapper::Buffer::CreateR(
        device, vpParam->mSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VMA_MEMORY_USAGE_GPU_ONLY, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    vpParam->m_Buffers.push_back(buffer);
  }

  m_UniformParams.push_back(vpParam);

  auto objectParam = Wrapper::UniformParameter::create();
  objectParam->mBinding = 1;
  objectParam->mCount = 1;
  objectParam->mDescriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  objectParam->mSize = sizeof(ObjectUniform);
  objectParam->mStage = VK_SHADER_STAGE_VERTEX_BIT;

  for (int i = 0; i < frame_count; ++i) {
    auto buffer = Wrapper::Buffer::CreateR(
        device, objectParam->mSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VMA_MEMORY_USAGE_GPU_ONLY, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    objectParam->m_Buffers.push_back(buffer);
  }

  m_UniformParams.push_back(objectParam);

  auto textureParam = Wrapper::UniformParameter::create();
  textureParam->mBinding = 2;
  textureParam->mCount = 1;
  textureParam->mDescriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  textureParam->mStage = VK_SHADER_STAGE_FRAGMENT_BIT;
  textureParam->mTexture = std::make_unique<Texture>(
      m_Device, command_buffer, "D:\\cpp\\vk\\assets\\jqm.png");

  m_UniformParams.push_back(textureParam);

  m_DescriptorSetLayout = Wrapper::DescriptorSetLayout::Create(device);
  m_DescriptorSetLayout->Build(m_UniformParams);

  m_DescriptorPool =
      Wrapper::DescriptorPool::Create(m_Device, m_UniformParams, frame_count);
  

  m_DescriptorSet = Wrapper::DescriptorSet::Create(
      device, m_UniformParams, m_DescriptorSetLayout, m_DescriptorPool,
      frame_count);
}

} // namespace MoChengEngine::FrameWork