#include "com_nana_uLCDInterface.h"
#include "ulcd.h"

JNIEXPORT jboolean JNICALL Java_com_nana_uLCDInterface_writeImageToULCD (JNIEnv * env, jclass java_class, jint sector_start, jobjectArray img) {
    return static_cast<jboolean>(false);
}