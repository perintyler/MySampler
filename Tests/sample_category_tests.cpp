/*** Piano960 Tests | sample_category_tests.cpp ***/

#include <catch2/catch_test_macros.hpp>

#include "sample_categories.h"

TEST_CASE("SampleCategory Test #1: category to int")
{
    REQUIRE(static_cast<int>(SampleCategory::NONE)     == 0);
    REQUIRE(static_cast<int>(SampleCategory::PIANO)    == 1);
    REQUIRE(static_cast<int>(SampleCategory::KEYBOARD) == 21);
}

TEST_CASE("SampleCategory Test #2: category to string", "[sample_categories]")
{
    REQUIRE(sampleCategoryToString(SampleCategory::NONE) == "None");
    REQUIRE(sampleCategoryToString(SampleCategory::PIANO) == "Piano");
    REQUIRE(sampleCategoryToString(SampleCategory::CELLO) == "Cello");
    REQUIRE(sampleCategoryToString(SampleCategory::TROMBONE) == "Trombone");
    REQUIRE(sampleCategoryToString(SampleCategory::ORGAN) == "Organ");
    REQUIRE(sampleCategoryToString(SampleCategory::WOODWIND) == "Woodwind");
    REQUIRE(sampleCategoryToString(SampleCategory::TRUMPET) == "Trumpet");
    REQUIRE(sampleCategoryToString(SampleCategory::GLOCKENSPIEL) == "Glockenspiel");
    REQUIRE(sampleCategoryToString(SampleCategory::SFX) == "SFX");
    REQUIRE(sampleCategoryToString(SampleCategory::GUITAR) == "Guitar");
    REQUIRE(sampleCategoryToString(SampleCategory::PLUCK) == "Pluck");
    REQUIRE(sampleCategoryToString(SampleCategory::WORLD) == "World");
    REQUIRE(sampleCategoryToString(SampleCategory::BRASS) == "Brass");
    REQUIRE(sampleCategoryToString(SampleCategory::BASS) == "Bass");
    REQUIRE(sampleCategoryToString(SampleCategory::VOCAL) == "Vocal");
    REQUIRE(sampleCategoryToString(SampleCategory::PAD) == "Pad");
    REQUIRE(sampleCategoryToString(SampleCategory::SYNTH) == "Synth");
    REQUIRE(sampleCategoryToString(SampleCategory::BELL) == "Bell");
    REQUIRE(sampleCategoryToString(SampleCategory::VOILIN) == "Voilin");
    REQUIRE(sampleCategoryToString(SampleCategory::ARP) == "Arp");
    REQUIRE(sampleCategoryToString(SampleCategory::FLUTE) == "Flute");
    REQUIRE(sampleCategoryToString(SampleCategory::KEYBOARD) == "Keyboard");
}

TEST_CASE("SampleCategory Test #3: string to category", "[sample_categories]")
{
    REQUIRE(getSampleCategory("None") == SampleCategory::NONE);
    REQUIRE(getSampleCategory("Piano") == SampleCategory::PIANO);
    REQUIRE(getSampleCategory("Cello") == SampleCategory::CELLO);
    REQUIRE(getSampleCategory("Trombone") == SampleCategory::TROMBONE);
    REQUIRE(getSampleCategory("Organ") == SampleCategory::ORGAN);
    REQUIRE(getSampleCategory("Woodwind") == SampleCategory::WOODWIND);
    REQUIRE(getSampleCategory("Trumpet") == SampleCategory::TRUMPET);
    REQUIRE(getSampleCategory("Glockenspiel") == SampleCategory::GLOCKENSPIEL);
    REQUIRE(getSampleCategory("SFX") == SampleCategory::SFX);
    REQUIRE(getSampleCategory("Guitar") == SampleCategory::GUITAR);
    REQUIRE(getSampleCategory("Pluck") == SampleCategory::PLUCK);
    REQUIRE(getSampleCategory("World") == SampleCategory::WORLD);
    REQUIRE(getSampleCategory("Brass") == SampleCategory::BRASS);
    REQUIRE(getSampleCategory("Bass") == SampleCategory::BASS);
    REQUIRE(getSampleCategory("Vocal") == SampleCategory::VOCAL);
    REQUIRE(getSampleCategory("Pad") == SampleCategory::PAD);
    REQUIRE(getSampleCategory("Synth") == SampleCategory::SYNTH);
    REQUIRE(getSampleCategory("Bell") == SampleCategory::BELL);
    REQUIRE(getSampleCategory("Voilin") == SampleCategory::VOILIN);
    REQUIRE(getSampleCategory("Arp") == SampleCategory::ARP);
    REQUIRE(getSampleCategory("Flute") == SampleCategory::FLUTE);
    REQUIRE(getSampleCategory("Keyboard") == SampleCategory::KEYBOARD);

    REQUIRE(getSampleCategory("Invalid-Category-Name") == SampleCategory::NONE);
}
