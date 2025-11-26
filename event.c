#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "event.h"

/* check resources */
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
FIXED EVENT (day1)
============================================
*/
int day1Event(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day); //Day data
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("First day.\n");

    int n;
    while(1) {
        printf("[1: Check resources] [2: Go seashore] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==0) return 4;
        else printf("wrong input\n");
    }

    if(n==2) {
        int r = rand()%2;
        if(r==1) {
            printf("==============================\n");
            printf("You find wood!\n");
            printf("[wood +3]\n");
            printf("==============================\n");
            item[5].count += 3;
        } else {
            printf("==============================\n");
            printf("You find food\n");
            printf("[food +1]\n");
            printf("==============================\n");
            item[1].count++;
        }
    }

    return 0;
}

/*
============================================
NORMAL EVENTS 
============================================
*/

/* 1) Tree hole (eggs / bird peck) */
int event_tree_hole(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You find a large tree with a hole in its trunk, and something inside is glimmering.\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Put your hand inside (risky)] [3: Walk past] [0: Quit]\n");
        if (scanf("%d", &n) != 1) { while (getchar()!='\n'); continue; }

        if (n == 1) checkR();      
        else if (n == 2) break;    
        else if (n == 3) break;    
        else if (n == 0) return 4; 
        else printf("wrong input!\n");
    }

    if (n == 2) {
        int r = rand() % 2;
        if (r == 0) {
            printf("==============================\n");
            printf("Failure: You disturbed a small bird’s nest; the bird pecked you and you fell.\n");
            printf("[Fatigue +15]\n");
            printf("==============================\n");
            player->Fatigue += 15;
        } else {
            printf("==============================\n");
            printf("Success: Inside the hole you find a few eggs. You take them.\n");
            printf("[food +1]\n");
            printf("==============================\n");
            item[1].count += 1;
        }
    } 
    else if (n == 3) {
        printf("==============================\n");
        printf("You walk past the tree, deciding not to risk it.\n");
        printf("==============================\n");
    }

    return 0;
}


int event_rock_shade(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You find a cool, shaded area under a large rock. It looks like a comfortable place to rest.\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Rest in the shade] [3: Keep walking] [0: Quit]\n");

        if (scanf("%d", &n) != 1) { 
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();
        }
        else if (n == 2 || n == 3 || n == 0) {
            break;
        }
        else {
            printf("wrong input!\n");
        }
    }

    if (n == 0) return 4;

    if (n == 2) {
        printf("==============================\n");
        printf("You lie down under the cool shade and relax.\n");
        printf("[Fatigue -15]\n");
        printf("==============================\n");
        player->Fatigue -= 15;
        if (player->Fatigue < 0) player->Fatigue = 0;
    }
    else { // n == 3
        printf("==============================\n");
        printf("You continue walking without resting.\n");
        printf("==============================\n");
    }

    return 0;
}

/* 3) Seaweed: dry -> rope, or eat -> food+water */
int event_seaweed(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You find a large pile of seaweed washed up on the beach. If dried, it could be used as rope, and it might also be edible.\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Dry the seaweed (make rope)] [3: Eat the seaweed] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();        
        }
        else if (n == 2 || n == 3 || n == 0) {
            break;
        }
        else {
            printf("wrong input!\n");
        }
    }

    if (n == 0) return 4;

    if (n == 2) {
        printf("==============================\n");
        printf("You dry the seaweed and make rope.\n");
        printf("[rope +1]\n");
        printf("==============================\n");
        item[3].count += 1; 
    }
    else if (n == 3) {
        printf("==============================\n");
        printf("You keep the seaweed as food and water.\n");
        printf("[food +1] [water +1]\n");
        printf("==============================\n");
        item[1].count += 1;
        item[2].count += 1;
    }

    return 0;
}


int event_herbs(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You discover a pile of fragrant herbs. They might be medicinal or poisonous. What will you do?\n");

    int n;
    while(1) {
        printf("[1: Check resources] [2: Gather and taste (risky)] [3: Walk past] [0: Quit]\n");

        if(scanf("%d", &n) != 1) { 
            while(getchar()!='\n');
            continue; 
        }

       
        if(n == 1) {
            checkR();
        }
      
        else if(n == 2 || n == 3 || n == 0) {
            break;
        }
        else {
            printf("wrong input!\n");
        }
    }

    if(n == 0) return 4;

 
    if(n == 2) {
        int r = rand() % 2;
        if(r == 0) { 
            printf("==============================\n");
            printf("Failure: The herb was poisonous. You feel severe stomach pain.\n");
            printf("[Fatigue +25]\n");
            printf("==============================\n");
            player->Fatigue += 25;

            if(player->Fatigue >= 100) {
                printf("==============================\n");
                printf("Condition worsened: You collapse from exhaustion.\n");
                printf("==============================\n");
                player->HP = 0;
            }
        } 
        else { 
            printf("==============================\n");
            printf("Success: The herb was medicinal and refreshing.\n");
            printf("[Fatigue -15] [food +1]\n");
            printf("==============================\n");
            player->Fatigue -= 15;
            if(player->Fatigue < 0) player->Fatigue = 0;
            item[1].count += 1;
        }
    }
   
    else if(n == 3) {
        printf("==============================\n");
        printf("You decide to walk past the herbs.\n");
        printf("==============================\n");
    }

    return 0;
}


