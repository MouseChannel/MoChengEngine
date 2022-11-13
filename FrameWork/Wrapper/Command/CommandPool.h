/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 11:53:44
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 13:22:58
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandPool.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"

namespace MoChengEngine::FrameWork::Wrapper {
class CommandPool : public WrapperBase<VkCommandPool, CommandPool> {
private:
  VkCommandPool m_handle;
  Device::Ptr m_device;

public:
  CommandPool(Device::Ptr device,VkQueueFlagBits bit,
              VkCommandPoolCreateFlagBits flag =
                  VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
  ~CommandPool();
  [[nodiscard]] VkCommandPool Get_handle() const { return m_handle; }
};

} // namespace MoChengEngine::FrameWork::Wrapper