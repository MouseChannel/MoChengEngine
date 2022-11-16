/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 10:26:21
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-16 20:33:57
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Command\CommandQueue.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Component/ComponentBase.hpp"

#include "FrameWork/Wrapper/WrapperBase.hpp"
#include "vulkan/vulkan_core.h"
#include <stdint.h>
namespace MoChengEngine::FrameWork::Wrapper {

class CommandQueue : public WrapperBase<VkQueue, CommandQueue> {
private:
  //   VkQueue m_handle;
  uint32_t family_index;
  uint32_t queue_index;
  bool presentSupport;
  VkQueueFamilyProperties familyProperties;

public:
  CommandQueue(VkDevice device, uint32_t family_index, uint32_t queue_index,
               VkQueueFamilyProperties familyProperties, bool presentSupport);
  ~CommandQueue();
  bool PresentSupport() { return presentSupport; }
  VkResult Present(const VkPresentInfoKHR &present_info);
  [[nodiscard]] auto Get_family_propertie() { return familyProperties; }
  //   [[nodiscard]] VkQueue Get_handle() const { return m_handle; }
};

} // namespace MoChengEngine::FrameWork::Wrapper