#include "score.h"

score::score(){
    stepNum=0;
    pushNum=0;
    lifeNum=3;
}
void score::pushUp(){pushNum++;}
void score::stepUp(){stepNum++;}
void score::lifeDown(){lifeNum--;}
int score::getPush(){return pushNum;}
int score::getStep(){return stepNum;}
int score::getLife(){return lifeNum;}
