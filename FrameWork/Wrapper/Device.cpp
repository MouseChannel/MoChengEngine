
/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 10:15:15
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 13:07:08
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Device.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "Device.h"
#include "FrameWork/Wrapper/Command/CommandPool.h"

#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Instance/Instance.h"
#include "FrameWork/Wrapper/PhysicalDevice.h"
#include "vulkan/vulkan_core.h"
#include <memory>

namespace MoChengEngine::FrameWork::Wrapper {

Device::Device(PhysicalDevice::Ptr gpu, WindowSurface::Ptr surface)
    : m_gpu(gpu), m_surface(surface) {

 

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;

  // queueFamilies.insert(m_GraphicQueueFamily.value());
  // queueFamilies.insert(m_PresentQueueFamily.value() );

  float queuePriority = 1.0;

  for (int i = 0; i < m_gpu->Get_queueFamilies().size(); i++) {

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = i;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    queueCreateInfos.push_back(queueCreateInfo);
  }

  VkPhysicalDeviceFeatures deviceFeatures = {};
  deviceFeatures.samplerAnisotropy = VK_TRUE;

  VkDeviceCreateInfo deviceCreateInfo = {};
  deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
  deviceCreateInfo.queueCreateInfoCount =
      static_cast<uint32_t>(queueCreateInfos.size());
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
}
Device::~Device() { vkDestroyDevice(m_handle, nullptr); }

 

} // namespace MoChengEngine::FrameWork::Wrapper