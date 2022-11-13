/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-11 20:10:22
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-11 20:16:28
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\WindowSurface.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

#include "WindowSurface.h"

namespace MoChengEngine::FrameWork::Wrapper {
WindowSurface::WindowSurface(Instance::Ptr instance, Glfw_Window::Ptr window) {
  m_instance = instance;
  m_window = window;
  VK_CHECK_SUCCESS(glfwCreateWindowSurface(instance->Get_handle(),
                                           window->Get_handle(), nullptr,
                                           &m_Handle),
                   "create windowSurface failed");
}
WindowSurface::~WindowSurface() {
  vkDestroySurfaceKHR(m_instance->Get_handle(), m_Handle, nullptr);
}

} // namespace MoChengEngine::FrameWork::Wrapper