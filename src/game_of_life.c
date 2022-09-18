// Copyright 2022 maplesar, animusal, milagros
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define WIDTH 80
#define HEIGHT 25
#define ANSI_COLOR_BG_YELLOW     "\x1b[103m"
#define ANSI_COLOR_FG_YELLOW     "\x1b[93m"
#define ANSI_COLOR_RESET         "\x1b[0m"

void fieldDrawing(int matrix[][WIDTH]);
void callMenu(int speed);
void figureInit(int matrix[][WIDTH]);
void life(int matrix[][WIDTH], int changes[][WIDTH]);
int countNeighbours(int matrix[][WIDTH], int i, int j);
void equal(int matrix[][WIDTH], int changes[][WIDTH]);
void fill_zeros(int matrix[][WIDTH]);
void checkState(int* i, int* j);
int isInt(const char number[]);
int getSpeed(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    callMenu(getSpeed(argc, argv));
    return 0;
}

void callMenu(int speed) {
    if (speed != 0) {
        int matrix[HEIGHT][WIDTH] = { 0 };
        int changes[HEIGHT][WIDTH] = { 0 };
        figureInit(matrix);
        while (1) {
            fieldDrawing(matrix);
            usleep(1000000 / speed);
            life(matrix, changes);
            fill_zeros(matrix);
            equal(matrix, changes);
            fill_zeros(changes);
        }
    } else {
        printf("n/a");
    }
}

int getSpeed(int argc, char* argv[]) {
    int speed = 1;
    if (argc == 2) {
        int check_integer = isInt(argv[1]);
        speed = check_integer == 1 ? atoi(argv[1]) : 0;
    } else {
        speed = 0;
    }
    return speed;
}

int isInt(const char number[]) {
    int res = 1;
    if (number[0] == '-')
        res = 0;
    for (int i = 0; number[i] != 0; i++) {
        if (number[i] > '9' || number[i] < '0')
            res = 0;
    }
    return res;
}

void equal(int matrix[][WIDTH], int changes[][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = changes[i][j];
        }
    }
}

void fill_zeros(int matrix[][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = 0;
        }
    }
}

void figureInit(int matrix[][WIDTH]) {
    int i, j;
    int tmp_i = 0, tmp_j = 0;
    while (1) {
        scanf("%d%d", &i, &j);
        if (tmp_i == i && tmp_j == j)
            break;
        matrix[i][j] = 1;
        tmp_i = i, tmp_j = j;
    }
}

void life(int matrix[][WIDTH], int changes[][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int neighbours = countNeighbours(matrix, i, j);
            if (matrix[i][j] == 0) {
                if (neighbours == 3) {
                    changes[i][j] = 1;  // birth
                }
            } else if (matrix[i][j] == 1) {
                if (neighbours == 2 || neighbours == 3) {
                    changes[i][j] = 1;  // stay alive
                }
            }
        }
    }
}

int countNeighbours(int matrix[][WIDTH], int i, int j) {
    int neighbours = 0;
    int tmp_k, tmp_m;
    for (int k = i - 1; k <= i + 1; k++) {
        for (int m = j - 1; m <= j + 1; m++) {
            tmp_k = k;
            tmp_m = m;
            checkState(&k, &m);
            if (matrix[k][m] == 1 && !(k == i && m == j)) {
                neighbours++;
            }
            k = tmp_k;
            m = tmp_m;
        }
    }
    return neighbours;
}

void checkState(int* i, int* j) {
    if (*i == -1)  {
        *i = HEIGHT - 1;
    } else if (*i == HEIGHT) {
        *i = 0;
    }
    if (*j == -1)  {
        *j = WIDTH - 1;
    } else if (*j == WIDTH) {
        *j = 0;
    }
}

void fieldDrawing(int matrix[][WIDTH]) {
    char space = ' ', hor_field = '-', vert_field = '|', sign = '*';
    system("clear");
    for (int i = -1; i <= HEIGHT; i++) {
        printf(ANSI_COLOR_BG_YELLOW ANSI_COLOR_FG_YELLOW "%c"
                                ANSI_COLOR_RESET, vert_field);
        for (int j = -1; j <= WIDTH; j++) {
            if (i == -1 || i == HEIGHT) {
                printf(ANSI_COLOR_BG_YELLOW ANSI_COLOR_FG_YELLOW "%c"
                                        ANSI_COLOR_RESET, hor_field);
            } else if (matrix[i][j] == 1) {
                printf(ANSI_COLOR_BG_YELLOW ANSI_COLOR_FG_YELLOW "%c"
                                            ANSI_COLOR_RESET, sign);
            } else {
                printf("%c", space);
            }
        }
        printf(ANSI_COLOR_BG_YELLOW ANSI_COLOR_FG_YELLOW "%c"
                                ANSI_COLOR_RESET, vert_field);
        printf("\n");
    }
}
