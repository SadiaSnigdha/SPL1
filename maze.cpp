#include <graphics.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 15
#define COLS 20
#define CELL_SIZE 30

// Maze elements
#define WALL 1
#define OBSTACLE 2
#define DOT 3
#define POWER_UP 4
#define EMPTY 0


int playerX = 1; // players row posiiton
int playerY = 1; // Player colm position
int ghostsX[3] = {3, 5, 7};   // Ghosts starting positions in row
int ghostsY[3] = {3, 5, 7}; // in clm
int ghostCount = 3;

int maze[ROWS][COLS];

void initializeMaze() {
    srand(time(0)); // Seed for randomness
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) {
                maze[i][j] = WALL; // boundary walls
            } else if (rand() % 5 == 0) {
                maze[i][j] = OBSTACLE; // Place obstacles
            } else if (rand() % 20 == 0) {
                maze[i][j] = POWER_UP; // Place power-ups randomly
            } else {
                maze[i][j] = DOT; // Place dots by default
            }
        }
    }

    // Clear initial positions for the player and ghosts
    maze[playerX][playerY] = EMPTY;
    for (int i = 0; i < ghostCount; ++i) {
        maze[ghostsX[i]][ghostsY[i]] = EMPTY;
    }
}

void drawMaze() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int x = j * CELL_SIZE;
            int y = i * CELL_SIZE;

            switch (maze[i][j]) {
                case WALL:
                    setfillstyle(SOLID_FILL, BLUE);
                    bar(x, y, x + CELL_SIZE, y + CELL_SIZE);
                    break;
                case OBSTACLE:
                    setfillstyle(SOLID_FILL, DARKGRAY);
                    bar(x, y, x + CELL_SIZE, y + CELL_SIZE);
                    break;
                case DOT:
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(x, y, x + CELL_SIZE, y + CELL_SIZE);
                    setcolor(WHITE);
                    fillellipse(x + CELL_SIZE / 2, y + CELL_SIZE / 2, 3, 3);
                    break;
                case POWER_UP:
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(x, y, x + CELL_SIZE, y + CELL_SIZE);
                    setcolor(YELLOW);
                    fillellipse(x + CELL_SIZE / 2, y + CELL_SIZE / 2, 8, 8);
                    break;
                case EMPTY:
                    setfillstyle(SOLID_FILL, BLACK);
                    bar(x, y, x + CELL_SIZE, y + CELL_SIZE);
                    break;
            }
        }
    }

    // Draw player
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(playerY * CELL_SIZE + CELL_SIZE / 2, playerX * CELL_SIZE + CELL_SIZE / 2, 10, 10);

    // Draw ghosts
    for (int i = 0; i < ghostCount; ++i) {
        setfillstyle(SOLID_FILL, RED);
        fillellipse(ghostsY[i] * CELL_SIZE + CELL_SIZE / 2, ghostsX[i] * CELL_SIZE + CELL_SIZE / 2, 10, 10);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    if (graphresult() != grOk) {
        printf("Graphics initialization failed.\n");
        return 1;
    }

    initializeMaze();

    while (1) {
        cleardevice(); // Clear the screen
        drawMaze();    // Draw the maze
        delay(100);    // Delay for smoother rendering

        // Exit condition (press Esc key)
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
    }

    closegraph();
    return 0;
}
