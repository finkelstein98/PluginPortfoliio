/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//==============================================================================
TheHouseShowAudioProcessor::TheHouseShowAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, Identifier("EQ Parameters"), createParameterLayout())
#endif
{
}

TheHouseShowAudioProcessor::~TheHouseShowAudioProcessor()
{
}

AudioProcessorValueTreeState::ParameterLayout
TheHouseShowAudioProcessor::createParameterLayout(){
  
    //parameters!
    
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>("HIGH PASS", "High Pass", 30.0f, 500.0f, 150.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("LOW PASS", "Low Pass", 6000.0f, 15000.0f, 8000.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("TONE", "Tone Knob", 750.0f, 10000.0f, 2000.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("GAIN", "Makeup Gain", 1.0f, 2.0f, 1.0f));
    params.push_back(std::make_unique<AudioParameterFloat>("THRESH", "Threshold", 0.1f, 1.0f, 0.55f));
    
    return{params.begin(), params.end()};
}

//==============================================================================
const String TheHouseShowAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheHouseShowAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheHouseShowAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheHouseShowAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheHouseShowAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheHouseShowAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheHouseShowAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheHouseShowAudioProcessor::setCurrentProgram (int index)
{
}

const String TheHouseShowAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheHouseShowAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TheHouseShowAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    biquad.setFs(sampleRate);
   
}

void TheHouseShowAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheHouseShowAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void TheHouseShowAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

 
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    // high-pass filter
    biquad.setFreq(freqVal);
    biquad.setQ(QVal);
    biquad.setAmpdB(0.0f);
    biquad.setFilterType(filterType);
    
    //low-pass filter
    biquad2.setFreq(freqVal2);
    biquad2.setQ(QVal);
    biquad2.setAmpdB(0.0f);
    biquad2.setFilterType(filterType2);
    
    //constant freq response
    miclow.setFreq(500.0f);
    miclow.setQ(1.0f);
    miclow.setAmpdB(-0.8f);
    miclow.setFilterType(filterType3);
    michigh.setFreq(3800.0f);
    michigh.setQ(3.0f);
    michigh.setAmpdB(1.5f);
    michigh.setFilterType(filterType4);

    //tone knob
    tone.setFreq(freqVal3);
    tone.setQ(QVal2);
    tone.setAmpdB(12.0f);
    tone.setFilterType(filterType4);
   
    
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        for (int n = 0; n < buffer.getNumSamples(); n++){
       
        float x = buffer.getReadPointer(channel)[n];

if (choose == 1)
{ if (x > threshold)
{ x = 1.0f-expf(-x); }

else{ x = -1.0f + expf(x); }}

if (choose == 2)
{ if (x > threshold)
{x = threshold;}

else if (x < -threshold)
{x = -threshold;}

else
{x = x;}}
            
            float y = biquad.processSample(x, channel); //high-pass
            float z = biquad2.processSample(x, channel); //low-pass
            
          float bpf = y + z;
            
            float a = miclow.processSample(bpf, channel); //frequency response low-mids
            float b = michigh.processSample(bpf, channel); //frequency response high-mids
            float c = tone.processSample(bpf, channel); //tone sweep knob
            float fx =  a + b + c;
            gainSmooth = (1.f-alpha)*makeupGain + alpha*gainSmooth;
            buffer.getWritePointer(channel)[n] = fx + gainSmooth;
         
        }
    }



}
//==============================================================================
bool TheHouseShowAudioProcessor::hasEditor() const
    {
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TheHouseShowAudioProcessor::createEditor()
    {
  return new TheHouseShowAudioProcessorEditor (*this);
}

//==============================================================================
void TheHouseShowAudioProcessor::getStateInformation (MemoryBlock& destData)
{
  
}

void TheHouseShowAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
     
    
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheHouseShowAudioProcessor();
}


