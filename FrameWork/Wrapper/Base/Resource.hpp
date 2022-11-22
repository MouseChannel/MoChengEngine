/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-14 10:01:38
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-19 14:19:33
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Base\Resource.hpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "FrameWork/Wrapper/Base/Component.hpp"
#include "FrameWork/Wrapper/Device.h"
#include <memory>

namespace MoChengEngine::FrameWork::Wrapper {
template <typename T, typename K> class Resource : public Component<T, K> {
public:
  Resource<T, K>(Device::Ptr device) : Component<T, K>{device} {}
  ~Resource<T, K>() = default;

protected:
  VmaAllocation allocation{VK_NULL_HANDLE};
};
} // namespace MoChengEngine::FrameWork::Wrapper