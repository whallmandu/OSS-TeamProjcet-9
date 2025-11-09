#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 3   // 인벤토리 최대 크기

// 플레이어 상태 구조체
typedef struct {
    int health;                 // 체력
    int hunger;                 // 허기 (0이면 죽음)
    int knowledge;              // 지식 포인트
    int day;                    // 날짜
    char inventory[MAX_ITEMS][20]; // 아이템 인벤토리 (문자열 저장)
    int itemCount;              // 현재 아이템 수
} Player;

// 함수 선언
void intro();
void day1(Player* p);
void day2(Player* p);
void quiz_network(Player* p);
void randomEvent(Player* p);
void addItem(Player* p, const char* item);
void showStatus(Player* p);

int main() {
    srand(time(NULL)); // 난수 초기화

    Player p = { 100, 100, 0, 1, {""}, 0 }; // 초기값 설정

    intro();
    day1(&p);
    day2(&p);

    printf("\n=== 게임 종료 ===\n");
    showStatus(&p);
    return 0;
}

// --------------------------------------------
// 소개 화면
// --------------------------------------------
void intro() {
    printf("=== 생존 선택 게임 ===\n");
    printf("무인도에 떨어졌습니다. 체력과 허기를 유지하며 생존하세요!\n\n");
}

// --------------------------------------------
// 인벤토리에 아이템 추가
// --------------------------------------------
void addItem(Player* p, const char* item) {
    if (p->itemCount < MAX_ITEMS) {
        strcpy(p->inventory[p->itemCount], item);
        p->itemCount++;
        printf("📦 아이템 '%s'을(를) 획득했습니다!\n", item);
    }
    else {
        printf("❌ 가방이 꽉 찼습니다! 아이템을 더 담을 수 없습니다.\n");
    }
}

// --------------------------------------------
// 플레이어 상태 출력
// --------------------------------------------
void showStatus(Player* p) {
    printf("\n=== 현재 상태 ===\n");
    printf("날짜: %d일차\n", p->day);
    printf("체력: %d\n", p->health);
    printf("허기: %d\n", p->hunger);
    printf("지식 포인트: %d\n", p->knowledge);
    printf("보유 아이템:\n");

    if (p->itemCount == 0)
        printf(" (없음)\n");
    else {
        for (int i = 0; i < p->itemCount; i++)
            printf(" - %s\n", p->inventory[i]);
    }
    printf("--------------------------\n");
}

// --------------------------------------------
// 랜덤 이벤트
// --------------------------------------------
void randomEvent(Player* p) {
    int event = rand() % 100;

    if (event < 20) { // 20% 확률: 음식 발견
        printf("[랜덤 이벤트] 해변에서 바나나를 발견했습니다! 허기 +20\n");
        addItem(p, "바나나");
        p->hunger += 20;
        if (p->hunger > 100) p->hunger = 100;
    }
    else if (event < 35) { // 15% 확률: 부상
        printf("[랜덤 이벤트] 갑자기 바위에서 떨어졌습니다! 체력 -15\n");
        p->health -= 15;
    }
    else if (event < 45) { // 10% 확률: 기술 노트 발견
        printf("[랜덤 이벤트] 기술 노트를 발견했습니다! 지식 +10\n");
        addItem(p, "기술노트");
        p->knowledge += 10;
    }
    else if (event < 60) { // 15% 확률: 비가 내려 허기 감소
        printf("[랜덤 이벤트] 비가 와서 사냥을 못했습니다... 허기 -10\n");
        p->hunger -= 10;
    }
    else {
        printf("[랜덤 이벤트 없음] 오늘은 평온한 하루입니다.\n");
    }

    // 허기와 체력 체크
    if (p->hunger <= 0) {
        printf("⚠️ 허기로 쓰러졌습니다!\n");
        p->health -= 20;
        p->hunger = 10;
    }
    if (p->health <= 0) {
        printf("💀 체력이 0이 되어 사망했습니다...\n");
        exit(0);
    }
}

// --------------------------------------------
// Day 1
// --------------------------------------------
void day1(Player* p) {
    int choice;
    printf("\n=== [Day %d] 무전기 고장 ===\n", p->day);
    printf("무전기가 고장났습니다. 어떻게 할까요?\n");
    printf("1. 회로를 수리한다.\n");
    printf("2. 프로그램 오류를 수정한다.\n");
    printf("선택: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("회로를 수리했습니다. 체력 -10, 허기 -5\n");
        p->health -= 10;
        p->hunger -= 5;
    }
    else if (choice == 2) {
        printf("펌웨어 재설정에 성공했습니다!\n");
        quiz_network(p);
        p->hunger -= 5;
    }
    else {
        printf("잘못된 선택입니다. 아무 일도 일어나지 않았습니다.\n");
    }

    randomEvent(p);
    showStatus(p);
    p->day++;
}

// --------------------------------------------
// Day 2
// --------------------------------------------
void day2(Player* p) {
    int choice;
    printf("\n=== [Day %d] 낯선 동굴 ===\n", p->day);
    printf("비를 피하려고 동굴에 들어왔습니다. 안쪽에서 소리가 납니다.\n");
    printf("1. 안으로 들어가본다.\n");
    printf("2. 밖으로 나간다.\n");
    printf("선택: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("노트북을 발견했습니다!\n");
        quiz_network(p);
        addItem(p, "노트북");
        p->knowledge += 5;
        p->hunger -= 10;
    }
    else if (choice == 2) {
        printf("밖으로 나왔습니다. 체력 -5, 허기 -5\n");
        p->health -= 5;
        p->hunger -= 5;
    }

    randomEvent(p);
    showStatus(p);
    p->day++;
}

// --------------------------------------------
// 지식 퀘스트 (네트워크 문제)
// --------------------------------------------
void quiz_network(Player* p) {
    int ans;
    printf("\n[지식 퀘스트] OSI 7계층에서 물리 계층의 역할은?\n");
    printf("1. 전송 매체를 통한 비트 전송\n");
    printf("2. 암호화 및 세션 관리\n");
    printf("정답: ");
    scanf("%d", &ans);

    if (ans == 1) {
        printf("정답입니다! 지식 포인트 +10\n");
        p->knowledge += 10;
    }
    else {
        printf("틀렸습니다. 지식 포인트 +0\n");
    }
}