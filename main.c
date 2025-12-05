#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include "event.h"


//item setting
Item item[] = {
  {0, "develop", 0}, //debug
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

//extra setting
int Shelter = 0; int SOS = 0;

//save data
typedef struct{
  players savedPlayer;      
    Item savedItems[9];     
    int savedShelter;         
    int savedSOS;                       
    int savedUsedEvents[eventCount];
    int savedEventID;
} GameState;

void gameSave(players *p, int current) {
  FILE *fp = fopen("save.dat", "wb");
  if (fp == NULL) {
    printf("[Error] Failed to save game.\n");
    return;
  }

  GameState state;

  state.savedPlayer = *p;

  for(int i = 0; i < itemCount; i++) {
    state.savedItems[i] = item[i];
  }

  state.savedShelter = Shelter;
  state.savedSOS = SOS;
  state.savedEventID = current;

  getUsedEvents(state.savedUsedEvents);

  fwrite(&state, sizeof(GameState), 1, fp);
  fclose(fp);
  printf("\n[Game Saved Successfully]\n");
}

//load game(success: 1, failue: 0)
int gameLoad(players *p) {
  FILE *fp = fopen("save.dat", "rb");
  if (fp == NULL) {
    printf("[Error] No save FILE.\n");
    return 0;
  }

  GameState state;
  fread(&state, sizeof(GameState), 1, fp);
  fclose(fp);

  *p = state.savedPlayer;

  for(int i=0; i<itemCount; i++) {
    item[i] = state.savedItems[i];
  }

  Shelter = state.savedShelter;
  SOS = state.savedSOS;

  setUsedEvents(state.savedUsedEvents);

  printf("\n[Game Loaded Successfully]\n");
  return 1;
}


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

  int currentEventID = -1;

  //first setting
  players player;
  player.Day = 1;
  player.HP = 40;
  player.Hunger = 0;
  player.Thirst = 0;
  srand(time(NULL));

  //load game
  int choice;
  printf("[1: New Game] [2: Load Game]\n");
  scanf("%d", &choice);
  
  if (choice == 2) {
      if (!gameLoad(&player)) {
           printf("Starting New Game...\n");
      }
  }

  int quit = 0;
  
  //main loop
  while(player.Day <= 30) {
    if(player.Day == 1) {
      if(day1Event(&player) == 4) {
        quit = 1;
        break;
      }
    }
    else if(player.Day == 10) {
      if(day10Event(&player) == 4) {
        quit = 1;
        break;
      }
    }
    else if(player.Day == 20) {
      if(day20Event(&player) == 4) {
        quit = 1;
        break;
      }
    }
    else if(player.Day == 30) {
      //final event
      printf("==============================\n");
      printf("You have survived for 30 days!\n");
      printf("Rescue team found you and brought you home.\n");
      printf("Congratulations, survivor!\n");
      printf("==============================\n");
      break;
    }
    else {
      if(currentEventID = -1) currentEventID = pickEventID();
      if(runEventByID(currentEventID, &player) == 4) {
        quit = 1;
        break;
      }
    }

    //Next Day increments and resource consumption
    player.Day++;
    
    //Setup HP
    if(player.HP > MAX_HP) player.HP = MAX_HP;
    
    //Hunger
    if(item[1].count <= 0) {
      player.Hunger += hungerIncrease;
      if(player.Hunger > MAX_Hunger) player.Hunger = MAX_Hunger; 
    } else {
      printf("\n==============================\n");
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
      item[1].count -= n;
      if(n == 0) {
        player.Hunger += hungerIncrease;
        if(player.Hunger > MAX_Hunger) player.Hunger = MAX_Hunger; 
      }
    }
    if(player.Hunger >= hungerLevel) player.HP -= 5;
    if(player.Hunger < 0) player.Hunger = 0;
    

    //Thirst
    if(item[2].count <= 0) {
      player.Thirst += thirstIncrease;
      if(player.Thirst > MAX_Thirst) player.Thirst = MAX_Thirst; 
    } else {
      printf("\n==============================\n");
      printf("How many portions of water would you like to eat?\n");
      printf("Now Water * %d\n", item[2].count);
      printf("==============================\n");
      int n;
      while(1) {
        scanf("%d", &n);
        if(n < 0 || n > item[2].count) printf("worong input!\n");
        else break;
      }
      player.Thirst -= n * thirstReduction;
      item[2].count -= n;
      if(n == 0) {
        player.Thirst += thirstIncrease;
        if(player.Thirst > MAX_Thirst) player.Thirst = MAX_Thirst; 
      }
    }
    if(player.Thirst >= thirstLevel) player.HP -= 5;
    if(player.Thirst < 0) player.Thirst = 0;
    

    // Home HP
    if(Shelter > 4) Shelter = 4;
    if(SOS > 4) SOS = 4;
    if(Shelter != 4) player.HP += Shelter + 1;
    else player.HP += 10; 
    
    //screen clear
    currentEventID = -1;
    printf("\nPress Enter to Continue...");
    int input;
    while ((input = getchar()) != '\n' && input != EOF); // buffer clear
    while ((input = getchar()) != '\n' && input != EOF);
    system("cls");
    

    //Death - Ending 1
    if(player.HP <= 0) {
      printf("==============================\n");
      printf("You are dead.\n");
      printf("==============================\n");
      break;
    }
  }

  //save
  system("cls");
  int S;
  printf("[1: Game save] [2: No save]\n");
  scanf("%d", &S);
  if (S == 1) {
    gameSave(&player, currentEventID);
  }

  //screen clear
  printf("Press Enter...");
  int input;
  while ((input = getchar()) != '\n' && input != EOF); 
  while ((input = getchar()) != '\n' && input != EOF); 
  


  return 0;
}
