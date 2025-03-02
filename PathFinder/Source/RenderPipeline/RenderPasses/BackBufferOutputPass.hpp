#pragma once

#include "../RenderPass.hpp"
#include "../RenderPassContentMediator.hpp"

#include "PipelineNames.hpp"

#include <glm/mat4x4.hpp>

namespace PathFinder
{

    struct BackBufferOutputPassData
    {
        uint32_t SourceTexIdx;
    };
     
    class BackBufferOutputPass : public RenderPass<RenderPassContentMediator> 
    {
    public:
        BackBufferOutputPass();
        ~BackBufferOutputPass() = default;

        virtual void SetupPipelineStates(PipelineStateCreator* stateCreator) override;
        virtual void ScheduleResources(ResourceScheduler<RenderPassContentMediator>* scheduler) override; 
        virtual void Render(RenderContext<RenderPassContentMediator>* context) override;
    };

}
