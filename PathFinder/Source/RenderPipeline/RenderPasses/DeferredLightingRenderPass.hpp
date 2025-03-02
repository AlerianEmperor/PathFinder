#pragma once

#include "../RenderPass.hpp"
#include "../RenderPassContentMediator.hpp"

#include "GBufferTextureIndices.hpp"
#include "PipelineNames.hpp"

#include <glm/mat4x4.hpp>

namespace PathFinder
{

    struct ShadingCBContent
    {
        GBufferTextureIndices GBufferIndices;
        glm::vec4 Halton;
        // 16 byte boundary
        uint32_t BlueNoiseTexIdx;
        uint32_t AnalyticOutputTexIdx;
        uint32_t ShadowRayPDFsTexIdx;
        uint32_t ShadowRayIntersectionPointsTexIdx;
        // 16 byte boundary
        glm::uvec2 BlueNoiseTextureSize;
        uint32_t RngSeedsTexIdx;
        uint32_t FrameNumber;
        // 16 byte boundary
        uint32_t SkyTexIdx;
    };

    class DeferredLightingRenderPass : public RenderPass<RenderPassContentMediator>
    {
    public:
        DeferredLightingRenderPass();
        ~DeferredLightingRenderPass() = default;

        virtual void SetupRootSignatures(RootSignatureCreator* rootSignatureCreator) override;
        virtual void SetupPipelineStates(PipelineStateCreator* stateCreator) override;
        virtual void ScheduleResources(ResourceScheduler<RenderPassContentMediator>* scheduler) override; 
        virtual void Render(RenderContext<RenderPassContentMediator>* context) override;
    };

}
