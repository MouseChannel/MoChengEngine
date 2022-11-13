/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-11 15:14:12
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-11 20:56:27
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\Glfw_Window.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include "Glfw_Window.h"
namespace MoChengEngine::FrameWork::Wrapper {
Glfw_Window::Glfw_Window(const int width, const int height) {

  m_Width = width;
  m_Height = height;
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  m_handle =
      glfwCreateWindow(m_Width, m_Height, "mochengWindow", nullptr, nullptr);
  if (!m_handle) {
    std::cout << "Error: failed to create window" << std::endl;
  }
  glfwSetWindowUserPointer(m_handle, this);
  glfwSetFramebufferSizeCallback(m_handle, WindowResized);
}
Glfw_Window::~Glfw_Window() {
  glfwDestroyWindow(m_handle);
  glfwTerminate();
}
bool Glfw_Window::ShouldClose() { return glfwWindowShouldClose(m_handle); }

void Glfw_Window::PollEvent() { glfwPollEvents(); }
void Glfw_Window::WindowResized(GLFWwindow *window, int width, int height) {
  auto pUserData =
      reinterpret_cast<Glfw_Window *>(glfwGetWindowUserPointer(window));
  pUserData->m_WindowResized = true;
}

} // namespace MoChengEngine::FrameWork::Wrapper