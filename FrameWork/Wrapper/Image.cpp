#include "Image.h"
#include "vulkan/vulkan_core.h"
namespace MoChengEngine::FrameWork::Wrapper {
Image::Image(const Device::Ptr  device, const int &width, const int &height,
             const VkFormat &format, const VkImageType &imageType,
             const VkImageTiling &tiling, const VkImageUsageFlags &usage,
             const VkSampleCountFlagBits &sample,
             const VkMemoryPropertyFlags &properties,
             const VkImageAspectFlags &aspectFlags)
    : m_device{device} {
  VkImageCreateInfo createInfo;
  VK_CHECK_SUCCESS(
      vkCreateImage(device->Get_handle(), &createInfo, nullptr, &m_handle),
      "Create image failed");
}
Image::~Image() { vkDestroyImage(m_device->Get_handle(), m_handle, nullptr); }
} // namespace MoChengEngine::FrameWork::Wrapper