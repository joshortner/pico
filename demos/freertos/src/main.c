#include "pico/stdlib.h"

#include <FreeRTOS.h>
#include <task.h>

#include <stdio.h>

void led_task()
{   
    const char * p_task_name = "LED_Task"; 
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    while (true) {
        gpio_put(LED_PIN, 1);
        vTaskDelay(100);
        gpio_put(LED_PIN, 0);
        vTaskDelay(100);

        printf("Delay from task (%s)\n", p_task_name);
    }
}

int main()
{
    stdio_init_all();

    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while(1){};
}