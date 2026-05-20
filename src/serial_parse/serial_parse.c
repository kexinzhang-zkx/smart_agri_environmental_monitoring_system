// ZigBee数据接收线程
void *zigbee_thread_func(void *arg)
{
    tty_fd = GEC_6818_TTY_Init(TTY0_NAME, BAUDRATE);
    if (tty_fd < 0) {
        printf("ZigBee serial init failed\n");
        return NULL;
    }

    while (1)
    {
        int recv_len = GEC_6818_TTY_Recv(tty_fd);
        if (recv_len > 0 && buf[0] != '\0')
        {
            char *light_ptr = strstr(buf, "Light:");
            if (light_ptr != NULL) {
                float light;
                sscanf(light_ptr, "Light:%f", &light);
                pthread_mutex_lock(&lvgl_mutex);
                char light_str[32] = {0};
                sprintf(light_str, "%.1f", light);
                lv_label_set_text(ui_Label50, light_str);
                pthread_mutex_unlock(&lvgl_mutex);
            }
        }
        usleep(100000);
    }
}
