
#include "CompressorBandControls.h"


CompressorBandControls::CompressorBandControls(juce::AudioProcessorValueTreeState& apv) : apvts(apv),
attackSlider(nullptr, "ms", "ATTACK"),
releaseSlider(nullptr, "ms", "RELEASE"),
thresholdSlider(nullptr, "dB", "THRESHOLD"),
ratioSlider(nullptr, "")
    {
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(thresholdSlider);
    addAndMakeVisible(ratioSlider);
        
        bypassButton.addListener(this);
        soloButton.addListener(this);
        muteButton.addListener(this);
        
    bypassButton.setName("X");
    soloButton.setName("S");
    muteButton.setName("M");
        
    addAndMakeVisible(bypassButton);
    addAndMakeVisible(muteButton);
    addAndMakeVisible(soloButton);
            
    lowBand.setName("Low");
    midBand.setName("Mid");
    highBand.setName("High");
    
    lowBand.setRadioGroupId(1);
    midBand.setRadioGroupId(1);
    highBand.setRadioGroupId(1);
    


    auto buttonSwitcher = [safePtr = this->safePtr](){
        if(auto* c = safePtr.getComponent()){
            c->updateAttachments();
        }
    };
    
    lowBand.onClick = buttonSwitcher;
    midBand.onClick = buttonSwitcher;
    highBand.onClick = buttonSwitcher;
    
    lowBand.setToggleState(true, juce::NotificationType::dontSendNotification);
    
    updateAttachments();
    
    addAndMakeVisible(lowBand);
    addAndMakeVisible(midBand);
    addAndMakeVisible(highBand);
}

CompressorBandControls::~CompressorBandControls() {
    bypassButton.removeListener(this);
    soloButton.removeListener(this);
    muteButton.removeListener(this);

}
void CompressorBandControls::resized() {
    
    using namespace juce;
    auto bounds = getLocalBounds().reduced(5);
    
    auto createBandButtonControlBox = [](std::vector<Component*> comps) {
        FlexBox flexbox;
        flexbox.flexDirection = FlexBox::Direction::column;
        flexbox.flexWrap = FlexBox::Wrap::noWrap;
        
        auto spacer = FlexItem().withHeight(2);
        
        for(auto* comp : comps) {
            flexbox.items.add(spacer);
            flexbox.items.add(FlexItem(*comp).withFlex(1.f));
        }
        
        flexbox.items.add(spacer);
        
        return flexbox;
    };
    
    auto bandButtonControlBox = createBandButtonControlBox({&bypassButton, &soloButton, &muteButton});
    auto bandSelectControlBox = createBandButtonControlBox({&lowBand, &midBand, &highBand});
    
    FlexBox flexbox;
    flexbox.flexDirection = FlexBox::Direction::row;
    flexbox.flexWrap = FlexBox::Wrap::noWrap;
    
    auto spacer = FlexItem().withWidth(4);
//    auto endCap = FlexItem().withWidth(6);
    
    flexbox.items.add(spacer);
    flexbox.items.add(FlexItem(bandSelectControlBox).withWidth(50));
    flexbox.items.add(spacer);
    flexbox.items.add(FlexItem(attackSlider).withFlex(1.f));
    flexbox.items.add(spacer);
    flexbox.items.add(FlexItem(releaseSlider).withFlex(1.f));
    flexbox.items.add(spacer);
    flexbox.items.add(FlexItem(thresholdSlider).withFlex(1.f));
    flexbox.items.add(spacer);
    flexbox.items.add(FlexItem(ratioSlider).withFlex(1.f));
    flexbox.items.add(spacer);
    flexbox.items.add(FlexItem(bandButtonControlBox).withWidth(30));
    
    flexbox.performLayout(bounds);

}



void CompressorBandControls::paint(juce::Graphics &g) {
    auto bounds = getLocalBounds();
    drawModuleBackground(g, bounds);
}

void CompressorBandControls::buttonClicked(juce::Button *button) {
    //if muted or bypassed prevent update
    updateSliderEnablements();
    // update the non-clicked buttons
    updateSoloMuteBypassToggleStates(*button);
}

void CompressorBandControls::updateSliderEnablements() {
    auto disabled = muteButton.getToggleState() || bypassButton.getToggleState();
    attackSlider.setEnabled(!disabled);
    releaseSlider.setEnabled(!disabled);
    thresholdSlider.setEnabled(!disabled);
    ratioSlider.setEnabled(!disabled);
}

