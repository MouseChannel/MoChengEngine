/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-14 11:30:26
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-19 14:18:04
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Buffer.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Base/Resource.hpp"

#include "Device.h"
namespace MoChengEngine::FrameWork::Wrapper {
class Buffer : public Resource<VkBuffer, Buffer> {
private:
 
  bool persistent;
  uint8_t *mapped_data;
  VmaAllocationInfo allocation_info;
  bool mapped = false;

public:
  Buffer(Device::Ptr device, VkDeviceSize size, VkBufferUsageFlags buffer_usage,
         VmaMemoryUsage memory_usage, VmaAllocationCreateFlags flags,
         VkMemoryPropertyFlags properties,
         const std::vector<uint32_t> &queue_family_indices =
             std::vector<uint32_t>());
  ~Buffer();
  uint8_t *Map();
  void UnMap();
  void Update(void *data, size_t size, size_t offset = 0);
  void Flush();
 
};
} // namespace MoChengEngine::FrameWork::Wrapper