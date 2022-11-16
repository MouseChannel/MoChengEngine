/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-15 15:24:53
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-15 15:28:59
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Fence.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"
#include "vulkan/vulkan_core.h" 
#include "Device.h"
#include <stdint.h>
namespace MoChengEngine::FrameWork::Wrapper {
class Fence : public WrapperBase<VkFence, Fence> {
private:
  Device::Ptr m_device;

public:
void Reset();
void Wait(uint64_t timeout= UINT64_MAX);
  Fence(Device::Ptr &device);
  ~Fence();
};
} // namespace MoChengEngine::FrameWork::Wrapper