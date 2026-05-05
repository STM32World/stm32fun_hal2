/**
 ******************************************************************************
 * file           : main.c
 * brief          : Main program body
 *                  Calls target system initialization then loop in main.
 ******************************************************************************
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "mx_usart1.h"

#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
hal_uart_handle_t *uart;
/* Private functions prototype -----------------------------------------------*/

// Send printf to uart1
int __io_putchar(int ch) {
    if (ch == '\n') {
        HAL_UART_Transmit(uart, (uint8_t*) "\r", 1, HAL_MAX_DELAY);
    }
    if (HAL_UART_Transmit(uart, (uint8_t*) &ch, 1, HAL_MAX_DELAY) != HAL_OK) {
        return -1;
    }
    return ch;
}

/**
 * brief:  The application entry point.
 * retval: none but we specify int to comply with C99 standard
 */
int main(void)
{
    /** System Init: this code placed in targets folder initializes your system.
     * It calls the initialization (and sets the initial configuration) of the peripherals.
     * You can use STM32CubeMX to generate and call this code or not in this project.
     * It also contains the HAL initialization and the initial clock configuration.
     */
    if (mx_system_init() != SYSTEM_OK)
            {
        return (-1);
    }
    else
    {
        /*
         * You can start your application code here
         */

        uart = mx_usart1_uart_gethandle();

        uint32_t now = 0, loop_cnt = 0, next_blink = 500, next_tick = 1000;

        while (1) {

            now = uwTick;

            if (now >= next_blink) {

                HAL_GPIO_TogglePin(LED_PORT, LED_PIN);

                next_blink = now + 500;

            }

            if (now >= next_tick) {

                printf("Tick %lu ( loop=%lu )\n", now / 1000, loop_cnt);

                loop_cnt = 0;
                next_tick = now + 1000;

            }

            ++loop_cnt;

        }
    }
}

/* end main */

