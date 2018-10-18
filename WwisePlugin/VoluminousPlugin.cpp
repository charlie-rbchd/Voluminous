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

#include "VoluminousPlugin.h"
#include "resource.h"
#include "PluginProcessorProxy.h"

#include "../VoluminousConfig.h"
#include "../JucePlugin/PluginEditor.h"
#include "../SoundEnginePlugin/VoluminousFXFactory.h"

// =============================================================================
static int numInstances = 0;

VoluminousPlugin::VoluminousPlugin() : propertySet (nullptr) { ++numInstances; }
VoluminousPlugin::~VoluminousPlugin() {}

void VoluminousPlugin::Destroy()
{
    delete this;

    if (--numInstances == 0)
    {
        for (int i = 20; --i >= 0;)
            MessageManager::getInstance()->runDispatchLoopUntil (1);

        shutdownJuce_GUI();
    }
}

// =============================================================================
HINSTANCE VoluminousPlugin::GetResourceHandle() const
{
    return GetModuleHandle (L"Voluminous");
}

bool VoluminousPlugin::WindowProc (AK::Wwise::IAudioPlugin::eDialog dialog, HWND nativeHandle, UINT message, WPARAM wparam, LPARAM lparam, LRESULT& result)
{
    switch (message)
    {
    case WM_INITDIALOG:
    {
        container.reset(new AudioProcessorEditorContainer(*this));
        container->setOpaque (true);
        container->setVisible (true);
        container->addToDesktop (0, nativeHandle);

        const auto* editor = dynamic_cast<VoluminousAudioProcessorEditor*> (container->getEditor());

        proxy.reset(new AudioProcessorPropertySetProxy(propertySet, { editor->masterDial }));
        addListener (proxy.get());
        proxy->audioProcessorAttached (this);
    }
    break;
    case WM_DESTROY:
    {
        removeListener (proxy.get());
        proxy = nullptr;

        container->removeFromDesktop();
        container = nullptr;
    }
    break;
    }

    result = 0;
    return false;
}

bool VoluminousPlugin::GetDialog (AK::Wwise::IAudioPlugin::eDialog dialog, UINT& dialogId, AK::Wwise::PopulateTableItem*& table) const
{
    if (dialog == AK::Wwise::IAudioPlugin::SettingsDialog)
    {
        dialogId = IDD_PLUGIN_SETTINGS;
        return true;
    }

    return false;
}

// =============================================================================
void VoluminousPlugin::SetPluginPropertySet (AK::Wwise::IPluginPropertySet* propertySet_)
{
    propertySet = propertySet_;
}

void VoluminousPlugin::NotifyPropertyChanged (const GUID& platformId, LPCWSTR propertyName)
{
    if (propertyName == VoluminousConfig::parameters[0].name)
        proxy->propertySetParameterChanged (this, 0);
}

bool VoluminousPlugin::GetBankParameters (const GUID& platformId, AK::Wwise::IWriteData* dataWriter) const
{
    VARIANT value;
    VariantInit (&value);
    propertySet->GetValue (platformId, VoluminousConfig::parameters[0].name, value);
    dataWriter->WriteReal32 (value.fltVal);

    return true;
}
