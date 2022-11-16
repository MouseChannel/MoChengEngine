#include "Image.h"
#include "vulkan/vulkan_core.h"

#include <assert.h>
#include <stdint.h>
namespace MoChengEngine::FrameWork::Wrapper {
Image::Image(const Device::Ptr device, const VkExtent3D &extent,
             const VkFormat &format, const VkImageType &imageType,
             const VkImageTiling &tiling, const VkImageUsageFlags &image_usage,
             const VkSampleCountFlagBits &sample,
             const VkMemoryPropertyFlags &properties,
             const VkImageAspectFlags &aspectFlags,
             const VmaMemoryUsage &memory_usage)
    : Resource<VkImage, Image>{device}, m_extent{extent}, m_imageType{
                                                              imageType} {
  VkImageCreateInfo imageCreateInfo;
  imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageCreateInfo.extent = extent;

  imageCreateInfo.format = format; // rgb rgba
  imageCreateInfo.imageType = imageType;
  imageCreateInfo.tiling = tiling;
  imageCreateInfo.usage = image_usage; // color or depth?
  imageCreateInfo.samples = sample;
  imageCreateInfo.mipLevels = 1;
  imageCreateInfo.arrayLayers = 1;
  imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  // create image in vma

  VmaAllocationCreateInfo memory_info{};
  memory_info.usage = memory_usage;

  if (image_usage & VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT) {
    memory_info.preferredFlags = VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT;
  }
  VK_CHECK_SUCCESS(vmaCreateImage(m_device->Get_allocator(), &imageCreateInfo,
                                  &memory_info, &m_handle, &allocation,
                                  nullptr),
                   "Create image failed");
  CreateView(Make_View_Info(aspectFlags), m_device);
}
Image::Image(const Device::Ptr &device, VkImage image_handle,
             const VkExtent3D &extent, VkFormat format,
             const VkImageUsageFlags &usage, VkSampleCountFlagBits sample_count)
    : Resource<VkImage, Image>{device}, m_extent{extent}, m_format(format) {
  m_handle = image_handle;
  CreateView(Make_View_Info(VK_IMAGE_ASPECT_COLOR_BIT), m_device);
}
Image::~Image() {
  if (m_view != VK_NULL_HANDLE) {
    vkDestroyImageView(m_device->Get_handle(), m_view, nullptr);
  }
  vmaDestroyImage(m_device->Get_allocator(), m_handle, allocation);
}
/*
void Image::Bind_Image_Memory(const VkMemoryPropertyFlags properties) {
  VkMemoryRequirements memReq{};
  vkGetImageMemoryRequirements(m_device->Get_handle(), m_handle, &memReq);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memReq.size;

  allocInfo.memoryTypeIndex =
      m_device->Get_gpu()->FindMemoryType(memReq.memoryTypeBits, properties);
  VK_CHECK_SUCCESS(vkAllocateMemory(m_device->Get_handle(), &allocInfo,
  nullptr,
                                    &m_ImageMemory),
                   "Error: failed to allocate memory");

  vkBindImageMemory(m_device->Get_handle(), m_handle, m_ImageMemory, 0);
}
*/
VkImageViewCreateInfo
Image::Make_View_Info(const VkImageAspectFlags aspectFlags) {
  VkImageViewCreateInfo imageViewCreateInfo{};
  imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  imageViewCreateInfo.viewType = m_imageType == VK_IMAGE_TYPE_2D
                                     ? VK_IMAGE_VIEW_TYPE_2D
                                     : VK_IMAGE_VIEW_TYPE_3D;
  imageViewCreateInfo.format = m_format;
  imageViewCreateInfo.image = m_handle;
  imageViewCreateInfo.subresourceRange.aspectMask = aspectFlags;
  imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
  imageViewCreateInfo.subresourceRange.levelCount = 1;
  imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
  imageViewCreateInfo.subresourceRange.layerCount = 1;
  return imageViewCreateInfo;
}

// 填充该image内容
void Image::FillImageData(size_t size, void *pData,
                          CommandBuffer::Ptr commandBuffer) {
  assert(pData);
  assert(size);
  VkBufferImageCopy a;
  //   auto stageBuffer = Buffer::CreateStageBuffer(m_Device, size, pData);

  //   auto commandBuffer = CommandBuffer::Create(m_Device, commandPool);
  //   commandBuffer->Begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
  //   commandBuffer->CopyBufferToImage(stageBuffer->getBuffer(), m_handle,
  //   m_layout,
  //                                    m_Width, m_Height);
  //   commandBuffer->End();

  //   commandBuffer->SubmitSync(m_Device->GetGraphicQueue());
}
// 使用barrier修改image格式
void Image::SetImageLayout(VkImageLayout newLayout,
                           VkPipelineStageFlags srcStageMask,
                           VkPipelineStageFlags dstStageMask,
                           VkImageSubresourceRange subresrouceRange,
                           CommandBuffer::Ptr commandBuffer) {}
VkImageView CreateView(VkImageViewCreateInfo viewInfo, Device::Ptr device) {
  VkImageView res;
  VK_CHECK_SUCCESS(
      vkCreateImageView(device->Get_handle(), &viewInfo, nullptr, &res),
      "Error: failed to create image view");
  return res;
}

} // namespace MoChengEngine::FrameWork::Wrapper