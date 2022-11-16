/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 10:26:37
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-16 21:18:56
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandQueue.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "CommandQueue.h"
#include "FrameWork/Wrapper/Command/CommandQueue.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Wrapper {

CommandQueue::CommandQueue(VkDevice device, uint32_t family_index,
                           uint32_t queue_index,
                           VkQueueFamilyProperties familyProperties,
                           bool presentSupport)
    : family_index(family_index), queue_index{queue_index},
      familyProperties{familyProperties}, presentSupport{presentSupport} {
  vkGetDeviceQueue(device, family_index, queue_index, &m_handle);
}
CommandQueue::~CommandQueue() {}
VkResult CommandQueue::Present(const VkPresentInfoKHR &present_info) {
  return vkQueuePresentKHR(m_handle, &present_info);
}
} // namespace MoChengEngine::FrameWork::Wrapper