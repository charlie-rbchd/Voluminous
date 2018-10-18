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

#include "PluginProcessorProxy.h"
#include "../VoluminousConfig.h"

#include <windows.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#include <atlstr.h>
#include <AK/Wwise/AudioPlugin.h>

#include <string>

// =============================================================================
AudioProcessorPropertySetProxy::AudioProcessorPropertySetProxy (AK::Wwise::IPluginPropertySet* propertySet, std::initializer_list<Slider*> controls)
    : propertySet (propertySet),
      controls (controls)
{
}
AudioProcessorPropertySetProxy::~AudioProcessorPropertySetProxy() {}

// =============================================================================
void AudioProcessorPropertySetProxy::audioProcessorAttached (AudioProcessor* processor)
{
    for (int i = 0; i < controls.size(); ++i)
        propertySetParameterChanged (processor, i);
}

void AudioProcessorPropertySetProxy::audioProcessorChanged (AudioProcessor* processor) {}
void AudioProcessorPropertySetProxy::audioProcessorParameterChanged (AudioProcessor* processor, int parameterIndex, float newValue)
{
    VARIANT varValue;
    VariantInit (&varValue);
    varValue.vt = VT_R4;
    varValue.fltVal = newValue;
    propertySet->SetValue (propertySet->GetCurrentPlatform(), VoluminousConfig::parameters[parameterIndex].name, varValue);
}

void AudioProcessorPropertySetProxy::audioProcessorParameterChangeGestureBegin (AudioProcessor* processor, int parameterIndex)
{
    if (auto* undo = propertySet->GetUndoManager())
        undo->OpenComplex();
}

void AudioProcessorPropertySetProxy::audioProcessorParameterChangeGestureEnd (AudioProcessor* processor, int parameterIndex)
{
    if (auto* undo = propertySet->GetUndoManager())
    {
        std::wstring text (L"Change ");
        text += VoluminousConfig::parameters[parameterIndex].displayName;
        undo->CloseComplex (text.c_str());
    }
}

// =============================================================================
void AudioProcessorPropertySetProxy::propertySetParameterChanged (AudioProcessor* processor, int parameterIndex)
{
    VARIANT value;
    VariantInit (&value);
    if (propertySet->GetValue (propertySet->GetCurrentPlatform(), VoluminousConfig::parameters[parameterIndex].name, value))
        controls[parameterIndex]->setValue (value.fltVal);
}
