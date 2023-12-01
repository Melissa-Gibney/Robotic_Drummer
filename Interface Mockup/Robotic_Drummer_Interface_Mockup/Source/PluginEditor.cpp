/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Robotic_Drummer_Interface_MockupAudioProcessorEditor::Robotic_Drummer_Interface_MockupAudioProcessorEditor (Robotic_Drummer_Interface_MockupAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 400);
    
    juce::Colour buttonOnColor(/*0xFF7689CF*/juce::Colours::red);
    juce::Colour buttonOffColor(/*0xFF9BA5C9*/juce::Colours::lightgrey);
    juce::Colour buttonPressedColor(/*0xFF818599*/juce::Colours::grey);
    
    //Set up the colors of the buttons
    otherLookAndFeel.setColour(juce::Slider::thumbColourId, buttonOnColor);
    
    //GUI Label Setup
    addAndMakeVisible(guiLabel);
    guiLabel.setText("Tempo", juce::dontSendNotification);
    guiLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    guiLabel.setJustificationType(juce::Justification::centred);
    
    //GUI Content Label Setup
    addAndMakeVisible(guiContent);
    guiContent.setText(juce::String(audioProcessor.tempo), juce::dontSendNotification);
    guiContent.setFont(juce::Font(16.0f, juce::Font::plain));
    guiContent.setJustificationType(juce::Justification::centred);
    
    //Timer Code
    startTimer(60000/audioProcessor.tempo);
    
    //Universal Knob Setup
    addAndMakeVisible(universalKnob);
    universalKnob.setSliderStyle(juce::Slider::Rotary);
    universalKnob.setNumDecimalPlacesToDisplay(2);
    universalKnob.setRange(0, 500);
    universalKnob.setValue(120);
    universalKnob.setTextValueSuffix("");
    universalKnob.setTextBoxStyle(universalKnob.NoTextBox, true, 0, 0);
    universalKnob.setColour(0x1001300, buttonOffColor);
    universalKnob.onValueChange = [this]()
    {
        if(tempoShown)
        {
            audioProcessor.tempo = universalKnob.getValue();
            guiContent.setText(juce::String(audioProcessor.tempo), juce::NotificationType::dontSendNotification);
        }
        else
        {
            switch(lastButtonPressed)
            {
                case 1:
                {
                    audioProcessor.firstHiHatVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.firstHiHatVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 2:
                {
                    audioProcessor.secondHiHatVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.secondHiHatVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 3:
                {
                    audioProcessor.thirdHiHatVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.thirdHiHatVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 4:
                {
                    audioProcessor.fourthHiHatVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.fourthHiHatVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 5:
                {
                    audioProcessor.fifthHiHatVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.fifthHiHatVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 6:
                {
                    audioProcessor.sixthHiHatVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.sixthHiHatVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 7:
                {
                    audioProcessor.seventhHiHatVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.seventhHiHatVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 8:
                {
                    audioProcessor.eighthHiHatVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.eighthHiHatVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 9:
                {
                    audioProcessor.firstSnareVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.firstSnareVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 10:
                {
                    audioProcessor.secondSnareVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.secondSnareVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 11:
                {
                    audioProcessor.thirdSnareVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.thirdSnareVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 12:
                {
                    audioProcessor.fourthSnareVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.fourthSnareVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 13:
                {
                    audioProcessor.fifthSnareVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.fifthSnareVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 14:
                {
                    audioProcessor.sixthSnareVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.sixthSnareVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 15:
                {
                    audioProcessor.seventhSnareVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.seventhSnareVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 16:
                {
                    audioProcessor.eighthSnareVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.eighthSnareVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 17:
                {
                    audioProcessor.firstTomVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.firstTomVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 18:
                {
                    audioProcessor.secondTomVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.secondTomVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 19:
                {
                    audioProcessor.thirdTomVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.thirdTomVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 20:
                {
                    audioProcessor.fourthTomVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.fourthTomVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 21:
                {
                    audioProcessor.fifthTomVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.fifthTomVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 22:
                {
                    audioProcessor.sixthTomVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.sixthTomVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 23:
                {
                    audioProcessor.seventhTomVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.seventhTomVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 24:
                {
                    audioProcessor.eighthTomVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.eighthTomVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 25:
                {
                    audioProcessor.firstKickVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.firstKickVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 26:
                {
                    audioProcessor.secondKickVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.secondKickVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 27:
                {
                    audioProcessor.thirdKickVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.thirdKickVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 28:
                {
                    audioProcessor.fourthKickVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.fourthKickVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 29:
                {
                    audioProcessor.fifthKickVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.fifthKickVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 30:
                {
                    audioProcessor.sixthKickVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.sixthKickVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 31:
                {
                    audioProcessor.seventhKickVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.seventhKickVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                case 32:
                {
                    audioProcessor.eighthKickVelocity = universalKnob.getValue();
                    guiContent.setText(juce::String(audioProcessor.eighthKickVelocity), juce::NotificationType::dontSendNotification);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    };
    
    //Universal Button Setup
    universalButton.setClickingTogglesState(false);
    universalButton.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    universalButton.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    universalButton.setToggleState(audioProcessor.firstHiHatHit, juce::NotificationType::dontSendNotification);
    universalButton.onClick = [this]()
    {
        tempoShown = true;
        universalKnob.setRange(0, 500);
        universalKnob.setValue(audioProcessor.tempo);
        guiLabel.setText("Tempo", juce::NotificationType::dontSendNotification);
        guiContent.setText(juce::String(audioProcessor.tempo), juce::NotificationType::dontSendNotification);
    };
    addAndMakeVisible(universalButton);
    
    //First Label Setup
    addAndMakeVisible(firstLabel);
    firstLabel.setText("1", juce::dontSendNotification);
    firstLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    firstLabel.setJustificationType(juce::Justification::centred);
    
    //Second Label Setup
    addAndMakeVisible(secondLabel);
    secondLabel.setText("2", juce::dontSendNotification);
    secondLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    secondLabel.setJustificationType(juce::Justification::centred);
    
    //Third Label Setup
    addAndMakeVisible(thirdLabel);
    thirdLabel.setText("3", juce::dontSendNotification);
    thirdLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    thirdLabel.setJustificationType(juce::Justification::centred);
    
    //Fourth Label Setup
    addAndMakeVisible(fourthLabel);
    fourthLabel.setText("4", juce::dontSendNotification);
    fourthLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    fourthLabel.setJustificationType(juce::Justification::centred);
    
    //First Hi Hat Setup
    firstHiHat.setClickingTogglesState(true);
    firstHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    firstHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    firstHiHat.setToggleState(audioProcessor.firstHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(firstHiHat);
    firstHiHat.onClick = [this]()
    {
        lastButtonPressed = 1;
        tempoShown = false;
        if(firstHiHat.getToggleState() == true){
            audioProcessor.firstHiHatHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.firstHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("first hihat on");
        }
        else{
            audioProcessor.firstHiHatHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.firstHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("first hihat off");
        }
    };
    
    //Second Hi Hat Setup
    secondHiHat.setClickingTogglesState(true);
    secondHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    secondHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    secondHiHat.setToggleState(audioProcessor.secondHiHatHit, juce::NotificationType::dontSendNotification);
    secondHiHat.onClick = [this]()
    {
        lastButtonPressed = 2;
        tempoShown = false;
        if(secondHiHat.getToggleState() == true){
            audioProcessor.secondHiHatHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.secondHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.secondHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("second hihat on");
        }
        else{
            audioProcessor.secondHiHatHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.secondHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.secondHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("second hihat off");
        }
    };
    addAndMakeVisible(secondHiHat);
    
    //Third Hi Hat Setup
    thirdHiHat.setClickingTogglesState(true);
    thirdHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    thirdHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    thirdHiHat.setToggleState(audioProcessor.thirdHiHatHit, juce::NotificationType::dontSendNotification);
    thirdHiHat.onClick = [this]()
    {
        lastButtonPressed = 3;
        tempoShown = false;
        if(thirdHiHat.getToggleState() == true){
            audioProcessor.thirdHiHatHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.thirdHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.thirdHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("third hihat on");
        }
        else{
            audioProcessor.thirdHiHatHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.thirdHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.thirdHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("third hihat off");
        }
    };
    addAndMakeVisible(thirdHiHat);
    
    //Fourth Hi Hat Setup
    fourthHiHat.setClickingTogglesState(true);
    fourthHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fourthHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fourthHiHat.setToggleState(audioProcessor.fourthHiHatHit, juce::NotificationType::dontSendNotification);
    fourthHiHat.onClick = [this]()
    {
        lastButtonPressed = 4;
        tempoShown = false;
        if(fourthHiHat.getToggleState() == true){
            audioProcessor.fourthHiHatHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fourthHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fourthHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("fourth hihat on");
        }
        else{
            audioProcessor.fourthHiHatHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fourthHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fourthHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("fourth hihat off");
        }
    };
    addAndMakeVisible(fourthHiHat);
    
    //Fifth Hi Hat Setup
    fifthHiHat.setClickingTogglesState(true);
    fifthHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fifthHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fifthHiHat.setToggleState(audioProcessor.fifthHiHatHit, juce::NotificationType::dontSendNotification);
    fifthHiHat.onClick = [this]()
    {
        lastButtonPressed = 5;
        tempoShown = false;
        if(fifthHiHat.getToggleState() == true){
            audioProcessor.fifthHiHatHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fifthHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fifthHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("fifth hihat on");
        }
        else{
            audioProcessor.fifthHiHatHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fifthHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fifthHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("fifth hihat off");
        }
    };
    addAndMakeVisible(fifthHiHat);
    
    //Sixth Hi Hat Setup
    sixthHiHat.setClickingTogglesState(true);
    sixthHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    sixthHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    sixthHiHat.setToggleState(audioProcessor.sixthHiHatHit, juce::NotificationType::dontSendNotification);
    sixthHiHat.onClick = [this]()
    {
        lastButtonPressed = 6;
        tempoShown = false;
        if(sixthHiHat.getToggleState() == true){
            audioProcessor.sixthHiHatHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.sixthHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.sixthHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("sixth hihat on");
        }
        else{
            audioProcessor.sixthHiHatHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.sixthHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.sixthHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("sixth hihat off");
        }
    };
    addAndMakeVisible(sixthHiHat);
    
    //Seventh Hi Hat Setup
    seventhHiHat.setClickingTogglesState(true);
    seventhHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    seventhHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    seventhHiHat.setToggleState(audioProcessor.seventhHiHatHit, juce::NotificationType::dontSendNotification);
    seventhHiHat.onClick = [this]()
    {
        lastButtonPressed = 7;
        tempoShown = false;
        if(seventhHiHat.getToggleState() == true){
            audioProcessor.seventhHiHatHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.seventhHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.seventhHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("seventh hihat on");
        }
        else{
            audioProcessor.seventhHiHatHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.seventhHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.seventhHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("seventh hihat off");
        }
    };
    addAndMakeVisible(seventhHiHat);
    
    //Eighth Hi Hat Setup
    eighthHiHat.setClickingTogglesState(true);
    eighthHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    eighthHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    eighthHiHat.setToggleState(audioProcessor.eighthHiHatHit, juce::NotificationType::dontSendNotification);
    eighthHiHat.onClick = [this]()
    {
        lastButtonPressed = 8;
        tempoShown = false;
        if(eighthHiHat.getToggleState() == true){
            audioProcessor.eighthHiHatHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.eighthHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.eighthHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("eighth hihat on");
        }
        else{
            audioProcessor.eighthHiHatHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.eighthHiHatVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.eighthHiHatVelocity), juce::NotificationType::dontSendNotification);
            DBG("eighth hihat off");
        }
    };
    addAndMakeVisible(eighthHiHat);
    
    //First Snare Setup
    firstSnare.setClickingTogglesState(true);
    firstSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    firstSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    firstSnare.setToggleState(audioProcessor.firstSnareHit, juce::NotificationType::dontSendNotification);
    firstSnare.onClick = [this]()
    {
        lastButtonPressed = 9;
        tempoShown = false;
        if(firstSnare.getToggleState() == true){
            audioProcessor.firstSnareHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.firstSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("first snare on");
        }
        else{
            audioProcessor.firstSnareHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.firstSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("first snare off");
        }
    };
    addAndMakeVisible(firstSnare);
    
    //Second Snare Setup
    secondSnare.setClickingTogglesState(true);
    secondSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    secondSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    secondSnare.setToggleState(audioProcessor.secondSnareHit, juce::NotificationType::dontSendNotification);
    secondSnare.onClick = [this]()
    {
        lastButtonPressed = 10;
        tempoShown = false;
        if(secondSnare.getToggleState() == true){
            audioProcessor.secondSnareHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.secondSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.secondSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("secon snare on");
        }
        else{
            audioProcessor.secondSnareHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.secondSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.secondSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("second snare off");
        }
    };
    addAndMakeVisible(secondSnare);
    
    //Third Snare Setup
    thirdSnare.setClickingTogglesState(true);
    thirdSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    thirdSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    thirdSnare.setToggleState(audioProcessor.thirdSnareHit, juce::NotificationType::dontSendNotification);
    thirdSnare.onClick = [this]()
    {
        lastButtonPressed = 11;
        tempoShown = false;
        if(thirdSnare.getToggleState() == true){
            audioProcessor.thirdSnareHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.thirdSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.thirdSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("third snare on");
        }
        else{
            audioProcessor.thirdSnareHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.thirdSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.thirdSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("third snare off");
        }
    };
    addAndMakeVisible(thirdSnare);
    
    //Fourth Snare Setup
    fourthSnare.setClickingTogglesState(true);
    fourthSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fourthSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fourthSnare.setToggleState(audioProcessor.fourthSnareHit, juce::NotificationType::dontSendNotification);
    fourthSnare.onClick = [this]()
    {
        lastButtonPressed = 12;
        tempoShown = false;
        if(fourthSnare.getToggleState() == true){
            audioProcessor.fourthSnareHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fourthSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fourthSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("fourth snare on");
        }
        else{
            audioProcessor.fourthSnareHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fourthSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fourthSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("fourth snare off");
        }
    };
    addAndMakeVisible(fourthSnare);
    
    //Fifth Snare Setup
    fifthSnare.setClickingTogglesState(true);
    fifthSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fifthSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fifthSnare.setToggleState(audioProcessor.fifthSnareHit, juce::NotificationType::dontSendNotification);
    fifthSnare.onClick = [this]()
    {
        lastButtonPressed = 13;
        tempoShown = false;
        if(fifthSnare.getToggleState() == true){
            audioProcessor.fifthSnareHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fifthSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fifthSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("fifth snare on");
        }
        else{
            audioProcessor.fifthSnareHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fifthSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fifthSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("fifth snare off");
        }
    };
    addAndMakeVisible(fifthSnare);
    
    //Sixth Snare Setup
    sixthSnare.setClickingTogglesState(true);
    sixthSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    sixthSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    sixthSnare.setToggleState(audioProcessor.sixthSnareHit, juce::NotificationType::dontSendNotification);
    sixthSnare.onClick = [this]()
    {
        lastButtonPressed = 14;
        tempoShown = false;
        if(sixthSnare.getToggleState() == true){
            audioProcessor.sixthSnareHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.sixthSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.sixthSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("sixth snare on");
        }
        else{
            audioProcessor.sixthSnareHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.sixthSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.sixthSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("sixth snare off");
        }
    };
    addAndMakeVisible(sixthSnare);
    
    //Seventh Snare Setup
    seventhSnare.setClickingTogglesState(true);
    seventhSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    seventhSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    seventhSnare.setToggleState(audioProcessor.seventhSnareHit, juce::NotificationType::dontSendNotification);
    seventhSnare.onClick = [this]()
    {
        lastButtonPressed = 15;
        tempoShown = false;
        if(seventhSnare.getToggleState() == true){
            audioProcessor.seventhSnareHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.seventhSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.seventhSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("seventh snare on");
        }
        else{
            audioProcessor.seventhSnareHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.seventhSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.seventhSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("seventh snare off");
        }
    };
    addAndMakeVisible(seventhSnare);
    
    //Eighth Snare Setup
    eighthSnare.setClickingTogglesState(true);
    eighthSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    eighthSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    eighthSnare.setToggleState(audioProcessor.eighthSnareHit, juce::NotificationType::dontSendNotification);
    eighthSnare.onClick = [this]()
    {
        lastButtonPressed = 16;
        tempoShown = false;
        if(eighthSnare.getToggleState() == true){
            audioProcessor.eighthSnareHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.eighthSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.eighthSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("eighth snare on");
        }
        else{
            audioProcessor.eighthSnareHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.eighthSnareVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.eighthSnareVelocity), juce::NotificationType::dontSendNotification);
            DBG("eighth snare off");
        }
    };
    addAndMakeVisible(eighthSnare);
    
    //First Tom Setup
    firstTom.setClickingTogglesState(true);
    firstTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    firstTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    firstTom.setToggleState(audioProcessor.firstTomHit, juce::NotificationType::dontSendNotification);
    firstTom.onClick = [this]()
    {
        lastButtonPressed = 17;
        tempoShown = false;
        if(firstTom.getToggleState() == true){
            audioProcessor.firstTomHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.firstTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("first tom on");
        }
        else{
            audioProcessor.firstTomHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.firstTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("first tom off");
        }
    };
    addAndMakeVisible(firstTom);
    
    //Second Tom Setup
    secondTom.setClickingTogglesState(true);
    secondTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    secondTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    secondTom.setToggleState(audioProcessor.secondTomHit, juce::NotificationType::dontSendNotification);
    secondTom.onClick = [this]()
    {
        lastButtonPressed = 18;
        tempoShown = false;
        if(secondTom.getToggleState() == true){
            audioProcessor.secondTomHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.secondTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.secondTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("second tom on");
        }
        else{
            audioProcessor.secondTomHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.secondTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.secondTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("second tom off");
        }
    };
    addAndMakeVisible(secondTom);
    
    //Third Tom Setup
    thirdTom.setClickingTogglesState(true);
    thirdTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    thirdTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    thirdTom.setToggleState(audioProcessor.thirdTomHit, juce::NotificationType::dontSendNotification);
    thirdTom.onClick = [this]()
    {
        lastButtonPressed = 19;
        tempoShown = false;
        if(thirdTom.getToggleState() == true){
            audioProcessor.thirdTomHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.thirdTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.thirdTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("third tom on");
        }
        else{
            audioProcessor.thirdTomHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.thirdTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.thirdTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("third tom off");
        }
    };
    addAndMakeVisible(thirdTom);
    
    //Fourth Tom Setup
    fourthTom.setClickingTogglesState(true);
    fourthTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fourthTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fourthTom.setToggleState(audioProcessor.fourthTomHit, juce::NotificationType::dontSendNotification);
    fourthTom.onClick = [this]()
    {
        lastButtonPressed = 20;
        tempoShown = false;
        if(fourthTom.getToggleState() == true){
            audioProcessor.fourthTomHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fourthTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fourthTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("fourth tom on");
        }
        else{
            audioProcessor.fourthTomHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fourthTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fourthTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("fourth tom off");
        }
    };
    addAndMakeVisible(fourthTom);
    
    //Fifth Tom Setup
    fifthTom.setClickingTogglesState(true);
    fifthTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fifthTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fifthTom.setToggleState(audioProcessor.fifthTomHit, juce::NotificationType::dontSendNotification);
    fifthTom.onClick = [this]()
    {
        lastButtonPressed = 21;
        tempoShown = false;
        if(fifthTom.getToggleState() == true){
            audioProcessor.fifthTomHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fifthTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fifthTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("fifth tom on");
        }
        else{
            audioProcessor.fifthTomHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fifthTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fifthTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("fifth tom off");
        }
    };
    addAndMakeVisible(fifthTom);
    
    //Sixth Tom Setup
    sixthTom.setClickingTogglesState(true);
    sixthTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    sixthTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    sixthTom.setToggleState(audioProcessor.sixthTomHit, juce::NotificationType::dontSendNotification);
    sixthTom.onClick = [this]()
    {
        lastButtonPressed = 22;
        tempoShown = false;
        if(sixthTom.getToggleState() == true){
            audioProcessor.sixthTomHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.sixthTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.sixthTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("sixth tom on");
        }
        else{
            audioProcessor.sixthTomHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.sixthTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.sixthTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("sixth tom off");
        }
    };
    addAndMakeVisible(sixthTom);
    
    //Seventh Tom Setup
    seventhTom.setClickingTogglesState(true);
    seventhTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    seventhTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    seventhTom.setToggleState(audioProcessor.seventhTomHit, juce::NotificationType::dontSendNotification);
    seventhTom.onClick = [this]()
    {
        lastButtonPressed = 23;
        tempoShown = false;
        if(seventhTom.getToggleState() == true){
            audioProcessor.seventhTomHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.seventhTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.seventhTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("seventh tom on");
        }
        else{
            audioProcessor.seventhTomHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.seventhTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.seventhTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("seventh tom off");
        }
    };
    addAndMakeVisible(seventhTom);
    
    //Eighth Tom Setup
    eighthTom.setClickingTogglesState(true);
    eighthTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    eighthTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    eighthTom.setToggleState(audioProcessor.eighthTomHit, juce::NotificationType::dontSendNotification);
    eighthTom.onClick = [this]()
    {
        lastButtonPressed = 24;
        tempoShown = false;
        if(eighthTom.getToggleState() == true){
            audioProcessor.eighthTomHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.eighthTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.eighthTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("eighth tom on");
        }
        else{
            audioProcessor.eighthTomHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.eighthTomVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.eighthTomVelocity), juce::NotificationType::dontSendNotification);
            DBG("eighth tom off");
        }
    };
    addAndMakeVisible(eighthTom);
    
    //First Kick Setup
    firstKick.setClickingTogglesState(true);
    firstKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    firstKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    firstKick.setToggleState(audioProcessor.firstKickHit, juce::NotificationType::dontSendNotification);
    firstKick.onClick = [this]()
    {
        lastButtonPressed = 25;
        tempoShown = false;
        if(firstKick.getToggleState() == true){
            audioProcessor.firstKickHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.firstKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("first kick on");
        }
        else{
            audioProcessor.firstKickHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.firstKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("first kick off");
        }
    };
    addAndMakeVisible(firstKick);
    
    //Second Kick Setup
    secondKick.setClickingTogglesState(true);
    secondKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    secondKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    secondKick.setToggleState(audioProcessor.secondKickHit, juce::NotificationType::dontSendNotification);
    secondKick.onClick = [this]()
    {
        lastButtonPressed = 26;
        tempoShown = false;
        if(secondKick.getToggleState() == true){
            audioProcessor.secondKickHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.secondKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.secondKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("second kick on");
        }
        else{
            audioProcessor.secondKickHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.secondKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.secondKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("second kick off");
        }
    };
    addAndMakeVisible(secondKick);
    
    //Third Kick Setup
    thirdKick.setClickingTogglesState(true);
    thirdKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    thirdKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    thirdKick.setToggleState(audioProcessor.thirdKickHit, juce::NotificationType::dontSendNotification);
    thirdKick.onClick = [this]()
    {
        lastButtonPressed = 27;
        tempoShown = false;
        if(thirdKick.getToggleState() == true){
            audioProcessor.thirdKickHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.thirdKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("third kick on");
        }
        else{
            audioProcessor.thirdKickHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.firstKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.thirdKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("third kick off");
        }
    };
    addAndMakeVisible(thirdKick);
    
    //Fourth Kick Setup
    fourthKick.setClickingTogglesState(true);
    fourthKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fourthKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fourthKick.setToggleState(audioProcessor.fourthKickHit, juce::NotificationType::dontSendNotification);
    fourthKick.onClick = [this]()
    {
        lastButtonPressed = 28;
        tempoShown = false;
        if(fourthKick.getToggleState() == true){
            audioProcessor.fourthKickHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fourthKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fourthKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("fourth kick on");
        }
        else{
            audioProcessor.fourthKickHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fourthKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fourthKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("fourth kick off");
        }
    };
    addAndMakeVisible(fourthKick);
    
    //Fifth Kick Setup
    fifthKick.setClickingTogglesState(true);
    fifthKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fifthKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fifthKick.setToggleState(audioProcessor.fifthKickHit, juce::NotificationType::dontSendNotification);
    fifthKick.onClick = [this]()
    {
        lastButtonPressed = 29;
        tempoShown = false;
        if(fifthKick.getToggleState() == true){
            audioProcessor.fifthKickHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fifthKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fifthKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("fifth kick on");
        }
        else{
            audioProcessor.fifthKickHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.fifthKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.fifthKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("fifth kick off");
        }
    };
    addAndMakeVisible(fifthKick);
    
    //Sixth Kick Setup
    sixthKick.setClickingTogglesState(true);
    sixthKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    sixthKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    sixthKick.setToggleState(audioProcessor.sixthKickHit, juce::NotificationType::dontSendNotification);
    sixthKick.onClick = [this]()
    {
        lastButtonPressed = 30;
        tempoShown = false;
        if(sixthKick.getToggleState() == true){
            audioProcessor.sixthKickHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.sixthKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.sixthKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("sixth snare on");
        }
        else{
            audioProcessor.sixthSnareHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.sixthKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.sixthKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("sixth snare off");
        }
    };
    addAndMakeVisible(sixthKick);
    
    //Seventh Kick Setup
    seventhKick.setClickingTogglesState(true);
    seventhKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    seventhKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    seventhKick.setToggleState(audioProcessor.seventhKickHit, juce::NotificationType::dontSendNotification);
    seventhKick.onClick = [this]()
    {
        lastButtonPressed = 31;
        tempoShown = false;
        if(seventhKick.getToggleState() == true){
            audioProcessor.seventhKickHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.seventhKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.seventhKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("seventh kick on");
        }
        else{
            audioProcessor.seventhKickHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.seventhKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.seventhKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("seventh kick off");
        }
    };
    addAndMakeVisible(seventhKick);
    
    //Eighth Kick Setup
    eighthKick.setClickingTogglesState(true);
    eighthKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    eighthKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    eighthKick.setToggleState(audioProcessor.eighthKickHit, juce::NotificationType::dontSendNotification);
    eighthKick.onClick = [this]()
    {
        lastButtonPressed = 32;
        tempoShown = false;
        if(eighthKick.getToggleState() == true){
            audioProcessor.eighthKickHit = true;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.eighthKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.eighthKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("eighth kick on");
        }
        else{
            audioProcessor.eighthKickHit = false;
            universalKnob.setRange(0, 255);
            universalKnob.setValue(audioProcessor.eighthKickVelocity);
            guiLabel.setText("Velocity", juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.eighthKickVelocity), juce::NotificationType::dontSendNotification);
            DBG("eighth kick off");
        }
    };
    addAndMakeVisible(eighthKick);
}

Robotic_Drummer_Interface_MockupAudioProcessorEditor::~Robotic_Drummer_Interface_MockupAudioProcessorEditor()
{
}

//==============================================================================
void Robotic_Drummer_Interface_MockupAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::Colour mainColor(/*0xFF161C33*/juce::Colours::darkgrey);
    juce::Colour secondaryColor(/*0xFF363C54*/juce::Colours::grey);
    juce::Colour screenColor(juce::Colours::black);
    
    g.fillAll(mainColor);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //Make custom colors
    g.setColour(screenColor);
    
    auto border = 5;
    auto numCols = 8;
    auto numRows = 5;
    auto area = getLocalBounds().reduced(border * 4);
    auto upperArea = area.removeFromTop(area.getHeight()/4);
    auto screenArea = upperArea.removeFromLeft(area.getWidth()/3);
    g.fillRect(screenArea);
    g.setColour(secondaryColor);
    auto drumsArea = area.removeFromBottom(area.getHeight()-20);
    g.fillRect(drumsArea);
    
    //Get drum row height
    auto rowHeight = drumsArea.getHeight()/numRows;
    
    drumsArea.removeFromLeft(border*10);

    //Get column width
    auto columnWidth = drumsArea.getWidth()/numCols;
    
    //Set up columns
    drumsArea.removeFromLeft(border);
    auto firstColumn = drumsArea.removeFromLeft(columnWidth);
    auto secondColumn = drumsArea.removeFromLeft(columnWidth);
    auto thirdColumn = drumsArea.removeFromLeft(columnWidth);
    auto fourthColumn = drumsArea.removeFromLeft(columnWidth);
    auto fifthColumn = drumsArea.removeFromLeft(columnWidth);
    auto sixthColumn = drumsArea.removeFromLeft(columnWidth);
    auto seventhColumn = drumsArea.removeFromLeft(columnWidth);
    auto eighthColumn = drumsArea.removeFromLeft(columnWidth);
    
    float reduceButtonWidth = (columnWidth - rowHeight)/2;
    
    //Set up initial colors of beats
    auto firstBeatArea = firstColumn.removeFromTop(rowHeight).reduced(border);
    firstBeatArea.removeFromLeft(reduceButtonWidth);
    firstBeatArea.removeFromRight(reduceButtonWidth);
    firstBeatArea.reduce(10, 10);
    beatAreas.add(firstBeatArea.getX(), firstBeatArea.getY(), firstBeatArea.getWidth(), firstBeatArea.getHeight());
    auto secondBeatArea = secondColumn.removeFromTop(rowHeight).reduced(border);
    secondBeatArea.removeFromLeft(reduceButtonWidth);
    secondBeatArea.removeFromRight(reduceButtonWidth);
    secondBeatArea.reduce(10, 10);
    beatAreas.add(secondBeatArea.getX(), secondBeatArea.getY(), secondBeatArea.getWidth(), secondBeatArea.getHeight());
    auto thirdBeatArea = thirdColumn.removeFromTop(rowHeight).reduced(border);
    thirdBeatArea.removeFromLeft(reduceButtonWidth);
    thirdBeatArea.removeFromRight(reduceButtonWidth);
    thirdBeatArea.reduce(10, 10);
    beatAreas.add(thirdBeatArea.getX(), thirdBeatArea.getY(), thirdBeatArea.getWidth(), thirdBeatArea.getHeight());
    auto fourthBeatArea = fourthColumn.removeFromTop(rowHeight).reduced(border);
    fourthBeatArea.removeFromLeft(reduceButtonWidth);
    fourthBeatArea.removeFromRight(reduceButtonWidth);
    fourthBeatArea.reduce(10, 10);
    beatAreas.add(fourthBeatArea.getX(), fourthBeatArea.getY(), fourthBeatArea.getWidth(), fourthBeatArea.getHeight());
    auto fifthBeatArea = fifthColumn.removeFromTop(rowHeight).reduced(border);
    fifthBeatArea.removeFromLeft(reduceButtonWidth);
    fifthBeatArea.removeFromRight(reduceButtonWidth);
    fifthBeatArea.reduce(10, 10);
    beatAreas.add(fifthBeatArea.getX(), fifthBeatArea.getY(), fifthBeatArea.getWidth(), fifthBeatArea.getHeight());
    auto sixthBeatArea = sixthColumn.removeFromTop(rowHeight).reduced(border);
    sixthBeatArea.removeFromLeft(reduceButtonWidth);
    sixthBeatArea.removeFromRight(reduceButtonWidth);
    sixthBeatArea.reduce(10, 10);
    beatAreas.add(sixthBeatArea.getX(), sixthBeatArea.getY(), sixthBeatArea.getWidth(), sixthBeatArea.getHeight());
    auto seventhBeatArea = seventhColumn.removeFromTop(rowHeight).reduced(border);
    seventhBeatArea.removeFromLeft(reduceButtonWidth);
    seventhBeatArea.removeFromRight(reduceButtonWidth);
    seventhBeatArea.reduce(10, 10);
    beatAreas.add(seventhBeatArea.getX(), seventhBeatArea.getY(), seventhBeatArea.getWidth(), seventhBeatArea.getHeight());
    auto eighthBeatArea = eighthColumn.removeFromTop(rowHeight).reduced(border);
    eighthBeatArea.removeFromLeft(reduceButtonWidth);
    eighthBeatArea.removeFromRight(reduceButtonWidth);
    eighthBeatArea.reduce(10, 10);
    beatAreas.add(eighthBeatArea.getX(), eighthBeatArea.getY(), eighthBeatArea.getWidth(), eighthBeatArea.getHeight());
    
    for(int i = 0; i < 8; i++)
    {
        if(audioProcessor.beats[i])
        {
            g.setColour(juce::Colours::red);
        }
        else
        {
            g.setColour(juce::Colours::darkgrey);
        }
        g.fillEllipse(beatAreas.getRectangle(i));
    }
    
//    g.setColour(juce::Colours::red);
//    g.fillEllipse(firstBeatArea.getX(), firstBeatArea.getY(), firstBeatArea.getWidth(), firstBeatArea.getHeight());
//    g.setColour(juce::Colours::darkgrey);
//    g.fillEllipse(secondBeatArea.getX(), secondBeatArea.getY(), secondBeatArea.getWidth(), secondBeatArea.getHeight());
//    g.fillEllipse(thirdBeatArea.getX(), thirdBeatArea.getY(), thirdBeatArea.getWidth(), thirdBeatArea.getHeight());
//    g.fillEllipse(fourthBeatArea.getX(), fourthBeatArea.getY(), fourthBeatArea.getWidth(), fourthBeatArea.getHeight());
//    g.fillEllipse(fifthBeatArea.getX(), fifthBeatArea.getY(), fifthBeatArea.getWidth(), fifthBeatArea.getHeight());
//    g.fillEllipse(sixthBeatArea.getX(), sixthBeatArea.getY(), sixthBeatArea.getWidth(), sixthBeatArea.getHeight());
//    g.fillEllipse(seventhBeatArea.getX(), seventhBeatArea.getY(), seventhBeatArea.getWidth(), seventhBeatArea.getHeight());
//    g.fillEllipse(eighthBeatArea.getX(), eighthBeatArea.getY(), eighthBeatArea.getWidth(), eighthBeatArea.getHeight());
}

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto border = 5;
    auto numCols = 8;
    auto numRows = 5;
    auto area = getLocalBounds().reduced(border * 4);
    auto controlsArea = area.removeFromTop(area.getHeight()/4);
    auto screenArea = controlsArea.removeFromLeft(area.getWidth()/4);
    auto drumsArea = area.removeFromBottom(area.getHeight()-20);
    
    //Set up universal knob and button
    auto universalKnobArea = controlsArea.removeFromRight(controlsArea.getWidth()/3);
    auto buttonArea = controlsArea.removeFromRight(controlsArea.getWidth()/2);
    auto universalButtonArea = buttonArea.removeFromRight(buttonArea.getWidth()-buttonArea.getHeight()).reduced(border*2);
    
    universalKnob.setBounds(universalKnobArea);
    universalButton.setBounds(universalButtonArea);
    
    //Set up LCD Screen and Labels
    guiContent.setBounds(screenArea);
    
    auto guiLabelArea = screenArea.removeFromLeft(screenArea.getWidth()/4).removeFromTop(screenArea.getHeight()/4);
    
    guiLabel.setBounds(guiLabelArea);
    
    //Get drum row height
    auto rowHeight = drumsArea.getHeight()/numRows;
    
    //Set up row labels
    auto drumLabels = drumsArea.removeFromLeft(border*10);
    drumLabels.removeFromTop(rowHeight);
    auto firstLabelArea = drumLabels.removeFromTop(rowHeight);
    auto secondLabelArea = drumLabels.removeFromTop(rowHeight);
    auto thirdLabelArea = drumLabels.removeFromTop(rowHeight);
    auto fourthLabelArea = drumLabels.removeFromTop(rowHeight);
    
    firstLabel.setBounds(firstLabelArea);
    secondLabel.setBounds(secondLabelArea);
    thirdLabel.setBounds(thirdLabelArea);
    fourthLabel.setBounds(fourthLabelArea);
    
    //Get column width
    auto columnWidth = drumsArea.getWidth()/numCols;
    
    float reduceButtonWidth = (columnWidth - rowHeight)/2.0;
    
    //Set up columns
    drumsArea.removeFromLeft(border);
    auto firstColumn = drumsArea.removeFromLeft(columnWidth);
    auto secondColumn = drumsArea.removeFromLeft(columnWidth);
    auto thirdColumn = drumsArea.removeFromLeft(columnWidth);
    auto fourthColumn = drumsArea.removeFromLeft(columnWidth);
    auto fifthColumn = drumsArea.removeFromLeft(columnWidth);
    auto sixthColumn = drumsArea.removeFromLeft(columnWidth);
    auto seventhColumn = drumsArea.removeFromLeft(columnWidth);
    auto eighthColumn = drumsArea.removeFromLeft(columnWidth);
    
    //Set up beats
    auto firstBeatArea = firstColumn.removeFromTop(rowHeight).reduced(border);
    firstBeatArea.removeFromLeft(reduceButtonWidth);
    firstBeatArea.removeFromRight(reduceButtonWidth);
    firstBeatArea.reduce(10, 10);
    auto secondBeatArea = secondColumn.removeFromTop(rowHeight).reduced(border);
    secondBeatArea.removeFromLeft(reduceButtonWidth);
    secondBeatArea.removeFromRight(reduceButtonWidth);
    secondBeatArea.reduce(10, 10);
    auto thirdBeatArea = thirdColumn.removeFromTop(rowHeight).reduced(border);
    thirdBeatArea.removeFromLeft(reduceButtonWidth);
    thirdBeatArea.removeFromRight(reduceButtonWidth);
    thirdBeatArea.reduce(10, 10);
    auto fourthBeatArea = fourthColumn.removeFromTop(rowHeight).reduced(border);
    fourthBeatArea.removeFromLeft(reduceButtonWidth);
    fourthBeatArea.removeFromRight(reduceButtonWidth);
    fourthBeatArea.reduce(10, 10);
    auto fifthBeatArea = fifthColumn.removeFromTop(rowHeight).reduced(border);
    fifthBeatArea.removeFromLeft(reduceButtonWidth);
    fifthBeatArea.removeFromRight(reduceButtonWidth);
    fifthBeatArea.reduce(10, 10);
    auto sixthBeatArea = sixthColumn.removeFromTop(rowHeight).reduced(border);
    sixthBeatArea.removeFromLeft(reduceButtonWidth);
    sixthBeatArea.removeFromRight(reduceButtonWidth);
    sixthBeatArea.reduce(10, 10);
    auto seventhBeatArea = seventhColumn.removeFromTop(rowHeight).reduced(border);
    seventhBeatArea.removeFromLeft(reduceButtonWidth);
    seventhBeatArea.removeFromRight(reduceButtonWidth);
    seventhBeatArea.reduce(10, 10);
    auto eighthBeatArea = eighthColumn.removeFromTop(rowHeight).reduced(border);
    eighthBeatArea.removeFromLeft(reduceButtonWidth);
    eighthBeatArea.removeFromRight(reduceButtonWidth);
    eighthBeatArea.reduce(10, 10);
    
    beatAreas.add(firstBeatArea.getX(), firstBeatArea.getY(), firstBeatArea.getWidth(), firstBeatArea.getHeight());
    beatAreas.add(secondBeatArea.getX(), secondBeatArea.getY(), secondBeatArea.getWidth(), secondBeatArea.getHeight());
    beatAreas.add(thirdBeatArea.getX(), thirdBeatArea.getY(), thirdBeatArea.getWidth(), thirdBeatArea.getHeight());
    beatAreas.add(fourthBeatArea.getX(), fourthBeatArea.getY(), fourthBeatArea.getWidth(), fourthBeatArea.getHeight());
    beatAreas.add(fifthBeatArea.getX(), fifthBeatArea.getY(), fifthBeatArea.getWidth(), fifthBeatArea.getHeight());
    beatAreas.add(sixthBeatArea.getX(), sixthBeatArea.getY(), sixthBeatArea.getWidth(), sixthBeatArea.getHeight());
    beatAreas.add(seventhBeatArea.getX(), seventhBeatArea.getY(), seventhBeatArea.getWidth(), seventhBeatArea.getHeight());
    beatAreas.add(eighthBeatArea.getX(), eighthBeatArea.getY(), eighthBeatArea.getWidth(), eighthBeatArea.getHeight());
    
    //Set up hi hat
    auto firstHiHatArea = firstColumn.removeFromTop(rowHeight).reduced(border*2);
    firstHiHatArea.removeFromLeft(reduceButtonWidth);
    firstHiHatArea.removeFromRight(reduceButtonWidth);
    auto secondHiHatArea = secondColumn.removeFromTop(rowHeight).reduced(border*2);
    secondHiHatArea.removeFromLeft(reduceButtonWidth);
    secondHiHatArea.removeFromRight(reduceButtonWidth);
    auto thirdHiHatArea = thirdColumn.removeFromTop(rowHeight).reduced(border*2);
    thirdHiHatArea.removeFromLeft(reduceButtonWidth);
    thirdHiHatArea.removeFromRight(reduceButtonWidth);
    auto fourthHiHatArea = fourthColumn.removeFromTop(rowHeight).reduced(border*2);
    fourthHiHatArea.removeFromLeft(reduceButtonWidth);
    fourthHiHatArea.removeFromRight(reduceButtonWidth);
    auto fifthHiHatArea = fifthColumn.removeFromTop(rowHeight).reduced(border*2);
    fifthHiHatArea.removeFromLeft(reduceButtonWidth);
    fifthHiHatArea.removeFromRight(reduceButtonWidth);
    auto sixthHiHatArea = sixthColumn.removeFromTop(rowHeight).reduced(border*2);
    sixthHiHatArea.removeFromLeft(reduceButtonWidth);
    sixthHiHatArea.removeFromRight(reduceButtonWidth);
    auto seventhHiHatArea = seventhColumn.removeFromTop(rowHeight).reduced(border*2);
    seventhHiHatArea.removeFromLeft(reduceButtonWidth);
    seventhHiHatArea.removeFromRight(reduceButtonWidth);
    auto eighthHiHatArea = eighthColumn.removeFromTop(rowHeight).reduced(border*2);
    eighthHiHatArea.removeFromLeft(reduceButtonWidth);
    eighthHiHatArea.removeFromRight(reduceButtonWidth);
    
    firstHiHat.setBounds(firstHiHatArea);
    secondHiHat.setBounds(secondHiHatArea);
    thirdHiHat.setBounds(thirdHiHatArea);
    fourthHiHat.setBounds(fourthHiHatArea);
    fifthHiHat.setBounds(fifthHiHatArea);
    sixthHiHat.setBounds(sixthHiHatArea);
    seventhHiHat.setBounds(seventhHiHatArea);
    eighthHiHat.setBounds(eighthHiHatArea);
    
    //Set up snare
    auto firstSnareArea = firstColumn.removeFromTop(rowHeight).reduced(border*2);
    firstSnareArea.removeFromLeft(reduceButtonWidth);
    firstSnareArea.removeFromRight(reduceButtonWidth);
    auto secondSnareArea = secondColumn.removeFromTop(rowHeight).reduced(border*2);
    secondSnareArea.removeFromLeft(reduceButtonWidth);
    secondSnareArea.removeFromRight(reduceButtonWidth);
    auto thirdSnareArea = thirdColumn.removeFromTop(rowHeight).reduced(border*2);
    thirdSnareArea.removeFromLeft(reduceButtonWidth);
    thirdSnareArea.removeFromRight(reduceButtonWidth);
    auto fourthSnareArea = fourthColumn.removeFromTop(rowHeight).reduced(border*2);
    fourthSnareArea.removeFromLeft(reduceButtonWidth);
    fourthSnareArea.removeFromRight(reduceButtonWidth);
    auto fifthSnareArea = fifthColumn.removeFromTop(rowHeight).reduced(border*2);
    fifthSnareArea.removeFromLeft(reduceButtonWidth);
    fifthSnareArea.removeFromRight(reduceButtonWidth);
    auto sixthSnareArea = sixthColumn.removeFromTop(rowHeight).reduced(border*2);
    sixthSnareArea.removeFromLeft(reduceButtonWidth);
    sixthSnareArea.removeFromRight(reduceButtonWidth);
    auto seventhSnareArea = seventhColumn.removeFromTop(rowHeight).reduced(border*2);
    seventhSnareArea.removeFromLeft(reduceButtonWidth);
    seventhSnareArea.removeFromRight(reduceButtonWidth);
    auto eighthSnareArea = eighthColumn.removeFromTop(rowHeight).reduced(border*2);
    eighthSnareArea.removeFromLeft(reduceButtonWidth);
    eighthSnareArea.removeFromRight(reduceButtonWidth);
    
    firstSnare.setBounds(firstSnareArea);
    secondSnare.setBounds(secondSnareArea);
    thirdSnare.setBounds(thirdSnareArea);
    fourthSnare.setBounds(fourthSnareArea);
    fifthSnare.setBounds(fifthSnareArea);
    sixthSnare.setBounds(sixthSnareArea);
    seventhSnare.setBounds(seventhSnareArea);
    eighthSnare.setBounds(eighthSnareArea);
    
    //Set up tom
    auto firstTomArea = firstColumn.removeFromTop(rowHeight).reduced(border*2);
    firstTomArea.removeFromLeft(reduceButtonWidth);
    firstTomArea.removeFromRight(reduceButtonWidth);
    auto secondTomArea = secondColumn.removeFromTop(rowHeight).reduced(border*2);
    secondTomArea.removeFromLeft(reduceButtonWidth);
    secondTomArea.removeFromRight(reduceButtonWidth);
    auto thirdTomArea = thirdColumn.removeFromTop(rowHeight).reduced(border*2);
    thirdTomArea.removeFromLeft(reduceButtonWidth);
    thirdTomArea.removeFromRight(reduceButtonWidth);
    auto fourthTomArea = fourthColumn.removeFromTop(rowHeight).reduced(border*2);
    fourthTomArea.removeFromLeft(reduceButtonWidth);
    fourthTomArea.removeFromRight(reduceButtonWidth);
    auto fifthTomArea = fifthColumn.removeFromTop(rowHeight).reduced(border*2);
    fifthTomArea.removeFromLeft(reduceButtonWidth);
    fifthTomArea.removeFromRight(reduceButtonWidth);
    auto sixthTomArea = sixthColumn.removeFromTop(rowHeight).reduced(border*2);
    sixthTomArea.removeFromLeft(reduceButtonWidth);
    sixthTomArea.removeFromRight(reduceButtonWidth);
    auto seventhTomArea = seventhColumn.removeFromTop(rowHeight).reduced(border*2);
    seventhTomArea.removeFromLeft(reduceButtonWidth);
    seventhTomArea.removeFromRight(reduceButtonWidth);
    auto eighthTomArea = eighthColumn.removeFromTop(rowHeight).reduced(border*2);
    eighthTomArea.removeFromLeft(reduceButtonWidth);
    eighthTomArea.removeFromRight(reduceButtonWidth);
    
    firstTom.setBounds(firstTomArea);
    secondTom.setBounds(secondTomArea);
    thirdTom.setBounds(thirdTomArea);
    fourthTom.setBounds(fourthTomArea);
    fifthTom.setBounds(fifthTomArea);
    sixthTom.setBounds(sixthTomArea);
    seventhTom.setBounds(seventhTomArea);
    eighthTom.setBounds(eighthTomArea);
    
    //Set up kick
    auto firstKickArea = firstColumn.removeFromTop(rowHeight).reduced(border*2);
    firstKickArea.removeFromLeft(reduceButtonWidth);
    firstKickArea.removeFromRight(reduceButtonWidth);
    auto secondKickArea = secondColumn.removeFromTop(rowHeight).reduced(border*2);
    secondKickArea.removeFromLeft(reduceButtonWidth);
    secondKickArea.removeFromRight(reduceButtonWidth);
    auto thirdKickArea = thirdColumn.removeFromTop(rowHeight).reduced(border*2);
    thirdKickArea.removeFromLeft(reduceButtonWidth);
    thirdKickArea.removeFromRight(reduceButtonWidth);
    auto fourthKickArea = fourthColumn.removeFromTop(rowHeight).reduced(border*2);
    fourthKickArea.removeFromLeft(reduceButtonWidth);
    fourthKickArea.removeFromRight(reduceButtonWidth);
    auto fifthKickArea = fifthColumn.removeFromTop(rowHeight).reduced(border*2);
    fifthKickArea.removeFromLeft(reduceButtonWidth);
    fifthKickArea.removeFromRight(reduceButtonWidth);
    auto sixthKickArea = sixthColumn.removeFromTop(rowHeight).reduced(border*2);
    sixthKickArea.removeFromLeft(reduceButtonWidth);
    sixthKickArea.removeFromRight(reduceButtonWidth);
    auto seventhKickArea = seventhColumn.removeFromTop(rowHeight).reduced(border*2);
    seventhKickArea.removeFromLeft(reduceButtonWidth);
    seventhKickArea.removeFromRight(reduceButtonWidth);
    auto eighthKickArea = eighthColumn.removeFromTop(rowHeight).reduced(border*2);
    eighthKickArea.removeFromLeft(reduceButtonWidth);
    eighthKickArea.removeFromRight(reduceButtonWidth);
    
    firstKick.setBounds(firstKickArea);
    secondKick.setBounds(secondKickArea);
    thirdKick.setBounds(thirdKickArea);
    fourthKick.setBounds(fourthKickArea);
    fifthKick.setBounds(fifthKickArea);
    sixthKick.setBounds(sixthKickArea);
    seventhKick.setBounds(seventhKickArea);
    eighthKick.setBounds(eighthKickArea);
}

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::timerCallback()
{
    repaint();
}

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::buttonClicked (juce::Button * button){}

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::sliderValueChanged (juce::Slider* slider){}

juce::Rectangle<int> getButtonArea(juce::Rectangle<int> column, float columnWidth, float rowHeight, float border)
{
    float reduceButtonWidth = (columnWidth - rowHeight)/2.0;
    
    juce::Rectangle<int> buttonArea = column.removeFromTop(rowHeight).reduced(border);
    buttonArea.removeFromLeft(reduceButtonWidth);
    buttonArea.removeFromRight(reduceButtonWidth);
    return buttonArea;
}
