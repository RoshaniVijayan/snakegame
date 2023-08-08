#include <stdio.h>
#include <conio.h>
#include <windows.h>

int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;

int tailX[100], tailY[100];
int countTail = 0;

void setup() {
    gameover = 0;

    // Initial position of the snake
    x = height / 2;
    y = width / 2;

    // Initial position of the fruit
    fruitx = rand() % height;
    if (fruitx == 0)
        fruitx = fruitx + 10;
    fruity = rand() % width;
    if (fruity == 0)
        fruity = fruity + 10;

    score = 0;
}

void draw() {
    system("cls");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == width - 1 || j == 0 || j == height - 1) {
                printf("#");
            } else {
                if (i == x && j == y)
                    printf("0");
                else if (i == fruitx && j == fruity)
                    printf("*");
                else {
                    int isPrinted = 0;
                    for (int k = 0; k < countTail; k++) {
                        if (i == tailX[k] && j == tailY[k]) {
                            printf("o");
                            isPrinted = 1;
                        }
                    }
                    if (isPrinted == 0)
                        printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score = %d", score);
    printf("\n");
    printf("Press X to quit the game");
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            flag = 1;
            break;
        case 's':
            flag = 2;
            break;
        case 'd':
            flag = 3;
            break;
        case 'w':
            flag = 4;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < countTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }

    if (x < 0 || x > height || y < 0 || y > width)
        gameover = 1;

    for (int i = 0; i < countTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;
    }

    if (x == fruitx && y == fruity) {
        score += 10;
        countTail++;
        fruitx = rand() % height;
        if (fruitx == 0)
            fruitx = fruitx + 10;
        fruity = rand() % width;
        if (fruity == 0)
            fruity = fruity + 10;
    }
}

int main() {
    int m, n;

    // Generate random seed
    srand(time(0));

    // Initialize console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    setup();

    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(10); // Sleep for 10 milliseconds
    }

    return 0;
}
