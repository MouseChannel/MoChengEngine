/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 10:26:21
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 12:25:47
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandQueue.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Component/ComponentBase.hpp"

#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"
namespace MoChengEngine::FrameWork::Wrapper {

class CommandQueue : public WrapperBase<VkQueue,CommandQueue> {
private:
  VkQueue m_handle;
  uint32_t queueFamilyIndex;

public:
  CommandQueue(Device::Ptr  device, uint32_t familyValue);
  ~CommandQueue();

  bool operator==(const CommandQueue &other) const {
    return other.queueFamilyIndex == queueFamilyIndex;
  }
  [[nodiscard]] VkQueue Get_handle() const { return m_handle; }
};

} // namespace MoChengEngine::FrameWork::Wrapper