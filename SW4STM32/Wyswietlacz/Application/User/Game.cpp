#include "Game.h"

//Object Init
MAX7219 max(hspi1);
MAX7219_MatrixDisplay display(max);
Player player;

//Button interupt callback
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if (GPIO_Pin == Left_Button_Pin) {
		for (int i = 0; i < 5000; i++)
			;
		if (HAL_GPIO_ReadPin(GPIOE, Left_Button_Pin) == 0)
			player.moveLeft(display);
	}
	if (GPIO_Pin == Right_Button_Pin) {
		for (int i = 0; i < 5000; i++)
			;
		if (HAL_GPIO_ReadPin(GPIOE, Right_Button_Pin) == 0)
			player.moveRight(display);
	}
	if (GPIO_Pin == Down_Button_Pin) {
		for (int i = 0; i < 5000; i++)
			;
		if (HAL_GPIO_ReadPin(GPIOE, Down_Button_Pin) == 0) {
			player.moveDown(display);
			TIM10->CNT = 0;
		}
	}

	if (GPIO_Pin == Rotate_Button_Pin) {
		for (int i = 0; i < 5000; i++)
			;
		if (HAL_GPIO_ReadPin(GPIOE, Rotate_Button_Pin) == 0) {
			player.rotate(display);
		}
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM10) { // Je¿eli przerwanie pochodzi od timera 10
		player.moveDown(display);
	}
}



extern void GameLoop() {

	//Display Init
	max.powerOn();
	max.intensity(3);
	max.scanLimit(7);
	player.Clear(display);
	display.write();
	//Spawning first block
	player.spawnRandomBlock(display);
	while (true) {}

}

