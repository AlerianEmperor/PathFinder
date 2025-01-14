#pragma once

#include "../RenderPass.hpp"
#include "../RenderPassContentMediator.hpp"

#include "PipelineNames.hpp"

namespace PathFinder
{

    struct RngSeedGenerationCBContent
    {
        uint32_t RngSeedTexIdx;
        uint32_t FrameNumber;
        uint32_t BlueNoiseTexSize;
        uint32_t BlueNoiseTexDepth;
    };

    class RngSeedGenerationRenderPass : public RenderPass<RenderPassContentMediator>
    { 
    public: 
        RngSeedGenerationRenderPass();
        ~RngSeedGenerationRenderPass() = default;

        virtual void SetupPipelineStates(PipelineStateCreator* stateCreator) override;
        virtual void ScheduleResources(ResourceScheduler<RenderPassContentMediator>* scheduler) override;
        virtual void Render(RenderContext<RenderPassContentMediator>* context) override;
    };

}
