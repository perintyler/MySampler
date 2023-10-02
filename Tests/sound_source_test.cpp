/*** Piano960 Tests | sample_category_tests.cpp ***/

#include <catch2/catch_test_macros.hpp>

#include "sound_source.h"

TEST_CASE("SoundSource Test #1: category to int")
{
    REQUIRE(static_cast<int>(SoundSource::NONE)     == 0);
    REQUIRE(static_cast<int>(SoundSource::PIANO)    == 1);
    REQUIRE(static_cast<int>(SoundSource::KEYBOARD) == 21);
}

TEST_CASE("SoundSource Test #2: category to string", "[sample_categories]")
{
    REQUIRE(sampleCategoryToString(SoundSource::NONE) == "None");
    REQUIRE(sampleCategoryToString(SoundSource::PIANO) == "Piano");
    REQUIRE(sampleCategoryToString(SoundSource::CELLO) == "Cello");
    REQUIRE(sampleCategoryToString(SoundSource::TROMBONE) == "Trombone");
    REQUIRE(sampleCategoryToString(SoundSource::ORGAN) == "Organ");
    REQUIRE(sampleCategoryToString(SoundSource::WOODWIND) == "Woodwind");
    REQUIRE(sampleCategoryToString(SoundSource::TRUMPET) == "Trumpet");
    REQUIRE(sampleCategoryToString(SoundSource::GLOCKENSPIEL) == "Glockenspiel");
    REQUIRE(sampleCategoryToString(SoundSource::SFX) == "SFX");
    REQUIRE(sampleCategoryToString(SoundSource::GUITAR) == "Guitar");
    REQUIRE(sampleCategoryToString(SoundSource::PLUCK) == "Pluck");
    REQUIRE(sampleCategoryToString(SoundSource::WORLD) == "World");
    REQUIRE(sampleCategoryToString(SoundSource::BRASS) == "Brass");
    REQUIRE(sampleCategoryToString(SoundSource::BASS) == "Bass");
    REQUIRE(sampleCategoryToString(SoundSource::VOCAL) == "Vocal");
    REQUIRE(sampleCategoryToString(SoundSource::PAD) == "Pad");
    REQUIRE(sampleCategoryToString(SoundSource::SYNTH) == "Synth");
    REQUIRE(sampleCategoryToString(SoundSource::BELL) == "Bell");
    REQUIRE(sampleCategoryToString(SoundSource::VOILIN) == "Voilin");
    REQUIRE(sampleCategoryToString(SoundSource::ARP) == "Arp");
    REQUIRE(sampleCategoryToString(SoundSource::FLUTE) == "Flute");
    REQUIRE(sampleCategoryToString(SoundSource::KEYBOARD) == "Keyboard");
}

TEST_CASE("SoundSource Test #3: string to category", "[sample_categories]")
{
    REQUIRE(getSoundSource("None") == SoundSource::NONE);
    REQUIRE(getSoundSource("Piano") == SoundSource::PIANO);
    REQUIRE(getSoundSource("Cello") == SoundSource::CELLO);
    REQUIRE(getSoundSource("Trombone") == SoundSource::TROMBONE);
    REQUIRE(getSoundSource("Organ") == SoundSource::ORGAN);
    REQUIRE(getSoundSource("Woodwind") == SoundSource::WOODWIND);
    REQUIRE(getSoundSource("Trumpet") == SoundSource::TRUMPET);
    REQUIRE(getSoundSource("Glockenspiel") == SoundSource::GLOCKENSPIEL);
    REQUIRE(getSoundSource("SFX") == SoundSource::SFX);
    REQUIRE(getSoundSource("Guitar") == SoundSource::GUITAR);
    REQUIRE(getSoundSource("Pluck") == SoundSource::PLUCK);
    REQUIRE(getSoundSource("World") == SoundSource::WORLD);
    REQUIRE(getSoundSource("Brass") == SoundSource::BRASS);
    REQUIRE(getSoundSource("Bass") == SoundSource::BASS);
    REQUIRE(getSoundSource("Vocal") == SoundSource::VOCAL);
    REQUIRE(getSoundSource("Pad") == SoundSource::PAD);
    REQUIRE(getSoundSource("Synth") == SoundSource::SYNTH);
    REQUIRE(getSoundSource("Bell") == SoundSource::BELL);
    REQUIRE(getSoundSource("Voilin") == SoundSource::VOILIN);
    REQUIRE(getSoundSource("Arp") == SoundSource::ARP);
    REQUIRE(getSoundSource("Flute") == SoundSource::FLUTE);
    REQUIRE(getSoundSource("Keyboard") == SoundSource::KEYBOARD);

    REQUIRE(getSoundSource("Invalid-Category-Name") == SoundSource::NONE);
}