/* 5) Pond fish */
int event_pond_fish(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You discover a small pond with several trapped fish. They look easy to catch. What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Catch the fish] [3: Walk past] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();
        }
        else if (n == 2 || n == 3 || n == 0) {
            break;
        }
        else {
            printf("wrong input!\n");
        }
    }

    if (n == 0) return 4;

    if (n == 2) {
        printf("==============================\n");
        printf("You reach into the pond and catch the fish easily.\n");
        printf("[food +1]\n");
        printf("==============================\n");
        item[1].count += 1;
    }
    else { /
        printf("==============================\n");
        printf("You decide not to catch the fish and leave.\n");
        printf("==============================\n");
    }

    return 0;
}

/* 6) Palm leaves -> rope or go out (risky) */
int event_palm_leaves(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You notice you have many palm leaves. You could spend the day turning some into rope, or go out to look for food.\n");
    printf("What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Go outside (risky chance)] [3: Turn palm leaves into rope] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();   
        }
        else if (n == 2 || n == 3 || n == 0) {
            break;
        }
        else {
            printf("wrong input!\n");
        }
    }

    if (n == 0) return 4;

    if (n == 2) {
        int r = rand() % 2;
        if (r == 0) {
            printf("==============================\n");
            printf("Failure: You found nothing while outside.\n");
            printf("==============================\n");
        } else {
            printf("==============================\n");
            printf("Success: You found some simple fruits.\n");
            printf("[food +1]\n");
            printf("==============================\n");
            item[1].count += 1;
        }
    }
    else if (n == 3) { // palm leaves → rope
        if (item[4].count >= 3) {
            item[4].count -= 3;
            item[3].count += 1; 
            printf("==============================\n");
            printf("You turned palm leaves into rope.\n");
            printf("[rope +1] [palm -3]\n");
            printf("==============================\n");
        } else {
            printf("==============================\n");
            printf("You don't have enough palm leaves (need 3). Nothing happens.\n");
            printf("==============================\n");
        }
    }

    return 0;
}




/*
============================================
RARE / SPECIAL EVENTS
============================================
*/

/* Rare: Collect driftwood but risk wave */
int event_wave_collect(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You notice a massive wave approaching and large pieces of driftwood on the beach.\n");
    printf("Should I collect the wood chips?\n");

    int n;
    while(1) {
        printf("[1: Check resources] [2: Collect the wood] [3: Escape to safety] [0: Quit]\n");

        if (scanf("%d", &n) != 1) { 
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();
        }
        else if (n == 2 || n == 3 || n == 0) {
            break;
        }
        else {
            printf("wrong input!\n");
        }
    }

    if(n == 0) return 4;

    if(n == 2) {   
        int r = rand()%2;
        if(r==0) {
            printf("==============================\n");
            printf("Failure: The wave hits sooner than expected; you are swept away.\n");
            printf("[HP -25]\n");
            printf("==============================\n");
            player->HP -= 25;
        } else {
            printf("==============================\n");
            printf("Success: You gathered a large amount of wood before the wave arrived.\n");
            printf("[wood +10]\n");
            printf("==============================\n");
            item[5].count += 10;
        }
    } 
    else {  
        printf("==============================\n");
        printf("You hide in a safe location and avoid danger.\n");
        printf("==============================\n");
    }

    return 0;
}


