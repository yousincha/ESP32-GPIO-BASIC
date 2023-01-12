#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


    static const char *TAG = "BLINK";

    void blink(){
        int counter = 0;
        while(true){
            if(counter<50){
                gpio_set_level(GPIO_NUM_4,1);
                ESP_LOGD(TAG, "Switiching off the led");
            }
            else{
                gpio_set_level(GPIO_NUM_4,0);
                ESP_LOGD(TAG, "Switiching on the led");
            }                                       
            if(counter > 100)
            {
                counter = 0;
            }
            ++counter;
            vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    }
    void ldrSwitch(){
        ESP_LOGD(TAG, "Starting the LDR switch");
        while(true){
            if(gpio_get_level(GPIO_NUM_34)==1)
            {
                ESP_LOGD(TAG,"detected....");
                gpio_set_level(GPIO_NUM_4, 1);
            }
            else
            {
                gpio_set_level(GPIO_NUM_4, 0);
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        
    }
    void ldrSwitch2(){
        ESP_LOGD(TAG, "Starting the LDR switch");
        while(true){
            if(gpio_get_level(GPIO_NUM_35)==1)
            {
                ESP_LOGD(TAG,"detected....");
                gpio_set_level(GPIO_NUM_4, 1);
            }
            else
            {
                gpio_set_level(GPIO_NUM_4, 0);
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        
    }
    void ldrSwitch3(){
        int counter = 0;
        bool isLongPress = false;
        int ledState = gpio_get_level (GPIO_NUM_4);
        ESP_LOGD(TAG, "Starting the LDR switch : ledState >> %d", ledState);
        while(true){
            if(gpio_get_level(GPIO_NUM_34)==1)
            {
                
                counter++;
                
                if(counter > 200)
                {
                    isLongPress = true;
                }
 
            }
            else
            {
                if(isLongPress)
                {
                    isLongPress = false;
                    ledState = !ledState;
                    gpio_set_level(GPIO_NUM_4, ledState);
                }
                counter = 0;
            }
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
        
    }
    void app_main() 
    {
    /*
    gpio_pad_select_gpio(GPIO_NUM_2);
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_2,1));

    gpio_pad_select_gpio(GPIO_NUM_16);
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_16, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_16,1));

    gpio_pad_select_gpio(GPIO_NUM_22);
    ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_22, GPIO_MODE_OUTPUT));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_22,1));
    */
    gpio_config_t gpioOutputConfig = {
        GPIO_SEL_4,
        GPIO_MODE_OUTPUT,
        GPIO_PULLUP_DISABLE,
        GPIO_PULLDOWN_DISABLE,
        GPIO_INTR_DISABLE};
    gpio_config(&gpioOutputConfig);
    
    gpio_config_t gpioKeyInputConfig = {
        GPIO_SEL_34,
        GPIO_MODE_INPUT,
        GPIO_PULLUP_DISABLE,
        GPIO_PULLDOWN_DISABLE,
        GPIO_INTR_DISABLE};
    gpio_config(&gpioKeyInputConfig);

    gpio_config_t gpioReedInputConfig = {
        GPIO_SEL_35,
        GPIO_MODE_INPUT,
        GPIO_PULLUP_DISABLE,
        GPIO_PULLDOWN_DISABLE,
        GPIO_INTR_DISABLE};
    gpio_config(&gpioReedInputConfig);

    ldrSwitch3();
    }
