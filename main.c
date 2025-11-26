#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include "event.h"


//item setting
Item item[] = {
  {0, "develop", 0}, //this is debuging item. plz it is first.
  {1, "food", 0},
  {2, "water", 0},
  {3, "rope", 0},
  {4, "leaves", 0},
  {5, "wood", 0},
  {6, "cloth", 0},
  {7, "stone", 0},
  {8, "knife", 0}
};
const int itemCount = sizeof(item) / sizeof(item[0]);


//extra settingl
int Shelter = 0; int SOS = 0; int Raft = 0;

int main() {
  FILE *setup = fopen("setup.txt", "r");

  if(setup == NULL) {
    printf("No setup.txt");
    return 0;
  }
  int hungerIncrease, thirstIncrease;
  int hungerLevel, thirstLevel;  
  fscanf(setup, "%d %d", &hungerIncrease, &thirstIncrease);
  fscanf(setup, "%d %d", &hungerLevel, &thirstLevel);
  int hungerReduction = hungerIncrease / 2;
  int thirstReduction = thirstIncrease / 2;

  //if(save data) player, data, eventN in save
  //else

  //first setting
  players player;
  player.Day = 1;
  player.HP = 50;
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
    //Setup HP
    if(player.HP > MAX_HP) player.HP = MAX_HP;
    //Hunger
    if(item[1].count <= 0) {
      player.Hunger += hungerIncrease;
      if(player.Hunger > MAX_Hunger) player.Hunger = MAX_Hunger; 
    } else {
      printf("==============================\n");
      printf("How many portions of food would you like to eat?\n");
      printf("Now Food * %d\n", item[1].count);
      printf("==============================\n");
      int n;
      while(1) {
        scanf("%d", &n);
        if(n < 0 || n > item[1].count) printf("worong input!\n");
        else break;
      }
      player.Hunger -= n * hungerReduction;
    }
    if(player.Hunger >= hungerLevel) player.HP -= 5;
    if(player.Hunger < 0) player.Hunger = 0;
    

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


      
    
    //screen clear
    printf("Press Enter to Continue...");
    int input;
    while ((input = getchar()) != '\n' && input != EOF); // buffer clear
    while ((input = getchar()) != '\n' && input != EOF);
    system("cls");
    



    //Death - Endig 1
    if(player.HP <= 0) {
      printf("==============================\n");
      printf("You are dead.\n");
      printf("==============================\n");
      break;
    }
  }

  //screen clear
  printf("Game Over...");
  int input;
  while ((input = getchar()) != '\n' && input != EOF); 
  


  return 0;
}
