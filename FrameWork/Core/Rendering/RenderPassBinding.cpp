#include "RenderPassBinding.h"
#include "FrameWork/Core/Rendering/RenderPassBinding.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "RenderManager.hpp"

namespace MoChengEngine::FrameWork::Core::Rendering {
RenderPassBinding::RenderPassBinding(Device::Ptr &device,
                                     RenderPass::Ptr &renderPass,
                                     VkExtent2D &extent)
    : m_device{device}, m_render_pass{renderPass}, m_extent{m_extent} {}
RenderPassBinding::~RenderPassBinding() {}

void RenderPassBinding::Add_attachment_and_description(
    std::tuple<VkImageView, VkAttachmentDescription> &bind,
    Wrapper::SubPass::attachment_type attachment_type) {
  attachments.push_back(std::get<0>(bind));
  descriptions.push_back(std::get<1>(bind));

  VkAttachmentReference ref{};
  ref.attachment = attachments.size() - 1;
  ref.layout = attachment_type == Wrapper::SubPass::DepthStencilAttachment
                   ? VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL
                   : VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  for (auto &subpass : m_render_pass->Get_subpasses()) {
    subpass->Add_attachment_reference(ref, attachment_type);
  }
}

void RenderPassBinding::Build() {
  m_render_pass->Set_attachment_description(descriptions);
  m_render_pass->BuildRenderPass();
  framebuffer =
      FrameBuffer::Create(m_device, m_extent, attachments, m_render_pass);
}
} // namespace MoChengEngine::FrameWork::Core::Rendering