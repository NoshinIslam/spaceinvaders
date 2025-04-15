
#include <stdio.h>
#define SCREEN_WIDTH 30
#define SCREEN_HEIGHT 20

int spaceshipRow = 18, spaceshipCol = 15; // spaceship position
int bulletRow = -1, bulletCol = -1; //bullet position

void displaySpaceship() {
    printf("\033[%d;%dH", spaceshipRow, spaceshipCol);
    printf("A");
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
    if (bulletRow == -1) { // Only one bullet can exist at a time
        bulletRow = spaceshipRow - 1;
        bulletCol = spaceshipCol;
    }
}
