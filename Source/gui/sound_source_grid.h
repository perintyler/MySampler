/*** Piano960 | gui/sound_source_grid.h ***/

#include <set>
#include <map>

#include <juce_gui_basics/juce_gui_basics.h>

#include "../sound_source.h"
#include "../audio_processor.h"

using SoundSourceButtonPointer = juce::Component::SafePointer<juce::ToggleButton>;

class SoundSourceGrid: public juce::Component {
public:
    SoundSourceGrid(AudioProcessor&);
    ~SoundSourceGrid() override;

    static float getHeight();

    std::set<SoundSource> getSelectedCategories() const;

    void resized() override;

private:
    std::vector<SoundSourceButtonPointer> buttons {};

    std::map<SoundSource, bool> selected {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SoundSourceGrid);
};
