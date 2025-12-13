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
int birdSpotted(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
    printf("You are exploring the beach to find food under bright sunshine.\n");
    printf("The weather is extremely hot and a bit unpleasant, but you don’t mind\n");
    printf("as long as you can secure food. At that moment, you hear the cry of a bird.\n");
    printf("Very hungry, you instinctively look up and spot a seagull. What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Throw a stone] [3: Make a trap] [0: Quit]\n");
        if (scanf("%d", &n) != 1) { while (getchar()!='\n'); continue; }
        if (n == 1) { checkR(); continue; }
        else if (n == 0) return 4;
        else break;
    }

    if (n == 2) {
        int r = rand() % 20;
        if (r < 1) {
            printf("==============================\n");
            printf("You pick the most suitable stone you can find nearby and throw it at the seagull.\n");
            printf("By sheer luck, the stone hits the seagull directly, and it crashes onto the beach.\n");
            printf("[Food +4]\n");
            printf("==============================\n");
            item[1].count += 4;
        } else {
            printf("==============================\n");
            printf("You pick the most suitable stone you can find nearby and throw it at the seagull.\n");
            printf("However, the chances of hitting it were far too low. Feeling disappointed,\n");
            printf("you move on to look for other food sources.\n");
            printf("==============================\n");
        }
    }
    else if (n == 3) {
        if (item[3].count >= 1 && item[5].count >= 1){
            printf("==============================\n");
            printf("You create a trap to lure the seagull and wait for it to be caught. After some time,\n");
            printf("the seagull falls for the trap without any suspicion\n");
            printf("Will you kill the seagull immediately to secure food?\n");
            
            int an;
            while (1) {
                printf("[1: Check resources] [2: Kill it] [3: Do not kill it] [0: Quit]\n");
                if (scanf("%d", &an) != 1) { while (getchar()!='\n'); continue; }
                if (an == 1) { checkR(); continue; }
                else if (an == 0) return 4;
                else break;
            }

            if (an == 2){
                printf("==============================\n");
                printf("In your haste to obtain food, you kill the seagull and successfully secure it as food.\n");
                printf("[Food +4]\n");
                printf("==============================\n");
                item[1].count += 4;
            }
            else if (an == 3){
                printf("==============================\n");
                printf("You decide not to kill the seagull right away, just in case. After a short while,\n");
                printf("the seagull lays eggs. You feel relieved that you didn’t kill it,\n");
                printf("and you decide to continue collecting eggs from it for the time being.\n");
                printf("[Food +8]\n");
                printf("==============================\n");
                item[1].count += 8;
            }
        }
        else{
            printf("==============================\n");
            printf("You try to create a trap to lure the seagull, but you didn’t realize\n");
            printf("you were lacking the necessary materials. The seagull simply flies past,\n");
            printf("and you continue searching for food in disappointment.\n");
            printf("==============================\n");
        }
    }

    return 0;
}

int clamsSpotted(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
    printf("You are walking along the coastline when you find several live clams on the sand.\n");
    printf("How will you collect them?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Break them with a stone] [3: Soak them in seawater] [4: Cook them first] [0: Quit]\n");
        if (scanf("%d", &n) != 1) { while (getchar()!='\n'); continue; }
        if (n == 1) { checkR(); continue; }
        else if (n == 0) return 4;
        else break;
    }

    if (n == 2) {
        printf("==============================\n");
        printf("You tried to use a small stone to break the clams to get food,\n");
        printf("but in the process of breaking them, much of the meat was crushed and damaged.\n");
        printf("[Food +1]\n");
        printf("==============================\n");
        item[1].count += 1;
    }
    else if (n == 3) {
        printf("==============================\n");
        printf("You soaked several clams in seawater. Some of them escaped,\n");
        printf("but a few opened up and can be used as food.\n");
        printf("[Food +3]\n");
        printf("==============================\n");
        item[1].count += 3;
    }
    else if (n == 4){
        printf("==============================\n");
        printf("Knowing that clams naturally open when cooked, you heated them over a fire.\n");
        printf("As a result, several clams opened, and you successfully obtained food.\n");
        printf("[Food +5]\n");
        printf("==============================\n");
        item[1].count += 5;
    }
    return 0;
}

