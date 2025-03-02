#include "SMAANeighborhoodBlendingRenderPass.hpp"

namespace PathFinder
{

    SMAANeighborhoodBlendingRenderPass::SMAANeighborhoodBlendingRenderPass()
        : RenderPass("SMAANeighborhoodBlending") {}

    void SMAANeighborhoodBlendingRenderPass::SetupPipelineStates(PipelineStateCreator* stateCreator)
    {
        stateCreator->CreateGraphicsState(PSONames::SMAANeighborhoodBlending, [](GraphicsStateProxy& state)
        {
            state.VertexShaderFileName = "SMAANeighborhoodBlending.hlsl";
            state.PixelShaderFileName = "SMAANeighborhoodBlending.hlsl";
            state.PrimitiveTopology = HAL::PrimitiveTopology::TriangleList;
            state.DepthStencilState.SetDepthTestEnabled(false);
        });
    }

    void SMAANeighborhoodBlendingRenderPass::ScheduleResources(ResourceScheduler<RenderPassContentMediator>* scheduler)
    {
        scheduler->ReadTexture(ResourceNames::BloomCompositionOutput, TextureReadContext::PixelShader);
        scheduler->ReadTexture(ResourceNames::SMAABlendingWeights, TextureReadContext::PixelShader);

        scheduler->NewRenderTarget(ResourceNames::SMAAAntialiased);
    }

    void SMAANeighborhoodBlendingRenderPass::Render(RenderContext<RenderPassContentMediator>* context)
    {
        context->GetCommandRecorder()->ApplyPipelineState(PSONames::SMAANeighborhoodBlending);

        SMAANeighborhoodBlendingCBContent cbContent{};
        cbContent.InputImageTexIdx = context->GetResourceProvider()->GetSRTextureIndex(ResourceNames::BloomCompositionOutput);
        cbContent.BlendingWeightsTexIdx = context->GetResourceProvider()->GetSRTextureIndex(ResourceNames::SMAABlendingWeights);

        context->GetConstantsUpdater()->UpdateRootConstantBuffer(cbContent);
        context->GetCommandRecorder()->SetRenderTarget(ResourceNames::SMAAAntialiased);
        context->GetCommandRecorder()->Draw(DrawablePrimitive::Triangle());
    }

}
