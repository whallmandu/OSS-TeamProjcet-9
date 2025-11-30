#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include "event.h"

//Shelter, Sos signal, Raft
extern int Shelter;
extern int SOS;
extern int Raft;

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


// image print
void drawImage(int x, int y, const char* filename) {
    // Console Handle
    HWND consoleWindow = GetConsoleWindow();
    if (!consoleWindow) return; 

    // Setting
    HDC hdc = GetDC(consoleWindow);
    HDC memDC = CreateCompatibleDC(hdc);

    // Image load
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    if (hBitmap == NULL) {
        printf("IMAGE ERROR!\n");
        return;
    }

    

    SelectObject(memDC, hBitmap);

    // Image size
    BITMAP bm;
    GetObject(hBitmap, sizeof(bm), &bm);

    // print
    BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);

    // clear
    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(consoleWindow, hdc);
}

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
    printf("[HP: %d] [Hunger: %d] [Thirst: %d] \n", player->HP, player->Hunger, player->Thirst); //player data
    printf("==============================\n\n");
    
    printf("First day.\n"); //text data(story)
    drawImage(450, 0, "test.bmp");
    int n;
    while(1) {
        printf("[1: Check resources] [2: Go seashore] [0: Quit]\n"); //selections
        
        //data input
        scanf("%d", &n);
        if(n==1) checkR();
        else if(n==2) break;
        else if(n==0) return 4; //this is 'Quit' return data. only 4.
        else printf("wrong input!\n");
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





/*
============================================
SPECIAL EVENT
============================================
*/
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

//namal and special event arr
int (*eventList[])(players *) = {
    // [Normal Events]
    suddenDownpour,     // 0
    fallenFruit,        // 1
    bigTree,            // 2
    findGroundWater,    // 3
    falmLeaves,         // 4
    fishingFish,        // 5
    
    // [Special Events]
    collapsedCabin,     // 6
    discoverLifeboat,   // 7
    shipwreck,          // 8
    somethingInSand,    // 9
    wildBoar,           // 10
    approachingStorm    // 11
};

//special arr
int isRare[] = {
    0, 0, 0, 0, 0, 0,   // Normal Events (0~5)
    1, 1, 1, 1, 1, 1    // Special Events (6~11)
};

//visit O/X arr
int usedEvent[] = {
    0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
};

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