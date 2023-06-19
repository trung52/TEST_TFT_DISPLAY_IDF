/**
 * @file tftdisplay.h
 * @author Vu Thanh Trung   (20203623)
 * @brief Library for SPI TFT display module (ILI9341)
 * @note Before use this file and the lvgl_esp32_driver,
 * run idf.py menuconfig, go to Component config then
 * LVGL TFT configuration and LVGL TFT Display configuration
 * to configure lvgl_esp32_drivers.
*/

#ifndef __TFTDISPLAY_H__
#define __TFTDISPLAY_H__

#include <stdio.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "../lvgl/lvgl.h"
#include "../../build/config/sdkconfig.h"
#include "driver/gpio.h"
#include "driver/spi_common.h"
#include "../lvgl_esp32_drivers/lvgl_helpers.h"
#include "../lvgl_esp32_drivers/lvgl_spi_conf.h"
#include "../lv_examples/lv_examples/src/lv_demo_widgets/lv_demo_widgets.h"

#define LV_TICK_PERIOD_MS 1

#define ID_TFT 0x03

#define ESP_ERROR_TFT_INIT_FAILED ((ID_TFT << 12)|0x00)

/**
 * @brief Initialize SPI and driver for TFT display
 * @return esp_err_t
*/
esp_err_t tft_initialize();
void _create_demo_application(void);


#endif