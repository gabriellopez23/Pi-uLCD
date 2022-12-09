package com.nana;

import java.awt.image.BufferedImage;
import javafx.scene.image.WritableImage;

public final class uLCDInterface {
    static {
        System.loadLibrary("pi-ulcd-jni");
    }

    public static final native boolean writeImageToULCD(int sectorStart, byte[][] image);

    private static interface ImageConverter {
        public int getIntColor(int row, int col);
    }

    private static final <T> short[][] convertImage(int width, int height, T imgSrc, ImageConverter converter) {
        short[][] result = new short[height][width];

      for (int row = 0; row < height; row++) {
         for (int col = 0; col < width; col++) {
            int imgPixel = converter.getIntColor(row, col);
            result[row][col] = (short) ((((imgPixel >> 16) & 0x1F) << 11) 
                                      | (((imgPixel >>  8) & 0x3F) <<  5) 
                                      | (((imgPixel >>  0) & 0x1F) <<  0)
                                       );
         }
      }
      return result;
    }

    public static final short[][] imageToRAW(BufferedImage img) {
        int width = img.getWidth();
        int height = img.getHeight();
        return convertImage(width, height, img, img::getRGB);
    }

    public static final short[][] imageToRAW(WritableImage img) {
        int width = (int) img.getWidth();
        int height = (int) img.getHeight();
        return convertImage(width, height, img, img.getPixelReader()::getArgb);
    }

    public static void main(String[] args) {
        for (int i = 0; i < args.length; i++)
            System.out.printf(args[i] + "\n");
        System.out.println("Loaded library " + writeImageToULCD(0, null));
    }
}