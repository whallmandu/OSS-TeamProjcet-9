#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "event.h"

//Home, Sos signal, Raft
extern int Home;
extern int SOS;
extern int Raft;

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
int fallenFruit(players *player) { 
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

int bigTree(players *player) {
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

int findGroundWater(players *player) { 
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
    printf("They might be useful for building a shelter.\n");
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


int fishingFish(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("While walking along the shore, you spot a few fish swimming in the shallow water.\n");
    printf("If you could catch them, they would be useful as food.\n");
    printf("What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Try catching them with your hands] [3: Just watch and move on] [0: Quit]\n");
        scanf("%d", &n);
        if (n == 1) checkR();
        else if (n == 2) break;
        else if (n == 3) break;
        else if (n == 0) return 4;
        else printf("wrong input!\n");
    }

    if(n == 2) { //Catching
        int a = rand()%3;
        if(a == 1) { //success
            printf("==============================\n");
            printf("You quickly reached out and caught one of the fish.\n");
            printf("[food +2]\n");
            printf("==============================\n");
            item[1].count += 2;
        } else { //failure
            printf("==============================\n");
            printf("The fish moved faster than you expected.\n");
            printf("While trying to catch one, you slipped and fell.\n");
            printf("[HP -3]\n");
            printf("==============================\n");
            player->HP -= 3;
        }
    }
    else if(n == 3) { //Move on
        printf("==============================\n");
        printf("You decide to save your energy and simply relax while looking our at the ocean horizon.\n");
        printf("[HP +3]\n");
        player->HP += 3;
    }

    return 0;
}





/*
============================================
SPECIAL EVENT
============================================
*/
int collapsedCabin(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
     printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You find a collapsed cabin deep in the forest.\n");
    printf("A box-like object is slightly visible under the debris.\n");
    printf("The structure looks ready to fall apart.\n");
    printf("What will you do?\n");

    int n;
    while(1) {
        printf("[1: Check resources] [2: Try to retrieve the box] [3: Walk past] [0: Quit]\n");
        
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //Try box
        int a = rand()%7;
        if(a>=5) { //success
            printf("==============================\n");
            printf("You found a small box containing food, cloth, and rope.\n");
            printf("[food +3] [cloth +3] [rope +3]\n");
            printf("==============================\n");
            item[1].count += 3;
            item[3].count += 3;
            item[6].count += 3;
        }
        else { //failure
            printf("==============================\n");
            printf("The cabin collapsed, injuring your shoulder.\n");
            printf("[HP -7]\n");
            printf("==============================\n");
            player->HP -= 7;
        }
    }
    if(n == 3) { //Walk past
        printf("==============================\n");
        printf("You pass by, considering it too dangerous.\n");
        printf("==============================\n");
    }

    return 0;
}


int discoverLifeboat(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");
    
    printf("You discover the remains of a lifeboat washed ashore.\n");
    printf("There might be useful items inside, or you may find food around it.\n");
    printf("What will you do?\n");
   
    int n;
    while (1) {
    printf("[1: Check resources] [2: Search inside the lifeboat] [3: Search around the lfieboat] [0: Quit]\n");
        scanf("%d", &n);
        if (n == 1) checkR();
        else if (n == 2) break;
        else if (n == 3) break;
        else if (n == 0) return 4;
        else printf("wrong input!\n");
    }

    if (n == 2) { //Search inside
        printf("==============================\n");
        printf("You found rope, wood, and stones inside the boat.\n");
        printf("[rope +2] [wood +2] [stone +2]\n");
        printf("==============================\n");
        item[3].count += 2;
        item[5].count += 2;
        item[7].count += 2;
    } 
    if (n == 3) { //Search around
        printf("==============================\n");
        printf("You found bottled water and stored food nearby.\n");
        printf("[food +3] [water +3]");
        printf("==============================\n");
        item[1].count += 3;
        item[2].count += 3;
    }

    return 0;
}


int shipwreck(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");
    
    printf("While exploring the beach, you discover the wreckage of a ship that seems to have sunk long ago.\n");
    printf("There might be something inside that could help you get rescued.\n");
    printf("What will you do?\n");
   
    int n;
    while (1) {
    printf("[1: Check resources] [2: Enter the shipwreck] [3: Ignore it] [0: Quit]\n");
        scanf("%d", &n);
        if (n == 1) checkR();
        else if (n == 2) break;
        else if (n == 3) break;
        else if (n == 0) return 4;
        else printf("wrong input!\n");
    }

    if (n == 2) { //Enter the ship
        int a = rand()%7;
        if(a >= 5) { //success
            printf("==============================\n");
            printf("You enter the shipwreck.\n");
            printf("You find several electronic devices, and after checking their condition, \nyou discover that some of them can still be used.\n");
            printf("[SOS signal LV +1]\n");
            printf("==============================\n");
            SOS += 1;
        }
        else { //faiure
            printf("==============================\n");
            printf("You enter the shipwreck.\n");
            printf("You find several electronic devices, but after checking their condition, \nyou realize they are too damaged to be used.\n");
            printf("==============================\n");
        }
    } 
    if (n == 3) { //Ignore it
        printf("==============================\n");
        printf("You decide to ignore the shipwreck since you don't know what might be inside.\n");
        printf("==============================\n");
    }

    return 0;
}


int somethingInSand(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");
    
    printf("While exploring the beach, you notice something half-buried in the sand.\n");
    printf("As you approach, you realize it's an old chest.\n");
    printf("It might contain something useful.\n");
    printf("What will you do?\n");
    
    int n;
    while(1) {
        printf("[1: Check resources] [2: Open it carefully] [3: Break it open] [0: Quit]\n");
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //Carefully
        printf("==============================\n");
        printf("You open the chest slowly and find various tools and supplies.\n");
        printf("[rope +2] [cloth +2] [wood +2]\n");
        printf("==============================\n");
        item[5].count += 2;
        item[3].count += 2;
        item[6].count += 2;
    } 
    if(n==3) { //Break
        printf("==============================\n");
        printf("You smash the cest open, but in the process, some of the items inside get damaged.\n");
        printf("[rope +1] [cloth +1] [wood +1]\n");
        printf("==============================\n");
        item[3].count += 1;
        item[5].count += 1;
        item[6].count += 1;
    }

    return 0;
}


int wildBoar(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n", player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");
    
    printf("While walking through the forest, you suddenly hear a loud rustling noise.\n");
    printf("A wild boar charges at you.\n");
    printf("You must react immediately.\n");
    
    int n;
    while(1) {
        printf("[1: Check resources] [2: Run away] [3: Climb a tree] [0: Quit]\n");
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //Run
        int a = rand() % 7;
        if(a >= 5) { //success
            printf("==============================\n");
            printf("You run at full speed and manage to escape the boar.\n");
            printf("==============================\n");
        }
        else { //failure
            printf("==============================\n");
            printf("You try to run, but the boar catches up and hits you.\n");
            printf("[HP -15]\n");
            printf("==============================\n");
            player->HP -= 15;
        }
    } 
    if(n==3) { //Climb
        printf("==============================\n");
        printf("You climb a tree as quickly as possible.\n");
        printf("The boar cannot reach you and eventually leaves.\n");
        printf("==============================\n");
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