/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-14 10:01:38
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-15 13:36:23
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Resource.hpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"
#include <memory>

namespace MoChengEngine::FrameWork::Wrapper {
template <typename T, typename K> class Resource : public WrapperBase<T, K> {
public:
  Resource<T, K>(Device::Ptr device) : m_device{device} {}
  ~Resource<T, K>();
  [[nodiscard]] auto& Get_device() { return m_device; }

protected:
  VmaAllocation allocation{VK_NULL_HANDLE};
  Device::Ptr m_device;
};
} // namespace MoChengEngine::FrameWork::Wrapper