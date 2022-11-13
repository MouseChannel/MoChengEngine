/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-07 21:45:47
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-09 12:22:29
 * @FilePath: \MoChengEngine\main.cpp
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */

// #include "FrameWork/Base/Singleton.hpp"
#include "app.hpp"

// using PTR = MoChengEngine::FrameWork::Wrapper::VInstance::Ptr;
int main(int, char **) {
//  VK_SUCCESS
  MoChengEngine::App app;
  app.InitWindow();
  app.InitVulkan();
  std::cout << "Hello, world!\n";
}
