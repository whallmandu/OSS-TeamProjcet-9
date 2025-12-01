#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "event.h"

//Shelter, Sos signal, Raft
extern int Shelter;
extern int SOS;
extern int Raft;



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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst); //player data
    printf("==============================\n\n");

    printf("First day.\n");

    int n;
    while(1) {
        printf("[1: Check resources] [2: Go seashore] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==0) return 4; //this is 'Quit' return data. only 4.
        else printf("wrong input!\n");
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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
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
            printf("[HP - 10]\n");
            printf("==============================\n");
            player->HP -=10;
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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
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
        printf("[HP +10]\n");
        printf("==============================\n");
        player->HP += 10;
    }
    else { // n == 3
        printf("==============================\n");
        printf("You continue walking without resting.\n");
        printf("==============================\n");
    }
    return 0;
}


int suddenDownpour(players *player) { 
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
   
    printf("While searching for food, you are suddenly caught in a heavy downpour.\n");
    printf("You panic briefly but must react quickly.\n");
    
    int n;
    while(1) {
        printf("[1: Check resources] [2: Hide under a tree] [3: Continue walking] [0: Quit]\n");
        
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //Hide
        printf("==============================\n");
        printf("You quickly hide under a tree to avoid the rain.\n");
        printf("After a short while, the downpour passes.\n");
        printf("==============================\n");
    } 
    else if(n==3) { //Walking
        int a = rand() % 2;
        if(a == 0) { //success
            printf("==============================\n");
            printf("You push forward despite the rain.\n");
            printf("While you find no food, you manage to collect rainwater using a container.\n");
            printf("The cold still makes you shiver.\n");
            printf("[water +1] [HP -4]\n");
            printf("==============================\n");
            item[2].count += 1;
            player->HP -= 4;
        }
        else { //failure
            printf("==============================\n");
            printf("You decide to push forward despite the rain in hopes of finding food.");
            printf("However, you find nothing, and your body begins th shiver from the cold.\n");
            printf("[HP -4]\n");
            printf("==============================\n");
            player->HP -= 4;
        }
    }

    return 0;
}



int fallenFruit(players *player) { 
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
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
            printf("[food +4]\n");
            printf("==============================\n");
            item[1].count += 4;
        }
        else { //failure
            printf("==============================\n");
            printf("You pick up the fruit and eat it.");
            printf("The taste is strange, and soon your stomach begins to hurt.\n");
            printf("[HP -7]\n");
            printf("==============================\n");
            player->HP -= 7;
        }
    } else if(n==3) { //Ignore
        printf("==============================\n");
        printf("You decide that you shouldn't eat a fruit you know nothing about and move on.\n");
        printf("==============================\n");
    }

    return 0;
}

/* 3) Seaweed: dry -> rope, or eat -> food+water */
int event_seaweed(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n",
           player->HP, player->Hunger, player->Thirst);
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

int bigTree(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
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
        printf("[wood +6]\n");
        printf("==============================\n");
        item[5].count += 6;
    } else if(n==3) { //Ignore
        printf("==============================\n");
        printf("You decide not to dismantle the tree and move on.\n");
        printf("==============================\n");
    }

    return 0;
}


int event_herbs(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
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
            printf("[HP -15]\n");
            printf("==============================\n");
            player->HP -= 15;
        

        } 
        else { 
            printf("==============================\n");
            printf("Success: The herb was medicinal and refreshing.\n");
            printf("[HP +10] [food +1]\n");
            printf("==============================\n");
            player->HP += 10;
   
        }
    }
   
    else if(n == 3) {
        printf("==============================\n");
        printf("You decide to walk past the herbs.\n");
        printf("==============================\n");
    }
    return 0;
}
int findGroundWater(players *player) { 
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
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
        printf("Fortunately, there is no issue, and you collect a large amount of water.\n");
        printf("[water +5]\n");
        printf("==============================\n");
        item[2].count += 5;
    } 
    if (n == 3) { //Boil it
        printf("==============================\n");
        printf("You boil the water to drink it safely.\n");
        printf("It takes time, so you only manage to gather a small amount.\n");
        printf("[water +2]\n");
        printf("==============================\n");
        item[2].count += 2;
    }

    return 0;
}

int falmLeaves(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
    
    printf("You are walking through the forest when you find a pile of palm leaves.\n");
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
        printf("[leaves +8]\n");
        printf("==============================\n");
        item[4].count += 8;
    } 
    if (n == 3) { //Walk past
        printf("==============================\n");
        printf("Thinking you don't really need them, you simply walk past.\n");
        printf("==============================\n");
    }

    return 0;
}


/* 5) Pond fish */
int event_pond_fish(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("You discover a small pond with several trapped fish. They look easy to catch.\n");
    printf("What will you do?\n");


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
    else { 
        printf("==============================\n");
        printf("You decide not to catch the fish and leave.\n");
        printf("==============================\n");
    }
    return 0;
}

