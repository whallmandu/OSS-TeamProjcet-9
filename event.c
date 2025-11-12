#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "event.h"


//Check Resources Function
void checkR() {
    int flag = 0;
    for(int i=1; i<itemCount; i++) {
        if(item[i].count > 0) {
            printf("[%s * %d]", item[i].itemname, item[i].count);
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
    printf("First day.\n"); //text data(story)
    printf("==============================\n");
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue); //player data
    int n;
    while(1) {
        printf("[1: Check resources] [2: Go seashore] [0: Quit]\n"); //selections
        
        //data input
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==0) return 4; //this is 'Quit' return data. only 4.
        else printf("wlong input\n");
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
NOMAL EVENT
============================================
*/
int dummy1(players *player) { //dummy 1
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("dummy1\n");
    printf("==============================\n");
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    int n;
    while(1) {
        printf("[1: Check resources] [2: water] [3: stone] [0: Quit]\n");
        
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wlong input!\n");
    }

    if(n==2) { //water
        printf("==============================\n");
        printf("water!\n");
        printf("[water +3]\n");
        printf("==============================\n");
        item[2].count += 3;
    } else if(n==3) { //stone
        printf("==============================\n");
        printf("stone!\n");
        printf("[stone +3]\n");
        printf("==============================\n");
        item[4].count += 3;
    }

    return 0;
}

int dummy2(players *player) { //dummy 2
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("dummy2\n");
    printf("==============================\n");
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    int n;
    while(1) {
        if(item[1].count > 0) {
            printf("[1: Check resources] [2: water] [3: stone--] [0: Quit]\n");
            scanf("%d", &n);
            if(n==1) checkR();
            else if(n==2) break;
            else if(n==3) break;
            else if(n==0) return 4;
            else printf("wlong input!\n");
        } else {
            printf("[1: Check resources] [2: water] [0: Quit]\n");
            scanf("%d", &n);
            if(n==1) checkR();
            else if(n==2) break;
            else if(n==0) return 4;
            else printf("wlong input!\n");
        }
    }

    if(n==2) { //water
        printf("==============================\n");
        printf("water!\n");
        printf("[water +3]\n");
        printf("==============================\n");
        item[2].count += 3;
    } else if(n==3) { //stone--
        printf("==============================\n");
        printf("stone--\n");
        printf("[stone -1]\n");
        printf("==============================\n");
        item[4].count += 3;
    }

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
    printf("dummy3\n");
    printf("==============================\n");
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    int n;
    while(1) {
        printf("[1: Check resources] [2: extra] [0: Quit]\n");
        
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==0) return 4;
        else printf("wlong input!\n");
    }

    if(n==2) { //extra
        printf("==============================\n");
        printf("whar are you extra!\n");
        printf("==============================\n");
        int m;
        while(1) {
            printf("[1: Check resources] [2: stone] [0: Quit]\n");
            
            scanf("%d", &m);
            if(m==1) checkR();
            else if(m==2) break;
            else if(m==0) return 4;
            else printf("wlong input!\n");
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
    dummy3
};

//special arr
int isRare[] = {0, 0, 1};

//visit O/X arr
int usedEvent[] = {0, 0, 0};

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