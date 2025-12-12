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
int event_tree_hole(players *player);
int event_rock_shade(players *player);
int event_seaweed(players *player);
int event_herbs(players *player);
int event_pond_fish(players *player);
int event_palm_leaves(players *player);
int suddenDownpour(players *player);  
int fallenFruit(players *player);  
int bigTree(players *player);         
int findGroundWater(players *player);  
int falmLeaves(players *player);     
int fishingFish(players *player);    
int event_weirdPlant(players *player);
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
