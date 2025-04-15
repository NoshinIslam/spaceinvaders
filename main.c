#include <stdio.h>
#include <windows.h>
#include <conio.h> // For getch()

#define MAX_ALIENS 4
#define SCREEN_WIDTH 30
#define SCREEN_HEIGHT 20



int spaceshipRow = 18, spaceshipCol = 15; // spaceship position
int bulletRow = -1, bulletCol = -1; //bullet position
int aliens[MAX_ALIENS][2];
int score = 0;
int alienMoveCounter = 0; // Counter to control alien movement speed


void displaySpaceship() {
    printf("\033[%d;%dH", spaceshipRow, spaceshipCol);
    printf("A");
}
void clearScreen() {
    system("cls");
}

void moveSpaceship(char key) {
    switch (key) {
        case 'A': case 'a': // moves left
            if (spaceshipCol > 1) spaceshipCol--;
            break;
        case 'D': case 'd': // moves right
            if (spaceshipCol < SCREEN_WIDTH) spaceshipCol++;
            break;
        case 'W': case 'w': // moves up
            if (spaceshipRow > 1) spaceshipRow--;
            break;
        case 'S': case 's': // moves down
            if (spaceshipRow < SCREEN_HEIGHT) spaceshipRow++;
            break;
    }
}


void shootBullet() {
    if (bulletRow == -1) { // only one bullet can exist at a time
        bulletRow = spaceshipRow - 1;
        bulletCol = spaceshipCol;
    }
}

void updateBullet() {
    if (bulletRow != -1) {
        bulletRow--; // moves the bullet upward
        if (bulletRow < 1) { // if the bullet goes off the screen
            bulletRow = -1;
            bulletCol = -1;
        }
    }
}



void spawnAliens() {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i][0] == -1) { // if an alien is not active
            aliens[i][0] = 1;                // spawn at the top row
            aliens[i][1] = 1 + rand() % 30;  // random columnn
        }
    }
}

void moveAliens() {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i][0] != -1) { // if an alien is active
            aliens[i][0]++; // moves downward
            if (aliens[i][0] > SCREEN_HEIGHT) { // if the alien goes off the screen
                aliens[i][0] = -1; // deactivates the alien
                aliens[i][1] = -1;
            }
        }
    }

    // Randomly spawn new aliens
    if (rand() % 10 < 3) { // 30% chance to spawn a new alien
        spawnAliens();
    }
}
void displayAliens() {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i][0] != -1) { // if an alien is active
            printf("\033[%d;%dHV\n", aliens[i][0], aliens[i][1]);
        }
    }
}
void checkCollisions() {
    for (int i = 0; i < MAX_ALIENS; i++) {
        // checks if bullet and alien occupy the same position
        if (aliens[i][0] != -1 && bulletRow == aliens[i][0] && bulletCol == aliens[i][1]) {
            // collision detected
            aliens[i][0] = -1; // deactivates the alien
            aliens[i][1] = -1;
            bulletRow = -1;    // removes the bullet
            bulletCol = -1;
            score++;           // increments the score
        }
    }
}


int isGameOver() {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i][0] == spaceshipRow && aliens[i][1] == spaceshipCol) {
            return 1; // Game over
        }
    }
    return 0;
}

int main() {
    char key;


    for (int i = 0; i < MAX_ALIENS; i++) {
        aliens[i][0] = -1; // -1 means alien is not active
        aliens[i][1] = -1;
    }

    // Game loop
    while (1) {
        clearScreen();

        displaySpaceship();
        displayAliens();
        if (bulletRow != -1) { // if a bullet exists
            printf("\033[%d;%dH|\n", bulletRow, bulletCol);
        }

        printf("\033[%d;%dHScore: %d\n", SCREEN_HEIGHT + 1, 1, score);

        if (isGameOver()) {
            printf("\033[%d;%dHGame Over! Final Score: %d\n", SCREEN_HEIGHT + 2, 1, score);
            break;
        }


        if (_kbhit()) { // Check if a key is pressed
            key = _getch();
            if (key == 'A' || key == 'a' || key == 'D' || key == 'd' ||
                key == 'W' || key == 'w' || key == 'S' || key == 's') {
                moveSpaceship(key);
            } else if (key == '\r') {
                shootBullet();
            }
        }

        updateBullet();

        // slower alien movement: update only every 5 game iterations
        alienMoveCounter++;
        if (alienMoveCounter >= 5) {
            moveAliens();
            alienMoveCounter = 0;
        }

        checkCollisions();

        // delays for smooth gameplay
        Sleep(100);
    }

    return 0;
}

