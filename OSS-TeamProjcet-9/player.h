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
  
  int itemCount = 13;
  Item item[] = {
    {0, "develop", 0}, //this is debuging item. plz it is first.
    {1, "food", 0},
    {2, "water", 0},
    {3, "wood", 0},
    {4, "stone", 0},
    {5, "herb", 0},
    {6, "cloth", 0},
    {7, "metal", 0},
    {8, "rope", 0},
    {9, "lighter", 0},
    {10, "knife", 0},
    {11, "fishingrod", 0},
    {12, "rope", 0}
  };

#endif
