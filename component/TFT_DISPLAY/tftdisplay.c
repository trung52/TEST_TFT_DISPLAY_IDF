#include "tftdisplay.h"

static void lv_tick_task(void *arg) {
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}


esp_err_t tft_initialize(){
    // Initialize LVGL library
    ESP_LOGI(__func__, "Initialize LVGL library");
    lv_init();

    // Initialize driver
    ESP_LOGI(__func__, "Initialize driver for ILI9341");
    lvgl_driver_init();

    static lv_disp_buf_t draw_buf_dsc_1;
    static lv_color_t draw_buf_1[DISP_BUF_SIZE];                          /*A buffer*/
    lv_disp_buf_init(&draw_buf_dsc_1, draw_buf_1, NULL,DISP_BUF_SIZE);   /*Initialize the display buffer*/

    lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_driver_flush;

    /*Set a display buffer*/
    disp_drv.buffer = &draw_buf_dsc_1;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);

    /* Create and start a periodic timer interrupt to call lv_tick_inc */
    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

    /*Change the active screen's background color*/
    lv_obj_set_style_local_bg_color(lv_scr_act(), LV_BTN_PART_MAIN, 0, LV_COLOR_WHITE);

    ESP_LOGI(__func__, "TFT initialize successfully.");
    return ESP_OK;
}

