#ifndef EVENT_H
#define EVENT_H

#include "player.h"

/* event count: 일반 이벤트 + 희귀 이벤트 */
#define eventCount 11

/*
----------- Fixed Event -----------
*/
int day1Event(players *player);

/*
----------- Normal Events -----------
*/
int event_tree_hole(players *player);
int event_rock_shade(players *player);
int event_seaweed(players *player);
int event_herbs(players *player);
int event_pond_fish(players *player);
int event_palm_leaves(players *player);
int event_rest_spot(players *player); // 이전 dummy6과 유사한 휴식 이벤트

/*
----------- Rare / Special Events -----------
*/
int event_wave_collect(players *player);
int event_waterfall(players *player);
int event_ship_signal(players *player);
int event_cabin(players *player);
int event_cave(players *player);

/*
----------- Manager -----------
*/
int handleEvent(players *player);

#endif
