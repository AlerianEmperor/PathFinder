#include "TAARenderPass.hpp"

#include <Foundation/Gaussian.hpp>

namespace PathFinder
{

    TAARenderPass::TAARenderPass()
        : RenderPass("TAA") {}

    void TAARenderPass::SetupPipelineStates(PipelineStateCreator* stateCreator)
    {
        stateCreator->CreateComputeState(PSONames::DenoiserPostStabilization, [](ComputeStateProxy& state)
        {
            state.ComputeShaderFileName = "TAA.hlsl";
        });
    }

    void TAARenderPass::ScheduleResources(ResourceScheduler<RenderPassContentMediator>* scheduler)
    {
        return; // Disable 

        auto frameIndex = scheduler->FrameNumber() % 2;

        scheduler->NewTexture(ResourceNames::StochasticShadowedShadingDenoisedStabilized);
        scheduler->NewTexture(ResourceNames::StochasticUnshadowedShadingDenoisedStabilized);

        scheduler->ReadTexture(ResourceNames::StochasticShadowedShadingDenoised[frameIndex]);
        scheduler->ReadTexture(ResourceNames::StochasticUnshadowedShadingDenoised[frameIndex]);
        scheduler->ReadTexture(ResourceNames::StochasticShadowedShadingReprojected);
        scheduler->ReadTexture(ResourceNames::StochasticUnshadowedShadingReprojected);
    }
     
    void TAARenderPass::Render(RenderContext<RenderPassContentMediator>* context)
    {
        context->GetCommandRecorder()->ApplyPipelineState(PSONames::DenoiserPostStabilization);

        auto resourceProvider = context->GetResourceProvider();
        auto frameIndex = context->FrameNumber() % 2;

        TAACBContent cbContent{};
        cbContent.VarianceSourceTexIdx = resourceProvider->GetSRTextureIndex(ResourceNames::StochasticShadowedShadingReprojected);
        cbContent.InputTexIdx = resourceProvider->GetSRTextureIndex(ResourceNames::StochasticShadowedShadingDenoised[frameIndex]);
        cbContent.OutputTexIdx = resourceProvider->GetUATextureIndex(ResourceNames::StochasticShadowedShadingDenoisedStabilized);
        context->GetConstantsUpdater()->UpdateRootConstantBuffer(cbContent);
        context->GetCommandRecorder()->Dispatch(context->GetDefaultRenderSurfaceDesc().Dimensions(), { 16, 16 });

        cbContent.VarianceSourceTexIdx = resourceProvider->GetSRTextureIndex(ResourceNames::StochasticUnshadowedShadingReprojected);
        cbContent.InputTexIdx = resourceProvider->GetSRTextureIndex(ResourceNames::StochasticUnshadowedShadingDenoised[frameIndex]);
        cbContent.OutputTexIdx = resourceProvider->GetUATextureIndex(ResourceNames::StochasticUnshadowedShadingDenoisedStabilized);
        context->GetConstantsUpdater()->UpdateRootConstantBuffer(cbContent);
        context->GetCommandRecorder()->Dispatch(context->GetDefaultRenderSurfaceDesc().Dimensions(), { 16, 16 });
    }

}