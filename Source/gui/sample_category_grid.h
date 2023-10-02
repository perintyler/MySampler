/*** Piano960 | gui/sample_category_grid.h ***/

#include <set>
#include <map>

#include <juce_gui_basics/juce_gui_basics.h>

#include "../sample_categories.h"

using CategoryButtonPointer = juce::Component::SafePointer<juce::ToggleButton>;

class SampleCategoryGrid: public juce::Component {
public:
    SampleCategoryGrid();
    ~SampleCategoryGrid() override;


    std::set<SampleCategory> getSelectedCategories() const;

    void resized() override;

private:
    std::vector<CategoryButtonPointer> buttons {};

    std::map<SampleCategory, bool> selected {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SampleCategoryGrid);
};