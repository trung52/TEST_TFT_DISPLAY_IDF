#include <stdio.h>
#include "tftdisplay.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t tft_semaphore = NULL;

/**
 * Create a button with a label and react on Click event.
 */
void lv_ex_get_started_1(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, LV_STATE_DEFAULT, 10);

    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_CYAN);
    lv_style_set_pad_hor(&style, LV_STATE_DEFAULT, 50);
    lv_style_set_pad_ver(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_text_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(obj, "HELLO");
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
    //lv_obj_set_size(obj, 150, 50);
    lv_obj_set_pos(obj,0,20);
    


    
                
}

void lv_ex_get_started_2(void)
{
    // lv_obj_t * label1 = lv_label_create(lv_scr_act(),NULL);
    // lv_label_set_long_mode(label1, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    // lv_label_set_recolor(label1, true);                      /*Enable re-coloring by commands in the text*/
    // lv_label_set_text(label1, "#000200 Re-color# #000200 words# #000200 of a# label, align the lines to the center "
    //                   "and wrap long text automatically.");
    // lv_obj_set_width(label1, 150);  /*Set smaller width to make the lines wrap*/
    // //lv_obj_set_style_text_align(label1, LV_TEXT_ALIGN_CENTER, 0);
    // lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, -40);

    lv_obj_t * label2 = lv_label_create(lv_scr_act(),NULL);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
    lv_obj_set_width(label2, 100);
    lv_label_set_text(label2, "NHOM 6 KTVXL ");
    //lv_obj_align(label2,NULL, LV_ALIGN_CENTER, 0, 40);                    /*Set the labels text*/
    lv_obj_set_pos(label2,50,0);
}

void tft_task(void* parameters){
    tft_semaphore = xSemaphoreCreateMutex();
    //lv_demo_widgets();
    lv_ex_get_started_1();
    lv_ex_get_started_2();

    while (1){
        vTaskDelay(pdMS_TO_TICKS(10));

        if (pdTRUE == xSemaphoreTake(tft_semaphore, portMAX_DELAY)) {
            lv_task_handler();
            xSemaphoreGive(tft_semaphore);
       }
    }

}



void app_main(void)
{
    tft_initialize();
    xTaskCreate(tft_task,"test", 1024*8,NULL,25,NULL);
    //tft_initialize();
}
