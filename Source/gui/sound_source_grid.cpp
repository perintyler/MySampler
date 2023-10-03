/*** Piano960 | gui/sound_source_grid.cpp ***/

#include "sound_source_grid.h"

SoundSourceGrid::SoundSourceGrid()
{
    for (SoundSource category = FIRST_SOUND_SOURCE
       ; category <= LAST_SOUND_SOURCE
       ; category = getNextSoundSource(category)
    ){
        selected[category] = true;

        CategoryButtonPointer button = CategoryButtonPointer(
          new juce::ToggleButton(soundSourceToString(category))
        );

        buttons.push_back(button);

        button->onClick = [&selected=selected, category]() { 
          selected[category] = !selected[category]; 
        };

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

void SoundSourceGrid::resized()
{
    juce::FlexBox flexbox;

    flexbox.flexWrap = juce::FlexBox::Wrap::wrap;
    flexbox.justifyContent = juce::FlexBox::JustifyContent::center;
    flexbox.alignContent = juce::FlexBox::AlignContent::stretch;

    for (Component* child : getChildren()) {
        flexbox.items.add(
            juce::FlexItem(*child).withMinWidth(75.0f).withMinHeight(35.0f)
        );
    }

    flexbox.performLayout(getLocalBounds());
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