int fishingFish(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
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
        printf("[HP +6]\n");
        player->HP += 6;
    }

    return 0;
}

/* 6) Palm leaves -> rope or go out (risky) */
int event_palm_leaves(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
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
int collapsedCabin(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
     printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
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
            printf("[food +3] [cloth +8] [rope +5]\n");
            printf("==============================\n");
            item[1].count += 3;
            item[3].count += 5;
            item[6].count += 8;
        }
        else { //failure
            printf("==============================\n");
            printf("The cabin collapsed, injuring your shoulder.\n");
            printf("[HP -12]\n");
            printf("==============================\n");
            player->HP -= 12;
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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
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
        printf("[rope +4] [wood +3] [stone +1]\n");
        printf("==============================\n");
        item[3].count += 4;
        item[5].count += 3;
        item[7].count += 1;
    } 
    if (n == 3) { //Search around
        printf("==============================\n");
        printf("You found bottled water and stored food nearby.\n");
        printf("[food +3] [water +3]\n");
        printf("==============================\n");
        item[1].count += 3;
        item[2].count += 3;
    }

    return 0;
}


int shipwreck(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
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
            printf("[SOS signal LV +3]\n");
            printf("==============================\n");
            SOS += 3;
            if(SOS > 5) SOS = 5;
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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
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
        printf("[rope +3] [stone +5] [wood +5]\n");
        printf("==============================\n");
        item[5].count += 5;
        item[3].count += 3;
        item[7].count += 5;
    } 
    if(n==3) { //Break
        printf("==============================\n");
        printf("You smash the cest open, but in the process, some of the items inside get damaged.\n");
        printf("[rope +1] [stone +2] [wood +2]\n");
        printf("==============================\n");
        item[3].count += 1;
        item[5].count += 2;
        item[7].count += 2;
    }

    return 0;
}


int wildBoar(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
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

int approachingStorm(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
    
    printf("You notice dark clouds forming quickly above the sea.\n");
    printf("A storm is approaching.\n");
    printf("You need a prepare.\n");
    
    int n;
    while(1) {
        printf("[1: Check resources] [2: Reinforce shelter] [3: Gather emergency supplies] [0: Quit]\n");
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) {
            if(item[5].count > 1 && item[7].count > 2) {
                break;
            }
            else printf("No woods or stones!\n");
        }
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //Reinforce
        printf("==============================\n");
        printf("You reinforce your shelter using woods and stones.\n");
        printf("Thanks to your preparation, you endure the storm safely.\n");
        printf("[stone -3] [wood -2]\n");
        printf("==============================\n");
        item[5].count -= 2;
        item[7].count -= 3;
    } 
    if(n==3) { //Gather supplies
        printf("==============================\n");
        printf("You prioritize gathering food and water.\n");
        printf("During the storm, you shelter is damaged, but you avoid starvation.\n");
        printf("[food +8] [water +8] [Shelter LV -2]\n");
        printf("==============================\n");
        item[1].count += 8;
        item[2].count += 8;
        Shelter -= 2;
        if(Shelter < 0) Shelter = 0;
    }

    return 0;
}


/* Rare: Waterfall cliff risky climb */
int event_waterfall(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
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
            SOS = 1;
        } else {
            int r = rand() % 3;
            if(r == 0) {
                printf("==============================\n");
                printf("Against the odds, your small fire attracts the ship. You are rescued!\n");
                printf("==============================\n");
                SOS = 1;
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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
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
    event_tree_hole,     //normal event
    event_rock_shade,
    event_seaweed,
    event_herbs,
    event_pond_fish,
    event_palm_leaves,         
    suddenDownpour,     // 0  
    fallenFruit,        // 1
    bigTree,            // 2
    findGroundWater,    // 3
    falmLeaves,         // 4
    fishingFish,        // 5
    event_wave_collect,    // [Special Events]
    event_waterfall,
    event_ship_signal,
    event_cabin,
    event_cave,
    collapsedCabin,     // 6
    discoverLifeboat,   // 7
    shipwreck,          // 8
    somethingInSand,    // 9
    wildBoar,           // 10
    approachingStorm    // 11
};


int isRare[] = {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1};

/* usedEvent flags */
int usedEvent[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    






/* event manager */
int pickEventID() {
    int randomIDX;
    while (1) {
        randomIDX = rand() % eventCount; 

        if (isRare[randomIDX] && usedEvent[randomIDX]) {
            continue;
        }
        return randomIDX;
    }
}

int runEventByID(int eventID, players *player) {
    if (eventID < 0 || eventID >= eventCount) return 0;

    int result = (*eventList[eventID])(player);

    if (isRare[eventID]) {
        usedEvent[eventID] = 1;
    }

    return result;
}


//Save
void getUsedEvents(int *buffer) {
    for (int i = 0; i < eventCount; i++) {
        buffer[i] = usedEvent[i];
    }
}

//Load
void setUsedEvents(int *buffer) {
    for (int i = 0; i < eventCount; i++) {
        usedEvent[i] = buffer[i];
    }
}