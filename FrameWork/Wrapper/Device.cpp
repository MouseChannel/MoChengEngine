
/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 10:15:15
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-17 18:50:37
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Device.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "Device.h"
#include "FrameWork/Wrapper/Command/CommandPool.h"

#include "FrameWork/Wrapper/Command/CommandQueue.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Instance/Instance.h"
#include "FrameWork/Wrapper/PhysicalDevice.h"
#include "vulkan/vulkan_core.h"
#include <memory>
#include <stdexcept>

namespace MoChengEngine::FrameWork::Wrapper {

Device::Device(Instance::Ptr instance, PhysicalDevice::Ptr gpu,
               WindowSurface::Ptr surface)
    : m_instance{instance}, m_gpu(gpu), m_surface(surface) {

  //   std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

  //   // queueFamilies.insert(m_GraphicQueueFamily.value());
  //   // queueFamilies.insert(m_PresentQueueFamily.value() );

  //   float queuePriority = 1.0;

  //   for (int i = 0; i < m_gpu->Get_queueFamilies().size(); i++) {

  //     VkDeviceQueueCreateInfo queueCreateInfo = {};
  //     queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  //     queueCreateInfo.queueFamilyIndex = i;
  //     queueCreateInfo.queueCount = 1;
  //     queueCreateInfo.pQueuePriorities = &queuePriority;

  //     queueCreateInfos.push_back(queueCreateInfo);
  //   }
  auto command_queue_create_info = MakeCommandQueueCreateInfo();
  VkPhysicalDeviceFeatures deviceFeatures = {};
  deviceFeatures.samplerAnisotropy = VK_TRUE;

  VkDeviceCreateInfo deviceCreateInfo = {};
  deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  deviceCreateInfo.pQueueCreateInfos = command_queue_create_info.data();
  deviceCreateInfo.queueCreateInfoCount =
      static_cast<uint32_t>(command_queue_create_info.size());
  deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
  deviceCreateInfo.enabledExtensionCount =
      static_cast<uint32_t>(deviceRequiredExtensions.size());
  deviceCreateInfo.ppEnabledExtensionNames = deviceRequiredExtensions.data();

  //   // layer��
  //   if (mInstance->getEnableValidationLayer()) {
  deviceCreateInfo.enabledLayerCount =
      static_cast<uint32_t>(validationLayers.size());
  deviceCreateInfo.ppEnabledLayerNames = validationLayers.data();
  //   } else {
  //     deviceCreateInfo.enabledLayerCount = 0;
  //   }
  deviceCreateInfo.enabledLayerCount = 0;

  VK_CHECK_SUCCESS(vkCreateDevice(m_gpu->Get_handle(), &deviceCreateInfo,
                                  nullptr, &m_handle),
                   "Error:failed to create logical device");

  CreateAllocator();
  FillCommandQueues();
}
Device::~Device() { vkDestroyDevice(m_handle, nullptr); }
void Device::CreateAllocator() {
  VmaAllocatorCreateInfo createInfo;
  createInfo.physicalDevice = m_gpu->Get_handle();
  createInfo.device = m_handle;
  createInfo.instance = m_instance->Get_handle();

  vmaCreateAllocator(&createInfo, &allocator);
}
std::vector<VkDeviceQueueCreateInfo> Device::MakeCommandQueueCreateInfo() {
  auto queueFamilies = m_gpu->Get_queueFamilies();
  auto queue_family_properties_count = queueFamilies.size();
  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(
      queue_family_properties_count);
  std::vector<std::vector<float>> queue_priorities(
      queue_family_properties_count);
  for (int family_index = 0; family_index < queue_family_properties_count;
       family_index++) {
    auto &current_family = queueFamilies[family_index];
    auto current_queue_count = current_family.queueCount;
    queue_priorities[family_index].resize(current_queue_count, 1.0f);
    auto &queue_create_info = queueCreateInfos[family_index];
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = family_index;
    queue_create_info.queueCount = current_queue_count;
    queue_create_info.pQueuePriorities = queue_priorities[family_index].data();
  }
  return queueCreateInfos;
}

void Device::FillCommandQueues() {
  auto queueFamilies = m_gpu->Get_queueFamilies();

  command_queues.resize(queueFamilies.size());
  for (int family_index = 0; family_index < queueFamilies.size();
       family_index++) {
    auto current_family = queueFamilies[family_index];

    for (int queue_index = 0; queue_index < current_family.queueCount;
         queue_index++) {
      bool present_support =
          m_gpu->IsPresentSupport(family_index, m_surface->Get_handle());
      command_queues[family_index].emplace_back(
          CommandQueue::Create(m_handle, family_index, queue_index,
                               current_family, present_support));
    }
  }
}
CommandQueue::Ptr Device::Get_suitable_graphics_queue() {
  for (auto &queues : command_queues) {
    if (queues[0]->PresentSupport()) {
      return queues[0];
    }
  }
  throw std::runtime_error("Failed to get suitable_graphics_queue");
}
CommandQueue::Ptr Device::Get_queue_by_flag(VkQueueFlags required_queue_flags,
                                            uint32_t queue_index) {
  for (auto &queue : command_queues) {
    VkQueueFlags queue_flags = queue[0]->Get_family_propertie().queueFlags;
    uint32_t queue_count = queue[0]->Get_family_propertie().queueCount;
    if (((queue_flags & required_queue_flags) == required_queue_flags) &&
        queue_index < queue_count) {
      return queue[0];
    }
  }
  throw std::runtime_error("Failed to get queue");
}

} // namespace MoChengEngine::FrameWork::Wrapper