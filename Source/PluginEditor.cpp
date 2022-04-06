/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SchroederReverbAudioProcessorEditor::SchroederReverbAudioProcessorEditor (SchroederReverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    
    mERDelayStageOneSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mERDelayStageOneSlider.setRange(0.0f, 300.0f, 0.01f);
    mERDelayStageOneSlider.setValue(audioProcessor.mERDelayMs[0]);
    addAndMakeVisible(&mERDelayStageOneSlider);
    mERDelayStageOneSlider.addListener(this);
    
    addAndMakeVisible(&mERDelayStageOneLabel);
    mERDelayStageOneLabel.setText("Stage 1", juce::dontSendNotification);
    mERDelayStageOneLabel.attachToComponent(&mERDelayStageOneSlider, true);
    mERDelayStageOneLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mERDelayStageOneLabel.setJustificationType(juce::Justification::right);
    
    mERDelayStageTwoSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mERDelayStageTwoSlider.setRange(0.0f, 300.0f, 0.01f);
    mERDelayStageTwoSlider.setValue(audioProcessor.mERDelayMs[1]);
    addAndMakeVisible(&mERDelayStageTwoSlider);
    mERDelayStageTwoSlider.addListener(this);
    
    addAndMakeVisible(&mERDelayStageOneLabel);
    mERDelayStageTwoLabel.setText("Stage 2", juce::dontSendNotification);
    mERDelayStageTwoLabel.attachToComponent(&mERDelayStageTwoSlider, true);
    mERDelayStageTwoLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mERDelayStageTwoLabel.setJustificationType(juce::Justification::right);
    
    mERDelayStageThreeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mERDelayStageThreeSlider.setRange(0.0f, 300.0f, 0.01f);
    mERDelayStageThreeSlider.setValue(audioProcessor.mERDelayMs[2]);
    addAndMakeVisible(&mERDelayStageThreeSlider);
    mERDelayStageThreeSlider.addListener(this);
    
    addAndMakeVisible(&mERDelayStageThreeLabel);
    mERDelayStageThreeLabel.setText("Stage 3", juce::dontSendNotification);
    mERDelayStageThreeLabel.attachToComponent(&mERDelayStageThreeSlider, true);
    mERDelayStageThreeLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mERDelayStageThreeLabel.setJustificationType(juce::Justification::right);
    
    mERDelayStageFourSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mERDelayStageFourSlider.setRange(0.0f, 300.0f, 0.01f);
    mERDelayStageFourSlider.setValue(audioProcessor.mERDelayMs[3]);
    addAndMakeVisible(&mERDelayStageFourSlider);
    mERDelayStageFourSlider.addListener(this);
    
    addAndMakeVisible(&mERDelayStageFourLabel);
    mERDelayStageFourLabel.setText("Stage 4", juce::dontSendNotification);
    mERDelayStageFourLabel.attachToComponent(&mERDelayStageFourSlider, true);
    mERDelayStageFourLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mERDelayStageFourLabel.setJustificationType(juce::Justification::right);
    
    mERDelayStageFiveSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mERDelayStageFiveSlider.setRange(0.0f, 300.0f, 0.01f);
    mERDelayStageFiveSlider.setValue(audioProcessor.mERDelayMs[4]);
    addAndMakeVisible(&mERDelayStageFiveSlider);
    mERDelayStageFiveSlider.addListener(this);
    
    addAndMakeVisible(&mERDelayStageFiveLabel);
    mERDelayStageFiveLabel.setText("Stage 5", juce::dontSendNotification);
    mERDelayStageFiveLabel.attachToComponent(&mERDelayStageFiveSlider, true);
    mERDelayStageFiveLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mERDelayStageFiveLabel.setJustificationType(juce::Justification::right);
    
    mEROutputGainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mEROutputGainSlider.setRange(0.0f, 1.0f, 0.01f);
    mEROutputGainSlider.setValue(audioProcessor.mERGainOutputSliderValue);
    addAndMakeVisible(&mEROutputGainSlider);
    mEROutputGainSlider.addListener(this);
    
    addAndMakeVisible(&mEROutputGainLabel);
    mEROutputGainLabel.setText("Output Gain", juce::dontSendNotification);
    mEROutputGainLabel.attachToComponent(&mEROutputGainSlider, true);
    mEROutputGainLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mEROutputGainLabel.setJustificationType(juce::Justification::right);
    
    mFBCFOneDelaySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mFBCFOneDelaySlider.setRange(0.0f, 200.0f, 0.01f);
    mFBCFOneDelaySlider.setValue(audioProcessor.mCombFilterDelaysMs[0]);
    addAndMakeVisible(&mFBCFOneDelaySlider);
    mFBCFOneDelaySlider.addListener(this);
    
    addAndMakeVisible(&mFBCFOneDelayLabel);
    mFBCFOneDelayLabel.setText("FBCF Delay 1", juce::dontSendNotification);
    mFBCFOneDelayLabel.attachToComponent(&mFBCFOneDelaySlider, true);
    mFBCFOneDelayLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mFBCFOneDelayLabel.setJustificationType(juce::Justification::right);
    
    mFBCFTwoDelaySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mFBCFTwoDelaySlider.setRange(0.0f, 200.0f, 0.01f);
    mFBCFTwoDelaySlider.setValue(audioProcessor.mCombFilterDelaysMs[1]);
    addAndMakeVisible(&mFBCFTwoDelaySlider);
    mFBCFTwoDelaySlider.addListener(this);
    
    addAndMakeVisible(&mFBCFTwoDelayLabel);
    mFBCFTwoDelayLabel.setText("FBCF Delay 2", juce::dontSendNotification);
    mFBCFTwoDelayLabel.attachToComponent(&mFBCFTwoDelaySlider, true);
    mFBCFTwoDelayLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mFBCFTwoDelayLabel.setJustificationType(juce::Justification::right);
    
    mFBCFThreeDelaySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mFBCFThreeDelaySlider.setRange(0.0f, 200.0f, 0.01f);
    mFBCFThreeDelaySlider.setValue(audioProcessor.mCombFilterDelaysMs[2]);
    addAndMakeVisible(&mFBCFThreeDelaySlider);
    mFBCFThreeDelaySlider.addListener(this);
    
    addAndMakeVisible(&mFBCFThreeDelayLabel);
    mFBCFThreeDelayLabel.setText("FBCF Delay 3", juce::dontSendNotification);
    mFBCFThreeDelayLabel.attachToComponent(&mFBCFThreeDelaySlider, true);
    mFBCFThreeDelayLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mFBCFThreeDelayLabel.setJustificationType(juce::Justification::right);
    
    mFBCFFourDelaySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mFBCFFourDelaySlider.setRange(0.0f, 200.0f, 0.01f);
    mFBCFFourDelaySlider.setValue(audioProcessor.mCombFilterDelaysMs[3]);
    addAndMakeVisible(&mFBCFFourDelaySlider);
    mFBCFFourDelaySlider.addListener(this);
    
    addAndMakeVisible(&mFBCFFourDelayLabel);
    mFBCFFourDelayLabel.setText("FBCF Delay 4", juce::dontSendNotification);
    mFBCFFourDelayLabel.attachToComponent(&mFBCFFourDelaySlider, true);
    mFBCFFourDelayLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mFBCFFourDelayLabel.setJustificationType(juce::Justification::right);

    mFBCFFeedbackOneSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mFBCFFeedbackOneSlider.setRange(0.0f, 99.0f, 0.01f);
    mFBCFFeedbackOneSlider.setValue(audioProcessor.mCombFilterFeedbacks[0]);
    addAndMakeVisible(&mFBCFFeedbackOneSlider);
    mFBCFFeedbackOneSlider.addListener(this);
    
    addAndMakeVisible(&mFBCFFeedbackOneLabel);
    mFBCFFeedbackOneLabel.setText("FBCF Feedback 1", juce::dontSendNotification);
    mFBCFFeedbackOneLabel.attachToComponent(&mFBCFFeedbackOneSlider, true);
    mFBCFFeedbackOneLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mFBCFFeedbackOneLabel.setJustificationType(juce::Justification::right);
    
    mFBCFFeedbackTwoSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mFBCFFeedbackTwoSlider.setRange(0.0f, 99.0f, 0.01f);
    mFBCFFeedbackTwoSlider.setValue(audioProcessor.mCombFilterFeedbacks[1]);
    addAndMakeVisible(&mFBCFFeedbackTwoSlider);
    mFBCFFeedbackTwoSlider.addListener(this);
    
    addAndMakeVisible(&mFBCFFeedbackTwoLabel);
    mFBCFFeedbackTwoLabel.setText("FBCF Feedback 2", juce::dontSendNotification);
    mFBCFFeedbackTwoLabel.attachToComponent(&mFBCFFeedbackTwoSlider, true);
    mFBCFFeedbackTwoLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mFBCFFeedbackTwoLabel.setJustificationType(juce::Justification::right);
    
    mFBCFFeedbackThreeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mFBCFFeedbackThreeSlider.setRange(0.0f, 99.0f, 0.01f);
    mFBCFFeedbackThreeSlider.setValue(audioProcessor.mCombFilterFeedbacks[2]);
    addAndMakeVisible(&mFBCFFeedbackThreeSlider);
    mFBCFFeedbackThreeSlider.addListener(this);
    
    addAndMakeVisible(&mFBCFFeedbackThreeLabel);
    mFBCFFeedbackThreeLabel.setText("FBCF Feedback 3", juce::dontSendNotification);
    mFBCFFeedbackThreeLabel.attachToComponent(&mFBCFFeedbackThreeSlider, true);
    mFBCFFeedbackThreeLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mFBCFFeedbackThreeLabel.setJustificationType(juce::Justification::right);
    
    mFBCFFeedbackFourSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mFBCFFeedbackFourSlider.setRange(0.0f, 99.0f, 0.01f);
    mFBCFFeedbackFourSlider.setValue(audioProcessor.mCombFilterFeedbacks[3]);
    addAndMakeVisible(&mFBCFFeedbackFourSlider);
    mFBCFFeedbackFourSlider.addListener(this);
    
    addAndMakeVisible(&mFBCFFeedbackFourLabel);
    mFBCFFeedbackFourLabel.setText("FBCF Feedback 4", juce::dontSendNotification);
    mFBCFFeedbackFourLabel.attachToComponent(&mFBCFFeedbackFourSlider, true);
    mFBCFFeedbackFourLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mFBCFFeedbackFourLabel.setJustificationType(juce::Justification::right);
    
    mLeftChannelMatrixMappingOutputBox.addItem("1", 1);
    mLeftChannelMatrixMappingOutputBox.addItem("2", 2);
    mLeftChannelMatrixMappingOutputBox.addItem("3", 3);
    mLeftChannelMatrixMappingOutputBox.addItem("4", 4);
    mLeftChannelMatrixMappingOutputBox.setSelectedId(audioProcessor.mLeftChannelOutputFlag);
    addAndMakeVisible(&mLeftChannelMatrixMappingOutputBox);
    mLeftChannelMatrixMappingOutputBox.addListener(this);
    
    addAndMakeVisible(&mLeftChannelMatrixMappingOutputLabel);
    mLeftChannelMatrixMappingOutputLabel.setText("Left Channel Output", juce::dontSendNotification);
    mLeftChannelMatrixMappingOutputLabel.attachToComponent(&mLeftChannelMatrixMappingOutputBox, true);
    mLeftChannelMatrixMappingOutputLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mLeftChannelMatrixMappingOutputLabel.setJustificationType(juce::Justification::centredBottom);
    
    mRightChannelMatrixMappingOutputBox.addItem("1", 1);
    mRightChannelMatrixMappingOutputBox.addItem("2", 2);
    mRightChannelMatrixMappingOutputBox.addItem("3", 3);
    mRightChannelMatrixMappingOutputBox.addItem("4", 4);
    mRightChannelMatrixMappingOutputBox.setSelectedId(audioProcessor.mRightChannelOutputFlag);
    addAndMakeVisible(&mRightChannelMatrixMappingOutputBox);
    mRightChannelMatrixMappingOutputBox.addListener(this);
    
    addAndMakeVisible(&mRightChannelMatrixMappingOutputLabel);
    mRightChannelMatrixMappingOutputLabel.setText("Right Channel Output", juce::dontSendNotification);
    mRightChannelMatrixMappingOutputLabel.attachToComponent(&mRightChannelMatrixMappingOutputBox, true);
    mRightChannelMatrixMappingOutputLabel.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mRightChannelMatrixMappingOutputLabel.setJustificationType(juce::Justification::centredBottom);
    
    mClearFBCFBufButton.setButtonText("Clear FBCF Buffer");
    addAndMakeVisible(mClearFBCFBufButton);
    mClearFBCFBufButton.setColour(juce::Label::backgroundColourId, juce::Colours::aquamarine);
    mClearFBCFBufButton.setColour(juce::Label::textColourId, juce::Colours::magenta);
    mClearFBCFBufButton.addListener(this);
}

