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

#include "VoluminousFX.h"
#include "../VoluminousConfig.h"

#include <AK/AkWwiseSDKVersion.h>
#include <AK/DSP/AkApplyGain.h>

//==============================================================================
AK::IAkPlugin* CreateVoluminousFX (AK::IAkPluginMemAlloc* allocator)
{
    return AK_PLUGIN_NEW (allocator, VoluminousFX());
}

AK::IAkPluginParam* CreateVoluminousFXParams (AK::IAkPluginMemAlloc* allocator)
{
    return AK_PLUGIN_NEW (allocator, VoluminousFXParams());
}

AK_IMPLEMENT_PLUGIN_FACTORY (VoluminousFX, AkPluginTypeEffect, VoluminousConfig::companyId, VoluminousConfig::pluginId)

//==============================================================================
VoluminousFX::VoluminousFX() : sharedParams (nullptr), currentGain (0.0f) {}
VoluminousFX::~VoluminousFX() {}

//==============================================================================
AKRESULT VoluminousFX::Init (AK::IAkPluginMemAlloc* allocator, AK::IAkEffectPluginContext* context, AK::IAkPluginParam* params, AkAudioFormat& format)
{
    sharedParams = (VoluminousFXParams*) params;
    currentGain = sharedParams->gain;

    return AK_Success;
}

AKRESULT VoluminousFX::Term (AK::IAkPluginMemAlloc* allocator)
{
    AK_PLUGIN_DELETE (allocator, this);
    return AK_Success;
}

//==============================================================================
AKRESULT VoluminousFX::GetPluginInfo (AkPluginInfo& pluginInfo)
{
    pluginInfo.eType = AkPluginTypeEffect;
    pluginInfo.bIsInPlace = true;
    pluginInfo.uBuildVersion = AK_WWISESDK_VERSION_COMBINED;
    return AK_Success;
}

//==============================================================================
void VoluminousFX::Execute (AkAudioBuffer* buffer)
{
    AK::DSP::ApplyGain (buffer, currentGain, sharedParams->gain, false);
    currentGain = sharedParams->gain;
}

AKRESULT VoluminousFX::Reset() { return AK_Success; }
AKRESULT VoluminousFX::TimeSkip (AkUInt32 numFrames) { return AK_DataReady; }
