/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#ifndef NETMGR_H
#define NETMGR_H

#if defined(__cplusplus)
extern "C"
{
#endif

#include <stdbool.h>

#ifdef NET_WITH_WIFI
#include "netmgr_wifi.h"
#endif

enum {
    INTERFACE_WIFI,
    INTERFACE_CELLULAR,
};

#define IP_STR_SIZE 32
typedef struct netmgr_stats_s {
    bool ip_available;
    char ip[IP_STR_SIZE];
} netmgr_stats_t;

/**
 *
 * initialize netmgr module
 *
 * @return 0   initialize success
 * @return < 0 initialize fail
 */
int netmgr_init(void);

/**
 *
 * deinitialize netmgr module
 *
 * @return 0   deinitialize success
 * @return < 0 deinitialize fail
 */
void netmgr_deinit(void);

/**
 *
 * start netmgr
 *
 * @param[in] autoconfig start WiFi provision or not
 *
 * @return 0   start network interface success
 * @return < 0 start network interface fail
 */
int netmgr_start(bool autoconfig);

/**
 *
 * get netmgr stats
 *
 * @param[in]     interface interface name
 * @param[in/out] stats network interface stats
 *
 */
void netmgr_stats(int32_t interface, netmgr_stats_t *stats);

#ifdef NET_WITH_wIFI
/**
 *
 * connect to specified WiFi network with given SSID and password
 *
 * @param[in] ssid     WiFi SSID
 * @param[in] password WiFi password
 * @param[in] timeout  timeout in milliseconds
 *
 * @return 0  connect success
 * @return -1 connect param error
 * @return -2 connect timeout
 */
int32_t netmgr_connect(const char *ssid, const uint8_t *password, uint32_t timeout);
#endif

#if defined(__cplusplus)
}
#endif

#endif /* NETMGR_H */
