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

//==============================================================================
VoluminousAudioProcessorEditor::VoluminousAudioProcessorEditor (VoluminousAudioProcessor& processor)
    : AudioProcessorEditor (&processor),
      slaveDials ({ &leftSmallDial, &leftMediumDial, &leftTopLargeDial, &leftBottomLargeDial,
                    &centerLargeDial, &centerBottomLargeDial,
                    &rightTopLargeDial, &rightBottomLargeDial, &rightMediumDial, &rightSmallDial }),
      masterDial (&centerTopLargeDial)
{
    masterDial->setColour (Slider::ColourIds::thumbColourId, Colours::white);
    masterDial->setSliderStyle (Slider::Rotary);
    masterDial->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);

    if (auto* param = dynamic_cast<AudioParameterFloat*> (processor.getParameters().getFirst()))
    {
        masterDial->setRange (param->range.start, param->range.end);
        masterDial->setValue (*param);

        masterDial->onValueChange = [this, param] { *param = (float) masterDial->getValue(); };
        masterDial->onDragStart   = [this, param] { param->beginChangeGesture(); };
        masterDial->onDragEnd     = [this, param] { param->endChangeGesture(); };

        startTimer (16);
    }
    else
    {
        masterDial->setEnabled (false);
    }

    addAndMakeVisible (masterDial);

    for (auto* dial : slaveDials)
    {
        dial->setSliderStyle (Slider::Rotary);
        dial->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        dial->setRange (masterDial->getRange().getStart(), masterDial->getRange().getEnd());
        dial->setValue (masterDial->getValue());
        dial->setEnabled (false);

        addAndMakeVisible (dial);
    }

    setSize (400, 300);
}

VoluminousAudioProcessorEditor::~VoluminousAudioProcessorEditor()
{
    stopTimer();
    removeAllChildren();
}

//==============================================================================
void VoluminousAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);
}

void VoluminousAudioProcessorEditor::resized()
{
    const Point<int> center (getWidth() / 2, getHeight() / 2);

    constexpr int smallDialOffset = smallDialRadius / 2;
    constexpr int mediumDialOffset = mediumDialRadius / 2;
    constexpr int largeDialOffset = largeDialRadius / 2;

    leftSmallDial.setBounds (
        center.x - largeDialRadius - mediumDialRadius - smallDialRadius - smallDialOffset,
        center.y - smallDialOffset,
        smallDialRadius,
        smallDialRadius);

    leftMediumDial.setBounds (
        center.x - largeDialRadius - mediumDialRadius - mediumDialOffset,
        center.y - mediumDialOffset,
        mediumDialRadius,
        mediumDialRadius);

    leftTopLargeDial.setBounds (
        center.x - largeDialRadius - largeDialOffset,
        center.y - largeDialRadius,
        largeDialRadius,
        largeDialRadius);

    leftBottomLargeDial.setBounds (
        center.x - largeDialRadius - largeDialOffset,
        center.y,
        largeDialRadius,
        largeDialRadius);

    centerTopLargeDial.setBounds (
        center.x - largeDialOffset,
        center.y - largeDialRadius - largeDialOffset,
        largeDialRadius,
        largeDialRadius);

    centerLargeDial.setBounds (
        center.x - largeDialOffset,
        center.y - largeDialOffset,
        largeDialRadius,
        largeDialRadius);

    centerBottomLargeDial.setBounds (
        center.x - largeDialOffset,
        center.y + largeDialOffset,
        largeDialRadius,
        largeDialRadius);

    rightTopLargeDial.setBounds (
        center.x + largeDialOffset,
        center.y - largeDialRadius,
        largeDialRadius,
        largeDialRadius);

    rightBottomLargeDial.setBounds (
        center.x + largeDialOffset,
        center.y,
        largeDialRadius,
        largeDialRadius);

    rightMediumDial.setBounds (
        center.x + largeDialRadius + mediumDialOffset,
        center.y - mediumDialOffset,
        mediumDialRadius,
        mediumDialRadius);

    rightSmallDial.setBounds (
        center.x + largeDialRadius + mediumDialRadius + smallDialOffset,
        center.y - smallDialOffset,
        smallDialRadius,
        smallDialRadius);
}

//==============================================================================
void VoluminousAudioProcessorEditor::timerCallback()
{
    const auto masterValue = masterDial->getValue();

    for (auto* dial : slaveDials)
        dial->setValue(masterValue);
}
