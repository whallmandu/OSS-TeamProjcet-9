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
