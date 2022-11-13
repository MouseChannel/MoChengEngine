/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 10:26:37
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 11:24:26
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandQueue.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "CommandQueue.h"

namespace MoChengEngine::FrameWork::Wrapper {
CommandQueue::CommandQueue(Device::Ptr device, uint32_t familyValue) {
  vkGetDeviceQueue(device->Get_handle(), familyValue, 0, &m_handle);
}
CommandQueue::~CommandQueue() {}
} // namespace MoChengEngine::FrameWork::Wrapper