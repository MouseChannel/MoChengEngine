#include "SwapChain.h"
namespace MoChengEngine::FrameWork::Wrapper {
SwapChain::SwapChain(Device::Ptr device, WindowSurface::Ptr surface)
    : m_device{device}, m_surface{surface} {
  auto swapChainInfo = QuerySwapChainSupportInfo();
  auto surfaceFormat = ChooseSurfaceFormat(swapChainInfo.m_Formats);
  auto presentMode = ChooseSurfacePresentMode(swapChainInfo.m_PresentModes);
  auto extent = ChooseExtent(swapChainInfo.m_Capabilities);
  // 设置交换链中图片个数
  imageCount = swapChainInfo.m_Capabilities.minImageCount + 1;
  if (swapChainInfo.m_Capabilities.maxImageCount > 0 &&
      imageCount > swapChainInfo.m_Capabilities.maxImageCount) {
    imageCount = swapChainInfo.m_Capabilities.maxImageCount;
  }

  VkSwapchainCreateInfoKHR createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface = m_surface->Get_handle();
  createInfo.minImageCount = imageCount;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = extent;

  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  createInfo.queueFamilyIndexCount = 0;
  createInfo.pQueueFamilyIndices = nullptr;

  // createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
  // createInfo.queueFamilyIndexCount =
  //     static_cast<uint32_t>(queueFamilies.size());
  // createInfo.pQueueFamilyIndices = queueFamilies.data();

  // 位置不做 任何变换操作
  createInfo.preTransform = swapChainInfo.m_Capabilities.currentTransform;
  // 忽略alpha通道
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  //
  createInfo.presentMode = presentMode;
  // VK_TRUE表示我们不关心被窗口系统中的其它窗口遮挡的像素的颜色
  createInfo.clipped = VK_TRUE;
  // 此次还没有任何老交换链，置空即可
  createInfo.oldSwapchain = VK_NULL_HANDLE;
  if (vkCreateSwapchainKHR(m_device->Get_handle(), &createInfo, nullptr,
                           &m_handle) != VK_SUCCESS) {
    throw std::runtime_error("Error: failed to create swapChain");
  }
}
SwapChain::~SwapChain() {}

SwapChainSupportInfo SwapChain::QuerySwapChainSupportInfo() {
  SwapChainSupportInfo info{};
  // 获取基础特性
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_device->Get_gpu()->Get_handle(),
                                            m_surface->Get_handle(),
                                            &info.m_Capabilities);

  uint32_t formatCount = 0;
  // 获取表面支持格式
  vkGetPhysicalDeviceSurfaceFormatsKHR(m_device->Get_gpu()->Get_handle(),
                                       m_surface->Get_handle(), &formatCount,
                                       nullptr);

  if (formatCount != 0) {
    info.m_Formats.resize(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(m_device->Get_gpu()->Get_handle(),
                                         m_surface->Get_handle(), &formatCount,
                                         info.m_Formats.data());
  }

  uint32_t presentModeCount = 0;
  // 获取呈现模式
  vkGetPhysicalDeviceSurfacePresentModesKHR(m_device->Get_gpu()->Get_handle(),
                                            m_surface->Get_handle(),
                                            &presentModeCount, nullptr);

  if (presentModeCount != 0) {
    info.m_PresentModes.resize(presentModeCount);
    vkGetPhysicalDeviceSurfacePresentModesKHR(
        m_device->Get_gpu()->Get_handle(), m_surface->Get_handle(),
        &presentModeCount, info.m_PresentModes.data());
  }

  return info;
}
VkSurfaceFormatKHR SwapChain::ChooseSurfaceFormat(
    const std::vector<VkSurfaceFormatKHR> &availableFormats) {

  if (availableFormats.size() == 1 &&
      availableFormats[0].format == VK_FORMAT_UNDEFINED) {
    return {VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
  }

  for (const auto &availableFormat : availableFormats) {
    if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
        availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return availableFormat;
    }
  }

  return availableFormats[0];
}
VkPresentModeKHR SwapChain::ChooseSurfacePresentMode(
    const std::vector<VkPresentModeKHR> &availablePresenstModes) {

  VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

  for (const auto &availablePresentMode : availablePresenstModes) {
    if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
      return availablePresentMode;
    } else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
      bestMode = availablePresentMode;
    }
  }

  return bestMode;
}
VkExtent2D
SwapChain::ChooseExtent(const VkSurfaceCapabilitiesKHR &capabilities) {

  if (capabilities.currentExtent.width !=
      std::numeric_limits<uint32_t>::max()) {
    return capabilities.currentExtent;
  }
  int width = 0, height = 0;
  glfwGetFramebufferSize(m_surface->Get_window()->Get_handle(), &width,
                         &height);

  VkExtent2D actualExtent = {static_cast<uint32_t>(width),
                             static_cast<uint32_t>(height)};
  // VkExtent2D actualExtent = {800, 600};

  actualExtent.width =
      std::max(capabilities.minImageExtent.width,
               std::min(capabilities.maxImageExtent.width, actualExtent.width));
  actualExtent.height = std::max(
      capabilities.minImageExtent.height,
      std::min(capabilities.maxImageExtent.height, actualExtent.height));

  return actualExtent;
}
} // namespace MoChengEngine::FrameWork::Wrapper