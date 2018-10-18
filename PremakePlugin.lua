--[[----------------------------------------------------------------------------
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
------------------------------------------------------------------------------]]

if not _AK_PREMAKE then
    error('You must use the custom Premake5 scripts by adding the following parameter: --scripts="Scripts\\Premake"', 1)
end

local Plugin = {}
Plugin.name = "Voluminous"
Plugin.sdk = {}
Plugin.sdk.static = {}
Plugin.sdk.shared = {}
Plugin.authoring = {}

-- SDK STATIC PLUGIN SECTION
Plugin.sdk.static.includedirs =
{
}
Plugin.sdk.static.files =
{
    "../VoluminousConfig.h",

    "VoluminousFX.cpp",
    "VoluminousFX.h",
    "VoluminousFXParams.cpp",
    "VoluminousFXParams.h",
}
Plugin.sdk.static.excludes =
{
}
Plugin.sdk.static.links =
{
}
Plugin.sdk.static.libsuffix = "FX"
Plugin.sdk.static.libdirs =
{
}
Plugin.sdk.static.defines =
{
}

-- SDK SHARED PLUGIN SECTION
Plugin.sdk.shared.includedirs =
{
}
Plugin.sdk.shared.files =
{
    "VoluminousFXShared.cpp",
    "VoluminousFXFactory.h",
}
Plugin.sdk.shared.excludes =
{
}
Plugin.sdk.shared.links =
{
}
Plugin.sdk.shared.libdirs =
{
}
Plugin.sdk.shared.defines =
{
}

-- AUTHORING PLUGIN SECTION
Plugin.authoring.includedirs =
{
    "../JuceLibraryCode",
    "../JuceModules",
}
Plugin.authoring.files =
{
    "../JuceLibraryCode/include_juce_*.cpp",
    "../JuceLibraryCode/include_juce_*.h",

    "../JucePlugin/PluginEditor.cpp",
    "../JucePlugin/PluginEditor.h",
    "../JucePlugin/PluginProcessor.cpp",
    "../JucePlugin/PluginProcessor.h",

    "../VoluminousConfig.h",

    "PluginProcessorProxy.cpp",
    "PluginProcessorProxy.h",
    "PluginEditorContainer.cpp",
    "PluginEditorContainer.h",

    "VoluminousPlugin.cpp",
    "VoluminousPlugin.h",
    "Voluminous.cpp",
    "Voluminous.rc",
    "Voluminous.def",
    "Voluminous.xml",

    "resource.h",
}
Plugin.authoring.excludes =
{
    "../JuceLibraryCode/include_juce_audio_plugin_client_*.cpp",
    "../JuceLibraryCode/include_juce_audio_plugin_client_*.h",
}
Plugin.authoring.links =
{
}
Plugin.authoring.libdirs =
{
}
Plugin.authoring.defines =
{
}
Plugin.authoring.custom = function()
    buildoptions { "/bigobj" }
end

return Plugin
