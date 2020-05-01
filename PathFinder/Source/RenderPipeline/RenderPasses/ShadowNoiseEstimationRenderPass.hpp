#pragma once

#include "../RenderPass.hpp"
#include "../RenderPassContentMediator.hpp"

#include <glm/mat4x4.hpp>

namespace PathFinder
{

    struct ShadowNoiseEstimationCBContent
    {
        uint32_t StochasticShadowedLuminanceTextureIndex;
        uint32_t StochasticUnshadowedLuminanceTextureIndex;
        uint32_t OutputTextureIndex;
        float MaximumLightsLuminance;
    };

    class ShadowNoiseEstimationRenderPass : public RenderPass<RenderPassContentMediator>
    { 
    public: 
        ShadowNoiseEstimationRenderPass();
        ~ShadowNoiseEstimationRenderPass() = default;

        virtual void SetupPipelineStates(PipelineStateCreator* stateCreator, RootSignatureCreator* rootSignatureCreator) override;
        virtual void ScheduleResources(ResourceScheduler* scheduler) override;
        virtual void Render(RenderContext<RenderPassContentMediator>* context) override;
    };

}