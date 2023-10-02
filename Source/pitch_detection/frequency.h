/*** Piano960 | pitch_detection/frequency.h ***/

#pragma once

#include "../notes.h"

bool isValidNote(float frequency);

Note getNoteForFrequency(float frequency);

Semitone getSemitoneForFrequency(float frequency);
