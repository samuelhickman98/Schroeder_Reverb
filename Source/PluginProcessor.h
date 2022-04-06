/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define NUMFBCF 4
#define NUMER 5
#define APGAIN 0.7

enum leftChannelMatrixOutput
{
    leftOne = 1,
    leftTwo = 2,
    leftThree = 3,
    leftFour = 4
};

enum rightChannelMatrixOutput
{
    rightOne = 1,
    rightTwo = 2,
    rightThree = 3,
    rightFour = 4
};

//==============================================================================
/**
*/
class SchroederReverbAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SchroederReverbAudioProcessor();
    ~SchroederReverbAudioProcessor() override;

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

    double mSampleRate;
    double mBlockSize;
    
    bool mLeftChannelOutputFlag;
    bool mRightChannelOutputFlag;
    
    double mERGainOutputSliderValue;
    double mERDelayMs[NUMER] = {13.88, 10.77, 7.63, 4.52, 1.48};
    double mCombFilterDelaysMs[NUMFBCF] = {67.48, 64.04, 82.12, 90.04};
    double mCombFilterFeedbacks[NUMFBCF] = {77.3, 80.2, 75.3, 73.3};
    
    int mFBCFDelSamps[NUMFBCF];
    float mFBCFFeedbackCoeffs[NUMFBCF];
    int mERDelSamps[NUMER];
    
    void clearAllBuffers();
    
private:
    
    juce::AudioParameterFloat* gain;
    
    atec::RingBuffer mFBFCRingBuf;
    atec::RingBuffer mERDelayRingBuf;
    juce::AudioBuffer<float> mMMBuf;
    juce::AudioBuffer<float> mERBuf;
    juce::AudioBuffer<float> mDelayBlockBuf;
    
    void doEarlyReflections(juce::AudioBuffer<float>& buffer);
    void clearAllBuffers(juce::AudioBuffer<float>& buffer);
    void doFeedbackCombFilters(int bufSize);
    void doMixingMatrix(int bufSize);
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SchroederReverbAudioProcessor)
};
