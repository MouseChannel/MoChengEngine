/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-11 13:46:02
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-12 12:19:39
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\WrapperBase.hpp
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
  Ptr ptr;
  static Ptr Create(auto &...args) {

    return std::make_shared<K>(std::forward<decltype(args)>(args)...);
  }
  static Ptr CreateR(auto &&...args) {
    return std::make_shared<K>(std::forward<decltype(args)>(args)...);
  }

  [[nodiscard]] virtual T Get_handle() const= 0;
};
} // namespace MoChengEngine::FrameWork::Wrapper