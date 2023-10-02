/*** Piano960 | gui/sound_source_grid.cpp ***/

#include "sound_source_grid.h"

SoundSourceGrid::SoundSourceGrid()
{
    for (SoundSource category = FIRST_CATEGORY
       ; category <= LAST_CATEGORY
       ; category = getNextSoundSource(category)
    ){
        selected[category] = true;

        CategoryButtonPointer button = CategoryButtonPointer(
          new juce::ToggleButton(sampleCategoryToString(category))
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
}

void SoundSourceGrid::resized()
{
    juce::FlexBox flexbox;

    flexbox.flexWrap = juce::FlexBox::Wrap::wrap;
    flexbox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    flexbox.alignContent = juce::FlexBox::AlignContent::stretch;

    for (Component* child : getChildren()) {
        flexbox.items.add(
            juce::FlexItem(*child).withMinWidth(75.0f).withMinHeight(50.0f)
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
