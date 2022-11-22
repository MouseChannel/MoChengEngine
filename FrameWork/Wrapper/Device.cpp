
/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 10:15:15
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-22 20:45:17
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Device.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

// #include "FrameWork/Base/vmaExporter.cpp"
#define VMA_IMPLEMENTATION
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 0
// #include <vma/vk_mem_alloc.h>
#include "Device.h"
#include "FrameWork/Wrapper/Command/CommandPool.h"
// #include "vma/vk_mem_alloc.h"

#include "FrameWork/Wrapper/Command/CommandQueue.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Instance/Instance.h"
#include "FrameWork/Wrapper/PhysicalDevice.h"
#include "vulkan/vulkan_core.h"
#include <memory>
#include <stdexcept>

// #include "vma/vk_mem_alloc.h"
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
Device::~Device() {
     vkDestroyDevice(m_handle, nullptr); 
     }
void Device::CreateAllocator() {
//   VmaVulkanFunctions vma_vulkan_func ;
//   vma_vulkan_func.vkAllocateMemory = &vkAllocateMemory;
//   vma_vulkan_func.vkBindBufferMemory = &vkBindBufferMemory;
//   vma_vulkan_func.vkBindImageMemory = &vkBindImageMemory;
//   vma_vulkan_func.vkCreateBuffer = &vkCreateBuffer;
//   vma_vulkan_func.vkCreateImage = &vkCreateImage;
//   vma_vulkan_func.vkDestroyBuffer = &vkDestroyBuffer;
//   vma_vulkan_func.vkDestroyImage = &vkDestroyImage;
//   vma_vulkan_func.vkFlushMappedMemoryRanges = &vkFlushMappedMemoryRanges;
//   vma_vulkan_func.vkFreeMemory = &vkFreeMemory;
//   vma_vulkan_func.vkGetBufferMemoryRequirements =
//       &vkGetBufferMemoryRequirements;
//   vma_vulkan_func.vkGetImageMemoryRequirements = &vkGetImageMemoryRequirements;
//   vma_vulkan_func.vkGetPhysicalDeviceMemoryProperties =
//       &vkGetPhysicalDeviceMemoryProperties;
//   vma_vulkan_func.vkGetPhysicalDeviceProperties =
//       &vkGetPhysicalDeviceProperties;
//   vma_vulkan_func.vkInvalidateMappedMemoryRanges =
//       &vkInvalidateMappedMemoryRanges;
//   vma_vulkan_func.vkMapMemory = &vkMapMemory;
//   vma_vulkan_func.vkUnmapMemory = &vkUnmapMemory;
//   vma_vulkan_func.vkCmdCopyBuffer = &vkCmdCopyBuffer;

  VmaAllocatorCreateInfo createInfo;
  createInfo.vulkanApiVersion = VK_API_VERSION_1_3;
  createInfo.physicalDevice = m_gpu->Get_handle();
  createInfo.device = Get_handle();
  createInfo.instance = m_instance->Get_handle();
//   createInfo.pVulkanFunctions = &vma_vulkan_func;
  
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
    // queue_priorities[family_index].resize(current_queue_count, 1.0f);
    float queuePriority = 1.0;
    auto &queue_create_info = queueCreateInfos[family_index];
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = family_index;
    queue_create_info.queueCount = current_queue_count;
    queue_create_info.pQueuePriorities = &queuePriority;
    // queue_priorities[family_index].data();
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
VkSampleCountFlagBits Device::getMaxUsableSampleCount() {
  VkSampleCountFlagBits res;
  getMaxUsableSampleCount(res);
  return res;
}
void Device::getMaxUsableSampleCount(VkSampleCountFlagBits &res) {
  VkPhysicalDeviceProperties props{};
  vkGetPhysicalDeviceProperties(m_gpu->Get_handle(), &props);

  VkSampleCountFlags counts =
      std::min(props.limits.framebufferColorSampleCounts,
               props.limits.framebufferDepthSampleCounts);

  if (counts & VK_SAMPLE_COUNT_64_BIT) {
    res = VK_SAMPLE_COUNT_64_BIT;
  } else if (counts & VK_SAMPLE_COUNT_32_BIT) {
    res = VK_SAMPLE_COUNT_32_BIT;
  } else if (counts & VK_SAMPLE_COUNT_16_BIT) {
    res = VK_SAMPLE_COUNT_16_BIT;
  } else if (counts & VK_SAMPLE_COUNT_8_BIT) {
    res = VK_SAMPLE_COUNT_8_BIT;
  } else if (counts & VK_SAMPLE_COUNT_4_BIT) {
    res = VK_SAMPLE_COUNT_4_BIT;
  } else if (counts & VK_SAMPLE_COUNT_2_BIT) {
    res = VK_SAMPLE_COUNT_2_BIT;
  } else if (counts & VK_SAMPLE_COUNT_1_BIT) {
    res = VK_SAMPLE_COUNT_1_BIT;
  }
}
VkFormat Device::findSupportedFormat(const std::vector<VkFormat> &candidates,
                                     VkImageTiling tiling,
                                     VkFormatFeatureFlags features) {
  for (auto format : candidates) {
    VkFormatProperties props;

    vkGetPhysicalDeviceFormatProperties(m_gpu->Get_handle(), format, &props);

    if (tiling == VK_IMAGE_TILING_LINEAR &&
        (props.linearTilingFeatures & features) == features) {
      return format;
    }

    if (tiling == VK_IMAGE_TILING_OPTIMAL &&
        (props.optimalTilingFeatures & features) == features) {
      return format;
    }
  }

  throw std::runtime_error("Error: can not find proper format");
}
} // namespace MoChengEngine::FrameWork::Wrapper