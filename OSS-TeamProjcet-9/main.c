#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "event.h"







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
      while(1) {
        handleEvent(&player);
      }
     
      
      
      //printf("%d\n", random);
      //event(random)
    }
  }


  return 0;
}
