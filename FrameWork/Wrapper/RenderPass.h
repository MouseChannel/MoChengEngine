/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-14 21:56:24
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-19 20:20:24
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\RenderPass.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "Device.h"
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/Base/Component.hpp"
#include "FrameWork/Wrapper/RenderPass.h"
#include <memory>

namespace MoChengEngine::FrameWork::Wrapper {
class SubPass;
class RenderPass : public Component<VkRenderPass, RenderPass> {
private:
  std::vector<std::unique_ptr<SubPass>> mSubPasses;
  std::vector<VkSubpassDependency> mDependencies;
  // need to sync index in frameBuffer attachments;
  std::vector<VkAttachmentDescription> mAttachmentDescriptions;

public:
  RenderPass(Device::Ptr device);
  ~RenderPass();
  void AddSubPass(const SubPass &subpass,
                  const VkSubpassDependency &dependency) {
    mSubPasses.push_back(std::make_unique<SubPass>(subpass));
    mDependencies.push_back(dependency);
  }

  void Set_attachment_description(
      std::vector<VkAttachmentDescription> &attachmentDes) {
    mAttachmentDescriptions = attachmentDes;
  }
  [[nodiscard]] auto &Get_subpasses() { return mSubPasses; }
  void BuildRenderPass();
};

class SubPass {
private:
  VkSubpassDescription m_SubPassDescription{};
  // AttachmentReference代表的是在RenderPassAttachments数组里面的下标
  // 该pass的输出
  std::vector<VkAttachmentReference> m_ColorAttachmentReferences{};
  // 上pass的输出，即该pass的输入
  std::vector<VkAttachmentReference> m_InputAttachmentReferences{};
  VkAttachmentReference m_DepthStencilAttachmentReference{};
  VkAttachmentReference m_ResolvedAttachmentReference{};
  VkSubpassDependency m_dependence;

public:
  enum attachment_type {
    ColorAttachment = 0,
    ResolveAttachment = 1,
    DepthStencilAttachment = 2,
    InputAttachment = 3

  };
  SubPass() = default;
  ~SubPass() = default;

  void Add_attachment_reference(const VkAttachmentReference ref,
                                attachment_type type) {
    switch (type) {
    case Wrapper::SubPass::ColorAttachment:
      m_ColorAttachmentReferences.push_back(ref);
      break;
    case Wrapper::SubPass::DepthStencilAttachment:
      m_DepthStencilAttachmentReference = ref;
      break;
    case Wrapper::SubPass::InputAttachment:
      m_InputAttachmentReferences.push_back(ref);
      break;
    case Wrapper::SubPass::ResolveAttachment:
      m_ResolvedAttachmentReference = ref;
      break;
    }

 
  }
  void Set_dependence(VkSubpassDependency dependence) {
    m_dependence = dependence;
  }
  void Build_SubPass_Description() {
    if (m_ColorAttachmentReferences.empty()) {
      throw std::runtime_error("Error: color attachment group is empty!");
    }
    m_SubPassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

    m_SubPassDescription.colorAttachmentCount =
        static_cast<uint32_t>(m_ColorAttachmentReferences.size());
    m_SubPassDescription.pColorAttachments = m_ColorAttachmentReferences.data();

    m_SubPassDescription.inputAttachmentCount =
        static_cast<uint32_t>(m_InputAttachmentReferences.size());
    m_SubPassDescription.pInputAttachments = m_InputAttachmentReferences.data();
    m_SubPassDescription.pResolveAttachments = &m_ResolvedAttachmentReference;

    m_SubPassDescription.pDepthStencilAttachment =
        m_DepthStencilAttachmentReference.layout == VK_IMAGE_LAYOUT_UNDEFINED
            ? nullptr
            : &m_DepthStencilAttachmentReference;
  }

  [[nodiscard]] auto GetSubPassDescription() const {
    return m_SubPassDescription;
  }
};
} // namespace MoChengEngine::FrameWork::Wrapper