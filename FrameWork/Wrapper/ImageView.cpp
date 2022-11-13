/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-12 17:39:46
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-13 13:28:46
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\ImageView.cpp
 * @Description: nullptr
 * 
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved. 
 */
#include "ImageView.h"
#include "vulkan/vulkan_core.h"
namespace MoChengEngine::FrameWork::Wrapper {
ImageView::ImageView(Device::Ptr device) : m_device{device} {
  VkImageViewCreateInfo createinfo{};
  vkCreateImageView(m_device->Get_handle(), &createinfo, nullptr, &m_handle);
}
ImageView::~ImageView() {
  vkDestroyImageView(m_device->Get_handle(), m_handle, nullptr);
}
} // namespace MoChengEngine::FrameWork::Wrapper