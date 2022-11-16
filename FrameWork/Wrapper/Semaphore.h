/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-15 15:19:29
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-15 18:52:38
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Semaphore.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"
#include "vulkan/vulkan_core.h"
#include"Device.h"
namespace MoChengEngine::FrameWork::Wrapper {
class Semaphore : public WrapperBase<VkSemaphore, Semaphore> {
private:
  Device::Ptr m_device;

public:

  Semaphore(Device::Ptr &device);
  ~Semaphore();
  
};
} // namespace MoChengEngine::FrameWork::Wrapper