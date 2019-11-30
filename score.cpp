#include "score.h"

score::score() {
    stepNum = 0;
    pushNum = 0;
}

void score::pushUp() { pushNum++; }

void score::stepUp() { stepNum++; }

int score::getPush() { return pushNum; }

int score::getStep() { return stepNum; }