/*** Piano960 Tests | samples_test.cpp ***/

#include <filesystem>

#include <catch2/catch_test_macros.hpp>

#include "samples.h"
#include "pitch/notes.h"

TEST_CASE("RandomSampler: keys start off as unlocked")
{
  RandomSampler sampler(C4, C5);

  for (Note note = C4; note <= C5; note++)
    REQUIRE(!sampler.isKeyLocked(note));
}

TEST_CASE("RandomSampler: locking / unlocking keys")
{
  RandomSampler sampler(C4, C5);

  for (Note note = C4; note <= C5; note++) {
    sampler.lockKey(note);
    REQUIRE(sampler.isKeyLocked(note));
    sampler.unlockKey(note);
    REQUIRE(!sampler.isKeyLocked(note));
  }
}

TEST_CASE("RandomSampler: get sample")
{
  RandomSampler sampler(C4, C4+1);
  const Sample& sample = sampler.getSample(C4);
  REQUIRE(!sample.name.empty());
  REQUIRE(std::filesystem::exists(sample.filepath));
  REQUIRE(sample.rootNote > B0);
  REQUIRE(sample.rootNote < G8);
}

TEST_CASE("RandomSampler: randomize samples") 
{
  RandomSampler sampler(C4, C5);
  std::string sampleNameBeforeRandomizing = sampler.getSample(C4).name;
  sampler.randomize();
  std::string sampleNameAfterRandomizing = sampler.getSample(C4).name;
  REQUIRE(sampleNameBeforeRandomizing != sampleNameAfterRandomizing);
}

