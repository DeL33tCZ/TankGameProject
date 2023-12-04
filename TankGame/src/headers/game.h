//
// Created by DeL33t on 30.11.2023.
//

#include "gen.h"
#include <stdlib.h>

#pragma once

#ifndef TANKGAME_GAME_H
#define TANKGAME_GAME_H

struct player {
    int pos[2];
    bool state;
};

void gameMenu();

void startGame(int scene[HEIGHT][WIDTH], int seed = 0, int map = 0, int players = 2);

#endif //TANKGAME_GAME_H
