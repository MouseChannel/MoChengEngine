#include "Pipeline.h"
#include "FrameWork/Wrapper/Pipeline.h"
#include "FrameWork/Wrapper/ShaderModule.h"
#include "FrameWork/Wrapper/Image.h"

namespace MoChengEngine::FrameWork::Wrapper {
Pipeline::Pipeline(Device::Ptr &device)
    : Component<VkPipeline, Pipeline>{device} {}
Pipeline::~Pipeline() {
  vkDestroyPipelineLayout(m_device->Get_handle(), m_layout, nullptr);
  vkDestroyPipeline(m_device->Get_handle(), m_handle, nullptr);
}

void Pipeline::Build_pipeline(
    RenderPass::Ptr renderpass,
    std::vector<VkPipelineShaderStageCreateInfo> &shaders_stage) {
  VkGraphicsPipelineCreateInfo pipelineCreateInfo{};
  pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

  pipelineCreateInfo.stageCount = static_cast<uint32_t>(shaders_stage.size());
  pipelineCreateInfo.pStages = shaders_stage.data();

  pipelineCreateInfo.pVertexInputState = &m_VertexInputInfo;
  pipelineCreateInfo.pInputAssemblyState = &m_InputAssembly;
  pipelineCreateInfo.pViewportState = &m_Viewport;
  pipelineCreateInfo.pRasterizationState = &m_Rasterizer;
  pipelineCreateInfo.pMultisampleState = &m_Multisampling;
  pipelineCreateInfo.pDepthStencilState = &m_DepthStencilState;
  // stencil
  pipelineCreateInfo.pColorBlendState = &m_BlendState;

  pipelineCreateInfo.layout = m_layout;
  pipelineCreateInfo.renderPass = renderpass->Get_handle();
  pipelineCreateInfo.subpass = 0;

  // �Դ��ڵ�pipelineΪ�������д���������죬������Ҫָ��flagsΪVK_PIPELINE_CREATE_DERIVATIVE_BIT
  pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
  pipelineCreateInfo.basePipelineIndex = -1;
}
void Pipeline::Set_pipeline_state(
    std::vector<VkVertexInputBindingDescription> &vertexbindindDes,
    std::vector<VkVertexInputAttributeDescription> &attributeDes,
    VkDescriptorSetLayout &layout) {

  Make_VertexInput_Info(vertexbindindDes, attributeDes);
  Make_AssemblyInput_Info();
  Make_ViewPort_Info();
  Make_Raster_Info();
  Make_MultiSample_Info();
  Make_BlendAttachment_Info();
  Make_BlendState_Info();
  Make_DepthStecil_Info();
  Make_LayoutCreate_Info(layout);


 
  
}
void Pipeline::Make_VertexInput_Info(
    std::vector<VkVertexInputBindingDescription> &vertexbindingDes,
    std::vector<VkVertexInputAttributeDescription> &attributeDes) {
  m_VertexInputInfo.sType =
      VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  m_VertexInputInfo.vertexBindingDescriptionCount = vertexbindingDes.size();
  m_VertexInputInfo.pVertexBindingDescriptions = vertexbindingDes.data();
  m_VertexInputInfo.vertexAttributeDescriptionCount = attributeDes.size();
  m_VertexInputInfo.pVertexAttributeDescriptions = attributeDes.data();
}

void Pipeline::Make_AssemblyInput_Info() {
  m_InputAssembly.sType =
      VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;

  m_InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  m_InputAssembly.primitiveRestartEnable = VK_FALSE;
}

void Pipeline::Make_ViewPort_Info() {
  m_Viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

  m_Viewport.viewportCount = static_cast<uint32_t>(m_Viewports.size());
  m_Viewport.pViewports = m_Viewports.data();
  m_Viewport.scissorCount = static_cast<uint32_t>(m_Scissors.size());
  m_Viewport.pScissors = m_Scissors.data();
}

void Pipeline::Make_Raster_Info() {
  m_Rasterizer.sType =
      VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  m_Rasterizer.polygonMode = VK_POLYGON_MODE_FILL; // ����ģʽ��Ҫ����gpu����
  m_Rasterizer.lineWidth = 1.0f; // ����1��Ҫ����gpu����
  m_Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  m_Rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  m_Rasterizer.depthBiasEnable = VK_FALSE;
  m_Rasterizer.depthBiasConstantFactor = 0.0f;
  m_Rasterizer.depthBiasClamp = 0.0f;
  m_Rasterizer.depthBiasSlopeFactor = 0.0f;
}

void Pipeline::Make_MultiSample_Info() {
  m_Multisampling.sType =
      VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;

  m_Multisampling.sampleShadingEnable = VK_FALSE;
  m_Multisampling.rasterizationSamples = m_device->getMaxUsableSampleCount();
  m_Multisampling.minSampleShading = 1.0f;
  m_Multisampling.pSampleMask = nullptr;
  m_Multisampling.alphaToCoverageEnable = VK_FALSE;
  m_Multisampling.alphaToOneEnable = VK_FALSE;
}

void Pipeline::Make_BlendAttachment_Info() {
  VkPipelineColorBlendAttachmentState blendAttachment{};

  blendAttachment.colorWriteMask =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
      VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

  blendAttachment.blendEnable = VK_FALSE;
  blendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
  blendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  blendAttachment.colorBlendOp = VK_BLEND_OP_ADD;

  blendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  blendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  blendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
  m_BlendAttachments.push_back(blendAttachment);
}

void Pipeline::Make_BlendState_Info() {
  m_BlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  m_BlendState.logicOpEnable = VK_FALSE;
  m_BlendState.logicOp = VK_LOGIC_OP_COPY;

  // ���blendAttachment��factor��operation
  m_BlendState.blendConstants[0] = 0.0f;
  m_BlendState.blendConstants[1] = 0.0f;
  m_BlendState.blendConstants[2] = 0.0f;
  m_BlendState.blendConstants[3] = 0.0f;
  m_BlendState.attachmentCount =
      static_cast<uint32_t>(m_BlendAttachments.size());
  m_BlendState.pAttachments = m_BlendAttachments.data();
}

void Pipeline::Make_LayoutCreate_Info(VkDescriptorSetLayout &layout) {
  m_LayoutState.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  m_LayoutState.setLayoutCount = 1;
  m_LayoutState.pSetLayouts = &layout;
  m_LayoutState.pushConstantRangeCount = 0;
  m_LayoutState.pPushConstantRanges = nullptr;
}
} // namespace MoChengEngine::FrameWork::Wrapper