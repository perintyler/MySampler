/*** Piano960 Tests | sampler_tests.cpp ***/

#include <filesystem>
#include <stdint.h>

#include <catch2/catch_test_macros.hpp>

#include "sampler.h"
#include "notes.h"

TEST_CASE("RandomSampler Test #1: keys start off as unlocked", "[samples][sampler]")
{
  RandomSampler sampler(C4, C5);

  for (Note note = C4; note <= C5; note++)
    REQUIRE(!sampler.isKeyLocked(note));
}

TEST_CASE("RandomSampler Test #2: locking / unlocking keys", "[samples][sampler]")
{
  RandomSampler sampler(C4, C5);

  for (Note note = C4; note <= C5; note++) {
    sampler.lockKey(note);
    REQUIRE(sampler.isKeyLocked(note));
    sampler.unlockKey(note);
    REQUIRE(!sampler.isKeyLocked(note));
  }
}

TEST_CASE("RandomSampler Test #3: get sample", "[samples][sampler]")
{
  RandomSampler sampler(C4, C4+1);
  sampler.randomizeAll();
  const Sample& sample = sampler.getSample(C4);
  REQUIRE(!sample.name.empty());
  REQUIRE(std::filesystem::exists(sample.filepath));
  REQUIRE(sample.rootNote > B0);
  REQUIRE(sample.rootNote < G8);
}

TEST_CASE("RandomSampler Test #4: randomize samples", "[samples][sampler]")
{
  RandomSampler sampler(C4, C5);
  std::string originalSampleName = sampler.getSample(C4).name;
  sampler.randomizeAll(false);
  std::string updatedSampleName = sampler.getSample(C4).name;
  REQUIRE(originalSampleName != updatedSampleName);
}

