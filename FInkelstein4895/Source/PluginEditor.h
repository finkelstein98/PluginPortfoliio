/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class TheHouseShowAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener, ComboBox::Listener

{
public:
    TheHouseShowAudioProcessorEditor (TheHouseShowAudioProcessor&);
    ~TheHouseShowAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TheHouseShowAudioProcessor& processor;
    
    Slider low_filterSlider;
    Label low_filterLabel;
    Slider high_filterSlider;
    Label high_filterLabel;
    Slider EFXgainSlider;
    Label EFXgainLabel;
    Slider toneKnob;
    Label toneLabel;
    ComboBox sat;
    Label satLabel;
    Slider thresh;
   
    std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment>
    sliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheHouseShowAudioProcessorEditor)
};
