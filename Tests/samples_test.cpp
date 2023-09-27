/*** Piano960 Tests | samples_test.cpp ***/

#include "samples.h"
#include "pitch/notes.h"

TEST_CASE("RandomSampler: keys start off as unlocked")
{
  RandomSampler sampler(C4, C5);

  for (Note note = C4; note <= C5; note++)
    REQUIRE(!sampler.isKeyLocked(note))
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

