/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 16:08:46
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 16:32:10
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
  VkSwapchainKHR m_handle;
  Device::Ptr m_device;
  WindowSurface::Ptr m_surface;
    int imageCount{0};
public:
  SwapChain(Device::Ptr device, WindowSurface::Ptr surface);
  ~SwapChain();
  SwapChainSupportInfo QuerySwapChainSupportInfo();
  VkSurfaceFormatKHR
  ChooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR ChooseSurfacePresentMode(
      const std::vector<VkPresentModeKHR> &availablePresenstModes);
  VkExtent2D ChooseExtent(const VkSurfaceCapabilitiesKHR &capabilities);
  [[nodiscard]] VkSwapchainKHR Get_handle() { return m_handle; }
};

} // namespace MoChengEngine::FrameWork::Wrapper