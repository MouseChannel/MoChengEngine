/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-08 12:26:03
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-19 22:08:17
 * @FilePath: \MoChengEngine\FrameWork\Base\baseHeader.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
 
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#define GLFW_INCLUDE_VULKAN

#include "error.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vulkan/vulkan.h>

#define VMA_IMPLEMENTATION
#include "vma/vk_mem_alloc.h"

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

const static int Width = 800;

const static int Height = 800;