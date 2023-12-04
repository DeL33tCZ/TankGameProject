//
// Created by DeL33t on 30.11.2023.
//

#include "../headers/game.h"
#include "gen.cpp"
#include <cmath>

void gameMenu() {
    cout << "\t\t \t           _____ _     _____   _ _____   _     ___  _________ \n"
            "\t\t\t          |_   _| |   |  __ \\ (_)  __ \\ | |    |  \\/  || ___ \\ \n"
            "                                    | | | |   | |  \\/  _| /  \\/ | |    | .  . || |_/ /\n"
            "    @============/-----\\      !     | | | |   | | __  | | |     | |    | |\\/| ||  __/  !      /-----\\============@\n"
            "           _____/_______\\_____|     | | | |___| |_\\ \\ | | \\__/\\ | |____| |  | || |     |_____/_______\\_____\n"
            "          /____________________\\    \\_/ \\_____/\\____/ |_|\\____/ \\_____/\\_|  |_/\\_|    /____________________\\\n"
            "          \\+__+__+__+__+__+__*/                   ______    ______                     \\+__+__+__+__+__+__*/\n"
            "####################################             |______|  |______|               ####################################" << endl;
    char  cmd;
    int seed = 0, playersn = 2;
    do
    {
        cout << "======================================================================================================================" << endl;
        printf("P: PLAY     ");
        printf("S: SET SEED     ");
        printf("N: SET PLAYERS     ");
        printf("C: CREDITS     ");
        printf("Q: QUIT TO DESKTOP\n");

        cmd = tolower(getchar());

        switch (cmd)
        {
            case 'p':
                int scene[HEIGHT][WIDTH];
                system("cls");
                startGame(scene, seed, 0, playersn);
                break;
            case 's':
                printf("Enter seed number: ");
                scanf_s("%d", &seed);
                printf("Seed: %d\n", seed);
                break;
            case 'n':
                printf("Enter number of players (Default is 2, Maximum is 4): ");
                scanf_s("%d", &playersn);
                if((playersn < 2) || (playersn > 4)) {
                    printf("Invalid number of players, setting the default.\n");
                    playersn = 2;
                }
                printf("Number of players: %d\n", playersn);
                break;
            case 'c':
                printf("This game was made as college project for ours programming class.\nAuthors:\n  Daniel Linduska\n  Martin Panacek\n\n\nAlso if you're looking for easter egg, here you can have one. Take care of it.\n\n  __\n /  \\\n|    |\n \\__/\n\n");
                break;
            case 'q':
                printf("Thank you so much for playing ours project game. We are looking forward to seeing you playing ours game again soon. :)");
                getchar();
                break;
            default:
                printf("Not a valid option was choosed.\n");
                break;
        }
        getchar();
    } while (cmd != 'q');
}


