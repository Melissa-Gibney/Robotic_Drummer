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
    
    juce::Colour buttonOnColor(0xFF7689CF);
    juce::Colour buttonOffColor(0xFF9BA5C9);
    juce::Colour buttonPressedColor(0xFF818599);
    
    //Set up the colors of the buttons
    otherLookAndFeel.setColour(juce::Slider::thumbColourId, buttonPressedColor);
    
    //GUI Label Setup
    addAndMakeVisible(guiLabel);
    firstLabel.setText("Tempo", juce::dontSendNotification);
    firstLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    firstLabel.setJustificationType(juce::Justification::centred);
    
    //GUI Content Label Setup
    addAndMakeVisible(guiContent);
    firstLabel.setText("120", juce::dontSendNotification);
    firstLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    firstLabel.setJustificationType(juce::Justification::centred);
    
    //Universal Knob Setup
    addAndMakeVisible(universalKnob);
    universalKnob.setSliderStyle(juce::Slider::LinearHorizontal);
    universalKnob.setNumDecimalPlacesToDisplay(2);
    universalKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    universalKnob.setTextValueSuffix("");
    
    //Universal Button Setup
    universalButton.setClickingTogglesState(false);
    universalButton.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    universalButton.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    universalButton.setToggleState(audioProcessor.firstHiHatHit, juce::NotificationType::dontSendNotification);
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
    
    //Second Hi Hat Setup
    secondHiHat.setClickingTogglesState(true);
    secondHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    secondHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    secondHiHat.setToggleState(audioProcessor.secondHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(secondHiHat);
    
    //Third Hi Hat Setup
    thirdHiHat.setClickingTogglesState(true);
    thirdHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    thirdHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    thirdHiHat.setToggleState(audioProcessor.thirdHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(thirdHiHat);
    
    //Fourth Hi Hat Setup
    fourthHiHat.setClickingTogglesState(true);
    fourthHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fourthHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fourthHiHat.setToggleState(audioProcessor.fourthHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fourthHiHat);
    
    //Fifth Hi Hat Setup
    fifthHiHat.setClickingTogglesState(true);
    fifthHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fifthHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fifthHiHat.setToggleState(audioProcessor.fifthHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fifthHiHat);
    
    //Sixth Hi Hat Setup
    sixthHiHat.setClickingTogglesState(true);
    sixthHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    sixthHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    sixthHiHat.setToggleState(audioProcessor.sixthHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(sixthHiHat);
    
    //Seventh Hi Hat Setup
    seventhHiHat.setClickingTogglesState(true);
    seventhHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    seventhHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    seventhHiHat.setToggleState(audioProcessor.seventhHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(seventhHiHat);
    
    //Eighth Hi Hat Setup
    eighthHiHat.setClickingTogglesState(true);
    eighthHiHat.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    eighthHiHat.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    eighthHiHat.setToggleState(audioProcessor.eighthHiHatHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(eighthHiHat);
    
    //First Snare Setup
    firstSnare.setClickingTogglesState(true);
    firstSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    firstSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    firstSnare.setToggleState(audioProcessor.firstSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(firstSnare);
    
    //Second Snare Setup
    secondSnare.setClickingTogglesState(true);
    secondSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    secondSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    secondSnare.setToggleState(audioProcessor.secondSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(secondSnare);
    
    //Third Snare Setup
    thirdSnare.setClickingTogglesState(true);
    thirdSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    thirdSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    thirdSnare.setToggleState(audioProcessor.thirdSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(thirdSnare);
    
    //Fourth Snare Setup
    fourthSnare.setClickingTogglesState(true);
    fourthSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fourthSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fourthSnare.setToggleState(audioProcessor.fourthSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fourthSnare);
    
    //Fifth Snare Setup
    fifthSnare.setClickingTogglesState(true);
    fifthSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fifthSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fifthSnare.setToggleState(audioProcessor.fifthSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fifthSnare);
    
    //Sixth Snare Setup
    sixthSnare.setClickingTogglesState(true);
    sixthSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    sixthSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    sixthSnare.setToggleState(audioProcessor.sixthSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(sixthSnare);
    
    //Seventh Snare Setup
    seventhSnare.setClickingTogglesState(true);
    seventhSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    seventhSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    seventhSnare.setToggleState(audioProcessor.seventhSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(seventhSnare);
    
    //Eighth Snare Setup
    eighthSnare.setClickingTogglesState(true);
    eighthSnare.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    eighthSnare.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    eighthSnare.setToggleState(audioProcessor.eighthSnareHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(eighthSnare);
    
    //First Tom Setup
    firstTom.setClickingTogglesState(true);
    firstTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    firstTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    firstTom.setToggleState(audioProcessor.firstTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(firstTom);
    
    //Second Tom Setup
    secondTom.setClickingTogglesState(true);
    secondTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    secondTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    secondTom.setToggleState(audioProcessor.secondTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(secondTom);
    
    //Third Tom Setup
    thirdTom.setClickingTogglesState(true);
    thirdTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    thirdTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    thirdTom.setToggleState(audioProcessor.thirdTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(thirdTom);
    
    //Fourth Tom Setup
    fourthTom.setClickingTogglesState(true);
    fourthTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fourthTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fourthTom.setToggleState(audioProcessor.fourthTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fourthTom);
    
    //Fifth Tom Setup
    fifthTom.setClickingTogglesState(true);
    fifthTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fifthTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fifthTom.setToggleState(audioProcessor.fifthTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fifthTom);
    
    //Sixth Tom Setup
    sixthTom.setClickingTogglesState(true);
    sixthTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    sixthTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    sixthTom.setToggleState(audioProcessor.sixthTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(sixthTom);
    
    //Seventh Tom Setup
    seventhTom.setClickingTogglesState(true);
    seventhTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    seventhTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    seventhTom.setToggleState(audioProcessor.seventhTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(seventhTom);
    
    //Eighth Tom Setup
    eighthTom.setClickingTogglesState(true);
    eighthTom.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    eighthTom.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    eighthTom.setToggleState(audioProcessor.eighthTomHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(eighthTom);
    
    //First Kick Setup
    firstKick.setClickingTogglesState(true);
    firstKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    firstKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    firstKick.setToggleState(audioProcessor.firstKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(firstKick);
    
    //Second Kick Setup
    secondKick.setClickingTogglesState(true);
    secondKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    secondKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    secondKick.setToggleState(audioProcessor.secondKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(secondKick);
    
    //Third Kick Setup
    thirdKick.setClickingTogglesState(true);
    thirdKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    thirdKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    thirdKick.setToggleState(audioProcessor.thirdKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(thirdKick);
    
    //Fourth Kick Setup
    fourthKick.setClickingTogglesState(true);
    fourthKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fourthKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fourthKick.setToggleState(audioProcessor.fourthKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fourthKick);
    
    //Fifth Kick Setup
    fifthKick.setClickingTogglesState(true);
    fifthKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    fifthKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    fifthKick.setToggleState(audioProcessor.fifthKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(fifthKick);
    
    //Sixth Kick Setup
    sixthKick.setClickingTogglesState(true);
    sixthKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    sixthKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    sixthKick.setToggleState(audioProcessor.sixthKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(sixthKick);
    
    //Seventh Kick Setup
    seventhKick.setClickingTogglesState(true);
    seventhKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    seventhKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    seventhKick.setToggleState(audioProcessor.seventhKickHit, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(seventhKick);
    
    //Eighth Kick Setup
    eighthKick.setClickingTogglesState(true);
    eighthKick.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    eighthKick.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
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
    juce::Colour mainColor(0xFF161C33);
    juce::Colour secondaryColor(0xFF363C54);
    
    g.fillAll(mainColor);

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //Make custom colors
    g.setColour(secondaryColor);
    
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
    auto drumLabels = drumsArea.removeFromLeft(border*10);

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
    
    
    g.setColour(juce::Colours::red);
    g.fillEllipse(firstBeatArea.getX(), firstBeatArea.getY(), firstBeatArea.getWidth(), firstBeatArea.getHeight());
    g.setColour(juce::Colours::grey);
    g.fillEllipse(secondBeatArea.getX(), secondBeatArea.getY(), secondBeatArea.getWidth(), secondBeatArea.getHeight());
    g.fillEllipse(thirdBeatArea.getX(), thirdBeatArea.getY(), thirdBeatArea.getWidth(), thirdBeatArea.getHeight());
    g.fillEllipse(fourthBeatArea.getX(), fourthBeatArea.getY(), fourthBeatArea.getWidth(), fourthBeatArea.getHeight());
    g.fillEllipse(fifthBeatArea.getX(), fifthBeatArea.getY(), fifthBeatArea.getWidth(), fifthBeatArea.getHeight());
    g.fillEllipse(sixthBeatArea.getX(), sixthBeatArea.getY(), sixthBeatArea.getWidth(), sixthBeatArea.getHeight());
    g.fillEllipse(seventhBeatArea.getX(), seventhBeatArea.getY(), seventhBeatArea.getWidth(), seventhBeatArea.getHeight());
    g.fillEllipse(eighthBeatArea.getX(), eighthBeatArea.getY(), eighthBeatArea.getWidth(), eighthBeatArea.getHeight());
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
    auto drumLabels = drumsArea.removeFromLeft(border*10);
    drumLabels.removeFromTop(rowHeight/2);
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
    auto firstBeatArea = firstColumn.removeFromTop(rowHeight/2).reduced(border);
    firstBeatArea.removeFromLeft(reduceButtonWidth);
    firstBeatArea.removeFromRight(reduceButtonWidth);
    firstBeatArea.reduce(10, 10);
    auto secondBeatArea = secondColumn.removeFromTop(rowHeight/2).reduced(border);
    secondBeatArea.removeFromLeft(reduceButtonWidth);
    secondBeatArea.removeFromRight(reduceButtonWidth);
    secondBeatArea.reduce(10, 10);
    auto thirdBeatArea = thirdColumn.removeFromTop(rowHeight/2).reduced(border);
    thirdBeatArea.removeFromLeft(reduceButtonWidth);
    thirdBeatArea.removeFromRight(reduceButtonWidth);
    thirdBeatArea.reduce(10, 10);
    auto fourthBeatArea = fourthColumn.removeFromTop(rowHeight/2).reduced(border);
    fourthBeatArea.removeFromLeft(reduceButtonWidth);
    fourthBeatArea.removeFromRight(reduceButtonWidth);
    fourthBeatArea.reduce(10, 10);
    auto fifthBeatArea = fifthColumn.removeFromTop(rowHeight/2).reduced(border);
    fifthBeatArea.removeFromLeft(reduceButtonWidth);
    fifthBeatArea.removeFromRight(reduceButtonWidth);
    fifthBeatArea.reduce(10, 10);
    auto sixthBeatArea = sixthColumn.removeFromTop(rowHeight/2).reduced(border);
    sixthBeatArea.removeFromLeft(reduceButtonWidth);
    sixthBeatArea.removeFromRight(reduceButtonWidth);
    sixthBeatArea.reduce(10, 10);
    auto seventhBeatArea = seventhColumn.removeFromTop(rowHeight/2).reduced(border);
    seventhBeatArea.removeFromLeft(reduceButtonWidth);
    seventhBeatArea.removeFromRight(reduceButtonWidth);
    seventhBeatArea.reduce(10, 10);
    auto eighthBeatArea = eighthColumn.removeFromTop(rowHeight/2).reduced(border);
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
    auto firstHiHatArea = firstColumn.removeFromTop(rowHeight).reduced(border);
    firstHiHatArea.removeFromLeft(reduceButtonWidth);
    firstHiHatArea.removeFromRight(reduceButtonWidth);
    auto secondHiHatArea = secondColumn.removeFromTop(rowHeight).reduced(border);
    secondHiHatArea.removeFromLeft(reduceButtonWidth);
    secondHiHatArea.removeFromRight(reduceButtonWidth);
    auto thirdHiHatArea = thirdColumn.removeFromTop(rowHeight).reduced(border);
    thirdHiHatArea.removeFromLeft(reduceButtonWidth);
    thirdHiHatArea.removeFromRight(reduceButtonWidth);
    auto fourthHiHatArea = fourthColumn.removeFromTop(rowHeight).reduced(border);
    fourthHiHatArea.removeFromLeft(reduceButtonWidth);
    fourthHiHatArea.removeFromRight(reduceButtonWidth);
    auto fifthHiHatArea = fifthColumn.removeFromTop(rowHeight).reduced(border);
    fifthHiHatArea.removeFromLeft(reduceButtonWidth);
    fifthHiHatArea.removeFromRight(reduceButtonWidth);
    auto sixthHiHatArea = sixthColumn.removeFromTop(rowHeight).reduced(border);
    sixthHiHatArea.removeFromLeft(reduceButtonWidth);
    sixthHiHatArea.removeFromRight(reduceButtonWidth);
    auto seventhHiHatArea = seventhColumn.removeFromTop(rowHeight).reduced(border);
    seventhHiHatArea.removeFromLeft(reduceButtonWidth);
    seventhHiHatArea.removeFromRight(reduceButtonWidth);
    auto eighthHiHatArea = eighthColumn.removeFromTop(rowHeight).reduced(border);
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
    auto firstSnareArea = firstColumn.removeFromTop(rowHeight).reduced(border);
    firstSnareArea.removeFromLeft(reduceButtonWidth);
    firstSnareArea.removeFromRight(reduceButtonWidth);
    auto secondSnareArea = secondColumn.removeFromTop(rowHeight).reduced(border);
    secondSnareArea.removeFromLeft(reduceButtonWidth);
    secondSnareArea.removeFromRight(reduceButtonWidth);
    auto thirdSnareArea = thirdColumn.removeFromTop(rowHeight).reduced(border);
    thirdSnareArea.removeFromLeft(reduceButtonWidth);
    thirdSnareArea.removeFromRight(reduceButtonWidth);
    auto fourthSnareArea = fourthColumn.removeFromTop(rowHeight).reduced(border);
    fourthSnareArea.removeFromLeft(reduceButtonWidth);
    fourthSnareArea.removeFromRight(reduceButtonWidth);
    auto fifthSnareArea = fifthColumn.removeFromTop(rowHeight).reduced(border);
    fifthSnareArea.removeFromLeft(reduceButtonWidth);
    fifthSnareArea.removeFromRight(reduceButtonWidth);
    auto sixthSnareArea = sixthColumn.removeFromTop(rowHeight).reduced(border);
    sixthSnareArea.removeFromLeft(reduceButtonWidth);
    sixthSnareArea.removeFromRight(reduceButtonWidth);
    auto seventhSnareArea = seventhColumn.removeFromTop(rowHeight).reduced(border);
    seventhSnareArea.removeFromLeft(reduceButtonWidth);
    seventhSnareArea.removeFromRight(reduceButtonWidth);
    auto eighthSnareArea = eighthColumn.removeFromTop(rowHeight).reduced(border);
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
    auto firstTomArea = firstColumn.removeFromTop(rowHeight).reduced(border);
    firstTomArea.removeFromLeft(reduceButtonWidth);
    firstTomArea.removeFromRight(reduceButtonWidth);
    auto secondTomArea = secondColumn.removeFromTop(rowHeight).reduced(border);
    secondTomArea.removeFromLeft(reduceButtonWidth);
    secondTomArea.removeFromRight(reduceButtonWidth);
    auto thirdTomArea = thirdColumn.removeFromTop(rowHeight).reduced(border);
    thirdTomArea.removeFromLeft(reduceButtonWidth);
    thirdTomArea.removeFromRight(reduceButtonWidth);
    auto fourthTomArea = fourthColumn.removeFromTop(rowHeight).reduced(border);
    fourthTomArea.removeFromLeft(reduceButtonWidth);
    fourthTomArea.removeFromRight(reduceButtonWidth);
    auto fifthTomArea = fifthColumn.removeFromTop(rowHeight).reduced(border);
    fifthTomArea.removeFromLeft(reduceButtonWidth);
    fifthTomArea.removeFromRight(reduceButtonWidth);
    auto sixthTomArea = sixthColumn.removeFromTop(rowHeight).reduced(border);
    sixthTomArea.removeFromLeft(reduceButtonWidth);
    sixthTomArea.removeFromRight(reduceButtonWidth);
    auto seventhTomArea = seventhColumn.removeFromTop(rowHeight).reduced(border);
    seventhTomArea.removeFromLeft(reduceButtonWidth);
    seventhTomArea.removeFromRight(reduceButtonWidth);
    auto eighthTomArea = eighthColumn.removeFromTop(rowHeight).reduced(border);
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
    auto firstKickArea = firstColumn.removeFromTop(rowHeight).reduced(border);
    firstKickArea.removeFromLeft(reduceButtonWidth);
    firstKickArea.removeFromRight(reduceButtonWidth);
    auto secondKickArea = secondColumn.removeFromTop(rowHeight).reduced(border);
    secondKickArea.removeFromLeft(reduceButtonWidth);
    secondKickArea.removeFromRight(reduceButtonWidth);
    auto thirdKickArea = thirdColumn.removeFromTop(rowHeight).reduced(border);
    thirdKickArea.removeFromLeft(reduceButtonWidth);
    thirdKickArea.removeFromRight(reduceButtonWidth);
    auto fourthKickArea = fourthColumn.removeFromTop(rowHeight).reduced(border);
    fourthKickArea.removeFromLeft(reduceButtonWidth);
    fourthKickArea.removeFromRight(reduceButtonWidth);
    auto fifthKickArea = fifthColumn.removeFromTop(rowHeight).reduced(border);
    fifthKickArea.removeFromLeft(reduceButtonWidth);
    fifthKickArea.removeFromRight(reduceButtonWidth);
    auto sixthKickArea = sixthColumn.removeFromTop(rowHeight).reduced(border);
    sixthKickArea.removeFromLeft(reduceButtonWidth);
    sixthKickArea.removeFromRight(reduceButtonWidth);
    auto seventhKickArea = seventhColumn.removeFromTop(rowHeight).reduced(border);
    seventhKickArea.removeFromLeft(reduceButtonWidth);
    seventhKickArea.removeFromRight(reduceButtonWidth);
    auto eighthKickArea = eighthColumn.removeFromTop(rowHeight).reduced(border);
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

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::buttonClicked (juce::Button * button)
{
    if(button == &firstHiHat)
    {
        if(firstHiHat.getToggleState() == true){
            audioProcessor.firstHiHatHit = true;
            DBG("first hihat on");
        }
        else{
            audioProcessor.firstHiHatHit = false;
            DBG("first hihat off");
        }
    }
    else if(button == &secondHiHat)
    {
        if(secondHiHat.getToggleState() == true){
            audioProcessor.secondHiHatHit = true;
            DBG("secon hihat on");
        }
        else{
            audioProcessor.secondHiHatHit = false;
            DBG("second hihat off");
        }
    }
    else if(button == &thirdHiHat)
    {
        if(thirdHiHat.getToggleState() == true){
            audioProcessor.thirdHiHatHit = true;
            DBG("third hihat on");
        }
        else{
            audioProcessor.thirdHiHatHit = false;
            DBG("third hihat off");
        }
    }
    else if(button == &fourthHiHat)
    {
        if(fourthHiHat.getToggleState() == true){
            audioProcessor.fourthHiHatHit = true;
            DBG("fourth hihat on");
        }
        else{
            audioProcessor.fourthHiHatHit = false;
            DBG("fourth hihat off");
        }
    }
    else if(button == &fifthHiHat)
    {
        if(fifthHiHat.getToggleState() == true){
            audioProcessor.fifthHiHatHit = true;
            DBG("fifth hihat on");
        }
        else{
            audioProcessor.fifthHiHatHit = false;
            DBG("fifth hihat off");
        }
    }
    else if(button == &sixthHiHat)
    {
        if(sixthHiHat.getToggleState() == true){
            audioProcessor.sixthHiHatHit = true;
            DBG("sixth hihat on");
        }
        else{
            audioProcessor.sixthHiHatHit = false;
            DBG("sixth hihat off");
        }
    }
    else if(button == &seventhHiHat)
    {
        if(seventhHiHat.getToggleState() == true){
            audioProcessor.seventhHiHatHit = true;
            DBG("seventh hihat on");
        }
        else{
            audioProcessor.seventhHiHatHit = false;
            DBG("seventh hihat off");
        }
    }
    else if(button == &eighthHiHat)
    {
        if(eighthHiHat.getToggleState() == true){
            audioProcessor.eighthHiHatHit = true;
            DBG("eighth hihat on");
        }
        else{
            audioProcessor.eighthHiHatHit = false;
            DBG("eighth hihat off");
        }
    }
    else if(button == &firstSnare)
    {
        if(firstSnare.getToggleState() == true){
            audioProcessor.firstSnareHit = true;
            DBG("first snare on");
        }
        else{
            audioProcessor.firstSnareHit = false;
            DBG("first snare off");
        }
    }
    else if(button == &secondSnare)
    {
        if(secondSnare.getToggleState() == true){
            audioProcessor.secondSnareHit = true;
            DBG("secon snare on");
        }
        else{
            audioProcessor.secondSnareHit = false;
            DBG("second snare off");
        }
    }
    else if(button == &thirdSnare)
    {
        if(thirdSnare.getToggleState() == true){
            audioProcessor.thirdSnareHit = true;
            DBG("third snare on");
        }
        else{
            audioProcessor.thirdSnareHit = false;
            DBG("third snare off");
        }
    }
    else if(button == &fourthSnare)
    {
        if(fourthSnare.getToggleState() == true){
            audioProcessor.fourthSnareHit = true;
            DBG("fourth snare on");
        }
        else{
            audioProcessor.fourthSnareHit = false;
            DBG("fourth snare off");
        }
    }
    else if(button == &fifthSnare)
    {
        if(fifthSnare.getToggleState() == true){
            audioProcessor.fifthSnareHit = true;
            DBG("fifth snare on");
        }
        else{
            audioProcessor.fifthSnareHit = false;
            DBG("fifth snare off");
        }
    }
    else if(button == &sixthSnare)
    {
        if(sixthSnare.getToggleState() == true){
            audioProcessor.sixthSnareHit = true;
            DBG("sixth snare on");
        }
        else{
            audioProcessor.sixthSnareHit = false;
            DBG("sixth snare off");
        }
    }
    else if(button == &seventhSnare)
    {
        if(seventhSnare.getToggleState() == true){
            audioProcessor.seventhSnareHit = true;
            DBG("seventh snare on");
        }
        else{
            audioProcessor.seventhSnareHit = false;
            DBG("seventh snare off");
        }
    }
    else if(button == &eighthSnare)
    {
        if(eighthSnare.getToggleState() == true){
            audioProcessor.eighthSnareHit = true;
            DBG("eighth snare on");
        }
        else{
            audioProcessor.eighthSnareHit = false;
            DBG("eighth snare off");
        }
    }
    else if(button == &firstTom)
    {
        if(firstTom.getToggleState() == true){
            audioProcessor.firstTomHit = true;
            DBG("first tom on");
        }
        else{
            audioProcessor.firstTomHit = false;
            DBG("first tom off");
        }
    }
    else if(button == &secondTom)
    {
        if(secondTom.getToggleState() == true){
            audioProcessor.secondTomHit = true;
            DBG("secon tom on");
        }
        else{
            audioProcessor.secondTomHit = false;
            DBG("second tom off");
        }
    }
    else if(button == &thirdTom)
    {
        if(thirdTom.getToggleState() == true){
            audioProcessor.thirdTomHit = true;
            DBG("third tom on");
        }
        else{
            audioProcessor.thirdTomHit = false;
            DBG("third tom off");
        }
    }
    else if(button == &fourthTom)
    {
        if(fourthTom.getToggleState() == true){
            audioProcessor.fourthTomHit = true;
            DBG("fourth tom on");
        }
        else{
            audioProcessor.fourthTomHit = false;
            DBG("fourth tom off");
        }
    }
    else if(button == &fifthTom)
    {
        if(fifthTom.getToggleState() == true){
            audioProcessor.fifthTomHit = true;
            DBG("fifth tom on");
        }
        else{
            audioProcessor.fifthTomHit = false;
            DBG("fifth tom off");
        }
    }
    else if(button == &sixthTom)
    {
        if(sixthTom.getToggleState() == true){
            audioProcessor.sixthTomHit = true;
            DBG("sixth tom on");
        }
        else{
            audioProcessor.sixthTomHit = false;
            DBG("sixth tom off");
        }
    }
    else if(button == &seventhTom)
    {
        if(seventhTom.getToggleState() == true){
            audioProcessor.seventhTomHit = true;
            DBG("seventh tom on");
        }
        else{
            audioProcessor.seventhTomHit = false;
            DBG("seventh tom off");
        }
    }
    else if(button == &eighthTom)
    {
        if(eighthTom.getToggleState() == true){
            audioProcessor.eighthTomHit = true;
            DBG("eighth tom on");
        }
        else{
            audioProcessor.eighthTomHit = false;
            DBG("eighth tom off");
        }
    }
    else if(button == &firstKick)
    {
        if(firstKick.getToggleState() == true){
            audioProcessor.firstKickHit = true;
            DBG("first kick on");
        }
        else{
            audioProcessor.firstKickHit = false;
            DBG("first kick off");
        }
    }
    else if(button == &secondKick)
    {
        if(secondKick.getToggleState() == true){
            audioProcessor.secondKickHit = true;
            DBG("secon kick on");
        }
        else{
            audioProcessor.secondKickHit = false;
            DBG("second kick off");
        }
    }
    else if(button == &thirdKick)
    {
        if(thirdKick.getToggleState() == true){
            audioProcessor.thirdKickHit = true;
            DBG("third kick on");
        }
        else{
            audioProcessor.thirdKickHit = false;
            DBG("third kick off");
        }
    }
    else if(button == &fourthKick)
    {
        if(fourthKick.getToggleState() == true){
            audioProcessor.fourthKickHit = true;
            DBG("fourth kick on");
        }
        else{
            audioProcessor.fourthKickHit = false;
            DBG("fourth kick off");
        }
    }
    else if(button == &fifthKick)
    {
        if(fifthKick.getToggleState() == true){
            audioProcessor.fifthKickHit = true;
            DBG("fifth kick on");
        }
        else{
            audioProcessor.fifthKickHit = false;
            DBG("fifth kick off");
        }
    }
    else if(button == &sixthKick)
    {
        if(sixthKick.getToggleState() == true){
            audioProcessor.sixthKickHit = true;
            DBG("sixth kick on");
        }
        else{
            audioProcessor.sixthKickHit = false;
            DBG("sixth kick off");
        }
    }
    else if(button == &seventhKick)
    {
        if(seventhKick.getToggleState() == true){
            audioProcessor.seventhKickHit = true;
            DBG("seventh kick on");
        }
        else{
            audioProcessor.seventhKickHit = false;
            DBG("seventh kick off");
        }
    }
    else if(button == &eighthKick)
    {
        if(eighthKick.getToggleState() == true){
            audioProcessor.eighthKickHit = true;
            DBG("eighth kick on");
        }
        else{
            audioProcessor.eighthKickHit = false;
            DBG("eighth kick off");
        }
    }
}

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if(slider == &universalKnob)
    {
        
    }
}

juce::Rectangle<int> getButtonArea(juce::Rectangle<int> column, float columnWidth, float rowHeight, float border)
{
    float reduceButtonWidth = (columnWidth - rowHeight)/2.0;
    
    juce::Rectangle<int> buttonArea = column.removeFromTop(rowHeight).reduced(border);
    buttonArea.removeFromLeft(reduceButtonWidth);
    buttonArea.removeFromRight(reduceButtonWidth);
    return buttonArea;
}