SchroederReverbAudioProcessorEditor::~SchroederReverbAudioProcessorEditor()
{
    mERDelayStageOneSlider.removeListener(this);
    mERDelayStageTwoSlider.removeListener(this);
    mERDelayStageThreeSlider.removeListener(this);
    mERDelayStageFourSlider.removeListener(this);
    mERDelayStageFiveSlider.removeListener(this);
    mEROutputGainSlider.removeListener(this);
    mFBCFOneDelaySlider.removeListener(this);
    mFBCFTwoDelaySlider.removeListener(this);
    mFBCFThreeDelaySlider.removeListener(this);
    mFBCFFourDelaySlider.removeListener(this);
    mFBCFFeedbackOneSlider.removeListener(this);
    mFBCFFeedbackTwoSlider.removeListener(this);
    mFBCFFeedbackThreeSlider.removeListener(this);
    mFBCFFeedbackFourSlider.removeListener(this);
    mLeftChannelMatrixMappingOutputBox.removeListener(this);
    mRightChannelMatrixMappingOutputBox.removeListener(this);
    mClearFBCFBufButton.removeListener(this);
}
void SchroederReverbAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (slider == &mERDelayStageOneSlider)
    {
        audioProcessor.mERDelayMs[0] = mERDelayStageOneSlider.getValue();
        audioProcessor.mERDelSamps[0] = atec::Utilities::sec2samp(audioProcessor.mERDelayMs[0]/1000.0f, audioProcessor.mSampleRate);
    }
    else if (slider == &mERDelayStageTwoSlider)
    {
        audioProcessor.mERDelayMs[1] = mERDelayStageTwoSlider.getValue();
        audioProcessor.mERDelSamps[1] = atec::Utilities::sec2samp(audioProcessor.mERDelayMs[1]/1000.0f, audioProcessor.mSampleRate);
    }
    else if (slider == &mERDelayStageThreeSlider)
    {
        audioProcessor.mERDelayMs[2] = mERDelayStageThreeSlider.getValue();
        audioProcessor.mERDelSamps[2] = atec::Utilities::sec2samp(audioProcessor.mERDelayMs[2]/1000.0f, audioProcessor.mSampleRate);
    }
    else if (slider == &mERDelayStageFourSlider)
    {
        audioProcessor.mERDelayMs[3] = mERDelayStageFourSlider.getValue();
        audioProcessor.mERDelSamps[3] = atec::Utilities::sec2samp(audioProcessor.mERDelayMs[3]/1000.0f, audioProcessor.mSampleRate);
    }
    else if (slider == &mERDelayStageFiveSlider)
    {
        audioProcessor.mERDelayMs[4] = mERDelayStageFiveSlider.getValue();
        audioProcessor.mERDelSamps[4] = atec::Utilities::sec2samp(audioProcessor.mERDelayMs[4]/1000.0f, audioProcessor.mSampleRate);
    }
    else if (slider == &mEROutputGainSlider)
    {
        audioProcessor.mERGainOutputSliderValue = mEROutputGainSlider.getValue();
    }
    else if (slider == &mFBCFOneDelaySlider)
    {
        audioProcessor.mCombFilterDelaysMs[0] = mFBCFOneDelaySlider.getValue();
        audioProcessor.mFBCFDelSamps[0] = atec::Utilities::sec2samp(audioProcessor.mCombFilterDelaysMs[0]/1000.0f, audioProcessor.mSampleRate);
    }
    else if (slider == &mFBCFTwoDelaySlider)
    {
        audioProcessor.mCombFilterDelaysMs[1] = mFBCFTwoDelaySlider.getValue();
        audioProcessor.mFBCFDelSamps[1] = atec::Utilities::sec2samp(audioProcessor.mCombFilterDelaysMs[1]/1000.0f, audioProcessor.mSampleRate);
    }
    else if (slider == &mFBCFThreeDelaySlider)
    {
        audioProcessor.mCombFilterDelaysMs[2] = mFBCFThreeDelaySlider.getValue();
        audioProcessor.mFBCFDelSamps[2] = atec::Utilities::sec2samp(audioProcessor.mCombFilterDelaysMs[2]/1000.0f, audioProcessor.mSampleRate);
    }
    else if (slider == &mFBCFFourDelaySlider)
    {
        audioProcessor.mCombFilterDelaysMs[3] = mFBCFFourDelaySlider.getValue();
        audioProcessor.mFBCFDelSamps[3] = atec::Utilities::sec2samp(audioProcessor.mCombFilterDelaysMs[3]/1000.0f, audioProcessor.mSampleRate);
    }
    else if (slider == &mFBCFFeedbackOneSlider)
    {
        audioProcessor.mCombFilterFeedbacks[0] = mFBCFFeedbackOneSlider.getValue();
        audioProcessor.mFBCFFeedbackCoeffs[0] = audioProcessor.mCombFilterFeedbacks[0]/100.0f;
    }
    else if (slider == &mFBCFFeedbackTwoSlider)
    {
        audioProcessor.mCombFilterFeedbacks[1] = mFBCFFeedbackTwoSlider.getValue();
        audioProcessor.mFBCFFeedbackCoeffs[1] = audioProcessor.mCombFilterFeedbacks[1]/100.0f;
    }
    else if (slider == &mFBCFFeedbackThreeSlider)
    {
        audioProcessor.mCombFilterFeedbacks[2] = mFBCFFeedbackThreeSlider.getValue();
        audioProcessor.mFBCFFeedbackCoeffs[2] = audioProcessor.mCombFilterFeedbacks[2]/100.0f;
    }
    else if (slider == &mFBCFFeedbackFourSlider)
    {
        audioProcessor.mCombFilterFeedbacks[3] = mFBCFFeedbackFourSlider.getValue();
        audioProcessor.mFBCFFeedbackCoeffs[3] = audioProcessor.mCombFilterFeedbacks[3]/100.0f;
    }
}

void SchroederReverbAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox)
{
    if (comboBox == &mLeftChannelMatrixMappingOutputBox)
    {
        audioProcessor.mLeftChannelOutputFlag = mLeftChannelMatrixMappingOutputBox.getSelectedId() -1;
    }
    else
    {
        audioProcessor.mRightChannelOutputFlag = mRightChannelMatrixMappingOutputBox.getSelectedId() -1;
    }
}

void SchroederReverbAudioProcessorEditor::buttonClicked(juce::Button *button)
{
    audioProcessor.clearAllBuffers();
}

//==============================================================================
void SchroederReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (30.0f);
    g.drawFittedText ("SchroederReverb", getLocalBounds(), juce::Justification::centred, 1);
}

void SchroederReverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    mERDelayStageOneSlider.setBounds(150, 20, 250, 50);
    mERDelayStageTwoSlider.setBounds(200, 70, 250, 50);
    mERDelayStageThreeSlider.setBounds(250, 120, 250, 50);
    mERDelayStageFourSlider.setBounds(300, 170, 250, 50);
    mERDelayStageFiveSlider.setBounds(350, 220, 250, 50);
    
    mEROutputGainSlider.setBounds(150, 250, 500, 50);
    
    mFBCFOneDelaySlider.setBounds(100, 400, 250, 50);
    mFBCFTwoDelaySlider.setBounds(100, 450, 250, 50);
    mFBCFThreeDelaySlider.setBounds(100, 500, 250, 50);
    mFBCFFourDelaySlider.setBounds(100, 550, 250, 50);
    
    mFBCFFeedbackOneSlider.setBounds(525, 400, 250, 50);
    mFBCFFeedbackTwoSlider.setBounds(525, 450, 250, 50);
    mFBCFFeedbackThreeSlider.setBounds(525, 500, 250, 50);
    mFBCFFeedbackFourSlider.setBounds(525, 550, 250, 50);
    
    mLeftChannelMatrixMappingOutputBox.setBounds(175, 300, 75, 50);
    mRightChannelMatrixMappingOutputBox.setBounds(600, 300, 75, 50);
    
    mClearFBCFBufButton.setBounds(300, 350, 125, 50);
}
