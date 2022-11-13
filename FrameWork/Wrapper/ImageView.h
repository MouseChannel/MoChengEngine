#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"
#include "Device.h"
#include "vulkan/vulkan_core.h"

namespace MoChengEngine::FrameWork::Wrapper {
class ImageView : public WrapperBase<VkImageView, ImageView> {
private:
  VkImageView m_handle;
  Device::Ptr m_device;

public:
  ImageView(Device::Ptr device);
  ~ImageView();
  [[nodiscard]] VkImageView Get_handle() { return m_handle; }
};
} // namespace MoChengEngine::FrameWork::Wrapper