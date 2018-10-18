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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
class VoluminousAudioProcessorEditor  : public AudioProcessorEditor,
                                        private Timer
{
public:
    VoluminousAudioProcessorEditor (VoluminousAudioProcessor&);
    virtual ~VoluminousAudioProcessorEditor();

    //==========================================================================
    enum { smallDialRadius = 40, mediumDialRadius = 55, largeDialRadius = 70 };

    void paint (Graphics&) override;
    void resized() override;

    //==========================================================================
    Array<Slider*> slaveDials;
    Slider* masterDial;

private:
    Slider leftSmallDial;

    Slider leftMediumDial;

    Slider leftTopLargeDial;
    Slider leftBottomLargeDial;

    Slider centerTopLargeDial;
    Slider centerLargeDial;
    Slider centerBottomLargeDial;

    Slider rightTopLargeDial;
    Slider rightBottomLargeDial;

    Slider rightMediumDial;

    Slider rightSmallDial;

private:
    //==========================================================================
    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoluminousAudioProcessorEditor)
};
