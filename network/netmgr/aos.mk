NAME := netmgr

$(NAME)_MBINS_TYPE := kernel
$(NAME)_VERSION := 1.0.1
$(NAME)_SUMMARY := network manager manages different types of RF.
$(NAME)_SOURCES-y := src/netmgr.c

#default gcc
ifeq ($(COMPILER),)
$(NAME)_CFLAGS-y      += -Wall -Werror
else ifeq ($(COMPILER),gcc)
$(NAME)_CFLAGS-y      += -Wall -Werror
endif

ifeq (y,$(AOS_NET_WITH_CELLULAR))
GLOBAL_DEFINES-y += NET_WITH_CELLULAR
$(NAME)_SOURCES-y += hal/cellular.c
$(NAME)_SOURCES-y += src/netmgr_cellular.c
$(NAME)_INCLUDES-y += ../include/hal/
endif

AOS_NET_WITH_WIFI ?= y
ifeq (y,$(AOS_NET_WITH_WIFI))
$(NAME)_SOURCES-y += src/netmgr_wifi.c
GLOBAL_DEFINES-y += NET_WITH_WIFI
$(NAME)_SOURCES-y += hal/wifi.c
endif

ifeq (y,$(AOS_NET_WITH_BLANK))
$(NAME)_SOURCES-y += hal/net.c
$(NAME)_SOURCES-y += src/netmgr_net.c
$(NAME)_INCLUDES-y += ../include/hal/
endif

ifeq (y,$(pvtest))
GLOBAL_DEFINES-y += PREVALIDATE_TEST
endif

$(NAME)_COMPONENTS-y += kv osal_aos yloop

$(NAME)_INCLUDES-y += include

GLOBAL_DEFINES-y += AOS_NETMGR
