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
    //juce::Colour buttonPressedColor(/*0xFF818599*/juce::Colours::grey);
    
    //Set up the colors of the buttons
    otherLookAndFeel.setColour(juce::Slider::thumbColourId, buttonOnColor);
    
    //GUI Label Setup
    addAndMakeVisible(guiLabel);
    guiLabel.setText("Tempo", juce::dontSendNotification);
    guiLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    guiLabel.setJustificationType(juce::Justification::centredLeft);
    
    //GUI Content Label Setup
    addAndMakeVisible(guiContent);
    guiContent.setText(juce::String(audioProcessor.tempo) + " bpm", juce::dontSendNotification);
    guiContent.setFont(juce::Font(16.0f, juce::Font::plain));
    guiContent.setJustificationType(juce::Justification::centred);
    
    //GUI Knob Setup
    addAndMakeVisible(guiKnob);
    guiKnob.setSliderStyle(juce::Slider::Rotary);
    guiKnob.setNumDecimalPlacesToDisplay(2);
    guiKnob.setRange(0, 500);
    guiKnob.setValue(250);
    guiKnob.setTextValueSuffix("");
    guiKnob.setTextBoxStyle(tempoKnob.NoTextBox, true, 0, 0);
    guiKnob.setColour(0x1001300, buttonOffColor);
    guiKnob.onValueChange = [this](){};
    
    //Left Arrow Button Setup
    addAndMakeVisible(leftArrowButton);
    leftArrowButton.setClickingTogglesState(false);
    leftArrowButton.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    leftArrowButton.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    leftArrowButton.setToggleState(false, juce::NotificationType::sendNotification);
    leftArrowButton.onClick = [this](){};
    
    //Right Arrow Button Setup
    addAndMakeVisible(rightArrowButton);
    rightArrowButton.setClickingTogglesState(false);
    rightArrowButton.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    rightArrowButton.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    rightArrowButton.setToggleState(false, juce::NotificationType::sendNotification);
    rightArrowButton.onClick = [this](){};
    
    //Tempo Button Label Setup
    addAndMakeVisible(tempoButtonLabel);
    tempoButtonLabel.setText("Reset Tempo", juce::dontSendNotification);
    tempoButtonLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    tempoButtonLabel.setJustificationType(juce::Justification::centred);
    
    //Tempo Knob Label Setup
    addAndMakeVisible(tempoKnobLabel);
    tempoKnobLabel.setText("Tempo", juce::dontSendNotification);
    tempoKnobLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    tempoKnobLabel.setJustificationType(juce::Justification::centred);
    
    //Tempo Button Setup
    tempoButton.setClickingTogglesState(false);
    tempoButton.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    tempoButton.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    tempoButton.setToggleState(audioProcessor.sequencerHits[0], juce::NotificationType::dontSendNotification);
    tempoButton.onClick = [this]()
    {
        tempoShown = true;
        audioProcessor.tempo = 120;
        tempoKnob.setValue(audioProcessor.tempo);
        guiLabel.setText("Tempo", juce::NotificationType::dontSendNotification);
        guiContent.setText(juce::String(audioProcessor.tempo), juce::NotificationType::dontSendNotification);
    };
    addAndMakeVisible(tempoButton);
    
    //Tempo Knob Setup
    addAndMakeVisible(tempoKnob);
    tempoKnob.setSliderStyle(juce::Slider::Rotary);
    tempoKnob.setNumDecimalPlacesToDisplay(2);
    tempoKnob.setRange(0, 500);
    tempoKnob.setValue(120);
    tempoKnob.setTextValueSuffix("");
    tempoKnob.setTextBoxStyle(tempoKnob.NoTextBox, true, 0, 0);
    tempoKnob.setColour(0x1001300, buttonOffColor);
    tempoKnob.onValueChange = [this]()
    {
        if(tempoKnob.getValue() == 0.0)
        {
            audioProcessor.tempo = 1.0;
        }
        else
        {
            audioProcessor.tempo = tempoKnob.getValue();
        }
        if(playButton.getToggleState())
        {
            startTimer(33, 60000/audioProcessor.tempo);
        }
        guiLabel.setText("Tempo", juce::NotificationType::dontSendNotification);
        guiContent.setText(juce::String(audioProcessor.tempo) + " bpm", juce::NotificationType::dontSendNotification);
    };
    
    //Velocity Knob Label Setup
    addAndMakeVisible(velocityKnobLabel);
    velocityKnobLabel.setText("Velocity", juce::dontSendNotification);
    velocityKnobLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    velocityKnobLabel.setJustificationType(juce::Justification::centred);
    
    //Velocity Knob Setup
    addAndMakeVisible(velocityKnob);
    velocityKnob.setSliderStyle(juce::Slider::Rotary);
    velocityKnob.setNumDecimalPlacesToDisplay(0);
    velocityKnob.setRange(0, 127);
    velocityKnob.setTextValueSuffix("");
    velocityKnob.setTextBoxStyle(velocityKnob.NoTextBox, true, 0, 0);
    velocityKnob.setColour(0x1001300, buttonOffColor);
    velocityKnob.onValueChange = [this]()
    {
        if(lastButtonPressed >= 1 && lastButtonPressed <= 32)
        {
            audioProcessor.sequencerVelocities[lastButtonPressed-1] = velocityKnob.getValue();
            guiLabel.setText("Velocity: Drum " + juce::String(int((lastButtonPressed-1)/8)+1) + ", Beat " + juce::String((lastButtonPressed-1)%8+1), juce::NotificationType::dontSendNotification);
            guiContent.setText(juce::String(audioProcessor.sequencerVelocities[lastButtonPressed-1]), juce::NotificationType::dontSendNotification);
        }
    };
    
    //Play Button Label Setup
    addAndMakeVisible(playButtonLabel);
    playButtonLabel.setText("Play/Stop", juce::dontSendNotification);
    playButtonLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    playButtonLabel.setJustificationType(juce::Justification::centred);
    
    //Play Button Setup
    playButton.setClickingTogglesState(true);
    playButton.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    playButton.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    playButton.setToggleState(false, juce::NotificationType::sendNotification);
    playButton.onClick = [this]()
    {
        audioProcessor.isPlaying = !audioProcessor.isPlaying;
        if(playButton.getToggleState())
        {
            startTimer(33, 60000/audioProcessor.tempo);
        }
        else
        {
            stopTimer(33);
        }
    };
    addAndMakeVisible(playButton);
    
    //Restart Button Label Setup
    addAndMakeVisible(restartButtonLabel);
    restartButtonLabel.setText("Restart", juce::dontSendNotification);
    restartButtonLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    restartButtonLabel.setJustificationType(juce::Justification::centred);
    
    //Restart Button Setup
    restartButton.setClickingTogglesState(false);
    restartButton.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    restartButton.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    restartButton.setToggleState(false, juce::NotificationType::sendNotification);
    restartButton.onClick = [this]()
    {
        for(int i = 0; i < 8; i++)
        {
            if(i == 0)
            {
                audioProcessor.beats[i] = true;
            }
            else
            {
                audioProcessor.beats[i] = false;
            }
        }
    };
    addAndMakeVisible(restartButton);
    
    //Velocity Mode Label Setup
    addAndMakeVisible(velocityModeLabel);
    velocityModeLabel.setText("Velocity Mode", juce::dontSendNotification);
    restartButtonLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    restartButtonLabel.setJustificationType(juce::Justification::centred);
    
    //Velocity Mode Button Setup
    velocityModeButton.setClickingTogglesState(true);
    velocityModeButton.setColour(juce::TextButton::buttonColourId, buttonOffColor);
    velocityModeButton.setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
    velocityModeButton.setToggleState(false, juce::NotificationType::sendNotification);
    velocityModeButton.onClick = [this]()
    {
        audioProcessor.velocityMode = !audioProcessor.velocityMode;
        if(audioProcessor.velocityMode == true)
        {
            //Set every flashing button to be false
            for(int i = 0; i < 32; i++)
            {
                audioProcessor.flashingButtons[i] = false;
                sequencerButtons[i].setToggleState(audioProcessor.flashingButtons[i], juce::NotificationType::dontSendNotification);
            }
        }
        else
        {
            //Set buttons to what they were before velocity mode
            for(int i = 0; i < 32; i++)
            {
                sequencerButtons[i].setToggleState(audioProcessor.sequencerHits[i], juce::NotificationType::dontSendNotification);
            }
        }
    };
    addAndMakeVisible(velocityModeButton);
    
    //Mute Label Setup
    addAndMakeVisible(muteLabel);
    muteLabel.setText("Mute", juce::dontSendNotification);
    muteLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    muteLabel.setJustificationType(juce::Justification::centred);
    
    //Mute Buttons Setup
    for(int i = 0; i < 4; i++)
    {
        muteButtons[i].setClickingTogglesState(true);
        muteButtons[i].setColour(juce::TextButton::buttonColourId, buttonOffColor);
        muteButtons[i].setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
        muteButtons[i].setToggleState(false, juce::NotificationType::sendNotification);
        muteButtons[i].onClick = [this](){};
        addAndMakeVisible(muteButtons[i]);
    }
    addAndMakeVisible(muteButtons);
    
    //Clear Label Setup
    addAndMakeVisible(clearLabel);
    clearLabel.setText("Clear", juce::dontSendNotification);
    clearLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    clearLabel.setJustificationType(juce::Justification::centred);
    
    //Clear Buttons Setup
    for(int i = 0; i < 4; i++)
    {
        clearButtons[i].setClickingTogglesState(false);
        clearButtons[i].setColour(juce::TextButton::buttonColourId, buttonOffColor);
        clearButtons[i].setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
        clearButtons[i].setToggleState(false, juce::NotificationType::sendNotification);
        clearButtons[i].onClick = [this, i]()
        {
            if(!audioProcessor.velocityMode)
            {
                switch(i)
                {
                    case 0:
                    {
                        for(int j = 0; j < 8; j++)
                        {
                            audioProcessor.sequencerHits[j] = false;
                            sequencerButtons[j].setToggleState(audioProcessor.sequencerHits[j], juce::NotificationType::dontSendNotification);
                        }
                        break;
                    }
                    case 1:
                    {
                        for(int j = 8; j < 16; j++)
                        {
                            audioProcessor.sequencerHits[j] = false;
                            sequencerButtons[j].setToggleState(audioProcessor.sequencerHits[j], juce::NotificationType::dontSendNotification);
                        }
                        break;
                    }
                    case 2:
                    {
                        for(int j = 16; j < 24; j++)
                        {
                            audioProcessor.sequencerHits[j] = false;
                            sequencerButtons[j].setToggleState(audioProcessor.sequencerHits[j], juce::NotificationType::dontSendNotification);
                        }
                        break;
                    }
                    default:
                    {
                        for(int j = 24; j < 32; j++)
                        {
                            audioProcessor.sequencerHits[j] = false;
                            sequencerButtons[j].setToggleState(audioProcessor.sequencerHits[j], juce::NotificationType::dontSendNotification);
                        }
                        break;
                    }
                }
            }
        };
        addAndMakeVisible(clearButtons[i]);
    }
    addAndMakeVisible(clearButtons);
    
    //Sequencer Label Setup
    addAndMakeVisible(sequencerLabel);
    sequencerLabel.setText("Drum Sequencer", juce::dontSendNotification);
    sequencerLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    sequencerLabel.setJustificationType(juce::Justification::centred);
    
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
    
    //Button Flash Timer Setup
    startTimer(34, 60000/audioProcessor.tempo);
    
    //Sequencer Buttons Setup
    for(int i = 0; i < 32; i++)
    {
        sequencerButtons[i].setClickingTogglesState(true);
        sequencerButtons[i].setColour(juce::TextButton::buttonColourId, buttonOffColor);
        sequencerButtons[i].setColour(juce::TextButton::buttonOnColourId, buttonOnColor);
        sequencerButtons[i].setToggleState(audioProcessor.sequencerHits[i], juce::NotificationType::dontSendNotification);
        addAndMakeVisible(sequencerButtons[i]);
        sequencerButtons[i].onClick = [this, i]()
        {
            lastButtonPressed = i+1;
            if(audioProcessor.velocityMode)
            {
                tempoShown = false;
                audioProcessor.flashingButtons[i] = !audioProcessor.flashingButtons[i];
                if(!audioProcessor.flashingButtons[i])
                {
                    sequencerButtons[i].setToggleState(false, juce::NotificationType::sendNotification);
                }
                for(int j = 0; j < 32; j++)
                {
                    if(j != lastButtonPressed-1)
                    {
                        sequencerButtons[j].setToggleState(false, juce::NotificationType::sendNotification);
                    }
                    //DBG(juce::String(j) + " " + juce::String(int(audioProcessor.flashingButtons[j])));
                }
                velocityKnob.setValue(audioProcessor.sequencerVelocities[i]);
                guiLabel.setText("Velocity: Drum " + juce::String(int(i/8)+1) + ", Beat " + juce::String(i%8+1), juce::NotificationType::dontSendNotification);
                guiContent.setText(juce::String(audioProcessor.sequencerVelocities[i]), juce::NotificationType::dontSendNotification);
            }
            else
            {
                if(sequencerButtons[i].getToggleState() == true){
                    audioProcessor.sequencerHits[i] = true;
                    tempoShown = true;
                    DBG(juce::String(i) + " on");
                }
                else{
                    audioProcessor.sequencerHits[i] = false;
                    tempoShown = true;
                    DBG(juce::String(i) + " off");
                }
            }
        };
        sequencerButtons[i].onStateChange = [this, i]()
        {
            if(sequencerButtons[i].isDown())
            {
                if(!isTimerRunning(i+1))
                {
                    startTimer(i+1, 1000); //Hold button for 1 second to trigger velocity change
                }
            }
            else if(!sequencerButtons[i].isOver() && !sequencerButtons[i].isDown())
            {
                if(isTimerRunning(i+1))
                {
                    stopTimer(i+1);
                }
            }
        };
        addAndMakeVisible(sequencerButtons[i]);
    }
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
    auto numRows = 6;
    auto area = getLocalBounds().reduced(border * 4);
    auto controlsArea = area.removeFromTop(area.getHeight()/3);
    auto guiControlsArea = controlsArea.removeFromLeft(controlsArea.getWidth()/3);
    auto screenArea = guiControlsArea.removeFromLeft(guiControlsArea.getWidth()*2/3);
    screenArea.removeFromBottom(screenArea.getHeight()/4);
    auto drumsArea = area.removeFromBottom(area.getHeight()-10);
    g.fillRect(screenArea);
    g.setColour(secondaryColor);
    //auto drumsArea = area.removeFromBottom(area.getHeight()-20);
    g.fillRect(drumsArea);
    
    //Get drum row height
    auto rowHeight = drumsArea.getHeight()/numRows;
    
    drumsArea.removeFromLeft(border*10);

    //Get column width
    auto columnWidth = drumsArea.getWidth()/numCols;
    
    //Set up columns
    drumsArea.removeFromLeft(border);
    drumsArea.removeFromTop(rowHeight);
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
    firstBeatArea.reduce(5, 5);
    beatAreas.add(firstBeatArea.getX(), firstBeatArea.getY(), firstBeatArea.getWidth(), firstBeatArea.getHeight());
    auto secondBeatArea = secondColumn.removeFromTop(rowHeight).reduced(border);
    secondBeatArea.removeFromLeft(reduceButtonWidth);
    secondBeatArea.removeFromRight(reduceButtonWidth);
    secondBeatArea.reduce(5, 5);
    beatAreas.add(secondBeatArea.getX(), secondBeatArea.getY(), secondBeatArea.getWidth(), secondBeatArea.getHeight());
    auto thirdBeatArea = thirdColumn.removeFromTop(rowHeight).reduced(border);
    thirdBeatArea.removeFromLeft(reduceButtonWidth);
    thirdBeatArea.removeFromRight(reduceButtonWidth);
    thirdBeatArea.reduce(5, 5);
    beatAreas.add(thirdBeatArea.getX(), thirdBeatArea.getY(), thirdBeatArea.getWidth(), thirdBeatArea.getHeight());
    auto fourthBeatArea = fourthColumn.removeFromTop(rowHeight).reduced(border);
    fourthBeatArea.removeFromLeft(reduceButtonWidth);
    fourthBeatArea.removeFromRight(reduceButtonWidth);
    fourthBeatArea.reduce(5, 5);
    beatAreas.add(fourthBeatArea.getX(), fourthBeatArea.getY(), fourthBeatArea.getWidth(), fourthBeatArea.getHeight());
    auto fifthBeatArea = fifthColumn.removeFromTop(rowHeight).reduced(border);
    fifthBeatArea.removeFromLeft(reduceButtonWidth);
    fifthBeatArea.removeFromRight(reduceButtonWidth);
    fifthBeatArea.reduce(5, 5);
    beatAreas.add(fifthBeatArea.getX(), fifthBeatArea.getY(), fifthBeatArea.getWidth(), fifthBeatArea.getHeight());
    auto sixthBeatArea = sixthColumn.removeFromTop(rowHeight).reduced(border);
    sixthBeatArea.removeFromLeft(reduceButtonWidth);
    sixthBeatArea.removeFromRight(reduceButtonWidth);
    sixthBeatArea.reduce(5, 5);
    beatAreas.add(sixthBeatArea.getX(), sixthBeatArea.getY(), sixthBeatArea.getWidth(), sixthBeatArea.getHeight());
    auto seventhBeatArea = seventhColumn.removeFromTop(rowHeight).reduced(border);
    seventhBeatArea.removeFromLeft(reduceButtonWidth);
    seventhBeatArea.removeFromRight(reduceButtonWidth);
    seventhBeatArea.reduce(5, 5);
    beatAreas.add(seventhBeatArea.getX(), seventhBeatArea.getY(), seventhBeatArea.getWidth(), seventhBeatArea.getHeight());
    auto eighthBeatArea = eighthColumn.removeFromTop(rowHeight).reduced(border);
    eighthBeatArea.removeFromLeft(reduceButtonWidth);
    eighthBeatArea.removeFromRight(reduceButtonWidth);
    eighthBeatArea.reduce(5, 5);
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
}

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto border = 5;
    auto numCols = 8;
    auto numRows = 6;
    auto area = getLocalBounds().reduced(border * 4);
    auto controlsArea = area.removeFromTop(area.getHeight()/3);
    auto guiControlsArea = controlsArea.removeFromLeft(controlsArea.getWidth()/3);
    auto screenArea = guiControlsArea.removeFromLeft(guiControlsArea.getWidth()*2/3);
    auto arrowsArea = screenArea.removeFromBottom(screenArea.getHeight()/4);
    auto leftArrowArea = arrowsArea.removeFromLeft(arrowsArea.getWidth()/2).reduced(border);
    auto rightArrowArea = arrowsArea.reduced(border);
    auto drumsArea = area.removeFromBottom(area.getHeight()-10);
    
    guiKnob.setBounds(guiControlsArea);
    leftArrowButton.setBounds(leftArrowArea);
    rightArrowButton.setBounds(rightArrowArea);
    
    //Set up universal knobs and buttons
    auto playRestartArea = controlsArea.removeFromRight(controlsArea.getWidth()/6);
    auto playButtonArea = playRestartArea.removeFromTop(playRestartArea.getHeight()/2);
    auto tempArea = playButtonArea;
    playButtonArea.removeFromLeft((tempArea.getWidth()-tempArea.getHeight())/2);
    playButtonArea.removeFromRight((tempArea.getWidth()-tempArea.getHeight())/2);
    playButtonArea.reduced(border);
    auto playButtonLabelArea = playButtonArea.removeFromBottom(playButtonArea.getHeight()/4);
    auto restartButtonArea = playRestartArea;
    tempArea = restartButtonArea;
    restartButtonArea.removeFromLeft((tempArea.getWidth()-tempArea.getHeight())/2);
    restartButtonArea.removeFromRight((tempArea.getWidth()-tempArea.getHeight())/2);
    restartButtonArea.reduced(border);
    auto restartButtonLabelArea = restartButtonArea.removeFromBottom(restartButtonArea.getHeight()/4);
    auto tempoKnobArea = controlsArea.removeFromRight(controlsArea.getWidth()/3);
    auto tempoKnobLabelArea = tempoKnobArea.removeFromBottom(tempoKnobArea.getHeight()/4);
    auto velocityKnobArea = controlsArea.removeFromRight(controlsArea.getWidth()/2);
    auto velocityKnobLabelArea = velocityKnobArea.removeFromBottom(velocityKnobArea.getHeight()/4);
    auto velocityModeArea = controlsArea;
    auto velocityModeLabelArea = velocityModeArea.removeFromBottom(velocityModeArea.getHeight()/4);
    auto velocityModeButtonArea = velocityModeArea;
    velocityModeButtonArea.removeFromLeft((velocityModeArea.getWidth()-velocityModeArea.getHeight())/2);
    velocityModeButtonArea.removeFromRight((velocityModeArea.getWidth()-velocityModeArea.getHeight())/2);
    velocityModeButtonArea.reduced(border*4);
    velocityModeLabelArea.removeFromLeft((velocityModeArea.getWidth()-velocityModeArea.getHeight())/2 + border);
    velocityModeLabelArea.removeFromRight((velocityModeArea.getWidth()-velocityModeArea.getHeight())/2 + border);
    
    playButton.setBounds(playButtonArea);
    playButtonLabel.setBounds(playButtonLabelArea);
    restartButton.setBounds(restartButtonArea);
    restartButtonLabel.setBounds(restartButtonLabelArea);
    tempoKnob.setBounds(tempoKnobArea);
    tempoKnobLabel.setBounds(tempoKnobLabelArea);
    velocityKnob.setBounds(velocityKnobArea);
    velocityKnobLabel.setBounds(velocityKnobLabelArea);
    velocityModeButton.setBounds(velocityModeButtonArea);
    velocityModeLabel.setBounds(velocityModeLabelArea);
    playButton.setBounds(playButtonArea);
    playButtonLabel.setBounds(playButtonLabelArea);
    
    //Set up LCD Screen and Labels
    guiContent.setBounds(screenArea);
    
    auto guiLabelArea = screenArea.removeFromTop(screenArea.getHeight()/4);
    
    guiLabel.setBounds(guiLabelArea);
    
    //Get drum row height
    auto rowHeight = drumsArea.getHeight()/numRows;
    
    //Set up sequencer label
    auto sequencerLabelArea = drumsArea.removeFromTop(rowHeight);
    sequencerLabelArea = sequencerLabelArea.removeFromRight(sequencerLabelArea.getWidth() - border*10);
    sequencerLabel.setBounds(sequencerLabelArea);
    
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
    auto columnWidth = drumsArea.getWidth()/(numCols+2);
    
    float reduceButtonWidth = (columnWidth - rowHeight)/2.0;
    
    auto reducedAmount = 5;
    
    //Set up columns
    
    //Set up mute buttons
    auto muteArea = drumsArea.removeFromLeft(columnWidth);
    auto muteLabelArea = muteArea.removeFromTop(rowHeight);
    auto firstMuteArea = muteArea.removeFromTop(rowHeight);
    firstMuteArea.removeFromLeft(reduceButtonWidth);
    firstMuteArea.removeFromRight(reduceButtonWidth);
    firstMuteArea.reduce(reducedAmount, reducedAmount);
    auto secondMuteArea = muteArea.removeFromTop(rowHeight);
    secondMuteArea.removeFromLeft(reduceButtonWidth);
    secondMuteArea.removeFromRight(reduceButtonWidth);
    secondMuteArea.reduce(reducedAmount, reducedAmount);
    auto thirdMuteArea = muteArea.removeFromTop(rowHeight);
    thirdMuteArea.removeFromLeft(reduceButtonWidth);
    thirdMuteArea.removeFromRight(reduceButtonWidth);
    thirdMuteArea.reduce(reducedAmount, reducedAmount);
    auto fourthMuteArea = muteArea;
    fourthMuteArea.removeFromLeft(reduceButtonWidth);
    fourthMuteArea.removeFromRight(reduceButtonWidth);
    fourthMuteArea.reduce(reducedAmount, reducedAmount);
    
    muteLabel.setBounds(muteLabelArea);
    muteButtons[0].setBounds(firstMuteArea);
    muteButtons[1].setBounds(secondMuteArea);
    muteButtons[2].setBounds(thirdMuteArea);
    muteButtons[3].setBounds(fourthMuteArea);
    
    //Set up clear buttons
    auto clearArea = drumsArea.removeFromLeft(columnWidth);
    auto clearLabelArea = clearArea.removeFromTop(rowHeight);
    auto firstClearArea = clearArea.removeFromTop(rowHeight);
    firstClearArea.removeFromLeft(reduceButtonWidth);
    firstClearArea.removeFromRight(reduceButtonWidth);
    firstClearArea.reduce(reducedAmount, reducedAmount);
    auto secondClearArea = clearArea.removeFromTop(rowHeight);
    secondClearArea.removeFromLeft(reduceButtonWidth);
    secondClearArea.removeFromRight(reduceButtonWidth);
    secondClearArea.reduce(reducedAmount, reducedAmount);
    auto thirdClearArea = clearArea.removeFromTop(rowHeight);
    thirdClearArea.removeFromLeft(reduceButtonWidth);
    thirdClearArea.removeFromRight(reduceButtonWidth);
    thirdClearArea.reduce(reducedAmount, reducedAmount);
    auto fourthClearArea = clearArea;
    fourthClearArea.removeFromLeft(reduceButtonWidth);
    fourthClearArea.removeFromRight(reduceButtonWidth);
    fourthClearArea.reduce(reducedAmount, reducedAmount);
    
    clearLabel.setBounds(clearLabelArea);
    clearButtons[0].setBounds(firstClearArea);
    clearButtons[1].setBounds(secondClearArea);
    clearButtons[2].setBounds(thirdClearArea);
    clearButtons[3].setBounds(fourthClearArea);
    
    //drumsArea.removeFromLeft(border);
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
    firstBeatArea.reduce(reducedAmount, reducedAmount);
    auto secondBeatArea = secondColumn.removeFromTop(rowHeight).reduced(border);
    secondBeatArea.removeFromLeft(reduceButtonWidth);
    secondBeatArea.removeFromRight(reduceButtonWidth);
    secondBeatArea.reduce(reducedAmount, reducedAmount);
    auto thirdBeatArea = thirdColumn.removeFromTop(rowHeight).reduced(border);
    thirdBeatArea.removeFromLeft(reduceButtonWidth);
    thirdBeatArea.removeFromRight(reduceButtonWidth);
    thirdBeatArea.reduce(reducedAmount, reducedAmount);
    auto fourthBeatArea = fourthColumn.removeFromTop(rowHeight).reduced(border);
    fourthBeatArea.removeFromLeft(reduceButtonWidth);
    fourthBeatArea.removeFromRight(reduceButtonWidth);
    fourthBeatArea.reduce(reducedAmount, reducedAmount);
    auto fifthBeatArea = fifthColumn.removeFromTop(rowHeight).reduced(border);
    fifthBeatArea.removeFromLeft(reduceButtonWidth);
    fifthBeatArea.removeFromRight(reduceButtonWidth);
    fifthBeatArea.reduce(reducedAmount, reducedAmount);
    auto sixthBeatArea = sixthColumn.removeFromTop(rowHeight).reduced(border);
    sixthBeatArea.removeFromLeft(reduceButtonWidth);
    sixthBeatArea.removeFromRight(reduceButtonWidth);
    sixthBeatArea.reduce(reducedAmount, reducedAmount);
    auto seventhBeatArea = seventhColumn.removeFromTop(rowHeight).reduced(border);
    seventhBeatArea.removeFromLeft(reduceButtonWidth);
    seventhBeatArea.removeFromRight(reduceButtonWidth);
    seventhBeatArea.reduce(reducedAmount, reducedAmount);
    auto eighthBeatArea = eighthColumn.removeFromTop(rowHeight).reduced(border);
    eighthBeatArea.removeFromLeft(reduceButtonWidth);
    eighthBeatArea.removeFromRight(reduceButtonWidth);
    eighthBeatArea.reduce(reducedAmount, reducedAmount);
    
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
    
    sequencerButtons[0].setBounds(firstHiHatArea);
    sequencerButtons[1].setBounds(secondHiHatArea);
    sequencerButtons[2].setBounds(thirdHiHatArea);
    sequencerButtons[3].setBounds(fourthHiHatArea);
    sequencerButtons[4].setBounds(fifthHiHatArea);
    sequencerButtons[5].setBounds(sixthHiHatArea);
    sequencerButtons[6].setBounds(seventhHiHatArea);
    sequencerButtons[7].setBounds(eighthHiHatArea);
    
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
    
    sequencerButtons[8].setBounds(firstSnareArea);
    sequencerButtons[9].setBounds(secondSnareArea);
    sequencerButtons[10].setBounds(thirdSnareArea);
    sequencerButtons[11].setBounds(fourthSnareArea);
    sequencerButtons[12].setBounds(fifthSnareArea);
    sequencerButtons[13].setBounds(sixthSnareArea);
    sequencerButtons[14].setBounds(seventhSnareArea);
    sequencerButtons[15].setBounds(eighthSnareArea);
    
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
    
    sequencerButtons[16].setBounds(firstTomArea);
    sequencerButtons[17].setBounds(secondTomArea);
    sequencerButtons[18].setBounds(thirdTomArea);
    sequencerButtons[19].setBounds(fourthTomArea);
    sequencerButtons[20].setBounds(fifthTomArea);
    sequencerButtons[21].setBounds(sixthTomArea);
    sequencerButtons[22].setBounds(seventhTomArea);
    sequencerButtons[23].setBounds(eighthTomArea);
    
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
    
    sequencerButtons[24].setBounds(firstKickArea);
    sequencerButtons[25].setBounds(secondKickArea);
    sequencerButtons[26].setBounds(thirdKickArea);
    sequencerButtons[27].setBounds(fourthKickArea);
    sequencerButtons[28].setBounds(fifthKickArea);
    sequencerButtons[29].setBounds(sixthKickArea);
    sequencerButtons[30].setBounds(seventhKickArea);
    sequencerButtons[31].setBounds(eighthKickArea);
}

