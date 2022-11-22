/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-11 13:46:02
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-22 20:35:34
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Base\WrapperBase.hpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

#pragma once
#include <memory>
namespace MoChengEngine::FrameWork::Wrapper {
template <typename T, typename K> class WrapperBase {
public:
  using Ptr = std::shared_ptr<K>;
  T m_handle{nullptr};

  static Ptr Create(auto... args) {

    return std::make_shared<K>(std::forward<decltype(args)>(args)...);
  }

  [[nodiscard]] T  &Get_handle() { return m_handle; };
};
} // namespace MoChengEngine::FrameWork::Wrapper