#ifndef PLAYER_H
#define PLAYER_H
#include "MAX7219_MatrixDisplay.h"

class Player {
	// Class fields
	bool block[3][3];
	bool landed;
	bool gameOver;

	// Top Left position of 3x3 block
	int topLeft[2]; //row col

	//possible rotations 0 90 180 270;
	int rotation;

	// letter of block used to rotate
	char letter;

public:
	Player() {
		landed = false;
		gameOver = false;
		rotation = 0;
		letter = 'D';
	}

	void setTopLeft(int row, int col);
	//Methods

	//Display block on display
	//TopLeft indicates position of block
	void displayPlayer(MAX7219_MatrixDisplay &display);

	//Playerblock is cleard used when moving/ rotation player
	void clearPlayer(MAX7219_MatrixDisplay &display);

	//Coping shape to block
	void shapeToBlock(bool block[3][3]);

	//Spawn new block on arg position
	//position depends of shape
	void spawnBlock(MAX7219_MatrixDisplay &display, int pos);

	//Movement Methods

	//Move one space down
	void moveDown(MAX7219_MatrixDisplay &display);

	//Move one space right
	void moveRight(MAX7219_MatrixDisplay &display);

	//Move one space left
	void moveLeft(MAX7219_MatrixDisplay &display);

	//Return true when rotation is allowed false when disallowed
	bool allowRotation(MAX7219_MatrixDisplay &display, bool newShape[3][3]);

	//Rotatie block 90 degree
	void rotate(MAX7219_MatrixDisplay &display);

	//Clear lines when row is filled
	void clearLines(MAX7219_MatrixDisplay &display);

	//Move rows down when one row is cleared
	void shiftDown(MAX7219_MatrixDisplay &display, int row);

	//Check collision of next move
	//TRUE - collison
	//FALSE - no collison
	bool checkColision(MAX7219_MatrixDisplay &display, int newTopLeft[2]);

	//Choosing Random block and calling spawnBlock
	void spawnRandomBlock(MAX7219_MatrixDisplay &display);

	//Czyszczenie wyswietlacza
	void Clear(MAX7219_MatrixDisplay &display);

	//Zapalanie po przekatnej
	void Diagonal(MAX7219_MatrixDisplay &display);

};

#endif /* PLAYER_H */
