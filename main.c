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

void printPrologue() {
    const char *lines[] = {
        "It was October, somewhere near the Caribbean.",
        "He was preparing to set sail on a rescue mission.",
        "The sea was pitch-black, and there was nothing in sight.",
        "Then, a massive wave lifted the rescue boat high into the air before slamming it back down.",
        "He lost consciousness, and the ocean quietly added him to the list of those who needed saving.",
        "The next morning, he woke up on the shore of an uninhabited island.",
        "There was no one around, and he had no way to tell where he was.",
        "He didn't know how long he'd be there, or even if anyone would come.",
        "But one thing was certain: he was no longer the rescuer-he was the one waiting to be rescued."
    };

    int count = sizeof(lines) / sizeof(lines[0]);

    system("cls");
    printf("===== PROLOGUE =====\n\n");
    drawImage(900, 0, "image\\prologue_1.bmp");
    for (int i = 0; i < count; i++) {
      if(i==4) drawImage(900, 0, "image\\prologue_2.bmp");
      printf("%s\n", lines[i]);
      Sleep(1000); // 1.3 seconds delay
    }

    printf("\nPress Enter to begin your survival journey...");
    getchar();
    system("cls");
}


int main() {
  system("mode con: cols=190 lines=40");
  system("title ISOLATED");
  SetConsoleOutputCP(CP_UTF8);
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
  printf("\n\n");
  printf("  ██╗███████╗ ██████╗ ██╗      █████╗ ████████╗███████╗██████╗ \n");
  printf("  ██║██╔════╝██╔═══██╗██║     ██╔══██╗╚══██╔══╝██╔════╝██╔══██╗\n");
  printf("  ██║███████╗██║   ██║██║     ███████║   ██║   █████╗  ██║  ██║\n");
  printf("  ██║╚════██║██║   ██║██║     ██╔══██║   ██║   ██╔══╝  ██║  ██║\n");
  printf("  ██║███████║╚██████╔╝███████╗██║  ██║   ██║   ███████╗██████╔╝\n");
  printf("  ╚═╝╚══════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═════╝ \n");
  printf("\n");
  printf("            [ 1 : New Game ]    [ 2 : Load Game ]\n");
  scanf("%d", &choice);
  

  int tmp;
  while ((tmp = getchar()) != '\n' && tmp != EOF);

  if (choice == 1) {
      printPrologue();
  }
  else if (choice == 2) {
     if (!gameLoad(&player)) {
         printf("Starting New Game...\n");
         printPrologue();
     }
  }



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
    else if (player.Day == 30) {

       int ending = event_final_day(&player);

       if (ending == 9) {         // Rescue Ending
           break;
       }
       else if (ending == 10) {   // Successful Deserted Ending
           break;
       }
       else if (ending == 11) {   // Forced Deserted Ending
           break;
       }
       else {
           // ending == 0 → re
           continue;
       }
    }
    else {
      if(currentEventID == -1) currentEventID = pickEventID();
      int k = runEventByID(currentEventID, &player)
      if(k == 4) {
        quit = 1;
        break;
      }
      else if(k == 9) break;
    }

    //Next Day increments and resource consumption
    player.Day++;
    //Special Death
    if(player.HP <= -100) {
      printf("==============================\n");
      printf("You are dead.\n");
      printf("==============================\n");
      break;
    }
    
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
    
    if (player.Hunger >= 50) {
    printf("==============================\n");
    printf("You collapsed from extreme hunger.\n");
    printf("Your vision fades to black...\n");
    printf("You died.\n");
    printf("==============================\n");
    break;
}

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
        if(n < 0 || n > item[2].count) printf("wrong input!\n");
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


    if (player.Thirst >= 50) {
    printf("==============================\n");
    printf("Your body could not endure the dehydration.\n");
    printf("You collapse on the ground...\n");
    printf("You died.\n");
    printf("==============================\n");
    break;
}


    

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
  if(quit == 1) {
    int S;
    printf("\n\n[1: Game save] [2: No save]\n");
    scanf("%d", &S);
    if (S == 1) {
      gameSave(&player, currentEventID);
    }
  }
  

  //screen clear
  printf("Press Enter...");
  int input;
  while ((input = getchar()) != '\n' && input != EOF); 
  while ((input = getchar()) != '\n' && input != EOF); 
  


  return 0;
}
