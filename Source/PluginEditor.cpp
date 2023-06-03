/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

OtherLookAndFeel::OtherLookAndFeel()
{
    setColour (juce::Slider::thumbColourId, juce::Colours::red);
}

void OtherLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&)
{
    auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    auto rw = radius * 2.0f;
    auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

    // fill
    g.setColour (juce::Colour(0xff1C2321));
    g.fillEllipse (rx, ry, rw, rw);

    // outline
    g.setColour (juce::Colour(0xff7D98A1));
    g.drawEllipse (rx, ry, rw, rw, 3.0f);

    juce::Path p;
    auto pointerLength = radius * 0.33f;
    auto pointerThickness = 3.0f;
    p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
    p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));

    // pointer
    g.setColour (juce::Colour(0xffEEF1EF));
    g.fillPath (p);
}

//==============================================================================
GainSliderAudioProcessorEditor::GainSliderAudioProcessorEditor (GainSliderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    gainSlider.setLookAndFeel(&SliderLookAndFeel);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
    gainSlider.setRange(-48.0, 48.0);
    gainSlider.setValue(0.0);
    gainSlider.addListener(this);
    
    addAndMakeVisible(gainSlider);
    
    addAndMakeVisible(titleLabel);
    titleLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    titleLabel.setText("HEADroom", juce::dontSendNotification);
    titleLabel.setColour(juce::Label::textColourId, juce::Colour(0xffEEF1EF));
    titleLabel.setJustificationType(juce::Justification::centred);
    
    setSize (450, 250);
}

GainSliderAudioProcessorEditor::~GainSliderAudioProcessorEditor()
{
}

//==============================================================================
void GainSliderAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
}

void GainSliderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    area.removeFromTop(40);
    area.removeFromBottom(20);
    gainSlider.setBounds(area);
    
    titleLabel.setBounds(0, 10, getWidth(), 30);
}

void GainSliderAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.rawVolume = pow(10, gainSlider.getValue() / 20);
    }
}
