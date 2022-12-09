#include "com_nana_uLCDInterface.h"
#include "ulcd.h"
#include <cstdint>
#include <iostream>

JNIEXPORT jboolean JNICALL Java_com_nana_uLCDInterface_internalWriteImageToULCD (JNIEnv * env, jclass java_class, jint sector_start, jobjectArray img) {
    gpioInitialise();
    uLCD_4DGL uLCD;

    uLCD.baudrate(115200);

    int height = env->GetArrayLength(img);
    int width  = env->GetArrayLength((jshortArray) env->GetObjectArrayElement(img, 0));

    uint32_t sector_address = static_cast<uint32_t>(sector_start);

    printf("init uLCD media\n");

    uLCD.media_init();

    printf("media initialized. Setting sector address...\n");
    uLCD.set_sector_address(
        ((sector_address >> 16) & 0xFFFF), 
        ((sector_address >>  0) & 0xFFFF)
    );

    printf("set sector address %x\n", sector_address);

    // for (int row = 0; row < height; row++) {
    //     printf("checking row widths: %d", row);
    //     if (env->GetArrayLength((jshortArray) env->GetObjectArrayElement(img, row)) != width) {
    //         return static_cast<jboolean>(false);
    //     printf(" done\n");
    //     }
    // }

    printf("writing metadata...");
    // uLCD.write_word(0x0);
    // uLCD.write_word(0x0);
    uLCD.write_word(width);
    uLCD.write_word(height);
    uLCD.write_word(0x0F);
    printf("metadata written\n");


    // printf("Progress: ");
    // fflush(stdout);

    std::cout << "Progress: " << std::flush;

    for (int row = 0; row < height; row++) {
        // printf(".");
        // fflush(stdout);
        std::cout << std::endl;
        for (int col = 0; col < width; col++) {
            printf("writing pixel: %d %d", row, col);
            // std::cout << "." << std::flush;
            jshort pixel_data = (
                    ((jshort*)      env->GetShortArrayElements(
                    (jshortArray) env->GetObjectArrayElement(img, row),
                                  nullptr
                ))[col]);
            if (uLCD.write_word(static_cast<int>(pixel_data)) < 1) {
                col--;
                printf(" failed. Retrying...\n");
                fflush(stdout);
            }
            printf(" done\n");
        }
    }
    // printf("|\nCompleted.");
    std::cout << std::endl << "Completed." << std::endl;

    printf("flushing media");
    uLCD.flush_media();
    printf("returning true.\n");
    return static_cast<jboolean>(true);
}