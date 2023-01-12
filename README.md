# ESP32-GPIO-BASIC

### main.c
```c
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
```
ESP-32 스위치를 누를때 LED가 켜진다.

```c
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
```
자석을 갖다대면 LED 불이 꺼진다.

```c
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
```
ESP-32 스위치를 2초 이상 누를때 LED가 켜지고, <
다시 2초 이상 누르면 LED가 꺼진다.

### platformio.ini
```c
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = espidf
monitor_baud = 115200
monitor_speed = 115200
```
log 글씨가 깨지는 것을 방지하기 위해<br>
monitor_baud = 115200와 monitor_speed= 115200를 추가했다.

