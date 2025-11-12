#ifndef PLAYER_H
#define PLAYER_H

//player setting
typedef struct playerdata {
    int Day, HP, Hunger, Thirst, Fatigue;
    int ability[10];
} players;

//item setting
typedef struct items{
    int ID;
    char itemname[30];
    int count;
  } Item;
  
extern const int itemCount;
extern Item item[];

#endif