/* Rare: Waterfall cliff risky climb */
int event_waterfall(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You find a cliff with a small waterfall and clear water below. Climbing down is dangerous.\n");
    printf("Would you like to go down?\n");

    int n;
    while(1) {
        printf("[1: Climb down (risky)] [2: Walk back] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        int r = rand()%2;
        if(r==0) {
            printf("==============================\n");
            printf("Failure: You slipped and were badly injured.\n");
            printf("[HP -30]\n");
            printf("==============================\n");
            player->HP -= 30;
        } else {
            printf("==============================\n");
            printf("Success: You collected plenty of water.\n");
            printf("[water +10]\n");
            printf("==============================\n");
            item[2].count += 10;
        }
    } else {
        printf("==============================\n");
        printf("You return safely without taking the risk.\n");
        printf("==============================\n");
    }

    return 0;
}

/* Rare: Ship on horizon -> try to signal with fire (escape ending) */
int event_ship_signal(players *player) {
    extern int resque; // declared in main.c; we'll set it to signal rescue
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You spot a ship far away on the horizon. This might be your chance to escape the island.\n");
    printf("What will you do?\n");

    int n;
    while(1) {
        printf("[1: Check resources] [2: Signal with a fire] [3: Wave your arms] [0: Quit]\n");

        if(scanf("%d", &n) != 1) {
            while(getchar() != '\n');
            continue;
        }

        if(n == 1) {
            checkR(); 
        }
        else if(n == 2 || n == 3 || n == 0) {
            break;
        }
        else {
            printf("wrong input!\n");
        }
    }

    if(n == 0) return 4;

    if(n == 2) { 
        int wood = item[3].count;
        if(wood >= 3) {
            item[3].count -= 3;
            printf("==============================\n");
            printf("You quickly gather wood, set a fire, and the ship changes course toward you.\n");
            printf("You are rescued!\n");
            printf("==============================\n");
            resque = 1;
        } else {
            int r = rand() % 3;
            if(r == 0) {
                printf("==============================\n");
                printf("Against the odds, your small fire attracts the ship. You are rescued!\n");
                printf("==============================\n");
                resque = 1;
            } else {
                printf("==============================\n");
                printf("Your fire wasn't enough; the ship doesn't see you.\n");
                printf("==============================\n");
            }
        }
    } else if(n == 3) { 
        printf("==============================\n");
        printf("You wave your arms, but the ship is too far and doesn't notice you.\n");
        printf("==============================\n");
    }

    return 0;
}

/* Rare: Abandoned cabin */
int event_cabin(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You discover an abandoned cabin deep in the forest. It looks old but may contain useful items.\n");
    printf("Would you like to go into that?\n");

    int n;
    while(1) {
        printf("[1: Check resources] [2: Enter the cabin] [3: Stay outside and observe] [0: Quit]\n");

        if(scanf("%d", &n) != 1) { 
            while(getchar() != '\n');
            continue;
        }

        if(n == 1) {
            checkR(); 
        }
        else if(n == 2 || n == 3 || n == 0) {
            break;
        }
        else {
            printf("wrong input!\n");
        }
    }

    if(n == 0) return 4;

    if(n == 2) {
        printf("==============================\n");
        printf("You find old tools and some preserved supplies inside the cabin.\n");
        printf("[cloth +1] [food +1]\n");
        printf("==============================\n");
        item[6].count += 1; 
        item[1].count += 1; 
    } else if(n == 3) {
        printf("==============================\n");
        printf("You observe for a while and find nothing useful.\n");
        printf("==============================\n");
    }

    return 0;
}


/* Rare: Cave with supplies and water */
int event_cave(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You find a cave entrance hidden behind vines. It looks dark but may contain valuables.\n");
    printf("Would you like to go into that?\n");

    int n;
    while(1) {
        printf("[1: Check resources] [2: Enter the cave] [3: Ignore it] [0: Quit]\n");

        if(scanf("%d", &n) != 1) {
            while(getchar() != '\n');
            continue;
        }

        if(n == 1) {
            checkR(); 
        }
        else if(n == 2 || n == 3 || n == 0) {
            break;
        }
        else {
            printf("wrong input!\n");
        }
    }

    if(n == 0) return 4;

    if(n == 2) {
        printf("==============================\n");
        printf("You cautiously enter and find some old supplies and a small amount of fresh water.\n");
        printf("[food +1] [water +2]\n");
        printf("==============================\n");
        item[1].count += 1;
        item[2].count += 2;
    } else if(n == 3) {
        printf("==============================\n");
        printf("You decide it's too risky and walk away.\n");
        printf("==============================\n");
    }

    return 0;
}


/* event list, rarity flags, used flags */
int (*eventList[])(players *) = {
    event_tree_hole,
    event_rock_shade,
    event_seaweed,
    event_herbs,
    event_pond_fish,
    event_palm_leaves,
    event_wave_collect,
    event_waterfall,
    event_ship_signal,
    event_cabin,
    event_cave
};

/*
   0 tree_hole
   1 rock_shade
   2 seaweed
   3 herbs
   4 pond_fish
   5 palm_leaves
   6 wave_collect (rare)
   7 waterfall (rare)
   8 ship_signal (rare)
   9 cabin (rare)
   10 cave(rare)
*/
int isRare[] = {0,0,0,0,0,0,1,1,1,1,1};

/* usedEvent flags */
int usedEvent[] = {0,0,0,0,0,0,0,0,0,0,0};

/* event manager */
int handleEvent(players *player) {
    int randomIDX;
    int k = 0;
    while (1) {
        randomIDX = rand() % eventCount;

        /* if rare and already used, reroll */
        if (randomIDX < (sizeof(isRare)/sizeof(isRare[0])) &&
            isRare[randomIDX] && usedEvent[randomIDX]) {
            continue;
        }

        /* call event */
        k = (*eventList[randomIDX])(player);

        /* if rare and chosen, mark used */
        if (randomIDX < (sizeof(isRare)/sizeof(isRare[0])) && isRare[randomIDX]) {
            usedEvent[randomIDX] = 1;
        }

        break;
    }
    return k;
}
