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
    
    //Beat Variables
    bool beats[8] = {true, false, false, false, false, false, false, false};
    
    //Hi Hat Variables
    bool firstHiHatHit;
    bool secondHiHatHit;
    bool thirdHiHatHit;
    bool fourthHiHatHit;
    bool fifthHiHatHit;
    bool sixthHiHatHit;
    bool seventhHiHatHit;
    bool eighthHiHatHit;
    
    //Snare Variables
    bool firstSnareHit;
    bool secondSnareHit;
    bool thirdSnareHit;
    bool fourthSnareHit;
    bool fifthSnareHit;
    bool sixthSnareHit;
    bool seventhSnareHit;
    bool eighthSnareHit;
    
    //Tom Variables
    bool firstTomHit;
    bool secondTomHit;
    bool thirdTomHit;
    bool fourthTomHit;
    bool fifthTomHit;
    bool sixthTomHit;
    bool seventhTomHit;
    bool eighthTomHit;
    
    //Kick Variables
    bool firstKickHit;
    bool secondKickHit;
    bool thirdKickHit;
    bool fourthKickHit;
    bool fifthKickHit;
    bool sixthKickHit;
    bool seventhKickHit;
    bool eighthKickHit;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Robotic_Drummer_Interface_MockupAudioProcessor)
};
