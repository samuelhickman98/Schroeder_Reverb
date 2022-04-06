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
class SchroederReverbAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener, public juce::ComboBox::Listener, public juce::Button::Listener
{
public:
    SchroederReverbAudioProcessorEditor (SchroederReverbAudioProcessor&);
    ~SchroederReverbAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SchroederReverbAudioProcessor& audioProcessor;
    
    juce::Slider mERDelayStageOneSlider;
    juce::Label mERDelayStageOneLabel;
    
    juce::Slider mERDelayStageTwoSlider;
    juce::Label mERDelayStageTwoLabel;
    
    juce::Slider mERDelayStageThreeSlider;
    juce::Label mERDelayStageThreeLabel;
    
    juce::Slider mERDelayStageFourSlider;
    juce::Label mERDelayStageFourLabel;
    
    juce::Slider mERDelayStageFiveSlider;
    juce::Label mERDelayStageFiveLabel;
    
    juce::Slider mEROutputGainSlider;
    juce::Label mEROutputGainLabel;
    
    juce::Slider mFBCFOneDelaySlider;
    juce::Label mFBCFOneDelayLabel;
    
    juce::Slider mFBCFTwoDelaySlider;
    juce::Label mFBCFTwoDelayLabel;
    
    juce::Slider mFBCFThreeDelaySlider;
    juce::Label mFBCFThreeDelayLabel;
    
    juce::Slider mFBCFFourDelaySlider;
    juce::Label mFBCFFourDelayLabel;
    
    juce::Slider mFBCFFeedbackOneSlider;
    juce::Label mFBCFFeedbackOneLabel;
    
    juce::Slider mFBCFFeedbackTwoSlider;
    juce::Label mFBCFFeedbackTwoLabel;
    
    juce::Slider mFBCFFeedbackThreeSlider;
    juce::Label mFBCFFeedbackThreeLabel;
    
    juce::Slider mFBCFFeedbackFourSlider;
    juce::Label mFBCFFeedbackFourLabel;
    
    juce::TextButton mClearFBCFBufButton;
    juce::Label mClearBufFBCFLabel;
    
    juce::ComboBox mLeftChannelMatrixMappingOutputBox;
    juce::Label mLeftChannelMatrixMappingOutputLabel;
    
    juce::ComboBox mRightChannelMatrixMappingOutputBox;
    juce::Label mRightChannelMatrixMappingOutputLabel;
    
    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* comboBox) override;
    void buttonClicked(juce::Button* button) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SchroederReverbAudioProcessorEditor)
};
