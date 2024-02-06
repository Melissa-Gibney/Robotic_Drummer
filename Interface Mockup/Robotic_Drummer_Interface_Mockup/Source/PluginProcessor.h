/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Robotic_Drummer_Interface_MockupAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    Robotic_Drummer_Interface_MockupAudioProcessor();
    ~Robotic_Drummer_Interface_MockupAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //Declare Variables
    
    //Edited Parameters
    int parameters[2] = {0, 1}; //0 == Tempo, 1 == velocity
    
    //Tempo
    int tempo = 120;
    
    //Is Playing
    bool isPlaying = false;
    
    //Use Velocity Mode
    bool velocityMode = false;
    
    //Beat Variables
    bool beats[8] = {true, false, false, false, false, false, false, false};
    
    //Beat Variables
    bool mutes[4] = {false, false, false, false};
    
    //Button Being Held Down
    int buttonHeld;
    
    //Hit Variables
    bool sequencerHits[32];
    
    //Flashing Buttons
    bool flashingButtons[32];
    
    //Velocity Variables
    int sequencerVelocities[32];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Robotic_Drummer_Interface_MockupAudioProcessor)
};
