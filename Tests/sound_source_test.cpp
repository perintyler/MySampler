/*** Piano960 Tests | sample_category_tests.cpp ***/

#include <catch2/catch_test_macros.hpp>

#include "sound_source.h"

TEST_CASE("SoundSource Test #1: category to int")
{
    REQUIRE(static_cast<int>(SoundSource::NONE) == 0);
    REQUIRE(static_cast<int>(SoundSource::PIANO) == 1);
}

TEST_CASE("SoundSource Test #2: category to string", "[sample_categories]")
{
    REQUIRE(soundSourceToString(SoundSource::NONE) == "None");
    REQUIRE(soundSourceToString(SoundSource::PIANO) == "Piano");
    REQUIRE(soundSourceToString(SoundSource::CELLO) == "Cello");
    REQUIRE(soundSourceToString(SoundSource::TROMBONE) == "Trombone");
    REQUIRE(soundSourceToString(SoundSource::ORGAN) == "Organ");
    REQUIRE(soundSourceToString(SoundSource::WOODWIND) == "Woodwind");
    REQUIRE(soundSourceToString(SoundSource::TRUMPET) == "Trumpet");
    REQUIRE(soundSourceToString(SoundSource::GLOCKENSPIEL) == "Glockenspiel");
    REQUIRE(soundSourceToString(SoundSource::SFX) == "SFX");
    REQUIRE(soundSourceToString(SoundSource::GUITAR) == "Guitar");
    REQUIRE(soundSourceToString(SoundSource::PLUCK) == "Pluck");
    REQUIRE(soundSourceToString(SoundSource::WORLD) == "World");
    REQUIRE(soundSourceToString(SoundSource::BRASS) == "Brass");
    REQUIRE(soundSourceToString(SoundSource::BASS) == "Bass");
    REQUIRE(soundSourceToString(SoundSource::VOCAL) == "Vocal");
    REQUIRE(soundSourceToString(SoundSource::PAD) == "Pad");
    REQUIRE(soundSourceToString(SoundSource::SYNTH) == "Synth");
    REQUIRE(soundSourceToString(SoundSource::BELL) == "Bell");
    REQUIRE(soundSourceToString(SoundSource::VOILIN) == "Voilin");
    REQUIRE(soundSourceToString(SoundSource::ARP) == "Arp");
    REQUIRE(soundSourceToString(SoundSource::FLUTE) == "Flute");
    REQUIRE(soundSourceToString(SoundSource::KEYBOARD) == "Keyboard");
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
