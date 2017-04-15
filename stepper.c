#include "tb32.h"

#include "FreeRTOS.h"
#include "task.h"

void task_stepper(void *args) {
	UNUSED(args);

	for (;;) {
		taskYIELD();
	}
}
