#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//player setting
typedef struct playerdata{
  int Day, HP, Hunger, Thirst, Fatigue;
  int ability[10];
}players;

//item setting
typedef struct items{
  int ID;
  char itemname[30];
  int count;
} Item;

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

//extra settingl
int home; int resque; int raft;

int main() {
  //if(save data) player, data, eventN in save
  //else

  //first setting
  players player;
  player.Day = 1;
  player.HP = 30;
  player.Fatigue = 0;
  player.Hunger = 0;
  player.Thirst = 0;

  while(player.Day <= 30) {
    if(player.Day == 1) {

    }
  }


  return 0;
}
