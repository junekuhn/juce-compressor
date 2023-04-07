#include "GlobalControls.h"
GlobalControls::GlobalControls(juce::AudioProcessorValueTreeState& apvts) {
    using namespace Params;
    const auto& params = GetParams();
    
    auto getParamsHelper = [&params, &apvts](const auto& name) -> auto& {
        return getParam(apvts, params, name);
    };
    
    auto& gainInParam = getParamsHelper(Names::Gain_In);
    auto& gainOutParam = getParamsHelper(Names::Gain_Out);
    auto& midHighParam = getParamsHelper(Names::Mid_High_Crossover_Freq);
    auto& lowMidParam = getParamsHelper(Names::Low_Mid_Crossover_Freq);
    
    inGainSlider = std::make_unique<RotarySliderWithLabels>(&gainInParam, "dB", "INPUT TRIM");
    lowMidXoverSlider = std::make_unique<RotarySliderWithLabels>(&lowMidParam, "Hz", "LOW-MID X-OVER");
    midHighXoverSlider = std::make_unique<RotarySliderWithLabels>(&midHighParam, "Hz", "MID_HI X-OVER");
    outGainSlider = std::make_unique<RotarySliderWithLabels>(&gainOutParam, "dB", "OUTPUT TRIM");
    
    auto makeAttachmentHelper = [&params, &apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider){
        makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(inGainSliderAttachment, Names::Gain_In, *inGainSlider);
    makeAttachmentHelper(lowMidXoverSliderAttachment, Names::Low_Mid_Crossover_Freq, *lowMidXoverSlider);
    makeAttachmentHelper(outGainSliderAttachment, Names::Mid_High_Crossover_Freq, *outGainSlider);
    
    addLabelPairs(inGainSlider->labels, gainInParam, "dB");
    addLabelPairs(lowMidXoverSlider->labels, lowMidParam, "Hz");
    addLabelPairs(midHighXoverSlider->labels, midHighParam, "Hz");
    addLabelPairs(outGainSlider->labels, gainOutParam, "dB");
    
    addAndMakeVisible(*inGainSlider);
    addAndMakeVisible(*lowMidXoverSlider);
    addAndMakeVisible(*midHighXoverSlider);
    addAndMakeVisible(*outGainSlider);
}

void GlobalControls::paint(juce::Graphics &g) {
    auto bounds = getLocalBounds();
    drawModuleBackground(g, bounds);
}

void GlobalControls::resized() {
    using namespace juce;
    auto bounds = getLocalBounds().reduced(5);
    
    FlexBox flexbox;
    flexbox.flexDirection = FlexBox::Direction::row;
    flexbox.flexWrap = FlexBox::Wrap::noWrap;
    
    auto spacer = FlexItem().withWidth(4);
    auto endCap = FlexItem().withWidth(6);
    
    flexbox.items.add(endCap);
    flexbox.items.add(FlexItem(*inGainSlider).withFlex(1.f));
    flexbox.items.add(spacer);
    flexbox.items.add(FlexItem(*lowMidXoverSlider).withFlex(1.f));
    flexbox.items.add(spacer);
    flexbox.items.add(FlexItem(*midHighXoverSlider).withFlex(1.f));
    flexbox.items.add(spacer);
    flexbox.items.add(FlexItem(*outGainSlider).withFlex(1.f));
    flexbox.items.add(endCap);
    
    flexbox.performLayout(bounds);
}
