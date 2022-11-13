#pragma once
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Core/Rendering/RenderFrame.h"
#include "FrameWork/Wrapper/Command/CommandQueue.h"
#include "FrameWork/Wrapper/Device.h"
#include "FrameWork/Wrapper/Swapchain.h"
#include <memory>

// #include "FrameWork/Wrapper/WrapperBase.hpp"
namespace MoChengEngine::FrameWork::Core::Rendering {
class RenderContext {
private:
  Wrapper::Instance::Ptr m_instance;
  Wrapper::Device::Ptr m_device;
  std::unique_ptr<RenderFrame> render_frames{nullptr};
  Wrapper::CommandQueue::Ptr m_command_queue{nullptr};
  Wrapper::SwapChain::Ptr m_swap_chain;

public:
  RenderContext();
  ~RenderContext();
  auto Get_commandQueue_by_flag(VkQueueFlagBits bit);
  
};
} // namespace MoChengEngine::FrameWork::Core::Rendering