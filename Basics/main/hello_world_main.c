/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "driver/gpio.h"

#include "hello_world_main.h"

#define LED_G GPIO_NUM_33
#define LED_B GPIO_NUM_26
#define LED_R GPIO_NUM_25

#define LED_G_BIT_MASK (1ULL << LED_G)      // ULL = Unsigned Long Long
#define LED_B_BIT_MASK (1ULL << LED_B)
#define LED_R_BIT_MASK (1ULL << LED_R)

void chip_data(void){
    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, ",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "");

    unsigned major_rev = chip_info.revision / 100;
    unsigned minor_rev = chip_info.revision % 100;
    printf("silicon revision v%d.%d, ", major_rev, minor_rev);
    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());
}

void reset_chip(){
    /* Count down to reset the ESP32 */
    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    /* Restart section */
    printf("Restarting now.\n");
    fflush(stdout); // flushes the output buffer of a stream
    esp_restart();
}

/* String print function */
void print_funct(char* input_string){
    // for (int i = 0; i < strlen(input_string); i++){
    //     printf("%p = %c\n", &input_string[i], input_string[i]);
    // }
    printf("%s", input_string);
}

/* Memory allocation function that returns a pointer */
char* allocate_mem(char *input_string){
    int length = 0;
    
    length = (int) strlen(input_string);        // Determining length of string to allocate memory
    printf("The string is %d long\n", length);
    char *ptr = (char *) calloc(length, sizeof(char));        // Making variable dynamic memory based on input

    // NULL Check, exit if ptr is NULL
    if (ptr == NULL){
        printf("failed allocation\n");
        exit(0);
    }

    // Storing input into allocated memory
    for (int i = 0; i < length; i++){
        ptr[i] = input_string[i];
    }
    return (ptr);
}



/* ESP struct instantiation for GPIO */
gpio_config_t myGPIO;

void app_main(void)
{
    /***** String Function *****/
    // Local declarations
    /*char user_string[256] = "Hello world";
    int length = 0;
    
    // Input
    printf("Please enter a string:\n");
    //scanf("%c", user_string);

    char* string = allocate_mem(user_string);                // Return ptr from function and place in new pointer
    length = (int) strlen(string);
    printf("Address: %p", string);
    printf("\n");
    
    print_funct(string);                          // Simple printing function
    free(string);                                 // Freeing the memory
    */

    /**** Simple GPIO LED Example ****/
    /*gpio_set_direction(LED_G, GPIO_MODE_OUTPUT);        // Establishing GPIO output for specified pin
    while(1) {
        gpio_set_level(LED_G, true);                    // Set HIGH
        vTaskDelay(100);                                // Delay 1 sec
        gpio_set_level(LED_G, false);                   // Set LOW
        vTaskDelay(100);                                // Delay
    }
    */

    /**** Bit Masking LED Example ****/
    /*myGPIO.pin_bit_mask = (LED_G_BIT_MASK | LED_B_BIT_MASK | LED_R_BIT_MASK);
    myGPIO.pull_down_en = GPIO_PULLDOWN_DISABLE;
    myGPIO.pull_up_en = GPIO_PULLUP_DISABLE;
    myGPIO.intr_type = GPIO_INTR_DISABLE;
    myGPIO.mode = GPIO_MODE_OUTPUT;

    gpio_config(&myGPIO);

    while (1){
        gpio_set_level(LED_G, true);
        vTaskDelay(100);
        gpio_set_level(LED_G, false);

        gpio_set_level(LED_B, true);
        vTaskDelay(100);
        gpio_set_level(LED_B, false);

        gpio_set_level(LED_R, true);
        vTaskDelay(100);
        gpio_set_level(LED_R, false);
        vTaskDelay(100);
    }*/

    /**** Bitwise Operations ****/
    // Example 1: Input is 0b1001 0010 0011  (0x923), j = ith bit, make 0010 0000
    uint16_t input_bit = 0b100100100011;
    int j = 6; // Hard-coded six bit

    uint16_t output_bit = input_bit & ~(0x1 << (j-1));
    printf("%X\n", output_bit);
    // Result is 0x903, as expected

    // Example 2: Input is 0b1101 0110, each bit determines an option, make function to print what options are enabled
    input_bit =  0b11010100;
    int check_bit = 2;
    int set = set_bit_check(input_bit, check_bit);
    if (set){
        printf("For %X, bit %d is set.\n", input_bit,  check_bit);
    }
    else {
        printf("For %X, bit %d is not set.\n", input_bit,  check_bit);
    }
    
}
 