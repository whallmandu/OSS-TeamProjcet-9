#ifndef PLAYER_H
#define PLAYER_H
#define MAX_HP 50
#define MAX_Hunger 50
#define MAX_Thirst 50

//player setting
typedef struct playerdata {
    int Day, HP, Hunger, Thirst;
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
