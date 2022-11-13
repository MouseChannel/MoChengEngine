/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-08 21:21:18
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-11 14:16:34
 * @FilePath: \MoChengEngine\FrameWork\Base\error.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
 #include <stdio.h>

 #define VK_CHECK_SUCCESS(error,mes)  if(error){ printf("%s, err_code: %d\n",mes ,error); abort();}  
//   VkResult err = error;