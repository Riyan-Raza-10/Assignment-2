#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(0));

    int x = 1;                 // Player position (0,1,2)
    int step = 0;              // Obstacle vertical movement
    int obstaclePos = rand() % 3;
    int delayTime = 100;       // Starting speed
    int speedIncrement = 2;    // Speed up by reducing delay
    int shield = 1;            // Player starts with a shield
    int score = 0;             // Scoreboard

    printf("==== DODGE THE OBSTACLE ====\n");
    printf("Avoid the falling obstacles (O) with your player (^)\n");
    printf("Use LEFT and RIGHT arrow keys to move.\n");
    printf("Shield protects you from ONE collision.\n");
    printf("Score increases every time you dodge an obstacle.\n");
    printf("Press any key to start...\n\n");
    getch();

    printf("==== GAME STARTS ====\n\n");
    Sleep(800);

    while (1) {

        // ---- INPUT ----
        if (_kbhit()) {
            char ch = getch();

            if (ch == 75 && x > 0)        // LEFT arrow
                x--;

            if (ch == 77 && x < 2)        // RIGHT arrow
                x++;
        }

        // ---- DRAW ----
        system("cls");
        printf("|--- --- ---|\n");

        for (int i = 0; i < 10; i++) {
            
            if (i == step) {
                if (obstaclePos == 0)
                    printf("| O         |\n");
                else if (obstaclePos == 1)
                    printf("|     O     |\n");
                else
                    printf("|        O  |\n");
            } 
            else {
                printf("|           |\n");
            }
        }

        // ---- PLAYER ----
        if (x == 0)
            printf("| ^         |\n");
        else if (x == 1)
            printf("|     ^     |\n");
        else
            printf("|        ^  |\n");

        // ---- UI ----
        printf("\nScore: %d  |  Shield: %s\n", score, shield ? "ACTIVE" : "NONE");

        // ---- COLLISION ----
        if (step == 10 && x == obstaclePos) {

            if (shield) {
                shield = 0;
                printf("\nShield absorbed the hit! Press any key...");
                getch();
            } 
            else {
                system("cls");
                printf("\n========== GAME OVER! ==========\n");
                printf("Final Score: %d\n", score);
                printf("================================\n\n");
                break;
            }

            // Reset obstacle
            step = 0;
            obstaclePos = rand() % 3;
        }

        Sleep(delayTime);

        // ---- MOVE OBSTACLE ----
        step++;

        // ---- OBSTACLE REACHES BOTTOM ----
        if (step > 10) {
            step = 0;

            // Increase score for successful dodge
            score += 5;

            obstaclePos = rand() % 3;

            if (delayTime > 40)
                delayTime -= speedIncrement;

            // Random chance to recharge shield
            if (!shield && rand() % 12 == 0)
                shield = 1;
        }
    }

    return 0;
}

