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
  {12, "gun", 0}
};
const int itemCount = sizeof(item) / sizeof(item[0]);


//extra settingl
int home; int resque; int raft;

int main() {
  FILE *setup = fopen("setup.txt", "r");

  if(setup == NULL) {
    printf("No setup.txt");
    return 0;
  }
  int hungerIncrease, thirstIncrease, fatigueIncrease;
  int hungerLevel, thirstLevel, fatigueLevel;  
  fscanf(setup, "%d %d %d", &hungerIncrease, &thirstIncrease, &fatigueIncrease);
  fscanf(setup, "%d %d %d", &hungerLevel, &thirstLevel, &fatigueLevel);


  //if(save data) player, data, eventN in save
  //else

  //first setting
  players player;
  player.Day = 1;
  player.HP = 50;
  player.Fatigue = 0;
  player.Hunger = 0;
  player.Thirst = 0;
  srand(time(NULL));


  while(player.Day <= 30) {
    if(player.Day == 1) {
      if(day1Event(&player) == 4) break;
    } 
    //else if(player.Day == 10) {
    //   //Day 10 event
    // } else if(player.Day == 20) {
    //   //Day 20 event}
    else if(player.Day == 30) {
      //final event
      printf("==============================\n");
      printf("You have survived for 30 days!\n");
      printf("Rescue team found you and brought you home.\n");
      printf("Congratulations, survivor!\n");
      printf("==============================\n");
      break;
    }
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
          player.Hunger -= hungerIncrease; 
          if(player.Hunger < 0) player.Hunger = 0;
      } else { //No food
          if(player.Hunger >= hungerLevel) player.HP -= 5;
          player.Hunger += hungerIncrease; 
      }
    }

    //Thirst
    if(player.Thirst >= 0) {
        if(item[2].count > 0) { 
            item[2].count--;
            player.Thirst -= thirstIncrease; 
            if(player.Thirst < 0) player.Thirst = 0;
        } else { //No water
            if(player.Thirst >= thirstLevel) player.HP -= 5;
            player.Thirst += thirstIncrease; 
        }
    }

    //Fatigue
    if(player.Fatigue >= fatigueLevel) player.HP -= 5;
    player.Fatigue += fatigueIncrease;


      
    
    //screen clear
    printf("Press Enter to Continue...");
    int input;
    while ((input = getchar()) != '\n' && input != EOF); // buffer clear
    while ((input = getchar()) != '\n' && input != EOF);
    printf("\x1b[2J\x1b[H");
    



    //Death - Endig 1
    if(player.HP <= 0) {
      printf("==============================\n");
      printf("You are dead.\n");
      printf("==============================\n");
      break;
    }
  }




  return 0;
}