//
// Created by DeL33t on 18.11.2023.
//

#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

#pragma once

#ifndef TANKGAME_GEN_H
#define TANKGAME_GEN_H

#define HEIGHT 12
#define WIDTH 119

//Function generating world
int worldGen(int scene[HEIGHT][WIDTH], int seed = 0, int map = 0);

//Scene showing function
void showScene(int scene[HEIGHT][WIDTH]);

//Function for testing
void showSceneNum(int scene[HEIGHT][WIDTH]);

#endif //TANKGAME_GEN_H