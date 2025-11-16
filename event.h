#ifndef EVENT_H
#define EVENT_H

#include "player.h"
#define eventCount 6

/*
-----------
Fixed Event
-----------
*/
int day1Event(players *player);

/*
-----------------------
Normal and Special Event
-----------------------
*/
int dummy1(players *player);
int dummy2(players *player);
int dummy3(players *player);
int dummy4(players *player);   // extra normal situation
int dummy5(players *player);   // extra normal situation
int dummy6(players *player); // fatigue recovery

/*
--------------------
Additional Functions
--------------------
*/
int handleEvent(players *player);

#endif