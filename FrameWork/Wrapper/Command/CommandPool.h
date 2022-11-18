/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 11:53:44
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-18 14:25:16
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandPool.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
 #pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"

namespace MoChengEngine::FrameWork::Wrapper {
class CommandPool : public WrapperBase<VkCommandPool, CommandPool> {
private:
//   VkCommandPool m_handle;
  Device::Ptr m_device;
  int queue_family_index;

public:
  CommandPool(Device::Ptr &device,VkQueueFlags& queue_flag,
              VkCommandPoolCreateFlagBits flag =
                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
  ~CommandPool();
  [[nodiscard]] auto Get_queue_family_index(){return queue_family_index;}
//   [[nodiscard]] VkCommandPool Get_handle() const { return m_handle; }
};

} // namespace MoChengEngine::FrameWork::Wrapper