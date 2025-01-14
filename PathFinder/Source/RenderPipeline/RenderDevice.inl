#include <aftermath/AftermathHelpers.hpp>

namespace PathFinder
{

    template <class Lambda>
    void RenderDevice::RecordWorkerCommandList(const RenderPassGraph::Node& passNode, const Lambda& action)
    {
        HAL::ComputeCommandListBase* worker = GetComputeCommandListBase(mFrameBlueprint.GetRenderPassEvent(passNode).CommandLists.WorkCommandList);
        worker->Reset();

        const std::string& passName = passNode.PassMetadata().Name.ToString();
        mEventTracker.StartGPUEvent(passName, *worker);

        GPUProfiler::EventID profilerEventID = mGPUProfiler->RecordEventStart(*worker, passNode.ExecutionQueueIndex);
        PipelineMeasurement& measurement = mPassWorkMeasurements[passNode.GlobalExecutionIndex()];
        measurement.Name = passName;
        measurement.ProfilerEventID = profilerEventID;

        if (worker->AftermathHandle())
        {
            AFTERMATH_CHECK_ERROR(GFSDK_Aftermath_SetEventMarker(*worker->AftermathHandle(), passName.c_str(), passName.size() + 1));
        }

        worker->SetDescriptorHeaps(mDescriptorAllocator->CBSRUADescriptorHeap(), mDescriptorAllocator->SamplerDescriptorHeap());
        action();

        mGPUProfiler->RecordEventEnd(*worker, profilerEventID);

        mEventTracker.EndGPUEvent(*worker);
        worker->Close();
    }

    template <class CommandQueueT, class CommandListT>
    void RenderDevice::ExecuteCommandListBatch(std::vector<CommandListPtrVariant>& batch, HAL::CommandQueue& queue)
    {
        std::vector<CommandListT*> commandLists;
        CommandQueueT* concreteQueue = static_cast<CommandQueueT*>(&queue);

        for (CommandListPtrVariant& ptr : batch)
        {
            CommandListT* cmdList = static_cast<CommandListT*>(GetComputeCommandListBase(ptr));
            commandLists.push_back(cmdList);
        }

        concreteQueue->ExecuteCommandLists(commandLists.data(), commandLists.size());
    }

}

