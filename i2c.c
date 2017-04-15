#include "tb32.h"

#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void task_i2c(void *args) {
	UNUSED(args);

	for (;;) {
		gpio_toggle(GPIOC,GPIO13);
        vTaskDelay(pdMS_TO_TICKS(500));
	}
}
