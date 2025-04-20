#include <stdio.h>
#include <windows.h>
#include <conio.h> 

#define MAX_ALIENS 4
#define SCREEN_WIDTH 30
#define SCREEN_HEIGHT 20



int spaceshipRow = 18, spaceshipCol = 15; 
int bulletRow = -1, bulletCol = -1; 
int aliens[MAX_ALIENS][2];
int score = 0;
int alienMoveCounter = 0; 


void displaySpaceship() {
    printf("\033[%d;%dH", spaceshipRow, spaceshipCol);
    printf("A");
}
void clearScreen() {
    system("cls");
}

void moveSpaceship(char key) {
    switch (key) {
        case 'A': case 'a': 
            if (spaceshipCol > 1) spaceshipCol--;
            break;
        case 'D': case 'd': 
            if (spaceshipCol < SCREEN_WIDTH) spaceshipCol++;
            break;
        case 'W': case 'w': 
            if (spaceshipRow > 1) spaceshipRow--;
            break;
        case 'S': case 's': 
            if (spaceshipRow < SCREEN_HEIGHT) spaceshipRow++;
            break;
    }
}


void shootBullet() {
    if (bulletRow == -1) { 
        bulletRow = spaceshipRow - 1;
        bulletCol = spaceshipCol;
    }
}

void updateBullet() {
    if (bulletRow != -1) {
        bulletRow--; 
        if (bulletRow < 1) { 
            bulletRow = -1;
            bulletCol = -1;
        }
    }
}

void displayAliens() {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i][0] != -1) { 
            printf("\033[%d;%dHV\n", aliens[i][0], aliens[i][1]);
        }
    }
}

void spawnAliens() {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i][0] == -1) { 
            aliens[i][0] = 1;                
            aliens[i][1] = 1 + rand() % 30;  
        }
    }
}

void moveAliens() {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i][0] != -1) { 
            aliens[i][0]++; 
            if (aliens[i][0] > SCREEN_HEIGHT) { 
                aliens[i][0] = -1; 
                aliens[i][1] = -1;
            }
        }
    }


    if (rand() % 10 < 3) { 
        spawnAliens();
    }
}

void checkCollisions() {
    for (int i = 0; i < MAX_ALIENS; i++) {
  
        if (aliens[i][0] != -1 && bulletRow == aliens[i][0] && bulletCol == aliens[i][1]) {
           
            aliens[i][0] = -1; 
            aliens[i][1] = -1;
            bulletRow = -1;    
            bulletCol = -1;
            score++;           
        }
    }
}


int isGameOver() {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i][0] == spaceshipRow && aliens[i][1] == spaceshipCol) {
            return 1; 
        }
    }
    return 0;
}

int main() {
    char key;


    for (int i = 0; i < MAX_ALIENS; i++) {
        aliens[i][0] = -1; 
        aliens[i][1] = -1;
    }

    // Game loop
    while (1) {
        clearScreen();

        displaySpaceship();
        displayAliens();
        if (bulletRow != -1) { 
            printf("\033[%d;%dH|\n", bulletRow, bulletCol);
        }

        printf("\033[%d;%dHScore: %d\n", SCREEN_HEIGHT + 1, 1, score);

        if (isGameOver()) {
            printf("\033[%d;%dHGame Over! Final Score: %d\n", SCREEN_HEIGHT + 2, 1, score);
            break;
        }


        if (_kbhit()) { 
            key = _getch();
            if (key == 'A' || key == 'a' || key == 'D' || key == 'd' ||
                key == 'W' || key == 'w' || key == 'S' || key == 's') {
                moveSpaceship(key);
            } else if (key == '\r') {
                shootBullet();
            }
        }

        updateBullet();

      
        alienMoveCounter++;
        if (alienMoveCounter >= 5) {
            moveAliens();
            alienMoveCounter = 0;
        }

        checkCollisions();

     
        Sleep(100);
    }

    return 0;
}

