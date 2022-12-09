package com.nana;

import java.awt.image.BufferedImage;
import javafx.scene.image.WritableImage;

public final class uLCDInterface {
    static {
        System.loadLibrary("pi-ulcd-jni");
    }

    public final native boolean writeImageToULCD(int sectorStart, byte[][] image);

    private interface ImageConverter {
        public int getIntColor(int row, int col);
    }

    private final <T> byte[][] convertImage(int width, int height, T imgSrc, ImageConverter converter) {
      byte[][] result = new byte[height][width * 4];

      for (int row = 0; row < height; row++) {
         for (int col = 0; col < width; col++) {
            int imgPixel = converter.getIntColor(row, col);
            result[row][col    ] = (byte) (                      0);
            result[row][col + 1] = (byte) ((imgPixel) >> 16 & 0xFF);
            result[row][col + 2] = (byte) ((imgPixel) >>  8 & 0xFF);
            result[row][col + 3] = (byte) ((imgPixel) >>  0 & 0xFF);
         }
      }
      return result;
    }

    public final byte[][] imageToRAW(BufferedImage img) {
        int width = img.getWidth();
        int height = img.getHeight();
        return convertImage(width, height, img, img::getRGB);
    }

    public final byte[][] imageToRAW(WritableImage img) {
        int width = (int) img.getWidth();
        int height = (int) img.getHeight();
        return convertImage(width, height, img, img.getPixelReader()::getArgb);
    }

    public static void main(String[] args) {
        for (int i = 0; i < args.length; i++)
            System.out.printf(args[i] + "\n");
    }
}