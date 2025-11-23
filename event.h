#ifndef EVENT_H
#define EVENT_H

#include "player.h"
#define eventCount 12

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
int suddenDownpour(players *player);  
int fallenFruit(players *player);  
int bigTree(players *player);         
int findGroundWater(players *player);  
int falmLeaves(players *player);     
int fishingFish(players *player);    
int collapsedCabin(players *player);   
int discoverLifeboat(players *player); 
int shipwreck(players *player);       
int somethingInSand(players *player);  
int wildBoar(players *player);       
int approachingStorm(players *player);

/*
--------------------
Additional Functions
--------------------
*/
int handleEvent(players *player);

#endif