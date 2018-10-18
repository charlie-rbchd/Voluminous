/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Apache License Usage

Alternatively, this file may be used under the Apache License, Version 2.0 (the
"Apache License"); you may not use this file except in compliance with the
Apache License. You may obtain a copy of the Apache License at
http://www.apache.org/licenses/LICENSE-2.0.

Unless required by applicable law or agreed to in writing, software distributed
under the Apache License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
OR CONDITIONS OF ANY KIND, either express or implied. See the Apache License for
the specific language governing permissions and limitations under the License.

  Version: <VERSION>  Build: <BUILDNUMBER>
  Copyright (c) <COPYRIGHTYEAR> Audiokinetic Inc.
*******************************************************************************/

#include "VoluminousFXParams.h"
#include "../VoluminousConfig.h"

#include <AK/Tools/Common/AkBankReadHelpers.h>

//==============================================================================
VoluminousFXParams::VoluminousFXParams() : gain(0.0f) {}
VoluminousFXParams::VoluminousFXParams (const VoluminousFXParams& params)
{
    gain = params.gain;
}

AK::IAkPluginParam* VoluminousFXParams::Clone (AK::IAkPluginMemAlloc* allocator)
{
    return AK_PLUGIN_NEW (allocator, VoluminousFXParams (*this));
}

VoluminousFXParams::~VoluminousFXParams() {}

//==============================================================================
AKRESULT VoluminousFXParams::Init (AK::IAkPluginMemAlloc* allocator, const void* paramsBlock, AkUInt32 blockSize)
{
    if (blockSize == 0)
    {
        gain = VoluminousConfig::parameters[0].defaultValue;
        return AK_Success;
    }

    return SetParamsBlock (paramsBlock, blockSize);
}

AKRESULT VoluminousFXParams::Term (AK::IAkPluginMemAlloc* allocator)
{
    AK_PLUGIN_DELETE (allocator, this);
    return AK_Success;
}

//==============================================================================
AKRESULT VoluminousFXParams::SetParamsBlock (const void* paramsBlock, AkUInt32 blockSize)
{
    AKRESULT result = AK_Success;
    AkUInt8* block = (AkUInt8*) paramsBlock;

    gain = READBANKDATA(AkReal32, block, blockSize);
    CHECKBANKDATASIZE(blockSize, result);

    return result;
}

AKRESULT VoluminousFXParams::SetParam (AkPluginParamID identifier, const void* value, AkUInt32 size)
{
    if (identifier == VoluminousConfig::parameters[0].id)
    {
        gain = *((AkReal32*) value);
        return AK_Success;
    }

    return AK_InvalidParameter;
}
