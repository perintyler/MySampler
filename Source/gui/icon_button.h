/*** MySampler | Source/gui/icon_button.h ***/

#pragma once

#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

using ImageButtonPointer = juce::Component::SafePointer<juce::ImageButton>;

struct BinaryResource {
    const char* address;
    int size;
    
    juce::Image getImage() const;
};

void setButtonIcon(ImageButtonPointer&, juce::Colour, BinaryResource);

void setToggleButtonIcons(ImageButtonPointer&, juce::Colour, BinaryResource, BinaryResource);