void Robotic_Drummer_Interface_MockupAudioProcessorEditor::timerCallback(int timerID)
{
    if(timerID == 33) //Tempo Timer
    {
        //Shift the beat to the next LED
        int curLEDPosition = -1;
        for(int i = 0; i < 8; i++)
        {
            if(audioProcessor.beats[i])
            {
                curLEDPosition = (i+1)%8;
                break;
            }
        }
        
        for(int i = 0; i < 8; i++)
        {
            if(i == curLEDPosition)
            {
                audioProcessor.beats[i] = true;
            }
            else
            {
                audioProcessor.beats[i] = false;
            }
        }
    }
    else if(timerID == 34) //Beat Flash Timer
    {
        if(audioProcessor.velocityMode && lastButtonPressed != -1)
        {
            sequencerButtons[lastButtonPressed-1].setToggleState(!sequencerButtons[lastButtonPressed-1].getToggleState(), juce::NotificationType::sendNotification);
        }
        
//        if(audioProcessor.buttonHeld != -1)
//        {
//            audioProcessor.sequencerHits[audioProcessor.buttonHeld-1] = !audioProcessor.sequencerHits[audioProcessor.buttonHeld-1];
//        }
    }
//    else
//    {
//        //Button Held Timers
//        if(timerID >= 1 && timerID <= 32)
//        {
//            audioProcessor.buttonHeld = timerID;
//            DBG(juce::String(timerID) + " callback");
//        }
//    }
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
