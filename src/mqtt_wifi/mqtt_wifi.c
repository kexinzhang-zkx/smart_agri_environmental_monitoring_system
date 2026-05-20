// MQTT读取线程
void *mqtt_thread_func(void *arg)
{
    FILE *fp = popen("mosquitto_sub -t \"light\" -h \"47.120.20.79\" -p 1883", "r");
    if (fp == NULL) {
        printf("加载进程失败\n");
        return 0;
    }
    printf("加载进程成功\n");

    while (1) {
        char buf[1024] = {0};
        char *ret = fgets(buf, sizeof(buf), fp);
        if (ret == NULL) {
            printf("进程加载结束\n");
            break;
        }
        printf("recv:%s", buf);

        float temp, humi, light;
        if (sscanf(buf, "T %f H %f L %f", &temp, &humi, &light) == 3) {
            char temp_str[32] = {0};
            sprintf(temp_str, "%.1f", temp);
            lv_label_set_text(ui_Label18, temp_str);

            char light_str[32] = {0};
            sprintf(light_str, "%.1f", light);
            lv_label_set_text(ui_Label20, light_str);

            char hum_str[32] = {0};
            sprintf(hum_str, "%.1f", humi);
            lv_label_set_text(ui_Label44, hum_str);
        }
    }
    pclose(fp);
}
