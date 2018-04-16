#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

class std::string;

struct DescriptorData
{
	vk::UniqueDescriptorPool Pool;
	std::vector<vk::UniqueDescriptorSet> Sets;
};

class VulkanGraphicsPipeline
{
public:

	VulkanGraphicsPipeline();
	~VulkanGraphicsPipeline();
	
	void BuildPipeline(class VulkanRenderPass& RenderPass,const std::string& VertexShader, const std::string& FragmentShader);
	vk::Pipeline GetHandle() { return GraphicsPipeline.get(); }
	vk::PipelineLayout GetLayout() { return PipelineLayout.get(); }

	//Creates a descriptor pool and allocates descriptor sets for the entirety of this Pipeline's descriptor bindings
	DescriptorData AllocateDescriptorSets(uint32_t NumSets);
	//Create a descriptor pool used to allocate up to MaxSets descriptor sets
	vk::UniqueDescriptorPool CreateDescriptorPool(uint32_t MaxSets);

	std::vector<vk::DescriptorSetLayoutBinding>& GetDescriptorBindings() { return DescriptorBindings; }

protected: //Internal Pipeline Member variables

	vk::UniquePipeline GraphicsPipeline;

public: //Shader Stage Functions

	std::vector<char> LoadShaderFromFile(const std::string& filename);
	vk::ShaderModule  CreateShaderModule(std::vector<char> spvCode);

public://Fixed Function Pipeline State

	vk::PipelineVertexInputStateCreateInfo VertexInput;
	
	void SetVertexInputBindings(std::vector<vk::VertexInputBindingDescription>& InputBindings, std::vector<vk::VertexInputAttributeDescription>& AttributeBindings);
	std::vector<vk::VertexInputBindingDescription> VertexInputBindings;
	std::vector<vk::VertexInputAttributeDescription> VertexAttributeBindings;

	vk::PipelineInputAssemblyStateCreateInfo InputAssembly;

	vk::PipelineTessellationStateCreateInfo Tessellation;
	
	vk::PipelineViewportStateCreateInfo ViewportState;
	vk::Viewport Viewport;
	vk::Rect2D Scissor;

	vk::PipelineRasterizationStateCreateInfo Rasterizer;

	vk::PipelineMultisampleStateCreateInfo Multisampling;

	vk::PipelineDepthStencilStateCreateInfo DepthStencil;

	vk::PipelineColorBlendStateCreateInfo ColorBlending;
	vk::PipelineColorBlendAttachmentState ColorBlendAttachment;

	vk::PipelineDynamicStateCreateInfo DynamicState;
	std::vector<vk::DynamicState> DynamicStates;

	vk::UniqueDescriptorSetLayout DescriptorSetLayout;
	std::vector<vk::DescriptorSetLayoutBinding> DescriptorBindings;

	vk::PipelineLayoutCreateInfo PipelineLayoutCreateInfo;
	vk::UniquePipelineLayout PipelineLayout;
};