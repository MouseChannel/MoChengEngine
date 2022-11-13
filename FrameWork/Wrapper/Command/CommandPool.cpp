/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 11:53:44
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 11:25:24
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandPool.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "CommandPool.h"
#include "FrameWork/Wrapper/Device.h"
#include "vulkan/vulkan_core.h"
namespace MoChengEngine::FrameWork::Wrapper {

CommandPool::CommandPool(Device::Ptr device, VkQueueFlagBits bit,
                         VkCommandPoolCreateFlagBits flag)
    : m_device{device} {
  auto queue_family_index = device->Get_Queue_Index_By_Flag(bit);
  VkCommandPoolCreateInfo createInfo;
  createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  createInfo.queueFamilyIndex = queue_family_index;

  createInfo.flags = flag;
  VK_CHECK_SUCCESS(vkCreateCommandPool(m_device->Get_handle(), &createInfo,
                                       nullptr, &m_handle),
                   "create commandPool failed");
}

CommandPool::~CommandPool() {

  vkDestroyCommandPool(m_device->Get_handle(), m_handle, nullptr);
}

} // namespace MoChengEngine::FrameWork::Wrapper