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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

// =============================================================================
namespace AK { namespace Wwise { class IPluginPropertySet; } }

// =============================================================================
class AudioProcessorPropertySetProxy  : public AudioProcessorListener
{
public:
    AudioProcessorPropertySetProxy (AK::Wwise::IPluginPropertySet* params, std::initializer_list<Slider*> controls);
    virtual ~AudioProcessorPropertySetProxy();

    // =========================================================================
    void audioProcessorAttached (AudioProcessor* processor);
    void audioProcessorChanged (AudioProcessor* processor) override;
    void audioProcessorParameterChanged (AudioProcessor* processor, int parameterIndex, float newValue) override;
    void audioProcessorParameterChangeGestureBegin (AudioProcessor* processor, int parameterIndex) override;
    void audioProcessorParameterChangeGestureEnd (AudioProcessor* processor, int parameterIndex) override;

    // =========================================================================
    void propertySetParameterChanged (AudioProcessor* processor, int parameterIndex);

private:
    AK::Wwise::IPluginPropertySet* propertySet;
    Array<Slider*> controls;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioProcessorPropertySetProxy)
};
