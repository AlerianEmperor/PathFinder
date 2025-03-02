#pragma once

#include "../RenderPass.hpp"
#include "../RenderPassContentMediator.hpp"

#include "PipelineNames.hpp"

#include <glm/mat4x4.hpp>

namespace PathFinder
{

    class DenoiserPreBlurRenderPass : public RenderPass<RenderPassContentMediator>
    { 
    public: 
        DenoiserPreBlurRenderPass();
        ~DenoiserPreBlurRenderPass() = default;

        virtual void SetupPipelineStates(PipelineStateCreator* stateCreator) override;
        virtual void ScheduleResources(ResourceScheduler<RenderPassContentMediator>* scheduler) override;
        virtual void Render(RenderContext<RenderPassContentMediator>* context) override;

    private:
        void BlurTexture(RenderContext<RenderPassContentMediator>* context, Foundation::Name inputName, Foundation::Name outputName);
    };

}