void CompressorBandControls::updateSoloMuteBypassToggleStates(juce::Button &clickedButton) {
    //if solo button clicked
    if(&clickedButton == &soloButton && soloButton.getToggleState()) {
        bypassButton.setToggleState(false, juce::NotificationType::sendNotification);
        muteButton.setToggleState(false, juce::NotificationType::sendNotification);
    } else if(&clickedButton == &muteButton && muteButton.getToggleState()) {
        bypassButton.setToggleState(false, juce::NotificationType::sendNotification);
        soloButton.setToggleState(false, juce::NotificationType::sendNotification);
    }else if(&clickedButton == &bypassButton && bypassButton.getToggleState()) {
        muteButton.setToggleState(false, juce::NotificationType::sendNotification);
        soloButton.setToggleState(false, juce::NotificationType::sendNotification);
    }

    
    
}

void CompressorBandControls::updateAttachments() {
   //find which button clicked
    //which parameter with which button
    enum BandType {
        Low, Mid, High
    };
    
    BandType bandType = [this]() {
        if(lowBand.getToggleState()) return BandType::Low;
        if(midBand.getToggleState()) return BandType::Mid;
        return BandType::High;
    }();
    
    using namespace Params;
    std::vector<Names> names;
    
    switch (bandType) {
            
        case Low:
            names = std::vector<Names>  {
                Names::Attack_Low_Band,
                Names::Release_Low_Band,
                Names::Threshold_Low_Band,
                Names::Ratio_Low_Band,
                Names::Mute_Low_Band,
                Names::Solo_Low_Band,
                Names::Bypassed_Low_Band,
            };
            break;
        case Mid:
            names = std::vector<Names>  {
                Names::Attack_Mid_Band,
                Names::Release_Mid_Band,
                Names::Threshold_Mid_Band,
                Names::Ratio_Mid_Band,
                Names::Mute_Mid_Band,
                Names::Solo_Mid_Band,
                Names::Bypassed_Mid_Band,
            };
            break;
        case High:
            names = std::vector<Names>  {
                Names::Attack_High_Band,
                Names::Release_High_Band,
                Names::Threshold_High_Band,
                Names::Ratio_High_Band,
                Names::Mute_High_Band,
                Names::Solo_High_Band,
                Names::Bypassed_High_Band,
            };
            break;
    }
    enum Pos {
        Attack,
        Release,
        Threshold,
        Ratio,
        Mute,
        Solo,
        Bypass
    };
    
    const auto& params = GetParams();
    
    auto getParamHelper = [&params, &apvts = this->apvts, &names](const auto& pos) -> auto& {
        return getParam(apvts, params, names.at(pos));
    };
    
    attackSliderAttachment.reset();
    releaseSliderAttachment.reset();
    thresholdSliderAttachment.reset();
    ratioSliderAttachment.reset();
    bypassButtonAttachment.reset();
    soloButtonAttachment.reset();
    muteButtonAttachment.reset();
    
    auto& attackParam = getParamHelper(Pos::Attack);
    addLabelPairs(attackSlider.labels, attackParam, "ms");
    attackSlider.changeParam(&attackParam);
    
    auto& releaseParam = getParamHelper(Pos::Release);
    addLabelPairs(releaseSlider.labels, releaseParam, "ms");
    releaseSlider.changeParam(&releaseParam);
    
    auto& thresholdParam = getParamHelper(Pos::Threshold);
    addLabelPairs(thresholdSlider.labels, thresholdParam, "dB");
    thresholdSlider.changeParam(&thresholdParam);
//    auto& ratioParam = getParamHelper(Pos::Ratio);
    
//    auto& bypassParam = getParamHelper(Pos::Bypass);
//    auto& soloParam = getParamHelper(Pos::Solo);
//    auto& muteParam = getParamHelper(Pos::Mute);
    
    auto& ratioParamRap = getParamHelper(Pos::Ratio);
    ratioSlider.labels.clear();
    ratioSlider.labels.add({0.f, "1:1"});
    auto ratioParam = dynamic_cast<juce::AudioParameterChoice*>(&ratioParamRap);
    ratioSlider.labels.add({1.f, juce::String(ratioParam->choices.getReference(ratioParam->choices.size()-1).getIntValue()) + ":1" });
    ratioSlider.changeParam(ratioParam);
    
    auto makeAttachmentHelper = [&params, &apvts = this->apvts](auto& attachment,
                                                  const auto& name,
                                                  auto& slider){
        makeAttachment(attachment, apvts, params, name, slider);
    };
    
    makeAttachmentHelper(attackSliderAttachment, names[Pos::Attack], attackSlider );
    makeAttachmentHelper(releaseSliderAttachment, names[Pos::Release], releaseSlider );
    makeAttachmentHelper(thresholdSliderAttachment , names[Pos::Threshold], thresholdSlider );
    makeAttachmentHelper(ratioSliderAttachment, names[Pos::Ratio], ratioSlider);
    makeAttachmentHelper(bypassButtonAttachment, names[Pos::Bypass], bypassButton);
    makeAttachmentHelper(soloButtonAttachment, names[Pos::Solo], soloButton);
    makeAttachmentHelper(muteButtonAttachment, names[Pos::Mute], muteButton);


}
