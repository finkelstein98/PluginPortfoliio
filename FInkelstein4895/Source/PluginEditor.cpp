/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TheHouseShowAudioProcessorEditor::TheHouseShowAudioProcessorEditor (TheHouseShowAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 450);
   
    //Saturation
    sat.addItem("Soft Clipping", 1);
    sat.addItem("Hard Clipping", 2);
    sat.addListener(this);
    sat.setBounds(20, 175, 150, 100);
    addAndMakeVisible(sat);
    addAndMakeVisible(satLabel);
    satLabel.attachToComponent(&sat, true);
    satLabel.setBounds(175, 50, 100, 100);
    thresh.addListener(this);
    thresh.setSliderStyle(Slider::Rotary);
    thresh.setBounds(365, 100, 100, 100);
    thresh.setRange(0.1f, 1.0f);
    thresh.setSkewFactorFromMidPoint(0.55f);
    thresh.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 50);
    thresh.setTextValueSuffix(" - Threshold");
    addAndMakeVisible(thresh);
    
    sliderAttachment =
    std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
    (processor.state,"THRESH",thresh);
    
    //Low Filter
    low_filterSlider.addListener(this);
    low_filterSlider.setSliderStyle(Slider::LinearBar);
    low_filterSlider.setBounds(180, 100, 150, 100);
    low_filterSlider.setRange(30, 500);
    low_filterSlider.setSkewFactorFromMidPoint(150.0f);
    addAndMakeVisible(low_filterSlider);
    addAndMakeVisible(low_filterLabel);
    low_filterLabel.attachToComponent(&low_filterSlider, true);
    low_filterLabel.setBounds(200, 120, 100, 100);
    
     sliderAttachment =
    std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
    (processor.state,"HIGH PASS",low_filterSlider);
    
    //High Filter
    high_filterSlider.addListener(this);
    high_filterSlider.setSliderStyle(Slider::LinearBar);
    high_filterSlider.setBounds(180, 250, 150, 100);
    high_filterSlider.setRange(6000, 15000);
    high_filterSlider.setSkewFactorFromMidPoint(8000.0f);
    addAndMakeVisible(high_filterSlider);
    addAndMakeVisible(high_filterLabel);
    high_filterLabel.attachToComponent(&low_filterSlider, true);
    high_filterLabel.setBounds(200, 280, 100, 100);
    
    sliderAttachment =
    std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
    (processor.state,"LOW PASS",high_filterSlider);
    
    //Tone Knob
    toneKnob.addListener(this);
    toneKnob.setSliderStyle(Slider::Rotary);
    toneKnob.setBounds(365, 250, 100, 100);
    toneKnob.setRange(750, 10000);
    toneKnob.setSkewFactorFromMidPoint(2500);
    toneKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 50);
    toneKnob.setTextValueSuffix(" - Tone Knob");
    addAndMakeVisible(toneKnob);
    
   
    sliderAttachment =
    std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
    (processor.state,"TONE",toneKnob);
    
    //Makeup Gain
    EFXgainSlider.addListener(this);
    EFXgainSlider.setSliderStyle(Slider::LinearVertical);
    EFXgainSlider.setBounds(485, 100, 100, 320);
    EFXgainSlider.setRange(1.0f, 2.0f);
    EFXgainSlider.setMouseDragSensitivity(15);
    EFXgainSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 100, 50);
    EFXgainSlider.setTextValueSuffix(" - Boost");
    addAndMakeVisible(EFXgainSlider);
    
   sliderAttachment =
      std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
      (processor.state,"GAIN",EFXgainSlider);
  
}

TheHouseShowAudioProcessorEditor::~TheHouseShowAudioProcessorEditor()
{
}

//==============================================================================
void TheHouseShowAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    ColourGradient gradient;
    auto viewBounds = getLocalBounds();
    
    gradient.point1 = viewBounds.getTopLeft().toFloat();
      gradient.point2 = viewBounds.getTopRight().toFloat();
        gradient.addColour(0.0, Colours::darkslateblue);
    gradient.addColour(1.0, Colours::darkslategrey);
        g.setGradientFill(gradient);
    g.fillRect((getLocalBounds()));



    g.setColour (Colours::yellow);
    g.setFont (40.0f);
    g.drawFittedText ("HOUSE SHOW MIC: EQ/Waveshaper", getLocalBounds(), Justification::topLeft, 1);
}

void TheHouseShowAudioProcessorEditor::resized()
{

}

void
TheHouseShowAudioProcessorEditor::sliderValueChanged(Slider* slider){
 
 
    if (slider == &low_filterSlider){
        processor.freqVal = low_filterSlider.getValue();
    }
    if (slider == &high_filterSlider){
        processor.freqVal2 = high_filterSlider.getValue();
    }
 
    if (slider == &EFXgainSlider){
        processor.makeupGain = EFXgainSlider.getValue();
    }
    if (slider == &toneKnob){
        processor.freqVal3 = toneKnob.getValue();
    }
    if (slider == &thresh){
        processor.threshold = thresh.getValue();
    }
}
void
TheHouseShowAudioProcessorEditor::comboBoxChanged(ComboBox* comboBoxThatHasChanged){
        
    processor.choose = comboBoxThatHasChanged->getSelectedId();
    }



