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

  Version: 1.0
  Copyright (c) 2018 Audiokinetic Inc.
*******************************************************************************/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "../VoluminousConfig.h"

VoluminousAudioProcessor::VoluminousAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                       .withOutput ("Output", AudioChannelSet::stereo(), true))
{
    const auto& gainInfo = VoluminousConfig::parameters[0];
    gain = new AudioParameterFloat (gainInfo.name, gainInfo.displayName,
                                    NormalisableRange<float> (gainInfo.minValue, gainInfo.maxValue),
                                    gainInfo.defaultValue);
    addParameter (gain);
}

VoluminousAudioProcessor::~VoluminousAudioProcessor() {}

//==============================================================================
const String VoluminousAudioProcessor::getName() const { return JucePlugin_Name; }

bool VoluminousAudioProcessor::acceptsMidi() const { return false; }
bool VoluminousAudioProcessor::producesMidi() const { return false; }
bool VoluminousAudioProcessor::isMidiEffect() const { return false; }

double VoluminousAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int VoluminousAudioProcessor::getNumPrograms() { return 1; }
int VoluminousAudioProcessor::getCurrentProgram() { return 0; }
void VoluminousAudioProcessor::setCurrentProgram (int index) {}

const String VoluminousAudioProcessor::getProgramName (int index) { return {}; }
void VoluminousAudioProcessor::changeProgramName (int index, const String& newName) {}

//==============================================================================
void VoluminousAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    previousGain = *gain;
}

void VoluminousAudioProcessor::releaseResources() {}
bool VoluminousAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void VoluminousAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    const auto currentGain = gain->get();
    if (currentGain == previousGain)
    {
        buffer.applyGain (currentGain);
    }
    else
    {
        buffer.applyGainRamp (0, buffer.getNumSamples(), previousGain, currentGain);
        previousGain = currentGain;
    }
}

//==============================================================================
bool VoluminousAudioProcessor::hasEditor() const { return true; }
AudioProcessorEditor* VoluminousAudioProcessor::createEditor()
{
    return new VoluminousAudioProcessorEditor (*this);
}

//==============================================================================
void VoluminousAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    MemoryOutputStream (destData, true).writeFloat (*gain);
}

void VoluminousAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    gain->setValueNotifyingHost (MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat());
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VoluminousAudioProcessor();
}
