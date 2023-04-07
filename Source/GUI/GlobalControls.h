
#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "LambdaHelpers.h"
#include "CustomSliders.h"
#include "LabelHelpers.h"
#include "ComponentHelpers.h"

struct GlobalControls : juce::Component {
    GlobalControls(juce::AudioProcessorValueTreeState& apvts);
    void paint(juce::Graphics& g) override;
    
    void resized() override;
private:
    using RSWL = RotarySliderWithLabels;
    std::unique_ptr<RSWL> inGainSlider, lowMidXoverSlider, midHighXoverSlider, outGainSlider;
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> lowMidXoverSliderAttachment,
                                midHighXoverSliderAttachment,
                                inGainSliderAttachment,
                                outGainSliderAttachment;
};
