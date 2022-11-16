/*
 * @Author: mousechannel mochenghh@gmail.com
 * @Date: 2022-11-14 21:56:24
 * @LastEditors: mousechannel mochenghh@gmail.com
 * @LastEditTime: 2022-11-15 13:34:49
 * @FilePath: \MoChengEngine\FrameWork\Wrapper\RenderPass.h
 * @Description: nullptr
 *
 * Copyright (c) 2022 by mousechannel mochenghh@gmail.com, All Rights Reserved.
 */
#pragma once
#include "Device.h"
#include "FrameWork/Base/baseHeader.h"
#include "FrameWork/Wrapper/RenderPass.h"
#include "FrameWork/Wrapper/WrapperBase.hpp"
#include <memory>

namespace MoChengEngine::FrameWork::Wrapper {
class SubPass;
class RenderPass : public WrapperBase<VkRenderPass, RenderPass> {
private:
  Device::Ptr m_device;
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

  void AddAttachment(const VkAttachmentDescription &attachmentDes) {
    mAttachmentDescriptions.push_back(attachmentDes);
  }
  void SetAttachment(std::vector<VkAttachmentDescription> &attachmentDes) {
    mAttachmentDescriptions = attachmentDes;
  }

  void BuildRenderPass();
  [[nodiscard]] auto& Get_device() const{return m_device;}
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

public:
  SubPass() = default;
  ~SubPass() = default;
  void AddColorAttachmentReference(const VkAttachmentReference &ref) {
    m_ColorAttachmentReferences.push_back(ref);
  }

  void AddInputAttachmentReference(const VkAttachmentReference &ref) {
    m_InputAttachmentReferences.push_back(ref);
  }

  void SetDepthStencilAttachmentReference(const VkAttachmentReference &ref) {
    m_DepthStencilAttachmentReference = ref;
  }

  void BuildSubPassDescription();
  void setResolveAttachmentReference(const VkAttachmentReference &ref) {
    m_ResolvedAttachmentReference = ref;
  }

  [[nodiscard]] auto GetSubPassDescription() const {
    return m_SubPassDescription;
  }
};
} // namespace MoChengEngine::FrameWork::Wrapper