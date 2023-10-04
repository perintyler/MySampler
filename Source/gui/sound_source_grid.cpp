/*** Piano960 | gui/sound_source_grid.cpp ***/

#include "sound_source_grid.h"

const int NUM_BUTTONS_PER_ROW = 14;

const float BUTTON_HEIGHT = 35;

SoundSourceGrid::SoundSourceGrid(AudioProcessor& processor)
{
    for (SoundSource sound_source = FIRST_SOUND_SOURCE
       ; sound_source <= LAST_SOUND_SOURCE
       ; sound_source = getNextSoundSource(sound_source)
    ){
        SoundSourceButtonPointer button = SoundSourceButtonPointer(
          new juce::ToggleButton(soundSourceToString(sound_source))
        );

        bool toggledAtStart = DEFAULT_SOUND_SOURCES.find(sound_source) != DEFAULT_SOUND_SOURCES.end();
        selected[sound_source] = toggledAtStart;
        button->setToggleState(toggledAtStart, juce::NotificationType::dontSendNotification);

        button->onClick = [&selected=selected, sound_source, &processor=processor]() {
            if (selected[sound_source]) {
                processor.sampler.removeSoundSource(sound_source);
                selected[sound_source] = false;
            } else {
                processor.sampler.addSoundSource(sound_source);
                selected[sound_source] = true;
            }
        };

        buttons.push_back(button);

        addAndMakeVisible(std::move(button));
    }
}

SoundSourceGrid::~SoundSourceGrid()
{
    for (auto& button: buttons) {
        button.deleteAndZero();
    }

    buttons.clear();
    selected.clear();
}

float SoundSourceGrid::getHeight() 
{
    int numButtons = static_cast<int>(getAllSoundSources().size());
    
    int numRows = numButtons / NUM_BUTTONS_PER_ROW 
                + (numButtons % NUM_BUTTONS_PER_ROW != 0); // integer divide, but round up
    return numRows*BUTTON_HEIGHT;
}

void SoundSourceGrid::resized()
{
    int numButtons = getChildren().size();
    int numRows = numButtons / NUM_BUTTONS_PER_ROW 
                + (numButtons % NUM_BUTTONS_PER_ROW != 0); // integer divide, but round up

    for (int row = 0; row < numRows; ++row) {
        juce::FlexBox flexbox;

        flexbox.flexWrap = juce::FlexBox::Wrap::wrap;
        flexbox.justifyContent = juce::FlexBox::JustifyContent::center;
        flexbox.alignContent = juce::FlexBox::AlignContent::center;

        for (int itemIndex = 0; itemIndex < NUM_BUTTONS_PER_ROW; ++itemIndex) {
            int childIndex = row*NUM_BUTTONS_PER_ROW + itemIndex;

            flexbox.items.add(
                juce::FlexItem(*getChildComponent(childIndex))
                    .withMinWidth(100.0f)
                    .withMinHeight(BUTTON_HEIGHT)
            );
        }

        juce::Rectangle<float> flexboxBounds( 
            0, BUTTON_HEIGHT*row, static_cast<float>(getLocalBounds().getWidth()), BUTTON_HEIGHT 
        );

        flexbox.performLayout(flexboxBounds);
    }
}

std::set<SoundSource> SoundSourceGrid::getSelectedCategories() const
{
    std::set<SoundSource> selectedCategories;

    for (const auto& [category, isSelected] : selected) {
        if (isSelected) {
            selectedCategories.insert(category);
        }
    }

    return selectedCategories;
}
