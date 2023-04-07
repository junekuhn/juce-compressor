/*
  ==============================================================================

    LabelHelpers.h
    Created: 7 Apr 2023 11:48:18am
    Author:  Justin Kuhn

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

juce::String getValString(const juce::RangedAudioParameter& param, bool getLow, juce::String suffix);

template<typename Labels, typename ParamType, typename SuffixType>
void addLabelPairs(Labels& labels, const ParamType& param, const SuffixType& suffix) {
    labels.clear();
    labels.add({0.f, getValString(param, true, suffix)});
    labels.add({1.f, getValString(param, false, suffix)});
}

