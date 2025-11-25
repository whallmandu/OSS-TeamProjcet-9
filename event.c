#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "event.h"

/* check resources (unchanged) */
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
            item[3].count += 3;
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
NORMAL EVENTS (user-provided)
Format: print header -> description -> choices -> outcomes
Return 4 if user selected Quit from menu
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
    while(1) {
        printf("[1: Put your hand inside (risky)] [2: Walk past] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        int r = rand()%2;
        if(r==0) { // failure
            printf("==============================\n");
            printf("Failure: You disturbed a small bird’s nest; the bird pecked you and you fell.\n");
            printf("[Fatigue +15]\n");
            printf("==============================\n");
            player->Fatigue += 15;
        } else { // success
            printf("==============================\n");
            printf("Success: Inside the hole you find a few eggs. You take them.\n");
            printf("[food +1]\n");
            printf("==============================\n");
            item[1].count += 1;
        }
    } else {
        printf("==============================\n");
        printf("You walk past the tree, deciding not to risk it.\n");
        printf("==============================\n");
    }

    return 0;
}

/* 2) Rock shade rest */
int event_rock_shade(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You find a cool, shaded area under a large rock. It looks like a comfortable place to rest.\n");
    

    int n;
    while(1) {
        printf("[1: Rest in the shade] [2: Keep walking] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        printf("==============================\n");
        printf("You lie down under the cool shade and relax. [Fatigue -15]\n");
        printf("==============================\n");
        player->Fatigue -= 15;
        if(player->Fatigue < 0) player->Fatigue = 0;
    } else {
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
    while(1) {
        printf("[1: Dry the seaweed (make rope)] [2: Eat the seaweed] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        printf("==============================\n");
        printf("You dry the seaweed and make rope.\n");
        printf("[rope +1]\n");
        printf("==============================\n");
        item[8].count += 1; // rope index = 8
    } else {
        printf("==============================\n");
        printf("You keep the seaweed as food and water.\n");
        printf("[food +1] [water +1]\n");
        printf("==============================\n");
        item[1].count += 1;
        item[2].count += 1;
    }

    return 0;
}

/* 4) Herbs (risky random) */
int event_herbs(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You discover a pile of fragrant herbs. They might be medicinal or poisonous. What will you do?\n");
  

    int n;
    while(1) {
        printf("[1: Gather and taste (risky)] [2: Walk past] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        int r = rand()%2;
        if(r==0) { // failure - poisonous
            printf("==============================\n");
            printf("Failure: The herb was poisonous. You feel severe stomach pain and sweat profusely.\n");
            printf("[Fatigue +25]\n");
            printf("==============================\n");
            player->Fatigue += 25;
            // if fatigue too high, cause collapse (map to ending)
            if(player->Fatigue >= 100) {
                printf("==============================\n");
                printf("Condition worsened: You collapse from exhaustion/poisoning.\n");
                printf("==============================\n");
                player->HP = 0; // force death / ending
            }
        } else { // success
            printf("==============================\n");
            printf("Success: The herb was delicious and invigorating.\n");
            printf("[Fatigue -15] [food +1]\n");
            printf("==============================\n");
            player->Fatigue -= 15;
            if(player->Fatigue < 0) player->Fatigue = 0;
            item[1].count += 1;
        }
    } else {
        printf("==============================\n");
        printf("You decide not to risk it and walk past.\n");
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
    while(1) {
        printf("[1: Catch the fish] [2: Walk past] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        printf("==============================\n");
        printf("You reach into the pond and catch the fish easily.\n");
        printf("[food +1]\n");
        printf("==============================\n");
        item[1].count += 1;
    } else {
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
    printf("what will you do?\n");

    int n;
    while(1) {
        printf("[1: Go outside (risky chance)] [2: Turn palm leaves into rope] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        int r = rand()%2;
        if(r==0) {
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
    } else { // turn into rope
        // palm index we added in main.c (index 13)
        int palmIdx = 13;
        if(palmIdx < itemCount && item[palmIdx].count >= 3) {
            item[palmIdx].count -= 3;
            item[8].count += 1; // rope +1
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

/* 7) Rest spot (previous dummy6) */
int event_rest_spot(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] [Fatigue: %d]\n",
           player->HP, player->Hunger, player->Thirst, player->Fatigue);
    printf("==============================\n\n");

    printf("You find a restful spot and decide whether to take a rest.\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Take a rest] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
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
        printf("[1: Collect the wood] [2: Escape to safety] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
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
            item[3].count += 10;
        }
    } else {
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
        printf("[1: Signal with a fire] [2: Wave your arms] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        // require some wood to make a visible fire; if none, try anyway but lower chance
        int wood = item[3].count;
        int chance = (wood >= 3) ? 0 : 1; // if enough wood, success guaranteed here (simpler)
        if(wood >= 3) {
            item[3].count -= 3;
            printf("==============================\n");
            printf("You quickly gather wood, set a fire, and the ship changes course toward you.\n");
            printf("You are rescued!\n");
            printf("==============================\n");
            resque = 1;
        } else {
            // small chance success
            int r = rand()%3;
            if(r==0) {
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
    } else {
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
        printf("[1: Enter the cabin] [2: Stay outside and observe] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        printf("==============================\n");
        printf("You find old tools and some preserved supplies inside the cabin.\n");
        printf("[cloth +1] [food +1]\n");
        printf("==============================\n");
        item[6].count += 1; // cloth
        item[1].count += 1; // food
    } else {
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
        printf("[1: Enter the cave] [2: Ignore it] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1 || n==2 || n==0) break;
        printf("wrong input!\n");
    }
    if(n==0) return 4;

    if(n==1) {
        printf("==============================\n");
        printf("You cautiously enter and find some old supplies and a small amount of fresh water.\n");
        printf("[food +1] [water +2]\n");
        printf("==============================\n");
        item[1].count += 1;
        item[2].count += 2;
    } else {
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
    event_rest_spot,
    event_wave_collect,
    event_waterfall,
    event_ship_signal,
    event_cabin,
    // event_cave is extra but eventCount currently defined as 11; if you want cave included, increase eventCount
    // we will keep cave as an included function in event selection below by including it in array and adjusting eventCount in header
    // but to avoid mismatch, ensure header's eventCount matches number of elements used at compile time.
};

/* Note: we declared eventCount=11 in header; ensure eventList length matches eventCount */

/* Set rarity: 1 means rare (should not re-roll if already used in a playthrough)
   Ordering must match eventList above.
   We'll mark: wave_collect, waterfall, ship_signal, cabin, cave as rare.
   Our eventList indices:
   0 tree_hole
   1 rock_shade
   2 seaweed
   3 herbs
   4 pond_fish
   5 palm_leaves
   6 rest_spot
   7 wave_collect (rare)
   8 waterfall (rare)
   9 ship_signal (rare)
   10 cabin (rare)
*/
int isRare[] = {0,0,0,0,0,0,0,1,1,1,1};

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
