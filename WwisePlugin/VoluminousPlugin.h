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

#include "PluginEditorContainer.h"

#include "../JucePlugin/PluginProcessor.h"
#include <windows.h>
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#include <atlstr.h>
#include <AK/Wwise/AudioPlugin.h>

#include <memory>

// =============================================================================
class AudioProcessorEditorContainer;
class AudioProcessorPropertySetProxy;

// =============================================================================
class VoluminousPlugin  : public AK::Wwise::DefaultAudioPluginImplementation,
                          public VoluminousAudioProcessor
{
public:
    VoluminousPlugin();

    ~VoluminousPlugin();
    void Destroy() override;

    // =========================================================================
    HINSTANCE GetResourceHandle() const override;
    bool WindowProc (AK::Wwise::IAudioPlugin::eDialog dialog, HWND nativeHandle, UINT message, WPARAM wparam, LPARAM lparam, LRESULT& result) override;
    bool GetDialog (AK::Wwise::IAudioPlugin::eDialog dialog, UINT& dialogId, AK::Wwise::PopulateTableItem*& table) const override;

    // =========================================================================
    void SetPluginPropertySet (AK::Wwise::IPluginPropertySet* params) override;
    void NotifyPropertyChanged (const GUID& platformId, LPCWSTR propertyName) override;

    bool GetBankParameters (const GUID& platformId, AK::Wwise::IWriteData* dataWriter) const override;

private:
    AK::Wwise::IPluginPropertySet* propertySet;

    std::unique_ptr<AudioProcessorPropertySetProxy> proxy;
    std::unique_ptr<AudioProcessorEditorContainer> container;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoluminousPlugin)
};
