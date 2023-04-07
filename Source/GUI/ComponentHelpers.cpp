
/*
  ==============================================================================

    ComponentHelpers.h
    Created: 7 Apr 2023 11:52:56am
    Author:  Justin Kuhn

  ==============================================================================
*/

#include "ComponentHelpers.h"


void drawModuleBackground(juce::Graphics& g, juce::Rectangle<int> bounds) {
    
        using namespace juce;
        g.setColour(Colours::blueviolet);
        g.fillAll();
        
        auto localBounds = bounds;
        
        bounds.reduce(3,3);
        g.setColour(Colours::black);
        g.fillRoundedRectangle(bounds.toFloat(), 3);
        
        g.drawRect(localBounds);
    
}

Placeholder::Placeholder() {
    juce::Random r;
    customColor = juce::Colour(r.nextInt(255), r.nextInt(), r.nextInt());
}
