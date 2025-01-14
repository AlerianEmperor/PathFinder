#include "CommonSetupRenderPass.hpp"

#include <Foundation/Gaussian.hpp>

namespace PathFinder
{

    CommonSetupRenderPass::CommonSetupRenderPass()
        : RenderPass("CommonSetup", RenderPassPurpose::Setup) {}

    void CommonSetupRenderPass::SetupRootSignatures(RootSignatureCreator* rootSignatureCreator)
    {
        rootSignatureCreator->CreateRootSignature(RootSignatureNames::UAVClear, [](RootSignatureProxy& signatureProxy)
        {
            signatureProxy.AddUnorderedAccessBufferParameter(0, 0); // Float buffer | u0 - s0
            signatureProxy.AddUnorderedAccessBufferParameter(1, 0); // UInt buffer | u0 - s0
        });
    }

    void CommonSetupRenderPass::SetupPipelineStates(PipelineStateCreator* stateCreator)
    {
        stateCreator->CreateComputeState(PSONames::Downsampling, [](ComputeStateProxy& state)
        {
            state.ComputeShaderFileName = "Downsampling.hlsl";
        });

        stateCreator->CreateComputeState(PSONames::SeparableBlur, [](ComputeStateProxy& state)
        {
            state.ComputeShaderFileName = "SeparableBlur.hlsl";
        });

        stateCreator->CreateComputeState(PSONames::UAVClear, [](ComputeStateProxy& state)
        {
            state.ComputeShaderFileName = "UAVClear.hlsl";
            state.RootSignatureName = RootSignatureNames::UAVClear;
        });

        stateCreator->CreateComputeState(PSONames::BoxBlur, [](ComputeStateProxy& state)
        {
            state.ComputeShaderFileName = "BoxBlur.hlsl";
        });
    }

    void CommonSetupRenderPass::ScheduleSamplers(SamplerCreator* samplerCreator)
    {
        samplerCreator->CreateSampler(SamplerNames::AnisotropicClamp, HAL::Sampler{ HAL::Sampler::UnifiedAlgorithm::Anisotropic, HAL::Sampler::AddressMode::Clamp });
        samplerCreator->CreateSampler(SamplerNames::AnisotropicWrap, HAL::Sampler{ HAL::Sampler::UnifiedAlgorithm::Anisotropic, HAL::Sampler::AddressMode::Wrap });
        samplerCreator->CreateSampler(SamplerNames::AnisotropicMirror, HAL::Sampler{ HAL::Sampler::UnifiedAlgorithm::Anisotropic, HAL::Sampler::AddressMode::Mirror });
        samplerCreator->CreateSampler(SamplerNames::LinearClamp, HAL::Sampler{ HAL::Sampler::UnifiedAlgorithm::Linear, HAL::Sampler::AddressMode::Clamp });
        samplerCreator->CreateSampler(SamplerNames::PointClamp, HAL::Sampler{ HAL::Sampler::UnifiedAlgorithm::Point, HAL::Sampler::AddressMode::Clamp });
        samplerCreator->CreateSampler(SamplerNames::Minimim, HAL::Sampler{ HAL::Sampler::MinMaxFilter::Minimum, HAL::Sampler::AddressMode::Clamp });
        samplerCreator->CreateSampler(SamplerNames::Maximum, HAL::Sampler{ HAL::Sampler::MinMaxFilter::Maximum, HAL::Sampler::AddressMode::Clamp });
    }

}
