#ifndef EVENT_H
#define EVENT_H

#include "player.h"
#define eventCount 3

/*
-----------
Fixed Event
-----------
*/
int day1Event(players *player);

/*
-----------------------
Nomal and Special Event
-----------------------
*/
int dummy1(players *player);
int dummy2(players *player);
int dummy3(players *player);

/*
--------------------
Additional Functions
--------------------
*/
int handleEvent(players *player);

#endif