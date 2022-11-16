/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-14 11:30:30
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-14 15:12:41
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Buffer.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "Buffer.h"

namespace MoChengEngine::FrameWork::Wrapper {
Buffer::Buffer(Device::Ptr device, VkDeviceSize size,
               VkBufferUsageFlags buffer_usage, VmaMemoryUsage memory_usage,
               VmaAllocationCreateFlags flags, VkMemoryPropertyFlags properties,
               const std::vector<uint32_t> &queue_family_indices)
    : Resource<VkBuffer, Buffer>{device} {

  VkBufferCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  createInfo.size = size;
  createInfo.usage = buffer_usage;
  createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  persistent = (flags & VMA_ALLOCATION_CREATE_MAPPED_BIT) != 0;

  if (queue_family_indices.size() >= 2) {
    createInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount =
        static_cast<uint32_t>(queue_family_indices.size());
    createInfo.pQueueFamilyIndices = queue_family_indices.data();
  }

  VmaAllocationCreateInfo memory_info{};
  memory_info.flags = flags;
  memory_info.usage = memory_usage;

  //   auto result =
  VK_CHECK_SUCCESS(vmaCreateBuffer(device->Get_allocator(), &createInfo,
                                   &memory_info, &m_handle, &allocation,
                                   &allocation_info),
                   "fail to create buffer");

  if (persistent) {
    mapped_data = static_cast<uint8_t *>(allocation_info.pMappedData);
  }
}
Buffer::~Buffer() {
  vmaDestroyBuffer(m_device->Get_allocator(), m_handle, allocation);
}

uint8_t *Buffer::Map() {
  if (!mapped && !mapped_data) {
    VK_CHECK_SUCCESS(vmaMapMemory(m_device->Get_allocator(), allocation,
                                  reinterpret_cast<void **>(&mapped_data)),
                     "map data failed");
  }
  return mapped_data;
}

void Buffer::UnMap() {
  if (mapped) {
    vmaUnmapMemory(m_device->Get_allocator(), allocation);
    mapped_data = nullptr;
    mapped = false;
  }
}

void Buffer::Flush() {
  vmaFlushAllocation(m_device->Get_allocator(), allocation, 0,
                     allocation_info.size);
}
void Buffer::Update(void *d, size_t size, size_t offset) {
  auto data = reinterpret_cast<const uint8_t *>(d);
  if (persistent) {
    std::copy(data, data + size, mapped_data + offset);
    Flush();
  } else {
    Map();
    std::copy(data, data + size, mapped_data + offset);
    Flush();
    UnMap();
  }
}
} // namespace MoChengEngine::FrameWork::Wrapper