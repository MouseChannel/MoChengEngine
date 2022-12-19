/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-08 21:21:18
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-12-17 12:03:11
 * @FilePath: \MoChengEngine\FrameWork\Base\error.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#include <stdio.h>
#include <vulkan/vk_enum_string_helper.h>

#define VK_CHECK_SUCCESS(error, mes)                                           \
  if (error) {                                                                 \
    printf("%s, err_code: %s\n", mes, string_VkResult(error));                 \
    abort();                                                                   \
  }
//   VkResult err = error;