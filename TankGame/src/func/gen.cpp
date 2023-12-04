//
// Created by DeL33t on 30.11.2023.
//

#include "../headers/gen.h"

//Function generating world
int worldGen(int scene[HEIGHT][WIDTH], int seed, int map) {
    vector points = vector<pair<int, int>>();
    int i = 0;

    //Set seed if it isn't declared
    if(seed == 0 && map == 0) {
        seed = time(NULL);
    }
    srand(seed);

    //Fill scene matrix with 0 and 1 for bottom layer
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            scene[h][w] = 0;
            if(h >= HEIGHT - 3) {
                scene[h][w] = 1;
            }
        }
    }

    //Generate Points
    for(int w = 0; w < WIDTH; w+=WIDTH/17) {
        int con = rand();
        int pos = rand();
        int offset = pos % static_cast<int>(HEIGHT / 3);
        int height;
        if(con % 5 == 0 || con % 5 == 2) {
            height = HEIGHT / 2 + offset;
        }
        else if(con % 5 == 1 || con % 5 == 3) {
            height = HEIGHT / 2 - offset;
        }
        else {
            height = HEIGHT / 2;
        }
        scene[height][w] = 1;
        points.push_back({height, w});
        i++;
    }
    points.push_back({HEIGHT/2, 119});

    /*
    //List Generated Points
    for (const auto& point : points) {
        cout << "(" << point.first << ", " << point.second << ")\n";
    }*/

    //Connect the points to make terrain (variable part is only used for testing)
    i = 0;
    int height1, width1, height2, width2, hstart, wstart, hoffset, woffset, hend, wend, hh;
    for(const auto& point : points) {
        if(i != 0) {
            height2 = point.first;
            width2 = point.second;
            hstart = height1<height2?height1:height2;
            hh = height1>height2?HEIGHT-height1-1:HEIGHT-height2-1;
            hoffset = (static_cast<int>(height1>height2?height1:height2)-static_cast<int>(height1>height2?height2:height1)+1);
            wstart = width1;
            woffset = static_cast<int>(width2-width1+1);
            int part[hoffset][woffset];
            for(int h = 0; h < hoffset; h++) {
                for(int w = 0; w < woffset; w++) {
                    part[h][w] = scene[hstart+h][wstart+w];
                    int z = 0;
                    if(hoffset == 1) {
                        while(z <= hh) {
                            scene[hstart+z][wstart + w] = 1;
                            ++z;
                        }
                    }
                    else {
                        hend = hstart + hoffset - 1;
                        wend = wstart + woffset - 1;
                        if(hstart == point.first) {
                            scene[hstart][wend-1] = 1;
                            scene[hend][wstart+1] = 1;
                            if(hoffset == 2) {
                                while(z <= hh) {
                                    if (h == 0 && w >= woffset / 2) {
                                        scene[hstart+z][wstart + w] = 1;
                                    } else if (h == 1 && w < woffset / 2) {
                                        scene[hstart + h+z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 3 ) {
                                while(z <= hh) {
                                    if (((h == 1) && (w < 6 && w > 1))) {
                                        scene[hstart + h+z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 4) {
                                while(z <= hh) {
                                    if ((h == 1 && (w > 3 && w < 6)) || (h == 2 && (w > 1 && w < 4))) {
                                        scene[hstart + h+z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 5) {
                                while(z <= hh) {
                                    if ((h == 1 && w == 5) || (h == 2 && (w > 2 && w < 5)) || (h == 3 && w == 2)) {
                                        scene[hstart + h+z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 6) {
                                while(z <= hh) {
                                    if ((h == 1 && w == 5) || (h == 2 && w == 4) || (h == 3 && w == 3) ||
                                        (h == 4 && w == 2)) {
                                        scene[hstart + h+z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 7) {
                                while(z <= hh) {
                                    if ((h == 1 && w == 5) || (w == 4 && (h > 1 && h < 4)) || (h == 4 && w == 3) ||
                                        (h == 5 && w == 2)) {
                                        scene[hstart + h+z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                        }
                        else {
                            scene[hstart][wstart+1] = 1;
                            scene[hend][wend-1] = 1;
                            if(hoffset == 2) {
                                while(z <= hh) {
                                    if (h == 0 && w < woffset / 2) {
                                        scene[hstart+z][wstart + w] = 1;
                                    } else if (h == 1 && w >= woffset / 2) {
                                        scene[hstart + h+z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 3 ) {
                                while(z <= hh) {
                                    if (((h == 1) && (w < 6 && w > 1))) {
                                        scene[hstart + h + z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 4) {
                                while(z <= hh) {
                                    if ((h == 2 && (w > 3 && w < 6)) || (h == 1 && (w > 1 && w < 4))) {
                                        scene[hstart + h + z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 5) {
                                while(z <= hh) {
                                    if ((h == 3 && w == 5) || (h == 2 && (w > 2 && w < 5)) || (h == 1 && w == 2)) {
                                        scene[hstart + h+z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 6) {
                                while(z <= hh) {
                                    if ((h == 4 && w == 5) || (h == 3 && w == 4) || (h == 2 && w == 3) ||
                                        (h == 1 && w == 2)) {
                                        scene[hstart + h + z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                            if(hoffset == 7) {
                                while(z <= hh) {
                                    if ((h == 1 && w == 2) || (w == 3 && (h > 1 && h < 4)) || (h == 4 && w == 4) ||
                                        (h == 5 && w == 5)) {
                                        scene[hstart + h+z][wstart + w] = 1;
                                    }
                                    ++z;
                                }
                            }
                        }
                        part[h][w] = scene[hstart+h][wstart+w];
                    }
                }
            }
            /*
            //Show part of scene matrix
            for(int h = 0; h < hoffset; h++) {
                for(int w = 0; w < woffset; w++) {
                    cout << part[h][w];
                }
                cout << "\n";
            }
            cout << "\n";*/
        }
        height1 = point.first;
        width1 = point.second;
        i++;
    }

    //Fill the blank parts of terrain
    for (int h = 4; h < HEIGHT - 3; h++) {
        for (int w = 0; w < WIDTH; w++) {
            if (scene[h][w] == 0) {
                if (scene[h - 1][w] == 1 && scene[h][w - 1] == 1) {
                    scene[h][w] = 1;
                }
            }
        }
        for (int w = WIDTH; w > -1; w--) {
            if (scene[h][w] == 0) {
                if (scene[h - 1][w] == 1 && scene[h][w + 1] == 1) {
                    scene[h][w] = 1;
                }
            }
        }
    }
    return seed;
}

void SetBackgroundColor(int BackC)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    WORD wColor = ((BackC & 0x0F) << 4) + (csbi.wAttributes & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

//Scene showing function
void showScene(int scene[HEIGHT][WIDTH]) {
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            if(scene[h][w] == 1) {
                SetBackgroundColor(8);
                cout << "#";
            }
            else if(scene[h][w] == 2) {
                SetBackgroundColor(9);
                cout << "1";
            }
            else if(scene[h][w] == 3) {
                SetBackgroundColor(12);
                cout << "2";
            }
            else if(scene[h][w] == 4) {
                SetBackgroundColor(10);
                cout << "3";
            }
            else if(scene[h][w] == 5) {
                SetBackgroundColor(14);
                cout << "4";
            }
            else if(scene[h][w] == 6) {
                SetBackgroundColor(13);
                cout << "%";
            }
            else {
                cout << " ";
            }
            SetBackgroundColor(0);
            if(w == WIDTH-1) {
                cout << "\n";
            }
        }
    }
}

//Function for testing
void showSceneNum(int scene[HEIGHT][WIDTH]) {
    for(int h = 0; h < HEIGHT; h++) {
        for(int w = 0; w < WIDTH; w++) {
            cout << scene[h][w];
            if(w == WIDTH-1) {
                cout << "\n";
            }
        }
    }
}

