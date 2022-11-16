/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-11 15:14:03
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-15 10:28:43
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Glfw_Window.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
 #pragma once
#include "FrameWork/Base/baseHeader.h"
#include "WrapperBase.hpp"
namespace MoChengEngine::FrameWork::Wrapper {
class Glfw_Window : public WrapperBase<GLFWwindow *, Glfw_Window> {
private:
//   GLFWwindow *m_handle{NULL};
  int m_Width{0};
  int m_Height{0};

public:
Glfw_Window(const int  width, const int  height);
~Glfw_Window();
  bool m_WindowResized{false};
  bool ShouldClose(); 
  void PollEvent();
  
  static void WindowResized(GLFWwindow *window, int width, int height);
//   [[nodiscard]] GLFWwindow *Get_handle()const { return m_handle; }
};

} // namespace MoChengEngine::FrameWork::Wrapper