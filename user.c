#include "string.h"
#include "stdio.h"

#include "tb32.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#ifdef DEBUG
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#endif

// transmit queue for serial
static QueueHandle_t usart_txq;

#define MAX_WAIT_TICKS	2500
#define TX_QUEUE_SIZE	256
#define BAUD			38400
#ifdef DEBUG
#define MAX_STATS_BUF	256
#endif

volatile unsigned long ulHighFrequencyTimerTicks = 0;

void task_user_init(void) {
	// transmit queue
	usart_txq = xQueueCreate(TX_QUEUE_SIZE,sizeof(char));

	usart_set_baudrate(USART1, BAUD);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_mode(USART1, USART_MODE_TX_RX);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_enable(USART1);
}

void task_user(void *args) {
	char ch;
	char ps[MAX_STATS_BUF];

	UNUSED(args);

	usart_queue("online\n");

	for (;;) {
		// send next character from queue
		if (xQueueReceive(usart_txq, &ch, MAX_WAIT_TICKS)) {
			usart_send_blocking(USART1, ch);
			taskYIELD();
#ifdef DEBUG
		} else if (uxQueueSpacesAvailable(usart_txq) >= MAX_STATS_BUF) {
			unsigned int x = getRunTimeCounterValue();
			UNUSED(x);
			sprintf(ps, "counter value: %d\n", x);
			usart_queue(ps);
#if 0
			vTaskList(ps);
			usart_queue(ps);
#else
			vTaskGetRunTimeStats(ps);
			usart_queue(ps);
#endif
			gpio_toggle(GPIOC, GPIO13);
#if 0
			char s[24];
			int i;
			sprintf(s, "pslen=%d\n", strlen(ps));
			usart_queue(s);
			for (i = 0; s[i] != '\0'; ++i)
				usart_send_blocking(USART1, s[i]);
			for (i = 0; ps[i] != '\0'; ++i)
				usart_send_blocking(USART1, ps[i]);
#endif
#endif
		}
#if 0
		usart_send_blocking(USART1, '.');
#endif
	}
}

void usart_queue(const char *s) {
	for (; *s; ++s)
		xQueueSend(usart_txq, s, portMAX_DELAY);
}

#ifdef DEBUG
unsigned getRunTimeCounterValue(void) {
	unsigned int x = TIM_CNT(TIM3);
	return x;
}

void configureTimerForRunTimeStats(void) {
	rcc_periph_reset_pulse(RST_TIM3);
	timer_set_prescaler(TIM3, 10);
	timer_set_period(TIM3, 0xffff);
	timer_enable_counter(TIM3);
}
#endif
