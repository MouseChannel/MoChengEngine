
// RenderTarget contains three vectors for:  Image, ImageView and Attachment.
#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Core/Rendering/RenderTarget.h"
#include  "FrameWork/Wrapper/Command/CommandPool.h"
#include "FrameWork/Wrapper/Device.h"
// #include "FrameWork/Wrapper/WrapperBase.hpp"
namespace MoChengEngine::FrameWork::Core::Rendering {
class RenderFrame {
private:
Wrapper::Device::Ptr m_device;
  std::unique_ptr<RenderTarget> render_target;
  Wrapper:: CommandPool::Ptr m_command_pool;


public:
  RenderFrame();
  ~RenderFrame();
  auto Get_command_pool(VkQueueFlagBits bit);
};
} // namespace MoChengEngine::FrameWork::Core::Rendering
