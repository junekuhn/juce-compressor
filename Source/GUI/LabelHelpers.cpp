/*
  ==============================================================================

    LaberHelpers.cpp
    Created: 7 Apr 2023 11:49:17am
    Author:  Justin Kuhn

  ==============================================================================
*/

#include "LabelHelpers.h"

template<typename T>
bool truncateKiloValue(T& value) {
    if(value> static_cast<T>(999)) {
        value /= static_cast<T>(1000);
        return true;
    }
    
    return false;
}

juce::String getValString(const juce::RangedAudioParameter& param, bool getLow, juce::String suffix) {
    juce::String str;
    auto val = getLow ? param.getNormalisableRange().start : param.getNormalisableRange().end;
    
    bool useK = truncateKiloValue(val);
    str <<val;
    
    if (useK) str << "k";
    
    str << suffix;
    
    return str;
}
