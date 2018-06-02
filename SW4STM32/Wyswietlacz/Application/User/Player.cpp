#include "Player.h"
#include "shapes.h"

//Random int
uint8_t TM_RNG_Get(void) {

	/* Wait until one RNG number is ready */
	while (!(RNG->SR & (RNG_SR_DRDY)))
		;

	/* Get a 32-bit Random number */
	return RNG->DR;
}

//Setters
void Player::setTopLeft(int row, int col) {
	topLeft[0] = row;
	topLeft[1] = col;
}

//Methods
//Clear both displays
void Player::Clear(MAX7219_MatrixDisplay &display) {
	for (std::size_t y = 0; y < 16; y++) {
		for (std::size_t x = 0; x < 8; x++) {
			display.writePixel(x, y, 0);
		}
	}
	display.write();
}

//Display diagonal
void Player::Diagonal(MAX7219_MatrixDisplay &display) {
	int count = 0;
	for (int i = 0; i < 24; i++) {
		for (int y = 0; y < 16; y++) {
			for (int x = 0; x < 8; x++) {
				display.writePixel(x, y, x + y == count);
			}
		}
		for (int i = 0; i < 30000; i++)
			;
		display.write();
		count++;
	}
}

void Player::displayPlayer(MAX7219_MatrixDisplay &display) {

	for (int y = topLeft[0]; y > topLeft[0] - 3; y--) {
		for (int x = topLeft[1]; x < topLeft[1] + 3; x++) {
			if (block[abs(y - topLeft[0])][abs(x - topLeft[1])] == 1)
				display.writePixel(x, y, 1);
		}
	}
	display.write();

}

void Player::clearPlayer(MAX7219_MatrixDisplay &display) {

	for (int y = topLeft[0]; y > topLeft[0] - 3; y--) {
		for (int x = topLeft[1]; x < topLeft[1] + 3; x++) {
			if (block[abs(y - topLeft[0])][abs(x - topLeft[1])] == 1)
				display.writePixel(x, y, 0);
		}
	}
	display.write();

}

void Player::shapeToBlock(bool block[3][3]) {
	//Copying new shape to player object
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->block[i][j] = block[i][j];
		}
	}
}

void Player::spawnBlock(MAX7219_MatrixDisplay &display, int pos) {

	//Spawn position for player
	// L, J ,I, T 15:3
	// O, S ,Z 16:3
	topLeft[0] = pos;
	topLeft[1] = 3;

	//Check if collide with start position if so gameOver
	if (checkColision(display, topLeft) == true) {
		displayPlayer(display);
		Diagonal(display);
		Clear(display);
	}
	//Display spawned block
	if (!gameOver)
		displayPlayer(display);
}

void Player::moveDown(MAX7219_MatrixDisplay &display) {
	if (!gameOver) {
		//Clear row that was top of block
		clearPlayer(display);

		//Check new position
		int newTopLeft[2] = { topLeft[0] - 1, topLeft[1] };

		//if new position is occupied block landed
		//otherwise move block down

		if (topLeft[0] == 2 || checkColision(display, newTopLeft)) {
			displayPlayer(display);
			//Check for full lane
			clearLines(display);
			spawnRandomBlock(display);

		} else {
			setTopLeft(topLeft[0] - 1, topLeft[1]);
			displayPlayer(display);
		}
	}
}

void Player::moveRight(MAX7219_MatrixDisplay &display) {
	if (!gameOver) {
		//Clear row that was top of block
		clearPlayer(display);

		//Check new position
		int newTopLeft[2] = { topLeft[0], topLeft[1] + 1 };

		//if new position is occupied block cant move right
		//otherwise block can move right
		if (topLeft[0] == 2 || checkColision(display, newTopLeft)) {
			displayPlayer(display);
		} else {
			setTopLeft(topLeft[0], topLeft[1] + 1);
			displayPlayer(display);
		}
	}
}

void Player::moveLeft(MAX7219_MatrixDisplay &display) {
	if (!gameOver) {
		//Clear row that was top of block
		clearPlayer(display);

		//Check new position
		int newTopLeft[2] = { topLeft[0], topLeft[1] - 1 };

		//if new position is occupied block cant move right
		//otherwise block can move right
		if (topLeft[0] == 2 || checkColision(display, newTopLeft)) {
			displayPlayer(display);
		} else {
			setTopLeft(topLeft[0], topLeft[1] - 1);
			displayPlayer(display);
		}
	}
}

