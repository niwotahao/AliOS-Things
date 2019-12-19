/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <stdio.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <netmgr.h>

extern int lwm2m_client_main(int argc, char *argv[]) ;

static int lwm2m_client_started = 0;

static void lwm2m_client_example(void *paras)
{
    int count = 0;
    char *value[15];

    (void) paras;

    printf("nano entry here!\r\n");
    value[count] = "lwm2mclient";
    count ++;
    value[count] = "-h";
    count ++;
    value[count] = "11.158.135.221";
    count ++;
    value[count] = "-p";
    count ++;
    value[count] = "5684";
    count ++;
    value[count] = "-n";
    count ++;
    value[count] = "a1k6Tex0gDo.lwm2m_device_1";
    count ++;
    value[count] = "-x";
    count ++;
    value[count] = "PhOiCvauesPrLw4KUB4d5FMVQJZnnhXm";
    count ++;
    value[count] = "-y";
    count ++;
    value[count] = "lwm2m_device_1";
    count ++;
    value[count] = "-z";
    count ++;
    value[count] = "a1k6Tex0gDo";
    count ++;
    value[count] = "-c";
    count ++;
    value[count] = "-4";
    count ++;
    lwm2m_client_main(count, value);

}

static void wifi_service_event(input_event_t *event, void *priv_data)
{
    if (event->type != EV_WIFI) {
        return;
    }

    if (event->code != CODE_WIFI_ON_GOT_IP) {
        return;
    }

    if(!lwm2m_client_started)
    {
       aos_task_new("lwm2m_client", (void (*)(void *))lwm2m_client_example, NULL, 1024 * 8);
       lwm2m_client_started = 1;
    }

}

int application_start(int argc, char *argv[])
{
    netmgr_init();

    aos_register_event_filter(EV_WIFI, wifi_service_event, NULL);

    netmgr_start(true);

    aos_loop_run();
    return 0;
}
