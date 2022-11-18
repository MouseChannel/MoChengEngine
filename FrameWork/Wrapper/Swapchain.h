/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:08:46
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-17 18:06:29
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Swapchain.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

#pragma once
#include "./Instance/Instance.h"
#include "Device.h"
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/WindowSurface.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Wrapper {
struct SwapChainSupportInfo {
  // 基础表面特性(交换链的最小/最大图像数量，最小/最大图像宽度、高度)
  VkSurfaceCapabilitiesKHR m_Capabilities;
  // 表面格式(像素格式，颜色空间)
  std::vector<VkSurfaceFormatKHR> m_Formats;
  // 可用的呈现模式
  std::vector<VkPresentModeKHR> m_PresentModes;
};
class SwapChain : public WrapperBase<VkSwapchainKHR, SwapChain> {
private:
 

  VkFormat m_SwapChainFormat;
  Device::Ptr m_device;
  WindowSurface::Ptr m_surface;
  uint32_t imageCount{0};
  VkExtent2D m_SwapChainExtent;
  std::vector<VkImage> m_SwapChainImages{};
  // image管理器
  std::vector<VkImageView> m_SwapChainImageViews{};
  void SpawnImages();
  VkImageView SpawnImageView(VkImage image);

  SwapChainSupportInfo QuerySwapChainSupportInfo();
  VkSurfaceFormatKHR
  ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR ChooseSurfacePresentMode(
      const std::vector<VkPresentModeKHR> &availablePresenstModes);
  VkExtent2D ChooseExtent(const VkSurfaceCapabilitiesKHR &capabilities);

public:
  SwapChain(Device::Ptr device, WindowSurface::Ptr surface);
  ~SwapChain();
  VkResult Acquire_next_image(uint32_t& image_index, VkSemaphore present_finish_semaphore, VkFence fence); 
 
  [[nodiscard]] auto &Get_images() { return m_SwapChainImages; }
  [[nodiscard]] auto &Get_images_view() { return m_SwapChainImageViews; }
  [[nodiscard]] auto &Get_format() { return m_SwapChainFormat; }
  [[nodiscard]] auto &Get_extent2D() { return m_SwapChainExtent; }
};

} // namespace MoChengEngine::FrameWork::Wrapper