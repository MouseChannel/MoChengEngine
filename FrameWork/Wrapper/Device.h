/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 10:15:12
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 13:18:13
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Device.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"

#include "FrameWork/Wrapper/Instance/Instance.h"
#include "FrameWork/Wrapper/PhysicalDevice.h"
#include "FrameWork/Wrapper/WindowSurface.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"

#include <memory>
#include <set>

namespace MoChengEngine::FrameWork::Wrapper {
class CommandQueue;

class Device : public WrapperBase<VkDevice, Device> {
private:
  VkDevice m_handle;
  PhysicalDevice::Ptr m_gpu;
  Instance::Ptr m_instance;
  WindowSurface::Ptr m_surface;
  std::set<uint32_t> queueFamilies;

  const std::vector<const char *> deviceRequiredExtensions{
      VK_KHR_SWAPCHAIN_EXTENSION_NAME};

public:
  Device(PhysicalDevice::Ptr gpu, WindowSurface::Ptr surface);
  ~Device();
  [[nodiscard]] auto Get_Queue_Index_By_Flag(VkQueueFlagBits bit) {
    return m_gpu->GetSuitableFamilyQueueIndex_ByFlag(bit);
  }

  [[nodiscard]] VkDevice Get_handle() const { return m_handle; }
  [[nodiscard]] auto Get_gpu() const { return m_gpu; }
};
} // namespace MoChengEngine::FrameWork::Wrapper