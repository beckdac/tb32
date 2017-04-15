#ifndef __TB32_H__
#define __TB32_H__

// i2c
#define TASK_NAME_I2C	"I2C"
#define TASK_STACK_SIZE_I2C	800
void task_i2c(void *args);

// user
#define TASK_NAME_USER	"user"
#define TASK_STACK_SIZE_USER	400
void task_user_init(void);
void task_user(void *args);
void usart_queue(const char *s);

// stepper
#define TASK_NAME_STEPPER "stepper"
#define TASK_STACK_SIZE_STEPPER	100
void task_stepper(void *args);

// utils
#define ticks_elapsed(then, now) (now >= then ? now - then : ~(TickType_t)0 - then + 1 + now)
#define UNUSED(x) (void)(x)

#endif /* __TB32_H__ */
