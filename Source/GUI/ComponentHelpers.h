
/*
  ==============================================================================

    ComponentHelpers.cpp
    Created: 7 Apr 2023 11:52:56am
    Author:  Justin Kuhn

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>

void drawModuleBackground(juce::Graphics& g, juce::Rectangle<int> bounds);

struct Placeholder : juce::Component {
    Placeholder();

    void paint(juce::Graphics& g) override {
        g.fillAll(customColor);
    }

    juce::Colour customColor;

};

