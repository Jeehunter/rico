#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
 
static lv_disp_draw_buf_t draw_buf;    //定义显示器变量
static lv_color_t buf[TFT_WIDTH * 10]; //定义刷新缓存
 
TFT_eSPI tft = TFT_eSPI();
 
/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
 
    tft.startWrite();                                        //使能写功能
    tft.setAddrWindow(area->x1, area->y1, w, h);             //设置填充区域
    tft.pushColors((uint16_t *)&color_p->full, w * h, true); //写入颜色缓存和缓存大小
    tft.endWrite();                                          //关闭写功能
 
    lv_disp_flush_ready(disp); //调用区域填充颜色函数
}
 
void setup()
{
    tft.init();         //初始化
    tft.setRotation(2); //屏幕旋转方向（横向）
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, TFT_WIDTH * 10);
 
    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
 
    /*获取LVGL版本信息*/
    String LVGL_Arduino = "RICO";
    // LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch(); //版本
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, LVGL_Arduino.c_str());
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0); //居中显示



    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_align(btn,LV_ALIGN_CENTER,0,0);

    String LVGL_Arduino_One = "click";
    // LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch(); //版本
    lv_obj_t *label_one = lv_label_create(lv_scr_act());
    lv_label_set_text(label_one, LVGL_Arduino_One.c_str());
    lv_obj_align(label_one, LV_ALIGN_CENTER, 0, 0); //居中显示
    lv_obj_set_width(btn,100);

    // lv_obj_fade_in(label,3000,0);
    // lv_obj_fade_out(label,3000,0);
    // lv_obj_fade_in(label,3000,0);
}
 
void loop()
{
    lv_timer_handler(); /* let the GUI do its work */
    delay(5);
}

