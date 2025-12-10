#ifndef EVENT_H
#define EVENT_H

#include "player.h"

/* event count: 일반 이벤트 + 희귀 이벤트 */
#define eventCount 23

/*
----------- Fixed Event -----------
*/
int day1Event(players *player);

/*
----------- Normal Events -----------
*/
int insideTheLog(players *player);
int rockShade(players *player);
int seaweedClump(players *player);
int event_herbs(players *player);
int fishSpotted(players *player);
int event_palm_leaves(players *player);
int thunderstorm(players *player);  
int fallenFruit(players *player);  
int fallenTree(players *player);         
int thePool(players *player);  
int palmLeaves(players *player);     
int fishingFish(players *player);    

/*
----------- Rare / Special Events -----------
*/
int event_wave_collect(players *player);
int event_waterfall(players *player);
int event_ship_signal(players *player);
int event_cabin(players *player);
int event_cave(players *player);
int collapsedCabin(players *player);   
int discoverLifeboat(players *player); 
int shipwreck(players *player);       
int somethingInSand(players *player);  
int wildBoar(players *player);       
int approachingStorm(players *player);

/*
----------- Manager -----------
*/
int pickEventID();
int runEventByID(int eventID, players *player);
void getUsedEvents(int *buffer);
void setUsedEvents(int *buffer);

#endif
