#ifndef __PLAYER_UTILS_H__
#define __PLAYER_UTILS_H__

#include <stdio.h>

#define ENABLE_LOGD 1

#if ENABLE_LOGD
#define LOGD(...)  printf(__VA_ARGS__)
#else
#define LOGD(...)
#endif
#define LOGI LOGD
#define LOGE LOGD

#endif
