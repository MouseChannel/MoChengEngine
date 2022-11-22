/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 10:15:12
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-22 12:07:22
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Device.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
 #include <vma/vk_mem_alloc.h>
#include "FrameWork/Base/baseHeader.h"

#include "FrameWork/Wrapper/Base/WrapperBase.hpp"
#include "FrameWork/Wrapper/Command/CommandQueue.h"
#include "FrameWork/Wrapper/Instance/Instance.h"
#include "FrameWork/Wrapper/PhysicalDevice.h"
#include "FrameWork/Wrapper/WindowSurface.h"

#include <memory>
#include <set>

namespace MoChengEngine::FrameWork::Wrapper {

class Device : public WrapperBase<VkDevice, Device> {
private:
  //   VkDevice m_handle;
  VmaAllocator allocator;

  PhysicalDevice::Ptr m_gpu;
  Instance::Ptr m_instance;
  WindowSurface::Ptr m_surface;
  std::set<uint32_t> queueFamilies;
  std::vector<std::vector<CommandQueue::Ptr>> command_queues;

  const std::vector<const char *> deviceRequiredExtensions{
      VK_KHR_SWAPCHAIN_EXTENSION_NAME};
  void FillCommandQueues();
  void CreateAllocator();
  std::vector<VkDeviceQueueCreateInfo> MakeCommandQueueCreateInfo();

public:
  Device(Instance::Ptr instance, PhysicalDevice::Ptr gpu,
         WindowSurface::Ptr surface);
  ~Device();
  CommandQueue::Ptr Get_suitable_graphics_queue();
  CommandQueue::Ptr Get_queue_by_flag(VkQueueFlags required_queue_flags,
                                      uint32_t queue_index);
  void getMaxUsableSampleCount(VkSampleCountFlagBits &res);
  VkSampleCountFlagBits getMaxUsableSampleCount();
  VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates,
                               VkImageTiling tiling,
                               VkFormatFeatureFlags features);
  [[nodiscard]] auto Get_queue_family_index_by_flag(VkQueueFlags bit) {
    return m_gpu->FindQueueFamilyIndex(bit);
  }

  //   [[nodiscard]] VkDevice Get_handle() const { return m_handle; }
  [[nodiscard]] auto &Get_gpu() const { return m_gpu; }
  [[nodiscard]] auto &Get_allocator() { return allocator; }
};
} // namespace MoChengEngine::FrameWork::Wrapper