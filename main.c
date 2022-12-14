#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <SDL/SDL_mixer.h>
#include <ncurses.h>

#define FIELD_WIDTH  12
#define FIELD_HEIGHT 22
#define MINO_WIDTH    4
#define MINO_HEIGHT   4

int minoType  = 0;
int minoAngle = 0;
int minoX     = 0;
int minoY     = 0;

enum
{
    MINO_TYPE_I,
    MINO_TYPE_O,
    MINO_TYPE_S,
    MINO_TYPE_Z,
    MINO_TYPE_J,
    MINO_TYPE_L,
    MINO_TYPE_T,
    MINO_TYPE_MAX
};

enum
{
    MINO_ANGLE_0,
    MINO_ANGLE_90,
    MINO_ANGLE_180,
    MINO_ANGLE_270,
    MINO_ANGLE_MAX
};

char field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };
char displayBuffer[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

char minoShapes[MINO_TYPE_MAX][MINO_ANGLE_MAX][MINO_WIDTH][MINO_HEIGHT] =
{
    // MINO_TYPE_I
    {
        // MINO_ANGLE_0
        {
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0
        },
        // MINO_ANGLE_90
        {
            0, 0, 0, 0,
            0, 0, 0, 0,
            1, 1, 1, 1,
            0, 0, 0, 0
        },
        // MINO_ANGLE_180
        {
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 0, 1, 0
        },
        // MINO_ANGLE_270
        {
            0, 0, 0, 0,
            1, 1, 1, 1,
            0, 0, 0, 0,
            0, 0, 0, 0
        }
    },

    // MINO_TYPE_O
    {
        // MINO_ANGLE_0
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_90
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_180
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_270
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        }
    },

    // MINO_TYPE_S
    {
        // MINO_ANGLE_0
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            1, 1, 0, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_90
        {
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 1, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_180
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            1, 1, 0, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_270
        {
            0, 0, 0, 0,
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 1, 0
        }
    },

    // MINO_TYPE_Z
    {
        // MINO_ANGLE_0
        {
            0, 0, 0, 0,
            1, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_90
        {
            0, 0, 0, 0,
            0, 0, 1, 0,
            0, 1, 1, 0,
            0, 1, 0, 0
        },
        // MINO_ANGLE_180
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            0, 0, 1, 1,
            0, 0, 0, 0
        },
        // MINO_ANGLE_270
        {
            0, 0, 1, 0,
            0, 1, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0
        }
    },

    // MINO_TYPE_J
    {
        // MINO_ANGLE_0
        {
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_90
        {
            0, 0, 0, 0,
            1, 1, 1, 0,
            0, 0, 1, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_180
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            0, 1, 0, 0,
            0, 1, 0, 0
        },
        // MINO_ANGLE_270
        {
            0, 0, 0, 0,
            0, 1, 0, 0,
            0, 1, 1, 1,
            0, 0, 0, 0
        }
    },

    // MINO_TYPE_L
    {
        // MINO_ANGLE_0
        {
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_90
        {
            0, 0, 0, 0,
            0, 0, 1, 0,
            1, 1, 1, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_180
        {
            0, 0, 0, 0,
            0, 1, 1, 0,
            0, 0, 1, 0,
            0, 0, 1, 0
        },
        // MINO_ANGLE_270
        {
            0, 0, 0, 0,
            0, 1, 1, 1,
            0, 1, 0, 0,
            0, 0, 0, 0
        }
    },

    // MINO_TYPE_T
    {
        // MINO_ANGLE_0
        {
            0, 0, 0, 0,
            1, 1, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0
        },
        // MINO_ANGLE_90
        {
            0, 0, 0, 0,
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 1, 0, 0
        },
        // MINO_ANGLE_180
        {
            0, 0, 0, 0,
            0, 0, 1, 0,
            0, 1, 1, 1,
            0, 0, 0, 0
        },
        // MINO_ANGLE_270
        {
            0, 0, 1, 0,
            0, 1, 1, 0,
            0, 0, 1, 0,
            0, 0, 0, 0
        }
    }
};

void end_display(int *score) {
    clear();
    printf("\nGAME OVER!!!\n\n");
    printf("?????????: %d\n\n", *score);
}

void display() {
    // write displayBuffer
    memcpy(displayBuffer, field, sizeof(field));

    for (int i = 0; i < MINO_HEIGHT; i++) {
        for (int j = 0; j < MINO_WIDTH; j++) {
            displayBuffer[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
        }
    }

    // display block on console
    clear();

    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (1 == displayBuffer[i][j]) {
                printw("##");
            }
            else {
                printw("  ");
            }
        }
        printw("\n");
    }
}

bool isHit(int argMinoX, int argMinoY, int argMinoType, int argMinoAngle) {
    for (int i = 0; i < MINO_HEIGHT; i++) {
        for (int j = 0; j < MINO_WIDTH; j++) {
            if (minoShapes[argMinoType][argMinoAngle][i][j] && field[argMinoY + i][argMinoX + j]) {
                return true;
            }
        }
    }
    return false;
}

unsigned int xorshift128(unsigned int l) { 
    static unsigned int x = 123456789;
    static unsigned int y = 362436069;
    static unsigned int z = 521288629;
    static unsigned int w;
    unsigned int t;
    w = l;

    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

void resetMino() {
    minoX = 4;
    minoY = 0;
    minoType = xorshift128((unsigned int)time(NULL)) % MINO_TYPE_MAX;
    minoAngle = xorshift128((unsigned int)time(NULL)) % MINO_ANGLE_MAX;
}
 
int main(int argc, char *argv[]) {
    if (argc > 1) {
        printf("???????????????:\n");
        printf("A?????????D??????????????????\n");
        printf("S???????????????????????????\n");
        printf("W???????????????\n");
        printf("Space????????????????????????\n");
        printf("Q????????????????????????\n");
        return 1;
    }

    /* ????????????????????????????????? */
    initscr();
    noecho();
    cbreak();
    refresh();
    timeout(0);

    int key, tmp_;
    int tmp   = 0;
    int score = 0;
    int inver = 0;
    
    tmp_ = 0;

    // create wall and bottom
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        field[i][0] = 1;
        field[i][FIELD_WIDTH - 1] = 1;
    }

    for (int i = 0; i < FIELD_WIDTH; ++i) {
        field[FIELD_HEIGHT - 1][i] = 1;
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        printf("Error inesperado");
        return 0;
    }
    Mix_Init(0);

    Mix_Music *music;
    music = Mix_LoadMUS("audio.mp3");
    Mix_VolumeMusic(-1);
    Mix_PlayMusic(music, -1);

    resetMino();

    clock_t start_clock;
    clock_t last_clock = clock();

    while (1) {
        start_clock = clock();
        if (start_clock >= last_clock + 10000 - inver) {
            last_clock = start_clock;

            if (isHit(minoX, minoY + 1, minoType, minoAngle)) {
                for (int i = 0; i < MINO_HEIGHT; ++i) {
                    for (int j = 0; j < MINO_WIDTH; ++j) {
                        field[minoY + i][minoX + j] |= minoShapes[minoType][minoAngle][i][j];
                    }
                }

                // erase block
                for (int i = 0; i < FIELD_HEIGHT - 1; i++) {
                    bool isLineFilled = true;
                    for (int j = 1; j < FIELD_WIDTH - 1; j++) {
                        if (1 != field[i][j]) {
                            isLineFilled = false;
                        }
                    }

                    if (true == isLineFilled) {
                        for (int j = i; j > 0; --j) {
                            memcpy(field[j], field[j - 1], FIELD_WIDTH);
                        }
                    }
                    score += 10;
                }
                resetMino();
                if (isHit(minoX, minoY - 1, minoType, minoAngle)) {
                    break;
                }
            }
            else {
                ++minoY;
            }

            display();

            inver += 4;
        }

        switch (getch()) {
        case 's':
            if (!isHit(minoX, minoY + 1, minoType, minoAngle)) {
                ++minoY;
            }
            break;
        case 'a':
            if (!isHit(minoX - 1, minoY, minoType, minoAngle)) {
                --minoX;
            }
            break;
        case 'd':
            if (!isHit(minoX + 1, minoY, minoType, minoAngle)) {
                ++minoX;
            }
            break;
        case 'w':
            if (!isHit(minoX, minoY, minoType, (minoAngle + 1) % MINO_ANGLE_MAX)) {
                minoAngle = (minoAngle + 1) % MINO_ANGLE_MAX;
            }
            break;
        case 0x20:
            for (;;) {
                if (!isHit(minoX, minoY + 1, minoType, minoAngle)) {
                    ++minoY;
                }
                else if (isHit(minoX, minoY + 1, minoType, minoAngle)) {
                    break;
                }
            }
            break;
        case 'q':
            tmp_ = 1;
        }
        if (tmp_ == 1) break;
        display();

        /* 60fps */
        usleep(60000);
    }

    Mix_HaltMusic();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    endwin();
    end_display(&score);

    return 0;
}