bool Player::allowRotation(MAX7219_MatrixDisplay &display,
		bool newShape[3][3]) {
	for (int y = topLeft[0]; y > topLeft[0] - 3; y--) {
		for (int x = topLeft[1]; x < topLeft[1] + 3; x++) {
			if (newShape[abs(y - topLeft[0])][abs(x - topLeft[1])] == 1) {
				if (x >= 8 || x < 0)
					return false;

				if (display.getPixel(x, y) == true)
					return false;
			}
		}
	}

	return true;
}

void Player::rotate(MAX7219_MatrixDisplay &display) {
	// O no rotations allowed
	// I S Z 90 degree rotation allowed
	// T L J all rotations allowed

	if (!gameOver) {
		clearPlayer(display);

		if (letter == 'O') {
			displayPlayer(display);
			return;
		} else if (letter == 'I') {
			if (rotation == 0) {
				if (allowRotation(display, IShape90)) {
					rotation = 90;
					shapeToBlock(IShape90);
				}
			} else if (rotation == 90) {
				if (allowRotation(display, IShape)) {
					rotation = 0;
					shapeToBlock(IShape);
				}
			}
		} else if (letter == 'S') {
			if (rotation == 0) {
				if (allowRotation(display, SShape90)) {
					rotation = 90;
					shapeToBlock(SShape90);
				}
			} else if (rotation == 90) {
				if (allowRotation(display, SShape)) {
					rotation = 0;
					shapeToBlock(SShape);
				}
			}
		} else if (letter == 'Z') {
			if (rotation == 0) {
				if (allowRotation(display, ZShape90)) {
					rotation = 90;
					shapeToBlock(ZShape90);
				}
			} else if (rotation == 90) {
				if (allowRotation(display, ZShape)) {
					rotation = 0;
					shapeToBlock(ZShape);
				}
			}
		} else if (letter == 'T') {
			if (rotation == 0) {
				if (allowRotation(display, TShape90)) {
					rotation = 90;
					shapeToBlock(TShape90);
				}
			} else if (rotation == 90) {
				if (allowRotation(display, TShape180)) {
					rotation = 180;
					shapeToBlock(TShape180);
				}
			} else if (rotation == 180) {
				if (allowRotation(display, TShape270)) {
					rotation = 270;
					shapeToBlock(TShape270);
				}
			} else if (rotation == 270) {
				if (allowRotation(display, TShape)) {
					rotation = 0;
					shapeToBlock(TShape);
				}
			}
		} else if (letter == 'L') {
			if (rotation == 0) {
				if (allowRotation(display, LShape90)) {
					rotation = 90;
					shapeToBlock(LShape90);
				}
			} else if (rotation == 90) {
				if (allowRotation(display, LShape180)) {
					rotation = 180;
					shapeToBlock(LShape180);
				}
			} else if (rotation == 180) {
				if (allowRotation(display, TShape270)) {
					rotation = 270;
					shapeToBlock(LShape270);
				}
			} else if (rotation == 270) {
				if (allowRotation(display, LShape)) {
					rotation = 0;
					shapeToBlock(LShape);
				}
			}
		} else if (letter == 'J') {
			if (rotation == 0) {
				if (allowRotation(display, JShape90)) {
					rotation = 90;
					shapeToBlock(JShape90);
				}
			} else if (rotation == 90) {
				if (allowRotation(display, JShape180)) {
					rotation = 180;
					shapeToBlock(JShape180);
				}
			} else if (rotation == 180) {
				if (allowRotation(display, JShape270)) {
					rotation = 270;
					shapeToBlock(JShape270);
				}
			} else if (rotation == 270) {
				if (allowRotation(display, JShape)) {
					rotation = 0;
					shapeToBlock(JShape);
				}
			}
		}
		displayPlayer(display);
	}
}

void Player::clearLines(MAX7219_MatrixDisplay &display) {
	int ones = 0;
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 8; x++) {
			if (display.getPixel(x, y) == 1)
				ones++;
		}
		if (ones == 0)
			break;
		if (ones == 8) {
			for (int x = 0; x < 8; x++) {
				display.writePixel(x, y, 0);
			}
			shiftDown(display, y);
			y--;
		}
		ones = 0;
	}

}

