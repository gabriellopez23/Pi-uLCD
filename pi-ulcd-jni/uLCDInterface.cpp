#include "com_nana_uLCDInterface.h"
#include "ulcd.h"
#include <cstdint>

JNIEXPORT jboolean JNICALL Java_com_nana_uLCDInterface_internal_writeImageToULCD (JNIEnv * env, jclass java_class, jint sector_start, jobjectArray img) {
    uLCD_4DGL uLCD;

    int height = env->GetArrayLength(img);
    int width  = env->GetArrayLength((jshortArray) env->GetObjectArrayElement(img, 0));

    uint32_t sector_address = static_cast<uint32_t>(sector_start);

    uLCD.media_init();
    uLCD.set_sector_address(
        ((sector_address >> 16) & 0xFFFF), 
        ((sector_address >>  0) & 0xFFFF)
    );

    for (int row = 0; row < height; row++) {
        if (env->GetArrayLength((jshortArray) env->GetObjectArrayElement(img, row)) != width) {
            return static_cast<jboolean>(false);
        }
    }

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            jshort pixel_data = (
                    ((jshort*)      env->GetShortArrayElements(
                    (jshortArray) env->GetObjectArrayElement(img, row),
                                  nullptr
                ))[col]);
            uLCD.write_byte(static_cast<int>(pixel_data));
        }
    }

    uLCD.flush_media();

    return static_cast<jboolean>(true);
}