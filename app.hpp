/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-08 12:13:24
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-14 10:33:19
 * @FilePath: \MoChengEngine\app.hpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

#include "FrameWork/Wrapper/Glfw_Window.h"
#include "FrameWork/Wrapper/Instance/Instance.h"
#include"FrameWork/Wrapper/WindowSurface.h"
#include"FrameWork/Wrapper/Device.h"

namespace MoChengEngine {
using namespace FrameWork::Wrapper;
class App {
private:
  unsigned int m_Width{800};
  unsigned int m_Height{600};
  Glfw_Window::Ptr m_Window{nullptr};
  Instance::Ptr m_Instance{nullptr};
  Device::Ptr m_Device{nullptr};
  WindowSurface::Ptr m_Surface{nullptr};

  

public:
  void InitWindow();
  void InitVulkan();

  void MainLoop();

  void CleanUp();
  void Run() {
    InitWindow();
    InitVulkan();
    MainLoop();
    CleanUp();
  }
  App() = default;
  ~App() = default;
};

void App::InitWindow() {
  m_Window = Glfw_Window::CreateR(800,600);
  // m_Window = Window::Create(m_Width, m_Height);
  // glfwSetWindowUserPointer(m_Window->GetWindow(), this);

  // glfwSetCursorPosCallback(m_Window->GetWindow(), cursorPosCallBack);
}
void App::InitVulkan(){
 m_Instance = Instance::Create();
 

 m_Surface = WindowSurface::Create(m_Instance, m_Window);
//  auto ss = typeid(m_Surface).name();
//  auto sws = typeid(m_Instance).name();
//  std::cout<<<<std::endl;
 m_Device = Device::Create(m_Instance, m_Surface);
// VInstance::Instance();
// Device::Instance();
int a = 0;
}

} // namespace MoChengEngine