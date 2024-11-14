// genshin 1.0 standard wish simulator
// @rookiyama - nov 13 2024
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define THREE_BASE_CHANCE 9430 // three star base chance (94.3 multiplied by 100)
#define FOUR_BASE_CHANCE 510 // four star base chance (5.1 multiplied by 100)
#define FIVE_BASE_CHANCE 60 // five star base chance (6.0 multiplied by 100)

char threeStarItems[15][90] = {
        "Fillet Blade", "Skyrider Sword", "Harbinger of Dawn",
        "Debate Club", "Bloodtainted Greatsword", "Ferrous Shadow",
        "Halberd", "White Tassel", "Black Tassel",
        "Thrilling Tales of Dragon Slayers", "Twin Nephrite", "Magic Guide",
        "Slingshot", "Raven Bow", "Sharpshooter's Oath"
};
char fourStarCharacters[12][90] = {
        "Amber", "Kaeya", "Lisa", "Barbara", "Razor", "Beidou",
        "Ningguang", "Xiangling", "Fischl", "Sucrose", "Noelle", "Xingqiu"
};
char fiveStarCharacters[6][90] = {
        "Diluc", "Jean", "Keqing", "Mona", "Qiqi", "Venti"
};

int fivePityArray[20] = {222,405,604,825,1070,1339,1637,1967,2331,2734,3178,3670,4213,4814,5478,6211,7021,7917,8907,10000};
int threeStarChance = 9430; // base rate 94.3
int fourStarChance = 510; // base rate 5.1
int fiveStarChance = 60; // base rate 0.6
int total = 10000; // always total up to 10000 as a whole
int totalPulls = 0;
int fourPity = 0;
int fivePity = 0;

void calcPity() {
    if (fivePity >= 70) {
        int index = fivePity - 70;
        int diff = fivePityArray[index] - 20;
        fiveStarChance = fivePityArray[index];
        int newRate = THREE_BASE_CHANCE - diff;
        if (newRate >= 0) {
            threeStarChance = newRate;
        } else {
            int newDiff = 0 - newRate;
            fourStarChance = FOUR_BASE_CHANCE - newDiff;
        }
    }
}

void getItem(int rarity) {
    int random;
    switch (rarity) {
        case 1:
            printf("\033[0;36m");
            int threeStarTotal = sizeof(threeStarItems) / sizeof(threeStarItems[0]);
            random = rand() % (threeStarTotal);
            printf("3* - %s\n", threeStarItems[random]);
            printf("\033[0m");
            break;
        case 2:
            printf("\033[0;35m");
            int fourStarTotal = sizeof(fourStarCharacters) / sizeof(fourStarCharacters[0]);
            random = rand() % (fourStarTotal);
            printf("4* - %s\n", fourStarCharacters[random]);
            fourPity = 0;
            printf("\033[0m");
            break;
        case 3:
            printf("\033[0;33m");
            int fiveStarTotal = sizeof(fiveStarCharacters) / sizeof(fiveStarCharacters[0]);
            random = rand() % (fiveStarTotal);
            printf("5* - %s\n", fiveStarCharacters[random]);
            fivePity = 0;
            threeStarChance = THREE_BASE_CHANCE;
            fourStarChance = FOUR_BASE_CHANCE;
            fiveStarChance = FIVE_BASE_CHANCE;
            printf("\033[0m");
        break;
    }
    totalPulls++;
    calcPity();
}

void pull(int total) {
    ++fourPity;
    ++fivePity;
    if (fourPity == 10 || fourPity > 10) {
        getItem(2);
    } else {
        int random = rand() % (total + 1);
        if (random <= fiveStarChance) {
            getItem(3);
        } else if (random > fiveStarChance && random <= fourStarChance) {
            getItem(2);
        } else {
            getItem(1);
        }
    }
}

void displayStats() {
    printf("Total Pulls: %d\n", totalPulls);
    printf("Four Star Pity: %d\n", fourPity);
    printf("Five Star Pity: %d\n", fivePity);
}

void tenPull() {
    for (int i = 0; i < 10; i++) {
        pull(total);
    }
    displayStats();
}

void singlePull() {
    pull(total);
    displayStats();
}

int main() {
    srand(time(NULL));
    int running = 1;
    int c = 0;
    printf("[1] for Single Pull\n[2] for Ten Pull\n[3] Exit\n");
    while (running) {
        printf("Input: ");
        scanf("%d", &c);
        switch (c) {
            case 1:
                singlePull();
                c = 0;
                break;
            case 2:
                tenPull();
                c = 0;
                break;
            case 3:
                exit(1);
            default:
                break;
        }
    }
    return 0;
}
