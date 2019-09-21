#include <OledDisplay.h>

const int WIDTH = 128;
const int HEIGHT = 8;
const int SIZE = WIDTH * HEIGHT;

unsigned char BMP[SIZE];

void setup() {
    // set up the screen
    Screen.init();

    // create a blank image
    for (int i = 0; i < SIZE; i++) {
        BMP[i] = 0x00;
    }
}

void loop() {
    // do stuff
    drawLine(3, 16, 31, 63);
    drawRect(7, 16, 32, 32, false);
    drawRect(66, 16, 32, 32, true);

    // draw the bitmap on the screen
    Screen.draw(0, 0, 128, 8, BMP);
}

void drawPixel(int x, int y) {
    int realX = x;
    int realY = y / 8;
    int value = pow(2, (y % 8));
    BMP[realY * 128 + realX] |= value;
}

void drawLine(int x1, int y1, int x2, int y2) {
    bool yLonger = false;

    int shortLen = y2 - y1;
    int longLen = x2 - x1;
    if (abs(shortLen) > abs(longLen)) {
        int swap = shortLen;
        shortLen = longLen;
        longLen = swap;
        yLonger = true;
    }

    int incrementVal = (longLen < 0) ? -1 : 1;

    float divDiff = (shortLen == 0)
        ? longLen
        : (float)longLen / (float)shortLen;
    if (yLonger) {
        for (int i = 0; i != longLen; i += incrementVal) {
            drawPixel(x1 + (int)((float)i / divDiff), y1 + i);
        }
    } else {
        for (int i = 0; i != longLen; i += incrementVal) {
            drawPixel(x1 + i, y1 + (int)((float)i / divDiff));
        }
    }
}

void drawRect(int x, int y, int w, int h, bool fill) {
    if (fill) {
        for (int yy = y; yy < y + h; yy++)
            drawLine(x, yy, x + w, yy);
    } else {
        drawLine(x, y, x + w, y);
        drawLine(x, y, x, y + h);
        drawLine(x, y + h, x + w, y + h);
        drawLine(x + w, y, x + w, y + h);
    }
}
