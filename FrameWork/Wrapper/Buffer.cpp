/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-14 11:30:30
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-11 10:00:01
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Buffer.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "Buffer.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Wrapper {
Buffer::Buffer(Device::Ptr device, VkDeviceSize size,
               VkBufferUsageFlags buffer_usage, VmaMemoryUsage memory_usage,
               VkMemoryPropertyFlags properties, VmaAllocationCreateFlags flags,
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

#ifdef Using_VMA
  VK_CHECK_SUCCESS(vmaCreateBuffer(device->Get_allocator(), &createInfo,
                                   &memory_info, &m_handle, &allocation,
                                   &allocation_info),
                   "fail to create buffer");

  if (persistent) {
    mapped_data = static_cast<uint8_t *>(allocation_info.pMappedData);
  }

#else
  VK_CHECK_SUCCESS(
      vkCreateBuffer(device->Get_handle(), &createInfo, nullptr, &m_handle),
      "Create buffer failed");
  VkMemoryRequirements memReq{};
  vkGetBufferMemoryRequirements(m_device->Get_handle(), m_handle, &memReq);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memReq.size;
  // memoryTypeBits里存放了所有可用的memoryType
  allocInfo.memoryTypeIndex = FindMemoryType(memReq.memoryTypeBits, properties);

  VK_CHECK_SUCCESS(vkAllocateMemory(m_device->Get_handle(), &allocInfo, nullptr,
                                    &mBufferMemory),
                   "Allocate Buffer failed");
  VK_CHECK_SUCCESS(
      vkBindBufferMemory(m_device->Get_handle(), m_handle, mBufferMemory, 0),
      "BindBuffer failed");
  m_BufferInfo.buffer = m_handle;
  m_BufferInfo.offset = 0;
  m_BufferInfo.range = size;
#endif
}
Buffer::~Buffer() {

#ifdef Using_VMA
  vmaDestroyBuffer(m_device->Get_allocator(), m_handle, allocation);
#else
  vkDestroyBuffer(m_device->Get_handle(), m_handle, nullptr);
  if (mBufferMemory != VK_NULL_HANDLE) {
    vkFreeMemory(m_device->Get_handle(), mBufferMemory, nullptr);
  }
#endif
}

uint32_t Buffer::FindMemoryType(uint32_t typeFilter,
                                VkMemoryPropertyFlags properties) {
  VkPhysicalDeviceMemoryProperties memProps;
  vkGetPhysicalDeviceMemoryProperties(m_device->Get_gpu()->Get_handle(),
                                      &memProps);

  for (uint32_t i = 0; i < memProps.memoryTypeCount; ++i) {
    // 该type可用&&该type符合要求
    if ((typeFilter & (1 << i)) &&
        ((memProps.memoryTypes[i].propertyFlags & properties) == properties)) {
      return i;
    }
  }

  throw std::runtime_error("Error: cannot find the property memory type!");
}

void Buffer::Map(size_t size, size_t offset) {
#ifdef Using_VMA
  if (!mapped && !mapped_data) {
    VK_CHECK_SUCCESS(vmaMapMemory(m_device->Get_allocator(), allocation,
                                  reinterpret_cast<void **>(&mapped_data)),
                     "map data failed");
  }
  return mapped_data;
#else

  vkMapMemory(m_device->Get_handle(), mBufferMemory, offset, size, 0,
              &mapped_data);
#endif
}

void Buffer::UnMap() {
#ifdef Using_VMA

  if (mapped) {
    vmaUnmapMemory(m_device->Get_allocator(), allocation);
    mapped_data = nullptr;
    mapped = false;
  }
#else
  vkUnmapMemory(m_device->Get_handle(), mBufferMemory);
#endif
}

void Buffer::Flush() {
  vmaFlushAllocation(m_device->Get_allocator(), allocation, 0,
                     allocation_info.size);
}
void Buffer::Update(void *d, size_t size, size_t offset) {
  if (d == nullptr)
    return;
  auto data = reinterpret_cast<const uint8_t *>(d);
#ifdef Using_VMA

  if (persistent) {
    std::copy(data, data + size, mapped_data + offset);
    Flush();
  } else {
    Map();
    std::copy(data, data + size, mapped_data + offset);
    Flush();
    UnMap();
  }
#else
  Map(size, offset);
  memcpy(mapped_data, data, size);
  // std::copy(data, data + size,  mapped_data + offset);
  UnMap();

#endif
}

Buffer::Ptr Buffer::Create_Image_buffer(Device::Ptr device, size_t size) {
  return Buffer::CreateR(device, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                         VMA_MEMORY_USAGE_CPU_TO_GPU,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                             VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
}
} // namespace MoChengEngine::FrameWork::Wrapper