/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Robotic_Drummer_Interface_MockupAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer, private juce::TextButton::Listener, private juce::Slider::Listener
{
public:
    Robotic_Drummer_Interface_MockupAudioProcessorEditor (Robotic_Drummer_Interface_MockupAudioProcessor&);
    ~Robotic_Drummer_Interface_MockupAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Robotic_Drummer_Interface_MockupAudioProcessor& audioProcessor;
    
    //Look and Feel
    juce::LookAndFeel_V4 otherLookAndFeel;
    
    //GUI Label
    juce::Label guiLabel;
    juce::Label guiContent;
    
    //Row Labels
    juce::Label firstLabel;
    juce::Label secondLabel;
    juce::Label thirdLabel;
    juce::Label fourthLabel;
    
    //Universal Knob
    juce::Slider universalKnob;
    
    //Universal Button
    juce::TextButton universalButton;
    
    //Hi hat buttons
    juce::TextButton firstHiHat;
    juce::TextButton secondHiHat;
    juce::TextButton thirdHiHat;
    juce::TextButton fourthHiHat;
    juce::TextButton fifthHiHat;
    juce::TextButton sixthHiHat;
    juce::TextButton seventhHiHat;
    juce::TextButton eighthHiHat;
    
    //Snare buttons
    juce::TextButton firstSnare;
    juce::TextButton secondSnare;
    juce::TextButton thirdSnare;
    juce::TextButton fourthSnare;
    juce::TextButton fifthSnare;
    juce::TextButton sixthSnare;
    juce::TextButton seventhSnare;
    juce::TextButton eighthSnare;
    
    //Tom buttons
    juce::TextButton firstTom;
    juce::TextButton secondTom;
    juce::TextButton thirdTom;
    juce::TextButton fourthTom;
    juce::TextButton fifthTom;
    juce::TextButton sixthTom;
    juce::TextButton seventhTom;
    juce::TextButton eighthTom;
    
    //Kick buttons
    juce::TextButton firstKick;
    juce::TextButton secondKick;
    juce::TextButton thirdKick;
    juce::TextButton fourthKick;
    juce::TextButton fifthKick;
    juce::TextButton sixthKick;
    juce::TextButton seventhKick;
    juce::TextButton eighthKick;
    
    juce::RectangleList<float> beatAreas;
    
    bool tempoShown = true;
    int lastButtonPressed = -1;

    void buttonClicked (juce::Button*) override;
    void sliderValueChanged (juce::Slider* slider) override;
    
    juce::Rectangle<int> getButtonArea(juce::Rectangle<int> column, float columnWidth, float rowHeight, float border);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Robotic_Drummer_Interface_MockupAudioProcessorEditor)
};
