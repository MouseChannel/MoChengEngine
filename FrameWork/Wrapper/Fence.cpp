#include "Fence.h"
#include "vulkan/vulkan_core.h"
namespace MoChengEngine::FrameWork::Wrapper {
Fence::Fence(Device::Ptr &device) : m_device{device} {
  VkFenceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
  vkCreateFence(m_device->Get_handle(), &createInfo, nullptr, &m_handle);
}
Fence::~Fence() { vkDestroyFence(m_device->Get_handle(), m_handle, nullptr); }

void Fence::Reset() { vkResetFences(m_device->Get_handle(), 1, &m_handle); }
void Fence::Wait(uint64_t timeout) {
  vkWaitForFences(m_device->Get_handle(), 1, &m_handle, VK_TRUE, timeout);
}

} // namespace MoChengEngine::FrameWork::Wrapper