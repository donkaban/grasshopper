#include <android/log.h>

#define TAG "[GRASSHOPPER]"
#define D_LOG(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define E_LOG(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA__ARGS__)


