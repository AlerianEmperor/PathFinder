#pragma once

#include "../RenderPass.hpp"
#include "../RenderPassContentMediator.hpp"

#include "PipelineNames.hpp"

#include <glm/mat4x4.hpp>

namespace PathFinder
{

    struct ToneMappingCBContent
    {
        uint32_t InputTexIdx;
        uint32_t OutputTexIdx;   
        uint32_t IsHDREnabled;
        float DisplayMaximumLuminance;
        // 16 byte boundary
        GTTonemappingParameterss TonemappingParams;
    };

    class ToneMappingRenderPass : public RenderPass<RenderPassContentMediator>
    { 
    public: 
        ToneMappingRenderPass();
        ~ToneMappingRenderPass() = default;

        virtual void SetupRootSignatures(RootSignatureCreator* rootSignatureCreator) override;
        virtual void SetupPipelineStates(PipelineStateCreator* stateCreator) override;
        virtual void ScheduleResources(ResourceScheduler<RenderPassContentMediator>* scheduler) override;
        virtual void Render(RenderContext<RenderPassContentMediator>* context) override;
    };

}
