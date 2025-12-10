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

/* event count: 일반 이벤트 + 희귀 이벤트 */
#define eventCount 23

/*
----------- Fixed Event -----------
*/
int day1Event(players *player);
int day10Event(players *player);
int day20Event(players *player);

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