/* 1) Tree hole (eggs / bird peck) */
int insideTheLog(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
    printf("You are walking through the forest when you discover a hole inside a log.\n");
    printf("Something is glimmering within it, but you can’t see clearly inside. What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Put your hand in] [3: Ignore it] [0: Quit]\n");
        if (scanf("%d", &n) != 1) { while (getchar()!='\n'); continue; }
        if (n == 1) { checkR(); continue; }
        else if (n == 0) return 4;
        else break;
    }

    if (n == 2) {
        int r = rand() % 2;
        if (r == 0) {
            printf("==============================\n");
            printf("You carefully reached your hand into the log. When you moved a little,\n");
            printf("you heard a rustling sound that startled you, but after feeling around,\n");
            printf("it seemed to be a bird’s nest. As you explored further, you felt some eggs.\n");
            printf("Feeling a bit sorry for the bird, you decided to take the eggs.\n");
            printf("[Food +4]\n");
            printf("==============================\n");
            item[1].count += 4;
        } else {
            printf("==============================\n");
            printf("You carefully reached your hand into the log. When you moved a little,\n");
            printf("you heard a rustling sound that startled you, but after feeling around,\n");
            printf("it seemed to be a bird’s nest. Suddenly, the bird pecked your hand with its beak\n");
            printf("Startled, you quickly pulled your hand out and fell over.\n");
            printf("[HP -8]\n");
            printf("==============================\n");
            player->HP -= 8;
        }
    }
    else if (n == 3) {
        printf("==============================\n");
        printf("Not knowing what might be inside the log, you decided to ignore it and walk past.\n");
        printf("==============================\n");
    }

    return 0;
}


int rockShade(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("You are walking through the forest in search of food when you begin to feel very tired.\n");
    printf("Just then, you notice a cool, shaded spot beneath a large rock ahead.\n");
    printf("It looks like a good place to rest for a moment. What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Rest] [3: Ignore it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) { while (getchar() != '\n'); continue; }

        if (n == 1) { checkR(); continue; }
        else if (n == 0) return 4;
        else break;
    }

    if (n == 2) {
        int k = rand() % 5;
        if (k < 4){
            printf("==============================\n");
            printf("You lie down in the shade of the rock and enjoy the cool breeze as you take a comfortable rest.\n");
            printf("[HP +8]\n");
            printf("==============================\n");
            player->HP += 8;
        }
        else{
            printf("==============================\n");
            printf("You lie down in the shade and feel the cool breeze. Suddenly,\n");
            printf("a large rock rolls toward you from behind. It strikes your back hard, and you become injured.\n");
            printf("[HP -8]\n");
            printf("==============================\n");
            player->HP -= 8;
        }
    }
    else {
        printf("==============================\n");
        printf("You decide it’s not worth the trouble and simply walk past it.\n");
        printf("You decide it’s not worth the trouble and simply walk past it.\n");
        printf("==============================\n");
    }
    return 0;
}


