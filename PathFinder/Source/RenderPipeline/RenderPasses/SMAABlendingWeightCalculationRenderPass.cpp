#include "SMAABlendingWeightCalculationRenderPass.hpp"

namespace PathFinder
{

    SMAABlendingWeightCalculationRenderPass::SMAABlendingWeightCalculationRenderPass()
        : RenderPass("SMAABlendingWeightCalculation") {}

    void SMAABlendingWeightCalculationRenderPass::SetupPipelineStates(PipelineStateCreator* stateCreator)
    {
        stateCreator->CreateGraphicsState(PSONames::SMAABlendingWeightCalculation, [](GraphicsStateProxy& state)
        {
            state.VertexShaderFileName = "SMAABlendingWeightCalculation.hlsl";
            state.PixelShaderFileName = "SMAABlendingWeightCalculation.hlsl";
            state.PrimitiveTopology = HAL::PrimitiveTopology::TriangleList;
            state.DepthStencilState.SetDepthTestEnabled(false);
            state.RenderTargetFormats = { HAL::ColorFormat::RGBA16_Float };
        });
    }

    void SMAABlendingWeightCalculationRenderPass::ScheduleResources(ResourceScheduler<RenderPassContentMediator>* scheduler)
    {
        scheduler->ReadTexture(ResourceNames::SMAADetectedEdges, TextureReadContext::PixelShader);
        scheduler->NewRenderTarget(ResourceNames::SMAABlendingWeights, NewTextureProperties{ HAL::ColorFormat::RGBA16_Float });
    }

    void SMAABlendingWeightCalculationRenderPass::Render(RenderContext<RenderPassContentMediator>* context)
    {
        context->GetCommandRecorder()->ApplyPipelineState(PSONames::SMAABlendingWeightCalculation);

        const Scene* scene = context->GetContent()->GetScene(); 

        SMAABlendingWeightCalculationCBContent cbContent{};
        cbContent.EdgesTexIdx = context->GetResourceProvider()->GetSRTextureIndex(ResourceNames::SMAADetectedEdges);
        cbContent.AreaTexIdx = scene->GetSMAAAreaTexture()->GetSRDescriptor()->IndexInHeapRange();
        cbContent.SearchTexIdx = scene->GetSMAASearchTexture()->GetSRDescriptor()->IndexInHeapRange();

        context->GetConstantsUpdater()->UpdateRootConstantBuffer(cbContent);
        context->GetCommandRecorder()->SetRenderTarget(ResourceNames::SMAABlendingWeights);
        context->GetCommandRecorder()->Draw(DrawablePrimitive::Triangle());
    }

}
