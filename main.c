#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "event.h"


//item setting
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
const int itemCount = sizeof(item) / sizeof(item[0]);


//extra settingl
int home; int resque; int raft;

<<<<<<< HEAD
int main(void){









=======
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
  srand(time(NULL));


  while(player.Day <= 30) {
    if(player.Day == 1) {
      if(day1Event(&player) == 4) break;
    } //else if(player.Day == 10) {
    //   //Day 10 event
    // } else if(player.Day == 20) {
    //   //Day 20 event
    // } else if(player.Day == 30) {
    //   //final event
    // } else if(player.HP <= 5) {
    //   //lowHP event
    // } else if(player.Hunger >= 50) {
    //   //highHunger event
    // } else if(player.Thirst >= 50) {
    //   //highThirst event
    // } else if(player.Fatigue >=70) {
    //   //highFatigue event
    // } 
    else{ //the other
      //random event
      if(handleEvent(&player) == 4) break;
    }

    //Next Day
    player.Day++;
    //Hunger
    if(player.Hunger >= 0) {
      if(item[1].count > 0) { 
        item[1].count--;
        player.Hunger -= 5;
        if(player.Hunger < 0) player.Hunger = 0;
      } else { //No food
        if(player.Hunger >= 30) player.HP -= 5;
        player.Hunger += 5;
      }
    }

    //Thirst
    if(player.Thirst >= 0) {
      if(item[2].count > 0) { 
        item[2].count--;
        player.Thirst -= 10;
        if(player.Thirst < 0) player.Thirst = 0;
      } else { //No water
        if(player.Thirst >= 30) player.HP -= 5;
        player.Thirst += 10;
      }
    }

    //Fatigue
    if(player.Fatigue >= 50) player.HP -= 5;
    player.Fatigue += 5;
    
    //screen clear
    printf("\n\n\n\n\n");

    //death
    if(player.HP <= 0) {
      printf("==============================\n");
      printf("You are dead.\n");
      printf("==============================\n");
      break;
    }
  }

    
>>>>>>> 17b2d3e51cea299ad71c85cf47317de2b4c7b03f


  return 0;
}