int thunderstorm(players *player) { 
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
   
    printf("You are exploring a deserted island to gather food as usual\n");
    printf("when suddenly a thunderstorm hits. You are startled by the sudden situation,\n");
    printf("but quick decisions are necessary to survive. How do you respond?\n");
    
    int n;
    while(1) {
        printf("[1: Check resources] [2: Find a place to hide] [3: Ignore it] [0: Quit]\n");
        
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //findAPlaceToHide
        printf("==============================\n");
        printf("You quickly start looking for a place to take cover. At that moment,\n");
        printf("you discover a cave. Where will you hide?\n");
        printf("==============================\n");
        
        int al;
        while (1){
            printf("[1: Check resources] [2: Under a tree] [3: In the cave] [0: Quit]\n");
        
            scanf("%d", &al);
            if(al==1) checkR();
            else if(al==2) break;
            else if(al==3) break;
            else if(al==0) return 4;
            else printf("wrong input!\n");
        }
        
        if (al==2){
            int k = rand() % 100;
            if (k < 35) {
                printf("==============================\n");
                printf("You hurriedly hide under a nearby tree. A few minutes later, the sky clears,\n");
                printf("and you feel relieved and continue searching for food.\n");
                printf("==============================\n");
            }
            else {
                printf("==============================\n");
                printf("You hurriedly hide under a nearby tree. While waiting for the storm to pass,\n");
                printf("unfortunately, you are struck by lightning.\n");
                printf("[HP -25]");
                printf("==============================\n");
                player->HP -= 25;
            }
        }
        else if (al==3){
                printf("==============================\n");
                printf("You hurriedly hide at the entrance of the cave you just found. Inside,\n");
                printf("there are signs that someone stored water here. A few minutes later, the sky clears,\n");
                printf("and you feel relieved and continue searching for food.\n");
                printf("[Water +4]");
                printf("==============================\n");
                item[2].count += 4;
        }

    } 
    else if(n==3) { //ignoreIt
        int a = rand() % 2;
        if(a == 0) { //success
            printf("==============================\n");
            printf("Believing that lightning will not strike you, you continue searching for food.\n");
            printf("At that moment, you notice fruit falling from a tree and gather it.\n");
            printf("However, you start shivering from getting soaked in the rain.\n");
            printf("[Food +4] [HP -4]\n");
            printf("==============================\n");
            item[1].count += 4;
            player->HP -= 4;
        }
        else { //failure
            printf("==============================\n");
            printf("Believing that lightning will not strike you, you continue searching for food.");
            printf("But it was too risky. While you are careless, lightning strikes you.\n");
            printf("[HP -25]\n");
            printf("==============================\n");
            player->HP -= 25;
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
int seaweedClump(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("You are walking along the coastline when you discover a large bundle of seaweed\n");
    printf("near the water. If dried, it can be used as rope, and it can also serve as food. What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Dry it] [3: Eat it] [4: Ignore it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) {
            checkR();        
        }
        else if (n == 2 || n == 3 || n == 4 || n == 0) {
            break;  
        }
        else {
            printf("wrong input!\n");
        }
    }

    if (n == 0) return 4;

    if (n == 2) {
        printf("==============================\n");
        printf("You decide to dry the seaweed and use it as rope.\n");
        printf("[Rope +3]\n");
        printf("==============================\n");
        item[3].count += 3; 
    }
    else if (n == 3) {
        int k = rand() % 5;
        if (k < 3){
            printf("==============================\n");
            printf("You decide to take the seaweed as food. While drying it,\n");
            printf("you also manage to gather some drinking water.\n");
            printf("[Food +4] [Water +3]\n");
            printf("==============================\n");
            item[1].count += 4;
            item[2].count += 3;
        }
        else{
            printf("==============================\n");
            printf("You decide to take the seaweed as food. As you unravel it,\n");
            printf("a jellyfish suddenly emerges from the seaweed and stings you\n");
            printf("before drifting away. Fortunately, it wasn’t poisonous.\n");
            printf("[HP -6]\n");
            printf("==============================\n");
            player->HP -= 6;
        }
    }
    else if (n == 4){
        printf("==============================\n");
        printf("You decide to ignore it, unsure of what might be hiding inside.\n");
        printf("==============================\n");
    }
    return 0;
}

int fallenTree(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
    
    printf("You are exploring the forest when you come across a tall fallen tree.\n");
    printf("It could be dangerous, but it’s also an opportunity\n");
    printf("to gather resources to expand your shelter. What will you do?\n");
    
    int n;
    while(1) {
        printf("[1: Check resources] [2: Harvest it] [3: Ignore it] [0: Quit]\n");
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==3) break;
        else if(n==0) return 4;
        else printf("wrong input!\n");
    }

    if(n==2) { //harvestIt
        int k = rand() % 10;
        if (k < 7){
            printf("==============================\n");
            printf("You harvest the fallen tree and obtain plenty of lumber.\n");
            printf("[Wood +7]\n");
            printf("==============================\n");
            item[5].count += 7;
        }
        else {
            printf("==============================\n");
            printf("While harvesting the fallen tree, you’re unlucky and get bitten by a squirrel.\n");
            printf("[HP -4]\n");
            printf("==============================\n");
            player->HP -= 4;  
        }
    } else if(n==3) { //ignoreIt
        printf("==============================\n");
        printf("You decide to pass by, just in case something unexpected happens.\n");
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
int thePool(players *player) { 
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
    
    printf("You were walking through the forest when you discovered a huge puddle on the ground.\n");
    printf("If the water was drinkable, you wouldn’t have to worry about water for a while.\n");
    printf("What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Drink it immediately] [3: Boil it] [0: Quit]\n");
        scanf("%d", &n);
        if (n == 1) checkR();
        else if (n == 2) break;
        else if (n == 3) break;
        else if (n == 0) return 4;
        else printf("wrong input!\n");
    }

    if (n == 2) { //Drink it as is
        printf("==============================\n");
        printf("You decided to drink the water as it was. After a short while,\n");
        printf("you began to feel your stomach hurting more and more.\n");
        printf("[HP -5]\n");
        printf("==============================\n");
        player->HP -= 5;
    } 
    if (n == 3) { //Boil it
        printf("==============================\n");
        printf("You lit a fire and safely boiled the water. Some of it evaporated while boiling,\n");
        printf("but you secured safe drinking water, so it’s enough.\n");
        printf("[Water +3]\n");
        printf("==============================\n");
        item[2].count += 3;
    }

    return 0;
}

int palmLeaves(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");
    
    printf("While exploring the forest, you find a pile of fallen palm leaves on the ground.\n");
    printf("The leaves are mostly undamaged, but there could be unknown creatures hiding within them.\n");
    printf("However, taking the leaves with you would be very useful for reinforcing your shelter.\n");
    printf("What will you do?\n");
   
    int n;
    while (1) {
    printf("[1: Check resources] [2: Take them] [3: Ignore them] [0: Quit]\n");
        scanf("%d", &n);
        if (n == 1) checkR();
        else if (n == 2) break;
        else if (n == 3) break;
        else if (n == 0) return 4;
        else printf("wrong input!\n");
    }

    if (n == 2) { //take them
        int k = rand() % 10;
        if (k < 7){
            printf("==============================\n");
            printf("You gathered many palm leaves to reinforce your shelter. Fortunately,\n");
            printf("there were no harmful creatures inside.\n");
            printf("[Leaves +8]\n");
            printf("==============================\n");
            item[4].count += 8;
        }
        else {
            printf("==============================\n");
            printf("You gathered many palm leaves to reinforce your shelter. However,\n");
            printf("a snake hidden among the leaves suddenly bit you. Luckily, as far as you know,\n");
            printf("the snake was not venomous.\n");
            printf("[HP -3]\n");
            printf("==============================\n");
            player->HP -= 3;
        }

    } 
    if (n == 3) { //ignore
        printf("==============================\n");
        printf("You decided to leave the leaves behind,\njust in case something might be hiding inside.\n");
        printf("==============================\n");
    }

    return 0;
}


/* 5) Pond fish */
int fishSpotted(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("You are walking along the coast when you spot a few fish swimming\n");
    printf("in the shallow water. They look edible to you. What will you do?\n");


    int n;
    while (1) {
        printf("[1: Check resources] [2: Catch them] [3: Ignore them] [0: Quit]\n");

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
        int k = rand() % 2;
        if (k == 0){
            printf("==============================\n");
            printf("You quickly use a nearby stick to spear one of the fish. You successfully catch it.\n");
            printf("[Food +3]\n");
            printf("==============================\n");
            item[1].count += 3;   
        }
        else{
            printf("==============================\n");
            printf("You thrust the nearby stick toward the fish, but it darts away.\n");
            printf("Unluckily, you step on a seashell on the seabed.\n");
            printf("[HP -8]\n");
            printf("==============================\n");
            player->HP -= 8;  
        }
    }
    else { 
        printf("==============================\n");
        printf("You decide to conserve your strength and take a moment to rest\n");
        printf("while gazing at the horizon beyond the sea.\n");
        printf("[HP +6]\n");
        printf("==============================\n");
        player->HP += 6;
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

/* 7) WeirdPlantEvent*/
int suspiciousWeeds(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("While exploring the deep forest of a deserted island, you come\n");
    printf("across a fruit hanging from a strangely shaped plant.\n");
    printf("However, you don’t know whether the fruit is poisonous.\n");
    printf("What would you do?\n"); 


    int n;
    while (1) {
        printf("[1: Check resources] [2: Eat it] [3: Ignore it] [0: Quit]\n");

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
        int k = rand() % 2;
        if (k == 0){
            printf("==============================\n");
            printf("Believing the fruit might have beneficial effects, you eat it.\n");
            printf("A few minutes later, you feel much more energetic than before.\n");
            printf("[HP +14]\n");
            printf("==============================\n");
            player->HP += 14;   
        }
        else{
            printf("==============================\n");
            printf("Believing the fruit might have beneficial effects, you eat it.\n");
            printf("A few minutes later, you start feeling a headache coming on.\n");
            printf("[HP -6]\n");
            printf("==============================\n");
            player->HP -= 6;  
        }
    }
    else { 
        printf("==============================\n");
        printf("To avoid potential danger, you decide not to eat the fruit.\n");
        printf("==============================\n");
    }
    return 0;
}

/* 8) TwigEvent*/
int event_twig(players *player) {
    int choice;
    printf("You find a pile of dry twigs.\n");
    printf("1) Collect them  2) Walk past\n> ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("You collected the twigs.\n");
        player->wood += 1;
        return 1;
    } else {
        printf("You decided to walk past.\n");
        return 2;
    }
}

/* 9) ClothEvent*/
int event_cloth(players *player) {
    int choice;
    printf("You were walking along the beach when you found a piece of cloth. Its condition looked good, and it seemed usable. What will you do?\n");
    printf("1) Pick it up  2) Walk past\n> ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("You successfully picked up the piece of cloth without any problems.\n");
        player->cloth += 4;
        return 1;
    } else {
        printf("You decided it wasn’t necessary and simply walked past it.\n");
        return 2;
    }
}

/* 10) FishingNetEvent*/
int event_fishingNet(players *player) {
    int choice;
    printf("You find a torn fishing net.\n");
    printf("1) Take it  2) Walk past\n> ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("You recovered the rope.\n");
        player->rope += 1;
        return 1;
    } else {
        printf("You decide to walk past.\n");
        return 2;
    }
}

/* 11) StoneEvent*/
int event_stone(players *player) {
    int choice;
    printf("You were walking along the coast when you discovered a cracked rock. If you strike it a little, it might break into a useful shape that could be used in many ways. What will you do?\n");
    printf("1) Pick them up  2) Walk past\n> ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("You decided to break the rock. You struck the cracked fragment against the larger rock, and it broke successfully, giving you several usable stones.\n");
        player->stone += 5;
        return 1;
    } else {
        printf("You felt it might be dangerous, so you decided to just pass by.\n");
        return 2;
    }
}

/* 12) RockRopeEvent*/
int event_rockRope(players *player) {
    int choice;
    printf("You find old rope stuck between rocks.\n");
    printf("1) Try to pull it out  2) Ignore it\n> ");
    scanf("%d", &choice);

    if (choice == 1) {
        int success = rand() % 2;

        if (success == 0) {
            printf("Your hand was cut by a sharp rock!\n");
            player->health -= 10;
            return 0;
        } else {
            printf("You successfully retrieved the rope.\n");
            player->rope += 1;
            return 1;
        }

    } else {
        printf("You walk away from the danger.\n");
        return 2;
    }
}

/* 13) Animal Carcass Event */
int event_animal_carcass(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("You find a dead animal on the ground. It could be edible, or it may be rotten.\n");
    printf("What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Inspect and eat it (risky)] [3: Leave it] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) checkR();
        else if (n == 2 || n == 3 || n == 0) break;
        else printf("wrong input!\n");
    }

    if (n == 0) return 4;

    if (n == 2) {  
        int r = rand() % 2;

        if (r == 0) {
            printf("==============================\n");
            printf("Failure: The meat was rotten. You feel sick.\n");
            printf("[HP -10]\n");
            printf("==============================\n");
            player->HP -= 10;
        } else {
            printf("==============================\n");
            printf("Success: The meat was still good.\n");
            printf("[Hunger -15]\n");
            printf("==============================\n");
            player->Hunger -= 15;
            if (player->Hunger < 0) player->Hunger = 0;
        }
    } 
    else if (n == 3) {
        printf("==============================\n");
        printf("You decide to leave the carcass and avoid the risk.\n");
        printf("==============================\n");
    }

    return 0;
}

     /* 14) Tornado Event */
int event_tornado(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("A tornado is forming in the distance. It is heading toward your area.\n");
    printf("What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Take shelter] [3: Run away] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) checkR();
        else if (n == 2 || n == 3 || n == 0) break;
        else printf("wrong input!\n");
    }

    if (n == 0) return 4;

    if (n == 2) {   
        int r = rand() % 2;

        if (r == 0) {
            printf("==============================\n");
            printf("Failure: The shelter partially collapses.\n");
            printf("[HP -20]\n");
            printf("==============================\n");
            player->HP -= 20;
        } else {
            printf("==============================\n");
            printf("Success: You safely waited out the tornado.\n");
            printf("[No damage]\n");
            printf("==============================\n");
        }
    }
    else if (n == 3) { 
        printf("==============================\n");
        printf("You run as fast as possible and barely escape the tornado.\n");
        printf("[Fatigue +10]\n");
        printf("==============================\n");
        player->Fatigue += 10;
    }

    return 0;
}

/* 15) Earthquake Event */
int event_earthquake(players *player) {
    printf("==============================\n");
    printf("Day %d\n", player->Day);
    printf("[HP: %d] [Hunger: %d] [Thirst: %d]\n",
           player->HP, player->Hunger, player->Thirst);
    printf("==============================\n\n");

    printf("The ground begins to shake violently. An earthquake is happening.\n");
    printf("What will you do?\n");

    int n;
    while (1) {
        printf("[1: Check resources] [2: Hide under stable rocks] [3: Run to open area] [0: Quit]\n");

        if (scanf("%d", &n) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (n == 1) checkR();
        else if (n == 2 || n == 3 || n == 0) break;
        else printf("wrong input!\n");
    }

    if (n == 0) return 4;

    if (n == 2) {  
        int r = rand() % 2;

        if (r == 0) {
            printf("==============================\n");
            printf("Failure: Falling debris hits you.\n");
            printf("[HP -15]\n");
            printf("==============================\n");
            player->HP -= 15;
        } else {
            printf("==============================\n");
            printf("Success: You find a stable spot and protect yourself.\n");
            printf("==============================\n");
        }
    }
    else if (n == 3) { 
        printf("==============================\n");
        printf("You run to an open area and avoid collapsing structures.\n");
        printf("[Fatigue +5]\n");
        printf("==============================\n");
        player->Fatigue += 5;
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
    insideTheLog,     //normal event
    rockShade,
    seaweedClump,
    event_herbs,
    fishSpotted,
    event_palm_leaves,         
    thunderstorm,     // 0  
    fallenFruit,        // 1
    fallenTree,            // 2
    thePool,    // 3
    palmLeaves,         // 4
    fishingFish,        // 5
    event_wave_collect,    // [Special Events]
    event_waterfall,
    event_cave,
    collapsedCabin,     // 6
    discoverLifeboat,   // 7
    shipwreck,          // 8
    somethingInSand,    // 9
    wildBoar,           // 10
    approachingStorm,    // 11
    suspiciousWeeds,
    event_twig,
    event_cloth,
    event_fishingNet,
    event_stone,
    event_rockRope,
    event_animal_carcass,
    event_tornado,
    event_earthquake


};


int isRare[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1};

/* usedEvent flags */
int usedEvent[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    






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


