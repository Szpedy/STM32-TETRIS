#ifndef GAME_H
#define GAME_H
#include "MAX7219.h"
#include "MAX7219_MatrixDisplay.h"
#include "Player.h"

extern SPI_HandleTypeDef hspi1;
extern RNG_HandleTypeDef hrng;
/*
Matrix
5V  - VCC
GNG - GND
PA5 - CLK
PA7 - DIN
PC5 - CS

BUTTONS
PE11-14

 */

//Game Loop
extern "C" void GameLoop();

#endif //GAME_H
