#ifndef EVENT_H
#define EVENT_H

#include "player.h"

/* event count: 일반 이벤트 + 희귀 이벤트 */
#define eventCount 22

/*
----------- Fixed Event -----------
*/
int day1Event(players *player);
int event_final_day(players *player);
/*
----------- Normal Events -----------
*/
int birdSpotted(players *player);
int clamsSpotted(players *player);
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
int suspiciousWeeds(players *player);
int event_twig(players *player);
int event_cloth(players *player);
int event_fishingNet(players *player);
int event_stone(players *player);
int event_rockRope(players *player);

/*
----------- Rare / Special Events -----------
*/
int event_wave_collect(players *player);
int event_waterfall(players *player);
int event_cave(players *player);
int collapsedCabin(players *player);   
int discoverLifeboat(players *player); 
int shipwreck(players *player);       
int somethingInSand(players *player);  
int wildBoar(players *player);       
int approachingStorm(players *player);
int event_military_supplies(players *player);

/*
----------- Manager -----------
*/
int pickEventID();
int runEventByID(int eventID, players *player);
void getUsedEvents(int *buffer);
void setUsedEvents(int *buffer);

#endif
