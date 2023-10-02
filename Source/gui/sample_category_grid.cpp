/*** Piano960 | gui/sample_category_grid.cpp ***/

#include "sample_category_grid.h"

SampleCategoryGrid::SampleCategoryGrid()
{
    for (SampleCategory category = FIRST_CATEGORY
       ; category <= LAST_CATEGORY
       ; category = getNextSampleCategory(category)
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

SampleCategoryGrid::~SampleCategoryGrid()
{
    for (auto& button: buttons) {
        button.deleteAndZero();
    }

    buttons.clear();
}

void SampleCategoryGrid::resized()
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

std::set<SampleCategory> SampleCategoryGrid::getSelectedCategories() const
{
    std::set<SampleCategory> selectedCategories;

    for (const auto& [category, isSelected] : selected) {
        if (isSelected) {
            selectedCategories.insert(category);
        }
    }

    return selectedCategories;
}
