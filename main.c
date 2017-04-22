/* Simple LED task demo, using timed delays:
 *
 * The LED on PC13 is toggled in task1.
 */
#include "tb32.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed portCHAR *pcTaskName);

void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed portCHAR *pcTaskName) {
	(void)pxTask;
	(void)pcTaskName;
	for(;;);
}

static void gpio_setup(void) {
	// set clock to 72 Mhz
	rcc_clock_setup_in_hse_8mhz_out_72mhz();

	// LED
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, \
					GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

	// usart1
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_USART1);
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, \
					GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,GPIO_USART1_TX);
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, \
					GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,GPIO11);
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, \
					GPIO_CNF_INPUT_FLOAT,GPIO_USART1_RX);
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, \
					GPIO_CNF_INPUT_FLOAT,GPIO12);
}

int main(void) {
	gpio_setup();

	task_user_init();

	xTaskCreate(task_stepper, "stepper", 100, NULL, configMAX_PRIORITIES-2, NULL);
	xTaskCreate(task_user, "user", 300, NULL, configMAX_PRIORITIES-2, NULL);
	vTaskStartScheduler();

	for (;;);

	return 0;
}
