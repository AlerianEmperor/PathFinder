//*********************************************************
//
// Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.
// 
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
// 
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//*********************************************************

#pragma once

#include <iomanip>
#include <string>
#include <sstream>

#include "GFSDK_Aftermath.h"
#include "GFSDK_Aftermath_GpuCrashDump.h"
#include "GFSDK_Aftermath_GpuCrashDumpDecoding.h"

//*********************************************************
// Some std::to_string overloads for some Nsight Aftermath
// API types.
//

namespace std
{
    template<typename T>
    inline std::string to_hex_string(T n)
    {
        std::stringstream stream;
        stream << std::setfill('0') << std::setw(2 * sizeof(T)) << std::hex << n;
        return stream.str();
    }

    inline std::string to_string(GFSDK_Aftermath_Result result)
    {
        return std::string("0x") + to_hex_string(static_cast<UINT>(result));
    }

    inline std::string to_string(const GFSDK_Aftermath_ShaderDebugInfoIdentifier& identifier)
    {
        return to_hex_string(identifier.id[0]) + "-" + to_hex_string(identifier.id[1]);
    }

    inline std::string to_string(const GFSDK_Aftermath_ShaderHash& hash)
    {
        return to_hex_string(hash.hash);
    }

    inline std::string to_string(const GFSDK_Aftermath_ShaderInstructionsHash& hash)
    {
        return to_hex_string(hash.hash) + "-" + to_hex_string(hash.hash);
    }

    template<> 
    struct hash<GFSDK_Aftermath_ShaderHash>
    {
        size_t operator()(const GFSDK_Aftermath_ShaderHash& x) const
        {
            return hash<decltype(x.hash)>()(x.hash);
        }
    };

    template<> 
    struct hash<GFSDK_Aftermath_ShaderInstructionsHash>
    {
        size_t operator()(const GFSDK_Aftermath_ShaderInstructionsHash& x) const
        {
            return hash<decltype(x.hash)>()(x.hash);
        }
    };

    template<>
    struct hash<GFSDK_Aftermath_ShaderDebugInfoIdentifier>
    {
        size_t operator()(const GFSDK_Aftermath_ShaderDebugInfoIdentifier& x) const
        {
            uint64_t a = x.id[0];
            uint64_t b = x.id[1];

            // Szudzik's function: https://stackoverflow.com/a/13871379/4308277
            uint64_t combined = a >= b ? a * a + a + b : a + b * b;

            return hash<uint64_t>()(combined);
        }
    };

    template<>
    struct hash<GFSDK_Aftermath_ShaderDebugName>
    {
        size_t operator()(const GFSDK_Aftermath_ShaderDebugName& x) const
        {
            return hash<std::string_view>()(std::string_view(x.name));
        }
    };

} // namespace std

//*********************************************************
// Helper for comparing shader hashes and debug info identifier.
//

// Helper for comparing GFSDK_Aftermath_ShaderDebugInfoIdentifier.
inline bool operator<(const GFSDK_Aftermath_ShaderDebugInfoIdentifier& lhs, const GFSDK_Aftermath_ShaderDebugInfoIdentifier& rhs)
{
    if (lhs.id[0] == rhs.id[0])
    {
        return lhs.id[1] < rhs.id[1];
    }
    return lhs.id[0] < rhs.id[0];
}

// Helper for comparing GFSDK_Aftermath_ShaderHash.
inline bool operator<(const GFSDK_Aftermath_ShaderHash& lhs, const GFSDK_Aftermath_ShaderHash& rhs)
{
    return lhs.hash < rhs.hash;
}

// Helper for comparing GFSDK_Aftermath_ShaderInstructionsHash.
inline bool operator<(const GFSDK_Aftermath_ShaderInstructionsHash& lhs, const GFSDK_Aftermath_ShaderInstructionsHash& rhs)
{
    return lhs.hash < rhs.hash;
}

// Helper for comparing GFSDK_Aftermath_ShaderDebugName.
inline bool operator<(const GFSDK_Aftermath_ShaderDebugName& lhs, const GFSDK_Aftermath_ShaderDebugName& rhs)
{
    return strncmp(lhs.name, rhs.name, sizeof(lhs.name)) < 0;
}

//
inline bool operator==(const GFSDK_Aftermath_ShaderDebugInfoIdentifier& lhs, const GFSDK_Aftermath_ShaderDebugInfoIdentifier& rhs)
{
    return lhs.id[0] == rhs.id[0] && lhs.id[1] == rhs.id[1];
}

inline bool operator==(const GFSDK_Aftermath_ShaderHash& lhs, const GFSDK_Aftermath_ShaderHash& rhs)
{
    return lhs.hash == rhs.hash;
}

inline bool operator==(const GFSDK_Aftermath_ShaderInstructionsHash& lhs, const GFSDK_Aftermath_ShaderInstructionsHash& rhs)
{
    return lhs.hash == rhs.hash;
}

inline bool operator==(const GFSDK_Aftermath_ShaderDebugName& lhs, const GFSDK_Aftermath_ShaderDebugName& rhs)
{
    return strncmp(lhs.name, rhs.name, sizeof(lhs.name)) == 0;
}

//*********************************************************
// Helper for checking Nsight Aftermath failures.
//

// Exception for Nsight Aftermath failures
class AftermathException : public std::runtime_error
{
public:
    AftermathException(GFSDK_Aftermath_Result result)
        : std::runtime_error(GetErrorMessage(result))
        , m_result(result)
    {
    }

    AftermathException Error() const
    {
        return m_result;
    }

    static std::string  GetErrorMessage(GFSDK_Aftermath_Result result)
    {
        switch (result)
        {
        case GFSDK_Aftermath_Result_FAIL_DriverVersionNotSupported:
            return "Unsupported driver version - requires at least an NVIDIA R435 display driver.";
        case GFSDK_Aftermath_Result_FAIL_D3dDllInterceptionNotSupported:
            return "Aftermath is incompatible with D3D API interception, such as PIX or Nsight Graphics.";
        default:
            return "Aftermath Error 0x" + std::to_hex_string(result);
        }
    }

private:
    const GFSDK_Aftermath_Result m_result;
};

// Helper macro for checking Nsight Aftermath results and throwing exception
// in case of a failure.
#define AFTERMATH_CHECK_ERROR(FC)                                                                       \
[&]() {                                                                                                 \
    GFSDK_Aftermath_Result _result = FC;                                                                \
    if (!GFSDK_Aftermath_SUCCEED(_result))                                                              \
    {                                                                                                   \
        MessageBoxA(0, AftermathException::GetErrorMessage(_result).c_str(), "Aftermath Error", MB_OK); \
        throw AftermathException(_result);                                                              \
    }                                                                                                   \
}()

