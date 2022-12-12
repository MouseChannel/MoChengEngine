/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-18 10:14:18
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-10 14:47:56
 * @FilePath: \MoChengEngine\FrameWork\Core\ObjectPool.hpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
#include "FrameWork/Wrapper/Command/CommandPool.h"
#include "FrameWork/Wrapper/Command/CommandBuffer.h"

namespace MoChengEngine::FrameWork::Core {
template <typename Object> class ObjectPool {
public:
  std::function<Object()> m_create_func;
  ObjectPool<Object>(std::function<Object()> create_func = nullptr)
      : m_create_func{create_func} {}
  template <int family_index = 0>
  Object request_object(std::function<Object()> create_func = nullptr,
                        bool reset = false) {
    static std::map<int, std::vector<Object>> objects;
    static std::map<int, int> indexs;
    if (reset) {
      for (auto &key : indexs) {
        key.second = 0;
      }
      return objects[0][0];
    }
    auto &object_index = indexs[family_index];
    if (object_index >= objects[family_index].size()) {
      if (create_func == nullptr && m_create_func == nullptr)
        throw std::runtime_error("missing Object create func");
      if (create_func == nullptr)
        create_func = m_create_func;
      objects[family_index].emplace_back(create_func());
    }

    return objects[family_index][object_index++];
  }
};
auto default_command_buffer_create_func = [ ](Wrapper::Device::Ptr device, Wrapper::CommandPool::Ptr command_pool)
                                       { return Wrapper::CommandBuffer::Create(device, command_pool); };
} // namespace MoChengEngine::FrameWork::Core