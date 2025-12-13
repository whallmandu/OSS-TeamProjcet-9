/*
    Survival Island - Text-based Survival Game
    Copyright (C) 2025 서바이버초이스

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef EVENT_H
#define EVENT_H

#include "player.h"

/* event count */
#define eventCount 33

/*
----------- Fixed Event -----------
*/
int day1Event(players *player);
int day10Event(players *player);
int day20Event(players *player);

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
int event_strange_plant(players *player);
int event_dry_twigs(players *player);
int event_cloth_found(players *player);
int event_old_net(players *player);
int event_stones_found(players *player);
int event_rock_rope(players *player);
int event_tornado(players *player);
int event_animal_carcass(players *player);
int event_earthquake(players *player);
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
void drawImage(int x, int y, const char* filename);
int pickEventID();
int runEventByID(int eventID, players *player);
void getUsedEvents(int *buffer);
void setUsedEvents(int *buffer);

#endif
