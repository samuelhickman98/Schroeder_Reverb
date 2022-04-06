/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SchroederReverbAudioProcessor::SchroederReverbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(gain = new juce::AudioParameterFloat ("gain", "Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    mERGainOutputSliderValue = APGAIN;
}

SchroederReverbAudioProcessor::~SchroederReverbAudioProcessor()
{
    
}

//==============================================================================
//void SchroederReverbAudioProcessor::setParamGain(float thisGain);
//{
//    *gain = (thisGain < 0.0f) ? 0.0f : thisGain;
//}
void SchroederReverbAudioProcessor::clearAllBuffers()
{
    mFBFCRingBuf.init();
    mERDelayRingBuf.init();
    mMMBuf.clear();
    mERBuf.clear();
    mDelayBlockBuf.clear();
}

void SchroederReverbAudioProcessor::doEarlyReflections(juce::AudioBuffer<float> &buffer)
{
    int bufSize = buffer.getNumSamples();
    
    mERBuf.clear();
    
    for (int stage = 0; stage < NUMER; stage++)
    {
        //buffer argument
        auto* lBufReadPtr = buffer.getReadPointer(0);
        auto* rBufReadPtr = buffer.getReadPointer(1);
        
        auto* lErBufPtr = mERBuf.getReadPointer(0);
        auto* rErBufPtr = mERBuf.getReadPointer(1);
    
        if(stage == 0)
        {
            mERBuf.copyFrom(0, 0, buffer, 0, 0, bufSize);
            mERBuf.addFrom(0, 0, buffer, 0, 1, bufSize);
            mERBuf.applyGain(0, 0, bufSize, mERGainOutputSliderValue);
            
            for(int i = 0; i < bufSize; i++)
                mERDelayRingBuf.writeSample(stage, i, (lBufReadPtr[i] - rBufReadPtr[i]) * APGAIN);
        }
        else
        {
            mERBuf.addFrom(0, 0, mERBuf, 1, 0, bufSize);
            mERBuf.applyGain(0, 0, bufSize, APGAIN);
            
            for(int i = 0; i < bufSize; i++)
                mERDelayRingBuf.writeSample(stage, i, (lErBufPtr[i] - rErBufPtr[i]) * APGAIN);
        }
    
    mERDelayRingBuf.readUnsafe(stage, mERDelSamps[stage], mERBuf, 1, bufSize);
    }
        
}
void SchroederReverbAudioProcessor::doFeedbackCombFilters(int bufSize)
{
    for (int channel = 0; channel < NUMFBCF; ++channel)
    {
        mFBFCRingBuf.readUnsafe(channel, mFBCFDelSamps[channel], mDelayBlockBuf, channel, bufSize);
        
        mDelayBlockBuf.applyGain(channel, 0, bufSize, mFBCFFeedbackCoeffs[channel]);
        
        mDelayBlockBuf.addFrom(channel, 0, mERBuf, channel % 2, 0, bufSize);
        
        mFBFCRingBuf.write(channel, mDelayBlockBuf, channel, bufSize, false);
    }

}
//==============================================================================
void SchroederReverbAudioProcessor::doMixingMatrix(int bufSize)
{
    mMMBuf.clear();
    
    //Out A: s1 + s2
    mMMBuf.copyFrom(0, 0, mDelayBlockBuf, 0, 0, bufSize);
    mMMBuf.addFrom(0, 0, mDelayBlockBuf, 2, 0, bufSize);
    mMMBuf.addFrom(0, 0, mDelayBlockBuf, 1, 0, bufSize);
    mMMBuf.addFrom(0, 0, mDelayBlockBuf, 3, 0, bufSize);
    
    //Out B: negation of Out A
    mMMBuf.copyFrom(1, 0, mMMBuf, 0, 0, bufSize);
    mMMBuf.applyGain(1, 0, bufSize, -1.0);
    
    //Out D: s1 mix
    mMMBuf.copyFrom(3, 0, mDelayBlockBuf, 0, 0, bufSize);
    mMMBuf.addFrom(3, 0, mDelayBlockBuf, 2, 0, bufSize);
    
    //Out D: s2 mix
    mMMBuf.copyFrom(2, 0, mDelayBlockBuf, 1, 0, bufSize);
    mMMBuf.addFrom(2, 0, mDelayBlockBuf, 3, 0, bufSize);
    mMMBuf.applyGain(2, 0, bufSize, -1.0);
    mMMBuf.addFrom(3, 0, mMMBuf, 2, 0, bufSize);
    
    //Out C: negation of Out C
    mMMBuf.copyFrom(2, 0, mMMBuf, 3, 0, bufSize);
    mMMBuf.applyGain(2, 0, bufSize, -1.0);
}
//==============================================================================
const juce::String SchroederReverbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SchroederReverbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SchroederReverbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SchroederReverbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SchroederReverbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SchroederReverbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SchroederReverbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SchroederReverbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SchroederReverbAudioProcessor::getProgramName (int index)
{
    return {};
}

void SchroederReverbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SchroederReverbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSampleRate = sampleRate;
    mBlockSize = samplesPerBlock;
    
    mFBFCRingBuf.setSize(NUMFBCF, 10.0f * mSampleRate, mBlockSize);
    
    mERDelayRingBuf.setSize(NUMER, mFBFCRingBuf.getSize(), mBlockSize);
    
    mERBuf.setSize(2, mBlockSize);
    
    mMMBuf.setSize(NUMFBCF, mBlockSize);
    
    mDelayBlockBuf.setSize(NUMFBCF, mBlockSize);
    
    clearAllBuffers();
    
    for (int i = 0; i < NUMER; i++)
        mERDelSamps[i] = atec::Utilities::sec2samp(mERDelayMs[i]/1000.0f, mSampleRate);
    
    for (int i = 0; i < NUMFBCF; i++)
    {
    mFBCFDelSamps[i] = juce::roundToInt((mCombFilterDelaysMs[i]/1000.0f) * mSampleRate);
    mFBCFFeedbackCoeffs[i] = mCombFilterFeedbacks[i]/100.0f;
    }
    
    DBG("ERDelSamps: [" + juce::String(mERDelSamps[0]) + ", " + juce::String(mERDelSamps[1]) + ", " + juce::String(mERDelSamps[2]) + "]");
    
}

void SchroederReverbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SchroederReverbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SchroederReverbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    int bufSize = buffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    doEarlyReflections(buffer);
    
    doFeedbackCombFilters(bufSize);
    
    doMixingMatrix(bufSize);
    
    buffer.copyFrom(0, 0, mMMBuf, mLeftChannelOutputFlag, 0, bufSize);
    buffer.copyFrom(1, 0, mMMBuf, mRightChannelOutputFlag, 0, bufSize);
    
    buffer.applyGain(0, bufSize, 0.4);
    
    mFBFCRingBuf.advanceWriteIdx(bufSize);
    mERDelayRingBuf.advanceWriteIdx(bufSize);
   //buffer.applyGain(*gain);
}

//==============================================================================
bool SchroederReverbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SchroederReverbAudioProcessor::createEditor()
{
    return new SchroederReverbAudioProcessorEditor (*this);
}

//==============================================================================
void SchroederReverbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream (destData, true).writeFloat (*gain);
    
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SchroederReverbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    *gain = juce::MemoryInputStream (data, static_cast<size_t>(sizeInBytes), false).readFloat();
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SchroederReverbAudioProcessor();
}
