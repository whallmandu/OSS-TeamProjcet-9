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
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("First day.\n");

    int n;
    while(1) {
        printf("[1: Check resources] [2: Go seashore] [0: Quit]\n");
        if(scanf("%d", &n) != 1) { while(getchar()!='\n'); continue; }
        if(n==1) { checkR(); continue; }
        else if(n==0) return 4;
        else break;
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

int event_final_day(players *player) {

    printf("==============================\n");
    printf("Day %d (Final Day)\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("You have survived for a full 30 days on an uninhabited island,\n");
    printf("enduring harsh conditions and constant threats.\n");
    printf("Now you must choose what to do next.\n\n");

    int n;

    while (1) {
        printf("[1: Check resources] [2: Request Rescue] [3: Remain on the Island] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();
            continue;
        }
        if (n == 2 || n == 3) break;
        if (n == 0) return 4;

        printf("wrong input!\n");
    }

    // ===================================================
    // [2] Request Rescue (Requires Distress Signal Lv 4)
    // ===================================================
    if (n == 2) {

        // 성공 조건: SOS >= 4
        if (SOS >= 4) {
            printf("==============================\n");
            printf("You activated all your distress signals.\n");
            printf("Soon, you hear helicopter blades cutting the sky.\n");
            printf("The rescue team calls out to you.\n");
            printf("One of them turns out to be an old colleague.\n");
            printf("You are finally rescued.\n");
            printf("=== RESCUE ENDING ===\n");
            printf("==============================\n");
            return 9;   // Rescue Ending
        }

        // Distress Signal Lv 3 이하
        else {
            printf("==============================\n");
            printf("You activated all your distress signals and waited.\n");
            printf("But by dawn, no sound came.\n");
            printf("You stay calm and decide to look for another option.\n");
            printf("==============================\n");
            return 0;   // 돌아가기
        }
    }

    // ===================================================
    // [3] Remain on the island
    // ===================================================
    if (n == 3) {

        // Shelter Lv 4 이상
        if (Shelter >= 4) {
            printf("==============================\n");
            printf("Your shelter is strong and comfortable.\n");
            printf("You sit before the sunset, feeling no pressure of past life.\n");
            printf("You realize escape is not necessary.\n");
            printf("=== SUCCESSFUL DESERTED ENDING ===\n");
            printf("==============================\n");
            return 10;  // Successful Deserted Ending
        }

        // Shelter Lv 3 이하
        else {
            printf("==============================\n");
            printf("Your shelter is unstable, but there's nothing more you can do.\n");
            printf("You decide to remain and hope for rescue someday.\n");
            printf("=== FORCED DESERTED ENDING ===\n");
            printf("==============================\n");
            return 11;  // Forced Deserted Ending
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
        if (n == 1) { checkR(); continue; }
        else if (n == 0) return 4;
        else break;
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

/* 2) Rock shade */
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

        if (scanf("%d", &n) != 1) { while (getchar() != '\n'); continue; }

        if (n == 1) { checkR(); continue; }
        else if (n == 0) return 4;
        else break;
    }

    if (n == 2) {
        printf("==============================\n");
        printf("You lie down under the cool shade and relax.\n");
        printf("[HP +10]\n");
        printf("==============================\n");
        player->HP += 10;
    }
    else {
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

int event_wave_collect(players *player) {


    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("As you walk along the coastline, you notice a fallen coconut tree.\n");
    printf("You could collect several coconuts and some usable wood from it.\n");
    printf("However, when you look toward the sea, you see a massive wave approaching.\n");
    printf("The coconuts and wood would be useful, but there is a risk of being swept away.\n");
    printf("What will you do?\n\n");

    int n;

  
    while (1) {
        printf("[1: Check resources] [2: Collect them] [3: Ignore it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();
            continue;
        }
        else if (n == 2 || n == 3) {
            break;
        }
        else if (n == 0) {
            return 4;
        }
        else {
            printf("wrong input!\n");
        }
    }



    if (n == 2) {    // Collect them
        int r = rand() % 100;

        if (r < 20) {
           
            printf("==============================\n");
            printf("Success: You rush forward and collect the coconuts and wood.\n");
            printf("You barely manage to escape, and the wave stops right in front of you.\n");
            printf("[Food +3] [Water +3] [Wood +7]\n");
            printf("==============================\n");

            item[1].count += 3;  // Food (item index는 네 프로젝트 기준)
            item[2].count += 3;  // Water
            item[5].count += 7;  // Wood
        }
        else {
            
            printf("==============================\n");
            printf("Failure: You attempt to collect them, but the massive wave is faster.\n");
            printf("You are swept away by the water.\n");
            printf("[HP -12]\n");
            printf("==============================\n");

            player->HP -= 12;
        }
    }
    else if (n == 3) {  // Ignore it
        printf("==============================\n");
        printf("The wave looks too fast, so you decide to avoid danger and retreat into the forest.\n");
        printf("==============================\n");
    }

    return 0;
}


int collapsedCabin(players *player) {

    // ===============================
    // 플레이어 정보 출력
    // ===============================
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    // ===============================
    // 상황 설명
    // ===============================
    printf("You are walking through the forest when you discover an old cabin that looks like it was built long ago.\n");
    printf("Inside the cabin, you see several rotten foods and a box. However, the cabin looks unstable and dangerous.\n");
    printf("What will you do?\n\n");

    int n;

    // ===============================
    // 공통 선택지 루프
    // ===============================
    while (1) {
        printf("[1: Check resources] [2: Enter the cabin] [3: Ignore it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n'); 
            continue;
        }

        if (n == 1) {
            checkR();
            continue;
        }
        else if (n == 2 || n == 3) {
            break;
        }
        else if (n == 0) {
            return 4;   // Quit
        }
        else {
            printf("wrong input!\n");
        }
    }

    // ===============================
    // 선택 실행
    // ===============================

    if (n == 2) { // Enter
        int r = rand() % 100;

        if (r < 25) {
            // 성공 (25%)
            printf("==============================\n");
            printf("Success: You decide to take the risk and enter the cabin.\n");
            printf("Inside, you open the box and find various supplies.\n");
            printf("[Cloth +8] [Rope +5]\n");
            printf("==============================\n");

            item[6].count += 8;  // Cloth
            item[3].count += 5;  // Rope (item index는 실제 프로젝트 기준으로 조정 필요)
        }
        else {
            // 실패 (75%)
            printf("==============================\n");
            printf("Failure: The moment you step inside, the unstable cabin collapses under your weight.\n");
            printf("You fall through the rotten floor and get injured.\n");
            printf("[HP -15]\n");
            printf("==============================\n");

            player->HP -= 15;
        }
    }
    else if (n == 3) { // Ignore
        printf("==============================\n");
        printf("The cabin looks too dangerous, so you decide to simply pass by.\n");
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
    printf("[1: Check resources] [2: Search inside the lifeboat] [3: Search around the lifeboat] [0: Quit]\n");
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

    // ===============================
    // Player Info
    // ===============================
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    // ===============================
    // Situation
    // ===============================
    printf("You were walking along the shore when you discovered a shipwreck stranded on the beach.\n");
    printf("You don't know what might be inside, but judging by its size, there could be useful materials.\n");
    printf("What will you do?\n\n");

    int n;

    // ===============================
    // 선택지 루프
    // ===============================
    while (1) {
        printf("[1: Check resources] [2: Explore it] [3: Board it and escape] [4: Ignore it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();
            continue;
        }
        else if (n == 2 || n == 3 || n == 4) {
            break;
        }
        else if (n == 0) {
            return 4;
        }
        else {
            printf("wrong input!\n");
        }
    }

    // ===============================
    // 선택: Explore it (n == 2)
    // ===============================
    if (n == 2) {
        int r = rand() % 100;

        if (r < 30) { // 성공 30%
            printf("==============================\n");
            printf("Success: You explore the shipwreck.\n");
            printf("Inside, you find far more supplies than expected and take everything you can.\n");
            printf("[Rope +4] [Wood +3] [Stone +1] [Food +3] [Water +4]\n");
            printf("==============================\n");

            item[4].count += 4;  // Rope
            item[5].count += 3;  // Wood
            item[3].count += 1;  // Stone
            item[1].count += 3;  // Food
            item[2].count += 4;  // Water
        }
        else {  // 실패 70%
            printf("==============================\n");
            printf("Failure: You enter the shipwreck.\n");
            printf("Unexpectedly, a jellyfish stings you.\n");
            printf("[HP -15]\n");
            printf("==============================\n");

            player->HP -= 15;
        }

        return 0;
    }

    // ===============================
    // 선택: Board it and escape (n == 3)
    // ===============================
    if (n == 3) {
        int r = rand() % 100;

        if (r < 5) {  // 성공 5%
            printf("==============================\n");
            printf("Success: The ship is more intact than expected.\n");
            printf("You attempt to sail away and miraculously find land.\n");
            printf("You send a rescue signal and are saved.\n");
            printf("You are now aboard a plane heading back home, reflecting on your survival.\n");
            printf(">>> Rare Escape Ending Achieved <<<\n");
            printf("==============================\n");

            return 9;   // Rare ending
        }
        else {          // 실패 95%
            printf("==============================\n");
            printf("Failure: You try to use the ship to escape.\n");
            printf("However, the ship collapses from the strain.\n");
            printf("You fall into the sea and meet your end.\n");
            printf("==============================\n");

            player->HP = 0;
            return 5;    // Death
        }
    }

    // ===============================
    // 선택: Ignore it (n == 4)
    // ===============================
    if (n == 4) {
        printf("==============================\n");
        printf("You decide it's not worth the trouble and simply walk past it.\n");
        printf("==============================\n");
        return 0;
    }

    return 0;
}



int somethingInSand(players *player) {

    // ===============================
    // Player Info
    // ===============================
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    // ===============================
    // Situation Description
    // ===============================
    printf("As you walk through the forest, you find a box buried in the soil.\n");
    printf("You brush off the dirt and lift it—it is heavier than you expected.\n");
    printf("What will you do?\n\n");

    int n;

    // ===============================
 
    // ===============================
    while (1) {
        printf("[1: Check resources] [2: Open it carefully] [3: Break it open] [4: Ignore it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();
            continue;
        }
        else if (n == 2 || n == 3 || n == 4) {
            break;
        }
        else if (n == 0) {
            return 4;  // Quit
        }
        else {
            printf("wrong input!\n");
        }
    }


    // ===============================
    if (n == 2) {

        int r = rand() % 100;

        if (r < 30) {  // 성공
            printf("==============================\n");
            printf("Success: You slowly opened the box.\n");
            printf("Inside, you found various supplies.\n");
            printf("[Wood +5] [Stone +5] [Rope +3]\n");
            printf("==============================\n");

            item[5].count += 5; // wood
            item[7].count += 5; // stone
            item[3].count += 3; // rope
        }
        else {  // 실패
            printf("==============================\n");
            printf("Failure: It was a trap! A sharp spike sprang out and injured you.\n");
            printf("[HP -15]\n");
            printf("==============================\n");

            player->HP -= 15;
        }

        return 0;
    }

    // ===============================
 
    // ===============================
    if (n == 3) {

        int r = rand() % 100;

        if (r < 30) {  
            printf("==============================\n");
            printf("Success: You broke the box open.\n");
            printf("Some materials were damaged.\n");
            printf("[Wood +2] [Stone +2] [Rope +1]\n");
            printf("==============================\n");

            item[5].count += 2; // wood
            item[7].count += 2; // stone
            item[3].count += 1; // rope
        }
        else {  // 실패
            printf("==============================\n");
            printf("Failure: The box was a trap! A hidden spike stabbed you.\n");
            printf("[HP -25]\n");
            printf("==============================\n");

            player->HP -= 25;
        }

        return 0;
    }

    // ===============================
    // [4] Ignore it
    // ===============================
    if (n == 4) {
        printf("==============================\n");
        printf("You decided to leave it alone and continue walking.\n");
        printf("==============================\n");
        return 0;
    }

    return 0;
}



int wildBoar(players *player) {

    // ===============================
    // Player Info
    // ===============================
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    // ===============================
    // Situation Description
    // ===============================
    printf("You suddenly hear heavy footsteps and rustling in the bushes.\n");
    printf("A wild boar charges toward you at high speed.\n");
    printf("What will you do?\n\n");

    int n;

    // ===============================
    // Main choice loop
    // ===============================
    while (1) {
        printf("[1: Check resources] [2: Run away] [3: Take cover] [4: Threaten it] [5: Attack it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) { checkR(); continue; }
        if (n == 2 || n == 3 || n == 4 || n == 5) break;
        if (n == 0) return 4;

        printf("wrong input!\n");
    }

    // ===============================
    // [2] Run away (성공 5% / 실패 95%)
    // ===============================
    if (n == 2) {

        int r = rand() % 100;

        if (r < 5) {   // 성공
            printf("==============================\n");
            printf("Success: You run as fast as you can and barely escape the boar.\n");
            printf("You pushed yourself too hard, and your legs feel numb.\n");
            printf("[HP -4]\n");
            printf("==============================\n");

            player->HP -= 4;
        }
        else {        // 실패
            printf("==============================\n");
            printf("Failure: Escaping a wild boar is nearly impossible.\n");
            printf("It catches up to you and attacks.\n");
            printf("[HP -25]\n");
            printf("==============================\n");

            player->HP -= 25;
        }

        return 0;
    }

    // ===============================
    // [3] Take cover → Sub-choice
    // ===============================
    if (n == 3) {

        int sub;

        printf("==============================\n");
        printf("You look around for cover.\n");
        printf("There is a tall tree and a large bush.\n");
        printf("Where will you hide?\n");
        printf("==============================\n");

        while (1) {
            printf("{2} Up the tree   {3} Inside the bush\n");

            if (scanf("%d", &sub) != 1) {
                while (getchar() != '\n');
                continue;
            }

            if (sub == 2 || sub == 3) break;

            printf("wrong input!\n");
        }

        // ---- Up the tree ----
        if (sub == 2) {
            printf("==============================\n");
            printf("You quickly climb up the tree.\n");
            printf("After waiting for a long time, the boar eventually gives up.\n");
            printf("==============================\n");
            return 0;
        }

        // ---- Inside the bush ----
        if (sub == 3) {
            printf("==============================\n");
            printf("You hide in the bush, but wild boars know bushes too well.\n");
            printf("You are quickly discovered and attacked.\n");
            printf("[HP -25]\n");
            printf("==============================\n");

            player->HP -= 25;
            return 0;
        }
    }

    // ===============================
    // [4] Threaten it → 즉사
    // ===============================
    if (n == 4) {
        printf("==============================\n");
        printf("You try to threaten the wild boar.\n");
        printf("This only enrages it further.\n");
        printf("You are killed instantly.\n");
        printf("(Death)\n");
        printf("==============================\n");

        player->HP = 0;
        return 0;
    }

    // ===============================
    // [5] Attack it (성공 10% / 실패 90%)
    // ===============================
    if (n == 5) {

        int r = rand() % 100;

        if (r < 10) {   // 성공
            printf("==============================\n");
            printf("Success: You grab a sharp branch and stab the boar.\n");
            printf("By sheer luck, it collapses.\n");
            printf("[Food +10] [Cloth +4]\n");
            printf("==============================\n");

            item[1].count += 10;  // Food
            item[6].count += 4;   // Cloth
        }
        else {          // 실패
            printf("==============================\n");
            printf("Failure: You attack with the branch, but it has no effect.\n");
            printf("The boar charges and hits you violently.\n");
            printf("[HP -35]\n");
            printf("==============================\n");

            player->HP -= 35;
        }

        return 0;
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
    // ===============================
    // Player Info
    // ===============================
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    // ===============================
    // Situation
    // ===============================
    printf("You were walking along a small stream in the forest when you discovered a small waterfall.\n");
    printf("The water looks clean, and collecting it from below might give you a large amount of drinking water.\n");
    printf("What will you do?\n\n");

    int n;

  
    while (1) {
        printf("[1: Check resources] [2: Go down] [3: Don't go down] [4: Ignore it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while(getchar()!='\n');
            continue;
        }

        if (n == 1) {
            checkR();
            continue;
        } 
        else if (n == 2 || n == 3 || n == 4) {
            break;
        }
        else if (n == 0) {
            return 4;
        }
        else {
            printf("wrong input!\n");
        }
    }


    if (n == 2) {
        int r = rand() % 100;

        if (r < 10) {   
            printf("==============================\n");
            printf("Success: You safely climb down beneath the waterfall.\n");
            printf("You collect a large amount of water.\n");
            printf("[Water +15]\n");
            printf("==============================\n");

            item[2].count += 15;
        }
        else {          
            printf("==============================\n");
            printf("Failure: You slipped while climbing down.\n");
            printf("Even small waterfalls can be dangerous.\n");
            printf("[HP -20]\n");
            printf("==============================\n");

            player->HP -= 20;
        }

        return 0;
    }


    if (n == 3) {
        int r = rand() % 100;

        if (r < 50) {   
            printf("==============================\n");
            printf("Success: You safely collect water from the stream above.\n");
            printf("[Water +2]\n");
            printf("==============================\n");

            item[2].count += 2;
        }
        else {          
            printf("==============================\n");
            printf("Failure: While collecting water above, you slipped and hurt yourself badly.\n");
            printf("[HP -12]\n");
            printf("==============================\n");

            player->HP -= 12;
        }

        return 0;
    }

    // ===========================================================
    // [4] Ignore it
    // ===========================================================
    if (n == 4) {
        printf("==============================\n");
        printf("You judge it too dangerous and simply walk past it.\n");
        printf("==============================\n");
        return 0;
    }

    return 0;
}






/* Rare: Cave with supplies and water */
int event_cave(players *player) {
    // ===============================
    // Player Info
    // ===============================
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    // ===============================
    // Situation Description
    // ===============================
    printf("While exploring deep inside the island, you push aside some vines\n");
    printf("and discover a hidden cave entrance behind them.\n");
    printf("What will you do?\n\n");

    int n;

    // ===============================
    // First Choice Loop
    // ===============================
    while (1) {
        printf("[1: Check resources] [2: Enter] [3: Ignore it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) { checkR(); continue; }
        if (n == 2 || n == 3) break;
        if (n == 0) return 4;

        printf("wrong input!\n");
    }

    // ===============================
    // [3] Ignore it
    // ===============================
    if (n == 3) {
        printf("==============================\n");
        printf("You judged it too dangerous and passed by the cave.\n");
        printf("==============================\n");
        return 0;
    }

    // ===============================
    // [2] Enter the cave
    // ===============================
    printf("==============================\n");
    printf("You decide to enter the cave. It's dark, but you find some supplies.\n");
    printf("[Wood +5] [Rope +2] [Water +2]\n");
    printf("==============================\n");

    item[5].count += 5;  // wood
    item[3].count += 2;  // rope
    item[2].count += 2;  // water

    // ===============================
    // Second choice (Go deeper / Retreat)
    // ===============================
    int sub;

    while (1) {
        printf("Will you go deeper?\n");
        printf("{2} Go deeper   {3} Retreat\n");

        if (scanf("%d", &sub) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (sub == 2 || sub == 3) break;

        printf("wrong input!\n");
    }

    // ===============================
    // [3] Retreat safely
    // ===============================
    if (sub == 3) {
        printf("==============================\n");
        printf("You decided to retreat safely from the cave.\n");
        printf("==============================\n");
        return 0;
    }

    // ===============================
    // [2] Go deeper (Success 20% / Failure 80%)
    // ===============================
    if (sub == 2) {

        int r = rand() % 100;

        if (r < 20) {  // Success
            printf("==============================\n");
            printf("Success: You went deeper, and it was worth it.\n");
            printf("You found several cans of food and exited safely.\n");
            printf("[Food +6]\n");
            printf("==============================\n");

            item[1].count += 6;  // food
        } 
        else {  // Failure
            printf("==============================\n");
            printf("Failure: You went too far into the cave.\n");
            printf("Breathing became difficult, and you barely escaped.\n");
            printf("[HP -20]\n");
            printf("==============================\n");

            player->HP -= 20;
        }
    }

    return 0;
}


int event_military_supplies(players *player) {

    // ===============================
    // Player Info
    // ===============================
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    // ===============================
    // Situation Description
    // ===============================
    printf("As you walk along the shoreline, you discover a box that appears to be old military supplies.\n");
    printf("If it really is a military supply crate, it might contain food—or even weapons.\n");
    printf("What will you do?\n\n");

    int n;

   
    while (1) {
        printf("[1: Check resources] [2: Open it] [3: Ignore it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();
            continue;
        }
        else if (n == 2 || n == 3) {
            break;
        }
        else if (n == 0) {
            return 4;   // Quit
        }
        else {
            printf("wrong input!\n");
        }
    }


    if (n == 2) {
        int r = rand() % 100;

        if (r < 10) {  
            printf("==============================\n");
            printf("Success: You opened the military supply crate.\n");
            printf("Inside, you found long-lasting food rations, clean water, and an old communication device.\n");
            printf("[Food +10] [Water +10] [Distress Signal Lv +1]\n");
            printf("==============================\n");

            item[1].count += 10;  // Food
            item[2].count += 10;  // Water

            SOS += 1;             // Distress Signal Level
            if (SOS > 4) SOS = 4;
        }
        else {  
            printf("==============================\n");
            printf("Failure: The box was not military supplies—it was a trap.\n");
            printf("A landmine hidden inside exploded, injuring you severely.\n");
            printf("[HP -35]\n");
            printf("==============================\n");

            player->HP -= 35;
        }

        return 0;
    }

    // ===============================
    // [3] Ignore it
    // ===============================
    if (n == 3) {
        printf("==============================\n");
        printf("It looked suspicious, so you decided to leave it alone and walk past it.\n");
        printf("==============================\n");
        return 0;
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
    event_cave,
    collapsedCabin,     // 6
    discoverLifeboat,   // 7
    shipwreck,          // 8
    somethingInSand,    // 9
    wildBoar,           // 10
    approachingStorm,   // 11
    event_military_supplies
};


int isRare[] = {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1};

/* usedEvent flags */
int usedEvent[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    






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