void Player::shiftDown(MAX7219_MatrixDisplay &display, int row) {
	for (int y = row + 1; y < 16; y++) {
		for (int x = 0; x < 8; x++) {
			if (display.getPixel(x, y) == 1) {
				display.writePixel(x, y - 1, 1);
			} else {
				display.writePixel(x, y - 1, 0);
			}
		}
	}
	display.write();
}

bool Player::checkColision(MAX7219_MatrixDisplay &display, int newTopLeft[2]) {
	for (int y = newTopLeft[0]; y > newTopLeft[0] - 3; y--) {
		for (int x = newTopLeft[1]; x < newTopLeft[1] + 3; x++) {
			if (block[abs(y - newTopLeft[0])][abs(x - newTopLeft[1])] == 1) {

				if (x >= 8 || x < 0)
					return true;

				if (display.getPixel(x, y) == true)
					return true;

			}
		}
	}
	return false;
}

void Player::spawnRandomBlock(MAX7219_MatrixDisplay &display) {

	int result = TM_RNG_Get() % 7;

	if (result == 0) {
		letter = 'O';
		this->rotation = 0;
		shapeToBlock(OShape);
		spawnBlock(display, 16);
	} else if (result == 1) {
		letter = 'S';
		int rotation = TM_RNG_Get() % 2;
		if (rotation == 0) {
			this->rotation = 0;
			shapeToBlock(SShape);
			spawnBlock(display, 16);
		}
		if (rotation == 1) {
			this->rotation = 90;
			shapeToBlock(SShape90);
			spawnBlock(display, 15);
		}
	} else if (result == 2) {
		letter = 'Z';
		int rotation = TM_RNG_Get() % 2;
		if (rotation == 0) {
			this->rotation = 0;
			shapeToBlock(ZShape);
			spawnBlock(display, 16);
		}
		if (rotation == 1) {
			this->rotation = 90;
			shapeToBlock(ZShape);
			spawnBlock(display, 15);
		}
	} else if (result == 3) {
		letter = 'T';
		int rotation = TM_RNG_Get() % 4;
		if (rotation == 0) {
			this->rotation = 0;
			shapeToBlock(TShape);
			spawnBlock(display, 15);
		}
		if (rotation == 1) {
			this->rotation = 90;
			shapeToBlock(TShape90);
			spawnBlock(display, 15);
		}
		if (rotation == 2) {
			this->rotation = 180;
			shapeToBlock(TShape180);
			spawnBlock(display, 16);
		}
		if (rotation == 3) {
			this->rotation = 270;
			shapeToBlock(TShape270);
			spawnBlock(display, 15);
		}

	} else if (result == 4) {
		letter = 'I';
		int rotation = TM_RNG_Get() % 2;

		if (rotation == 0) {
			this->rotation = 0;
			shapeToBlock(IShape);
			spawnBlock(display, 15);
		}
		if (rotation == 1) {
			this->rotation = 90;
			shapeToBlock(IShape90);
			spawnBlock(display, 16);
		}
	} else if (result == 5) {
		letter = 'L';
		int rotation = TM_RNG_Get() % 4;

		if (rotation == 0) {
			this->rotation = 0;
			shapeToBlock(LShape);
			spawnBlock(display, 15);
		}
		if (rotation == 1) {
			this->rotation = 90;
			shapeToBlock(LShape90);
			spawnBlock(display, 16);
		}
		if (rotation == 2) {
			this->rotation = 180;
			shapeToBlock(LShape180);
			spawnBlock(display, 15);
		}
		if (rotation == 3) {
			this->rotation = 270;
			shapeToBlock(LShape270);
			spawnBlock(display, 15);
		}
	} else if (result == 6) {
		letter = 'J';
		int rotation = TM_RNG_Get() % 4;
		if (rotation == 0) {
			this->rotation = 0;
			shapeToBlock(JShape);
			spawnBlock(display, 15);
		}
		if (rotation == 1) {
			this->rotation = 90;
			shapeToBlock(JShape90);
			spawnBlock(display, 15);
		}
		if (rotation == 2) {
			this->rotation = 180;
			shapeToBlock(JShape180);
			spawnBlock(display, 15);
		}
		if (rotation == 3) {
			this->rotation = 270;
			shapeToBlock(JShape270);
			spawnBlock(display, 16);
		}
	}
}
