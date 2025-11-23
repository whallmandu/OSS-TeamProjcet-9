#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "event.h"


//Check Resources Function
void checkR() {
    int flag = 0;
    for(int i=1; i<itemCount; i++) {
        if(item[i].count > 0) {
            printf("[%s * %d] ", item[i].itemname, item[i].count);
            flag = 1;
        }
    }
    if(!flag) printf("No resources");
    printf("\n");
}

/*
============================================
FIXED EVENT
============================================
*/
int day1Event(players *player) { //first day
    printf("==============================\n");
    printf("Day %d\n", player->Day); //Day data
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue); //player data
    printf("==============================\n\n");
    
    printf("First day.\n"); //text data(story)

    int n;
    while(1) {
        printf("[1: Check resources] [2: Go seashore] [0: Quit]\n"); //selections
        
        //data input
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==0) return 4; //this is 'Quit' return data. only 4.
        else printf("wrong input\n");
    }

    if(n==2) { //Go seashore
        int r = rand()%2; //random
        if(r==1) { //wood
            printf("==============================\n");
            printf("You find wood!\n");
            printf("[wood +3]\n");
            printf("==============================\n");
            item[3].count += 3; //item update
        } else { //food
            printf("==============================\n");
            printf("You find food\n");
            printf("[food +1]\n");
            printf("==============================\n");
            item[1].count++; //item update
        }
    }

    return 0;
}

/*
============================================
NORMAL EVENT
============================================
*/
int fallenFruit(players *player) { //krh
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");
   
    printf("You find a fruit lying on the ground in the forest.\n");
    printf("It looks edible, but you cannot be certain.\n");
    printf("What will you do?\n");
    
    int n;
    while(1) {
        printf("[1: Check resources] [2: Eat it] [3: Ignore it] [0: Quit]\n");
        
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //Eat
        int a = rand() % 2;
        if(a == 0) { //success
            printf("==============================\n");
            printf("You eat the fruit.\n");
            printf("It is delicious, so you gather more of them.\n");
            printf("[food +2]\n");
            printf("==============================\n");
            item[1].count += 2;
        }
        else { //failure
            printf("==============================\n");
            printf("You pick up the fruit and eat it.");
            printf("The taste is strange, and soon your stomach begins to hurt.\n")
            printf("[HP -3]\n");
            printf("==============================\n");
            player->HP -= 3;
        }
    } else if(n==3) { //Ignore
        printf("==============================\n");
        printf("You decide that you shouldn't eat a fruit you know nothing about and move on.\n");
        printf("==============================\n");
    }

    return 0;
}

int bigTree(players *player) { //krh
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");
    
    printf("You find a large fallen tree on your path.\n");
    printf("If you handle it well, it may be usable as meterial.\n");
    printf("What will you do?\n");
    
    int n;
    while(1) {
        printf("[1: Check resources] [2: Gather meterials] [3: Ignore it] [0: Quit]\n");
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //gather meterials
        printf("==============================\n");
        printf("You break down the tree and obtain a large amount of wood.\n");
        printf("[wood +5]\n");
        printf("==============================\n");
        item[5].count += 5;
    } else if(n==3) { //Ignore
        printf("==============================\n");
        printf("You decide not to dismantle the tree and move on.\n");
        printf("==============================\n");
    }

    return 0;
}

int findGroundWater(players *player) { //krh
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");
    
    printf("You find a puddle of water on the ground in the forest.\n");
    printf("It's hard to tell if it's safe to drink.\n");
    printf("What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Drink it as is] [3: Boil it first] [0: Quit]\n");
        scanf("%d", &n);
        if (n == 1) checkR();
        else if (n == 2) break;
        else if (n == 3) break;
        else if (n == 0) return 4;
        else printf("wrong input!\n");
    }

    if (n == 2) { //Drink it as is
        printf("==============================\n");
        printf("You decide to drink the water.\n");
        printf("Fortunately, there is no issue, and you collect a large amount of water.\n")
        printf("[water +4]\n");
        printf("==============================\n");
        item[2].count += 4;
    } 
    if (n == 3) { //Boil it
        printf("==============================\n");
        printf("You boil the water to drink it safely.\n");
        printf("It takes time, so you only manage to gather a small amount.\n")
        printf("[water +2]\n");
        printf("==============================\n");
        item[2].count += 2;
    }

    return 0;
}

int falmLeaves(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");
    
    printf("You are walking through the forest when you find a pile of pal leaves.\n");
    printf("They might be useful for building a shelter.\n")
    printf("What will you do?\n");
   
    int n;
    while (1) {
    printf("[1: Check resources] [2: Collect them] [3: Walk past] [0: Quit]\n");
        scanf("%d", &n);
        if (n == 1) checkR();
        else if (n == 2) break;
        else if (n == 3) break;
        else if (n == 0) return 4;
        else printf("wrong input!\n");
    }

    if (n == 2) { //Collect them
        printf("==============================\n");
        printf("You picked up the palm leaves.\n");
        printf("[leaves +2]\n");
        printf("==============================\n");
        item[4].count += 2;
    } 
    if (n == 3) { //Walk past
        printf("==============================\n");
        printf("Thinking you don't really need them, you simply walk past.\n");
        printf("==============================\n");
    }

    return 0;
}


int dummy6(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

     printf("Rest Spot Found\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Take a rest] [0: Quit]\n");
        scanf("%d", &n);
        if (n == 1) checkR();
        else if (n == 2) break;
        else if (n == 0) return 4;
        else printf("wrong input!\n");
    }

    printf("==============================\n");
    printf("You took a good rest.\n");
    printf("[Fatigue -20]\n");
    printf("==============================\n");

    player->Fatigue -= 20;
    if (player->Fatigue < 0) player->Fatigue = 0;

    return 0;
}





/*
============================================
SPECIAL EVENT
============================================
*/
int dummy3(players *player) { //dummy 3
    printf("==============================\n");
    printf("Day %d\n", player->Day);
     printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");
    printf("dummy3\n");
    int n;
    while(1) {
        printf("[1: Check resources] [2: extra] [0: Quit]\n");
        
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //extra
        printf("==============================\n");
        printf("what are you extra!\n");
        printf("==============================\n");
        int m;
        while(1) {
            printf("[1: Check resources] [2: stone] [0: Quit]\n");
            
            scanf("%d", &m);
            if(m==1) checkR();
            else if(m==2) break;
            else if(m==0) return 4;
            else printf("wrong input!\n");
        }
        if(m==2) {
            printf("==============================\n");
            printf("stones!\n");
            printf("[stone +10]\n");
            printf("==============================\n");
            item[4].count += 10;
        }
    }

    return 0;
}

//namal and special event arr
int (*eventList[])(players *) = {
    dummy1,
    dummy2,
    dummy3,
    dummy4,
    dummy5,
    dummy6
};

//special arr
int isRare[] = {0, 0, 1, 0, 0, 0};

//visit O/X arr
int usedEvent[] = {0, 0, 0, 0, 0, 0};

//event manage
int handleEvent(players *player) {
    int randomIDX;
    int k = 0;
    while (1) {
        randomIDX = rand() % eventCount; //random data

        // isRare -> reroll
        if (isRare[randomIDX] && usedEvent[randomIDX]) {
            continue;
        }

        // selection event
        k = (*eventList[randomIDX])(player);
        // isRare -> check
        if (isRare[randomIDX]) {
            usedEvent[randomIDX] = 1;
        }
        break;
    }
    return k;
}