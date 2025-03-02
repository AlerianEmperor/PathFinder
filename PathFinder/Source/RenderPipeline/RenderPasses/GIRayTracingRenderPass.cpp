#include "GIRayTracingRenderPass.hpp"

#include <Foundation/Halton.hpp>

namespace PathFinder
{

    GIRayTracingRenderPass::GIRayTracingRenderPass()
        : RenderPass("GIRayTracing") {} 

    void GIRayTracingRenderPass::SetupPipelineStates(PipelineStateCreator* stateCreator)
    {
        stateCreator->CreateRayTracingState(PSONames::GIRayTracing, [this](RayTracingStateProxy& state)
        {
            RayTracingStateProxy::HitGroupShaderFileNames meshHitGroup{};
            meshHitGroup.ClosestHitShaderFileName = "GIProbeRayTracing.hlsl";
            meshHitGroup.ClosestHitShaderEntryPoint = "MeshRayClosestHit";

            RayTracingStateProxy::HitGroupShaderFileNames lightHitGroup{};
            lightHitGroup.ClosestHitShaderFileName = "GIProbeRayTracing.hlsl";
            lightHitGroup.ClosestHitShaderEntryPoint = "LightRayClosestHit";

            // Order of hit group shaders must match hit group contribution of entities
            state.AddHitGroupShaders(meshHitGroup);
            state.AddHitGroupShaders(lightHitGroup);

            state.RayGenerationShaderFileName = "GIProbeRayTracing.hlsl";
            state.AddMissShader({ "GIProbeRayTracing.hlsl", "ProbeRayMiss" });
            state.AddMissShader({ "GIProbeRayTracing.hlsl", "SecondaryShadowRayMiss" });
            state.ShaderConfig = HAL::RayTracingShaderConfig{ sizeof(float), sizeof(float) * 2 };
            state.GlobalRootSignatureName = RootSignatureNames::ShadingCommon; // Reuse root sig from shading pass
            state.PipelineConfig = HAL::RayTracingPipelineConfig{ 2 };
        });
    }
     
    void GIRayTracingRenderPass::ScheduleResources(ResourceScheduler<RenderPassContentMediator>* scheduler)
    { 
        auto previousFrameIdx = (scheduler->GetFrameNumber() - 1) % 2;

        NewTextureProperties rayHitInfoTextureProperties{
            HAL::ColorFormat::RGBA16_Float,
            HAL::TextureKind::Texture2D,
            scheduler->GetContent()->GetSettings()->GlobalIlluminationSettings.GetRayHitInfoTextureSize()
        };

        scheduler->NewTexture(ResourceNames::GIRayHitInfo, rayHitInfoTextureProperties);

        scheduler->ReadTexture(ResourceNames::GIIlluminanceProbeAtlas[previousFrameIdx]);
        scheduler->ReadTexture(ResourceNames::GIDepthProbeAtlas[previousFrameIdx]);
        scheduler->ReadTexture(ResourceNames::SkyLuminance);

        scheduler->UseRayTracing();
        scheduler->ExecuteOnQueue(RenderPassExecutionQueue::AsyncCompute);
    } 

    void GIRayTracingRenderPass::Render(RenderContext<RenderPassContentMediator>* context)
    {
        auto previousFrameIdx = (context->GetFrameNumber() - 1) % 2;

        context->GetCommandRecorder()->ApplyPipelineState(PSONames::GIRayTracing);

        const Scene* scene = context->GetContent()->GetScene();
        const SceneGPUStorage* sceneStorage = context->GetContent()->GetSceneGPUStorage();
        const Memory::Texture* blueNoiseTexture = scene->GetBlueNoiseTexture();

        auto resourceProvider = context->GetResourceProvider();

        GIRayTracingCBContent cbContent{};
        cbContent.ProbeField = sceneStorage->GetIlluminanceFieldGPURepresentation();
        cbContent.ProbeField.PreviousIlluminanceProbeAtlasTexIdx = context->GetResourceProvider()->GetSRTextureIndex(ResourceNames::GIIlluminanceProbeAtlas[previousFrameIdx]);
        cbContent.ProbeField.PreviousDepthProbeAtlasTexIdx = context->GetResourceProvider()->GetSRTextureIndex(ResourceNames::GIDepthProbeAtlas[previousFrameIdx]);
        cbContent.ProbeField.RayHitInfoTextureIdx = context->GetResourceProvider()->GetUATextureIndex(ResourceNames::GIRayHitInfo);
        cbContent.BlueNoiseTexIdx = blueNoiseTexture->GetSRDescriptor()->IndexInHeapRange();
        cbContent.BlueNoiseTexSize = { blueNoiseTexture->Properties().Dimensions.Width, blueNoiseTexture->Properties().Dimensions.Height };
        cbContent.SkyTexIdx = context->GetResourceProvider()->GetSRTextureIndex(ResourceNames::SkyLuminance);

        auto start = context->GetFrameNumber() * 3;
        auto end = start + 3;
        auto haltonSequence = Foundation::Halton::Sequence(start, end);

        for (auto i = 0; i < 4; ++i)
        {
            cbContent.Halton[i] = haltonSequence[i];
        }

        context->GetConstantsUpdater()->UpdateRootConstantBuffer(cbContent);
        context->GetCommandRecorder()->SetRootConstants(sceneStorage->GetCompressedLightPartitionInfo(), 0, 0);

        const Memory::Buffer* bvh = sceneStorage->TopAccelerationStructure().AccelerationStructureBuffer();
        const Memory::Buffer* lights = sceneStorage->LightTable();
        const Memory::Buffer* materials = sceneStorage->MaterialTable();
        const Memory::Buffer* vertices = sceneStorage->UnifiedVertexBuffer();
        const Memory::Buffer* indices = sceneStorage->UnifiedIndexBuffer();
        const Memory::Buffer* meshInstances = sceneStorage->MeshInstanceTable();

        if (bvh) context->GetCommandRecorder()->BindExternalBuffer(*bvh, 0, 0, HAL::ShaderRegister::ShaderResource);
        if (lights) context->GetCommandRecorder()->BindExternalBuffer(*lights, 1, 0, HAL::ShaderRegister::ShaderResource);
        if (materials) context->GetCommandRecorder()->BindExternalBuffer(*materials, 2, 0, HAL::ShaderRegister::ShaderResource);
        if (vertices) context->GetCommandRecorder()->BindExternalBuffer(*vertices, 3, 0, HAL::ShaderRegister::ShaderResource);
        if (indices) context->GetCommandRecorder()->BindExternalBuffer(*indices, 4, 0, HAL::ShaderRegister::ShaderResource);
        if (meshInstances) context->GetCommandRecorder()->BindExternalBuffer(*meshInstances, 5, 0, HAL::ShaderRegister::ShaderResource);

        context->GetCommandRecorder()->DispatchRays(context->GetContent()->GetSettings()->GlobalIlluminationSettings.GetTotalRayCount());
    }

}
