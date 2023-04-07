
#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "CustomSliders.h"
#include "ComponentHelpers.h"
#include "LambdaHelpers.h"
#include "LabelHelpers.h"

struct CompressorBandControls : juce::Component, juce::Button::Listener {
    CompressorBandControls(juce::AudioProcessorValueTreeState& apvts);
    ~CompressorBandControls() override;
    void resized() override;
    void paint(juce::Graphics& g) override;
    void updateAttachments();
    void updateSliderEnablements();
    
    void updateSoloMuteBypassToggleStates(juce::Button& button);
    
    void buttonClicked(juce::Button* button) override;
private:
    juce::AudioProcessorValueTreeState& apvts;
    
    RotarySliderWithLabels attackSlider, releaseSlider, thresholdSlider;
    RatioSlider ratioSlider;
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<Attachment> attackSliderAttachment,
                                releaseSliderAttachment,
                                thresholdSliderAttachment,
                                ratioSliderAttachment;
    juce::ToggleButton bypassButton, soloButton, muteButton, lowBand, midBand, highBand;
    using BtnAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<BtnAttachment> bypassButtonAttachment,
                                muteButtonAttachment,
    soloButtonAttachment;
    
    juce::Component::SafePointer<CompressorBandControls> safePtr {this};
};
