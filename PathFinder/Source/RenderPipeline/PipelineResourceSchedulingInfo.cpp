#include "PipelineResourceSchedulingInfo.hpp"

namespace PathFinder
{

    PipelineResourceSchedulingInfo::PipelineResourceSchedulingInfo(Foundation::Name resourceName, const HAL::ResourceFormat& format)
        : mResourceFormat{ format }, mResourceName{ resourceName }, mCombinedResourceNames{ resourceName.ToString() }, mSubresourceCount{ format.SubresourceCount() }
    {
    }

    void PipelineResourceSchedulingInfo::AddExpectedStates(HAL::ResourceState states)
    {
        mExpectedStates |= states;
    }

    void PipelineResourceSchedulingInfo::AddNameAlias(Foundation::Name alias)
    {
        mAliases.push_back(alias);
        mCombinedResourceNames += " | " + alias.ToString();
    }

    void PipelineResourceSchedulingInfo::ApplyExpectedStates()
    {
        // Determine final memory requirements
        mResourceFormat.SetExpectedStates(mExpectedStates);
    }

    const PipelineResourceSchedulingInfo::PassInfo* PipelineResourceSchedulingInfo::GetInfoForPass(Foundation::Name passName) const
    {
        auto it = mPassInfoMap.find(passName);
        return it != mPassInfoMap.end() ? &it->second : nullptr;
    }

    PipelineResourceSchedulingInfo::PassInfo* PipelineResourceSchedulingInfo::GetInfoForPass(Foundation::Name passName)
    {
        auto it = mPassInfoMap.find(passName);
        return it != mPassInfoMap.end() ? &it->second : nullptr;
    }

    void PipelineResourceSchedulingInfo::SetSubresourceInfo(
        Foundation::Name passName,
        uint64_t subresourceIndex,
        HAL::ResourceState state,
        SubresourceInfo::AccessFlag accessFlag,
        std::optional<HAL::ColorFormat> shaderVisibleFormat)
    {
        assert_format(subresourceIndex < mSubresourceCount, "Subresource index is out of bounds");

        PassInfo& passInfo = mPassInfoMap[passName];
        passInfo.SubresourceInfos.resize(mSubresourceCount);
        passInfo.SubresourceInfos[subresourceIndex] = SubresourceInfo{};
        passInfo.SubresourceInfos[subresourceIndex]->AccessValidationFlag = accessFlag;
        passInfo.SubresourceInfos[subresourceIndex]->RequestedState = state;
        passInfo.SubresourceInfos[subresourceIndex]->ShaderVisibleFormat = shaderVisibleFormat;
        
        if (EnumMaskContains(state, HAL::ResourceState::UnorderedAccess))
        {
            passInfo.NeedsUnorderedAccessBarrier = true;
        }

        mExpectedStates |= state;
    }

}