void startGame(int scene[HEIGHT][WIDTH], int seed, int map, int playersn) {
    getchar();
    int gseed = worldGen(scene, seed, map);
    int playeri = 2;
    player players[playersn];
    for(int w = WIDTH/(playersn*2); w < WIDTH; w+=WIDTH/playersn) {
        for(int h = 0; h < HEIGHT; h++) {
            if(scene[h+1][w] == 1) {
                scene[h][w] = playeri;
                players[playeri-2].pos[0] = HEIGHT-h;
                players[playeri-2].pos[1] = w;
                players[playeri-2].state = true;
                playeri++;
                break;
            }
        }
    }
    bool game = true, round = true;
    int alive = playersn;
    int winner;
    while(game) {
        for(int p = 0; p < playersn; p++) {
            round = true;
            int fuel = 5;
            if(alive == 1) {
                game = false;
            }
            if(players[p].state) {
                char cmd;
                do {
                    system("cls");
                    showScene(scene);
                    cout << "=======================================================================================================================" << endl;
                    printf("A: MOVE LEFT     ");
                    printf("D: MOVE RIGHT     ");
                    printf("S: SHOOT     ");
                    printf("Q: QUIT      | ");
                    printf("Player%d is playing | ", p+1);
                    printf("Fuel: %d\n", fuel);
                    cmd = tolower(getchar());
                    int height, width;
                    switch (cmd) {
                        case 'a':
                            if(fuel == 0) {
                                printf("Insufficient fuel!\n[ENTER]\n");
                                getchar();
                            }
                            else if (fuel > 0) {
                                height = players[p].pos[0];
                                width = players[p].pos[1];
                                for(int h = 0; h < HEIGHT; h++) {
                                    if(scene[h+1][width-1] == 1) {
                                        if(h < HEIGHT-(height+1)) {
                                            if(scene[HEIGHT-height][width-1] == 0) {
                                                scene[HEIGHT-height][width] = 0;
                                                scene[HEIGHT-height][width - 1] = p + 2;
                                                players[p].pos[1] = width - 1;
                                                break;
                                            }
                                            else {
                                                printf("The surface is too steep!");
                                                fuel++;
                                                getchar();
                                                break;
                                            }
                                        }
                                        else {
                                            scene[HEIGHT-height][width] = 0;
                                            scene[h][width - 1] = p + 2;
                                            players[p].pos[0] = HEIGHT - h;
                                            players[p].pos[1] = width - 1;
                                            break;
                                        }
                                    }
                                }
                                fuel--;
                            }
                            break;
                        case 'd':
                            if(fuel == 0) {
                                printf("Insufficient fuel!\n[ENTER]\n");
                                getchar();
                            }
                            else if (fuel > 0) {
                                height = players[p].pos[0];
                                width = players[p].pos[1];
                                for(int h = 0; h < HEIGHT; h++) {
                                    if(scene[h+1][width+1] == 1) {
                                        if(h < HEIGHT-(height+1)) {
                                            if(scene[HEIGHT-height][width+1] == 0) {
                                                scene[HEIGHT-height][width] = 0;
                                                scene[HEIGHT-height][width + 1] = p + 2;
                                                players[p].pos[1] = width + 1;
                                                break;
                                            }
                                            else {
                                                printf("The surface is too steep!");
                                                fuel++;
                                                getchar();
                                                break;
                                            }
                                        }
                                        else {
                                            scene[HEIGHT-height][width] = 0;
                                            scene[h][width + 1] = p + 2;
                                            players[p].pos[0] = HEIGHT - h;
                                            players[p].pos[1] = width + 1;
                                            break;
                                        }
                                    }
                                }
                                fuel--;
                            }
                            break;
                        case 's':
                            char direct;
                            int angle, power;
                            printf("Enter the direction you want to shoot (a - left, d - right), angle (-90-90) and power (1-100).\n");
                            getchar();
                            printf(" Direction:");
                            direct = tolower(getchar());
                            printf(" Angle:");
                            scanf_s("%d", &angle);
                            printf(" Power:");
                            scanf_s("%d", &power);
                            if(((direct == 'a' || direct == 'd') && (angle >= -90 && angle <= 90)) && (power >= 1 && power <= 100)) {
                                for(float t = 0; t < 20; t+=.01){
                                    int x, y;
                                    if (direct == 'd') {
                                        x = (int) (players[p].pos[1] + power / 10 * t * cos(angle * (M_PI / 180)));
                                        y = (int) (players[p].pos[0] + power / 10 * t * sin(angle * (M_PI / 180)) - ((2 * pow(t, 2))/2));
                                    }
                                    else {
                                        x = (int) (players[p].pos[1] + power / 10 * t * cos((180-angle) * (M_PI / 180)));
                                        y = (int) (players[p].pos[0] + power / 10 * t * sin((180-angle) * (M_PI / 180)) - ((2 * pow(t, 2))/2));
                                    }
                                    if(((x > WIDTH-1) || (x < 0)) || (y <= 0)) {
                                        printf("You shot out of map!");
                                        getchar();
                                        break;
                                    }
                                    if(y > HEIGHT) {
                                        continue;
                                    }
                                    if (scene[HEIGHT-y][x] == p + 2) {
                                        continue;
                                    } else if (scene[HEIGHT-y][x] == 1) {
                                        scene[HEIGHT-y][x] = 6;
                                        system("cls");
                                        showScene(scene);
                                        cout << "=======================================================================================================================" << endl;
                                        printf("You hit ground at [%d, %d]", x, y);
                                        getchar();
                                        scene[HEIGHT-y][x] = 0;
                                        for(int pl = 0; pl < playersn; pl++) {
                                            if(scene[HEIGHT - (players[pl].pos[0] - 1)][players[pl].pos[1]] == 0) {
                                                scene[HEIGHT - players[pl].pos[0]][players[pl].pos[1]] = 0;
                                                players[pl].pos[0]--;
                                                scene[HEIGHT - players[pl].pos[0]][players[pl].pos[1]] = pl+2;
                                            }
                                        }
                                        break;
                                    } else if (scene[HEIGHT-y][x] > 1) {
                                        int ip = scene[HEIGHT-y][x];
                                        players[ip - 2].state = false;
                                        alive--;
                                        break;
                                    }
                                }
                                round = false;
                                break;
                            }
                            else {
                                printf("Some value was entered incorrectly! Try again.\n");
                                getchar();
                            }
                            break;
                        case 'q':
                            system("cls");
                            getchar();
                            gameMenu();
                            exit(0);
                        default:
                            printf("Not a valid option was chosen.\n");
                            break;
                    }
                    getchar();
                } while (round);
            }
        }
    }
    for(int p = 0; p < playersn; p++) {
        if(players[p].state) {
            winner = p;
        }
    }
    char end;
    system("cls");
    cout << "=======================================================================================================================" << endl;
    printf("Player%d won! Congratulation!\n", winner+1);
    printf("Would you like to play again? y/n: ");
    end = tolower(getchar());
    getchar();
    if(end == 'y' || end == '\n') {
        printf("Would you like to play the same seed? y/n: ");
        end = tolower(getchar());
        getchar();
        if(end == 'y' || end == '\n') {
            seed = gseed;
        }
        else {
            printf("Enter seed or enter 0 to get it random: ");
            scanf_s("%d", seed);
        }
        printf("Would you like to stay with the same number of players? y/n:");
        end = tolower(getchar());
        getchar();
        if(end != 'y' && end != '\n') {
            printf("How many players will play this round? ");
            scanf_s("%d", &playersn);
        }
        startGame(scene, seed, 0, playersn);
    }
    else {
        printf("Do you want to exit? y/n: ");
        end = tolower(getchar());
        getchar();
        if(end == 'y' || end == '\n') {
            printf("Thank you so much for playing ours project game. We are looking forward to seeing you playing ours game again soon. :)");
            getchar();
            exit(0);
        }
        else {
            gameMenu();
            exit(0);
        }
    }
}