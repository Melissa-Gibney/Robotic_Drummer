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
    
    //Set up the colors of the buttons
    otherLookAndFeel.setColour(juce::Slider::thumbColourId, juce::Colours::darkgreen);
    
    //First Hi Hat Setup
    firstHiHat.setClickingTogglesState(true);
    firstHiHat.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    firstHiHat.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    firstHiHat.setToggleState(audioProcessor.firstHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(firstHiHat);
    
    //Second Hi Hat Setup
    secondHiHat.setClickingTogglesState(true);
    secondHiHat.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    secondHiHat.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    secondHiHat.setToggleState(audioProcessor.secondHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(secondHiHat);
    
    //Third Hi Hat Setup
    thirdHiHat.setClickingTogglesState(true);
    thirdHiHat.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    thirdHiHat.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    thirdHiHat.setToggleState(audioProcessor.thirdHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(thirdHiHat);
    
    //Fourth Hi Hat Setup
    fourthHiHat.setClickingTogglesState(true);
    fourthHiHat.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    fourthHiHat.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    fourthHiHat.setToggleState(audioProcessor.fourthHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fourthHiHat);
    
    //Fifth Hi Hat Setup
    fifthHiHat.setClickingTogglesState(true);
    fifthHiHat.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    fifthHiHat.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    fifthHiHat.setToggleState(audioProcessor.fifthHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fifthHiHat);
    
    //Sixth Hi Hat Setup
    sixthHiHat.setClickingTogglesState(true);
    sixthHiHat.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    sixthHiHat.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    sixthHiHat.setToggleState(audioProcessor.sixthHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(sixthHiHat);
    
    //Seventh Hi Hat Setup
    seventhHiHat.setClickingTogglesState(true);
    seventhHiHat.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    seventhHiHat.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    seventhHiHat.setToggleState(audioProcessor.seventhHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(seventhHiHat);
    
    //Eighth Hi Hat Setup
    eighthHiHat.setClickingTogglesState(true);
    eighthHiHat.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    eighthHiHat.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    eighthHiHat.setToggleState(audioProcessor.eighthHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(eighthHiHat);
    
    //First Snare Setup
    firstSnare.setClickingTogglesState(true);
    firstSnare.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    firstSnare.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    firstSnare.setToggleState(audioProcessor.firstSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(firstSnare);
    
    //Second Snare Setup
    secondSnare.setClickingTogglesState(true);
    secondSnare.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    secondSnare.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    secondSnare.setToggleState(audioProcessor.secondSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(secondSnare);
    
    //Third Snare Setup
    thirdSnare.setClickingTogglesState(true);
    thirdSnare.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    thirdSnare.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    thirdSnare.setToggleState(audioProcessor.thirdSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(thirdSnare);
    
    //Fourth Snare Setup
    fourthSnare.setClickingTogglesState(true);
    fourthSnare.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    fourthSnare.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    fourthSnare.setToggleState(audioProcessor.fourthSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fourthSnare);
    
    //Fifth Snare Setup
    fifthSnare.setClickingTogglesState(true);
    fifthSnare.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    fifthSnare.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    fifthSnare.setToggleState(audioProcessor.fifthSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fifthSnare);
    
    //Sixth Snare Setup
    sixthSnare.setClickingTogglesState(true);
    sixthSnare.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    sixthSnare.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    sixthSnare.setToggleState(audioProcessor.sixthSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(sixthSnare);
    
    //Seventh Snare Setup
    seventhSnare.setClickingTogglesState(true);
    seventhSnare.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    seventhSnare.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    seventhSnare.setToggleState(audioProcessor.seventhSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(seventhSnare);
    
    //Eighth Snare Setup
    eighthSnare.setClickingTogglesState(true);
    eighthSnare.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    eighthSnare.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    eighthSnare.setToggleState(audioProcessor.eighthSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(eighthSnare);
    
    //First Tom Setup
    firstTom.setClickingTogglesState(true);
    firstTom.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    firstTom.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    firstTom.setToggleState(audioProcessor.firstTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(firstTom);
    
    //Second Tom Setup
    secondTom.setClickingTogglesState(true);
    secondTom.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    secondTom.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    secondTom.setToggleState(audioProcessor.secondTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(secondTom);
    
    //Third Tom Setup
    thirdTom.setClickingTogglesState(true);
    thirdTom.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    thirdTom.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    thirdTom.setToggleState(audioProcessor.thirdTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(thirdTom);
    
    //Fourth Tom Setup
    fourthTom.setClickingTogglesState(true);
    fourthTom.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    fourthTom.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    fourthTom.setToggleState(audioProcessor.fourthTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fourthTom);
    
    //Fifth Tom Setup
    fifthTom.setClickingTogglesState(true);
    fifthTom.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    fifthTom.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    fifthTom.setToggleState(audioProcessor.fifthTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fifthTom);
    
    //Sixth Tom Setup
    sixthTom.setClickingTogglesState(true);
    sixthTom.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    sixthTom.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    sixthTom.setToggleState(audioProcessor.sixthTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(sixthTom);
    
    //Seventh Tom Setup
    seventhTom.setClickingTogglesState(true);
    seventhTom.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    seventhTom.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    seventhTom.setToggleState(audioProcessor.seventhTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(seventhTom);
    
    //Eighth Tom Setup
    eighthTom.setClickingTogglesState(true);
    eighthTom.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    eighthTom.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    eighthTom.setToggleState(audioProcessor.eighthTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(eighthTom);
    
    //First Kick Setup
    firstKick.setClickingTogglesState(true);
    firstKick.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    firstKick.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    firstKick.setToggleState(audioProcessor.firstKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(firstKick);
    
    //Second Kick Setup
    secondKick.setClickingTogglesState(true);
    secondKick.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    secondKick.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    secondKick.setToggleState(audioProcessor.secondKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(secondKick);
    
    //Third Kick Setup
    thirdKick.setClickingTogglesState(true);
    thirdKick.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    thirdKick.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    thirdKick.setToggleState(audioProcessor.thirdKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(thirdKick);
    
    //Fourth Kick Setup
    fourthKick.setClickingTogglesState(true);
    fourthKick.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    fourthKick.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    fourthKick.setToggleState(audioProcessor.fourthKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fourthKick);
    
    //Fifth Kick Setup
    fifthKick.setClickingTogglesState(true);
    fifthKick.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    fifthKick.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    fifthKick.setToggleState(audioProcessor.fifthKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fifthKick);
    
    //Sixth Kick Setup
    sixthKick.setClickingTogglesState(true);
    sixthKick.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    sixthKick.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    sixthKick.setToggleState(audioProcessor.sixthKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(sixthKick);
    
    //Seventh Kick Setup
    seventhKick.setClickingTogglesState(true);
    seventhKick.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    seventhKick.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    seventhKick.setToggleState(audioProcessor.seventhKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(seventhKick);
    
    //Eighth Kick Setup
    eighthKick.setClickingTogglesState(true);
    eighthKick.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
    eighthKick.setColour(juce::TextButton::buttonOnColourId, juce::Colours::seagreen);
    eighthKick.setToggleState(audioProcessor.eighthKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(eighthKick);
}

Robotic_Drummer_Interface_MockupAudioProcessorEditor::~Robotic_Drummer_Interface_MockupAudioProcessorEditor()
{
}

//==============================================================================
void Robotic_Drummer_Interface_MockupAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::seagreen);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    g.setColour(juce::Colours::darkseagreen);
    
    auto border = 5;
    auto numCols = 8;
    auto numRows = 5;
    auto area = getLocalBounds().reduced(border * 4);
    auto upperArea = area.removeFromTop(area.getHeight()/4);
    auto screenArea = upperArea.removeFromLeft(area.getWidth()/3);
    g.fillRect(screenArea);
    auto drumsArea = area.removeFromBottom(area.getHeight()-20);
    g.fillRect(drumsArea);
    
    //Get drum row height
    auto rowHeight = drumsArea.getHeight()/numRows;
    
    //Set up row labels
    auto drumLabels = drumsArea.removeFromLeft(border*8);
    drumLabels.removeFromTop(rowHeight);
    auto firstLabel = drumLabels.removeFromTop(rowHeight);
    auto secondLabel = drumLabels.removeFromTop(rowHeight);
    auto thirdLabel = drumLabels.removeFromTop(rowHeight);
    auto fourthLabel = drumLabels.removeFromTop(rowHeight);
    
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
    
    //Set up beats
    auto firstBeat = firstColumn.removeFromTop(rowHeight);
    auto secondBeat = secondColumn.removeFromTop(rowHeight);
    auto thirdBeat = thirdColumn.removeFromTop(rowHeight);
    auto fourthBeat = fourthColumn.removeFromTop(rowHeight);
    auto fifthBeat = fifthColumn.removeFromTop(rowHeight);
    auto sixthBeat = sixthColumn.removeFromTop(rowHeight);
    auto seventhBeat = seventhColumn.removeFromTop(rowHeight);
    auto eighthBeat = eighthColumn.removeFromTop(rowHeight);
    
    //Testing
    g.setColour(juce::Colours::blue);
}

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto border = 5;
    auto numCols = 8;
    auto numRows = 5;
    auto area = getLocalBounds().reduced(border * 4);
    auto screenArea = area.removeFromTop(area.getHeight()/3).removeFromLeft(area.getWidth()/4);
    auto drumsArea = area.removeFromBottom(area.getHeight()-20);
    
    //Get drum row height
    auto rowHeight = drumsArea.getHeight()/numRows;
    
    //Set up row labels
    auto drumLabels = drumsArea.removeFromLeft(border*20);
    drumLabels.removeFromTop(rowHeight);
    auto firstLabel = drumLabels.removeFromTop(rowHeight);
    auto secondLabel = drumLabels.removeFromTop(rowHeight);
    auto thirdLabel = drumLabels.removeFromTop(rowHeight);
    auto fourthLabel = drumLabels.removeFromTop(rowHeight);
    
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
    
    //Set up beats
    auto firstBeat = firstColumn.removeFromTop(rowHeight);
    auto secondBeat = secondColumn.removeFromTop(rowHeight);
    auto thirdBeat = thirdColumn.removeFromTop(rowHeight);
    auto fourthBeat = fourthColumn.removeFromTop(rowHeight);
    auto fifthBeat = fifthColumn.removeFromTop(rowHeight);
    auto sixthBeat = sixthColumn.removeFromTop(rowHeight);
    auto seventhBeat = seventhColumn.removeFromTop(rowHeight);
    auto eighthBeat = eighthColumn.removeFromTop(rowHeight);
    
    //Set up hi hat
    auto firstHiHatArea = firstColumn.removeFromTop(rowHeight);
    auto secondHiHatArea = secondColumn.removeFromTop(rowHeight);
    auto thirdHiHatArea = thirdColumn.removeFromTop(rowHeight);
    auto fourthHiHatArea = fourthColumn.removeFromTop(rowHeight);
    auto fifthHiHatArea = fifthColumn.removeFromTop(rowHeight);
    auto sixthHiHatArea = sixthColumn.removeFromTop(rowHeight);
    auto seventhHiHatArea = seventhColumn.removeFromTop(rowHeight);
    auto eighthHiHatArea = eighthColumn.removeFromTop(rowHeight);
    
    firstHiHat.setBounds(firstHiHatArea);
    secondHiHat.setBounds(secondHiHatArea);
    thirdHiHat.setBounds(thirdHiHatArea);
    fourthHiHat.setBounds(fourthHiHatArea);
    fifthHiHat.setBounds(fifthHiHatArea);
    sixthHiHat.setBounds(sixthHiHatArea);
    seventhHiHat.setBounds(seventhHiHatArea);
    eighthHiHat.setBounds(eighthHiHatArea);
    
    //Set up snare
    auto firstSnareArea = firstColumn.removeFromTop(rowHeight);
    auto secondSnareArea = secondColumn.removeFromTop(rowHeight);
    auto thirdSnareArea = thirdColumn.removeFromTop(rowHeight);
    auto fourthSnareArea = fourthColumn.removeFromTop(rowHeight);
    auto fifthSnareArea = fifthColumn.removeFromTop(rowHeight);
    auto sixthSnareArea = sixthColumn.removeFromTop(rowHeight);
    auto seventhSnareArea = seventhColumn.removeFromTop(rowHeight);
    auto eighthSnareArea = eighthColumn.removeFromTop(rowHeight);
    
    firstSnare.setBounds(firstSnareArea);
    secondSnare.setBounds(secondSnareArea);
    thirdSnare.setBounds(thirdSnareArea);
    fourthSnare.setBounds(fourthSnareArea);
    fifthSnare.setBounds(fifthSnareArea);
    sixthSnare.setBounds(sixthSnareArea);
    seventhSnare.setBounds(seventhSnareArea);
    eighthSnare.setBounds(eighthSnareArea);
    
    //Set up tom
    auto firstTomArea = firstColumn.removeFromTop(rowHeight);
    auto secondTomArea = secondColumn.removeFromTop(rowHeight);
    auto thirdTomArea = thirdColumn.removeFromTop(rowHeight);
    auto fourthTomArea = fourthColumn.removeFromTop(rowHeight);
    auto fifthTomArea = fifthColumn.removeFromTop(rowHeight);
    auto sixthTomArea = sixthColumn.removeFromTop(rowHeight);
    auto seventhTomArea = seventhColumn.removeFromTop(rowHeight);
    auto eighthTomArea = eighthColumn.removeFromTop(rowHeight);
    
    firstTom.setBounds(firstTomArea);
    secondTom.setBounds(secondTomArea);
    thirdTom.setBounds(thirdTomArea);
    fourthTom.setBounds(fourthTomArea);
    fifthTom.setBounds(fifthTomArea);
    sixthTom.setBounds(sixthTomArea);
    seventhTom.setBounds(seventhTomArea);
    eighthTom.setBounds(eighthTomArea);
    
    //Set up kick
    auto firstKickArea = firstColumn.removeFromTop(rowHeight);
    auto secondKickArea = secondColumn.removeFromTop(rowHeight);
    auto thirdKickArea = thirdColumn.removeFromTop(rowHeight);
    auto fourthKickArea = fourthColumn.removeFromTop(rowHeight);
    auto fifthKickArea = fifthColumn.removeFromTop(rowHeight);
    auto sixthKickArea = sixthColumn.removeFromTop(rowHeight);
    auto seventhKickArea = seventhColumn.removeFromTop(rowHeight);
    auto eighthKickArea = eighthColumn.removeFromTop(rowHeight);
    
    firstKick.setBounds(firstKickArea);
    secondKick.setBounds(secondKickArea);
    thirdKick.setBounds(thirdKickArea);
    fourthKick.setBounds(fourthKickArea);
    fifthKick.setBounds(fifthKickArea);
    sixthKick.setBounds(sixthKickArea);
    seventhKick.setBounds(seventhKickArea);
    eighthKick.setBounds(eighthKickArea);
}

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::buttonClicked (juce::Button * button)
{
    if(button == &firstHiHat)
    {
        if(firstHiHat.getToggleState() == true){
            audioProcessor.firstHiHatHit = true;
            DBG("mute");
        }
        else{
            audioProcessor.firstHiHatHit = false;
            DBG("unmute");
        }
    }
    else if(button == &secondHiHat)
    {
        if(secondHiHat.getToggleState() == true){
            audioProcessor.secondHiHatHit = true;
            DBG("bypass on");
        }
        else{
            audioProcessor.secondHiHatHit = false;
            DBG("bypass off");
        }
    }
    else if(button == &thirdHiHat)
    {
        if(thirdHiHat.getToggleState() == true){
            audioProcessor.thirdHiHatHit = true;
            DBG("bypass on");
        }
        else{
            audioProcessor.thirdHiHatHit = false;
            DBG("bypass off");
        }
    }
    else if(button == &fourthHiHat)
    {
        if(fourthHiHat.getToggleState() == true){
            audioProcessor.fourthHiHatHit = true;
            DBG("bypass on");
        }
        else{
            audioProcessor.fourthHiHatHit = false;
            DBG("bypass off");
        }
    }
    else if(button == &fifthHiHat)
    {
        if(fifthHiHat.getToggleState() == true){
            audioProcessor.fifthHiHatHit = true;
            DBG("bypass on");
        }
        else{
            audioProcessor.fifthHiHatHit = false;
            DBG("bypass off");
        }
    }
    else if(button == &sixthHiHat)
    {
        if(sixthHiHat.getToggleState() == true){
            audioProcessor.sixthHiHatHit = true;
            DBG("bypass on");
        }
        else{
            audioProcessor.sixthHiHatHit = false;
            DBG("bypass off");
        }
    }
    else if(button == &seventhHiHat)
    {
        if(seventhHiHat.getToggleState() == true){
            audioProcessor.seventhHiHatHit = true;
            DBG("bypass on");
        }
        else{
            audioProcessor.seventhHiHatHit = false;
            DBG("bypass off");
        }
    }
    else if(button == &eighthHiHat)
    {
        if(eighthHiHat.getToggleState() == true){
            audioProcessor.eighthHiHatHit = true;
            DBG("bypass on");
        }
        else{
            audioProcessor.eighthHiHatHit = false;
            DBG("bypass off");
        }
    }
}
