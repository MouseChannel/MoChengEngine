/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-14 21:37:36
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-17 18:34:52
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\FrameBuffer.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "Device.h"
#include "FrameWork/Base/baseHeader.h"

#include "FrameWork/Wrapper/WrapperBase.hpp"
#include "RenderPass.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Wrapper {
class FrameBuffer : public WrapperBase<VkFrameBuffer, FrameBuffer> {
private:
  //   VkFrameBuffer m_handle;
  Device::Ptr m_device;

public:
  FrameBuffer(Device::Ptr &device, VkExtent2D &extent,
              std::vector<VkImageView> &attachments,

              RenderPass::Ptr &renderPass);
  ~FrameBuffer();
};
} // namespace MoChengEngine::FrameWork::Wrapper