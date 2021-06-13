#ifndef PROJECT_VOIDS_H
#define PROJECT_VOIDS_H
#endif

#include <SFML/Graphics.hpp>

using namespace sf;
float camx = 0, camy = 23 * 32 - 500;

class hero {
private:
    int k = 0;
public:
    float vx, vy, now, buff, g;
    FloatRect coord;
    Sprite spr;
    bool on, end, win;

    hero(Texture &image) {
        buff = 0;
        vx = vy = 0;
        g = 0.0000000005;
        now = 0;
        win = false;
        end = false;
        spr.setTexture(image);
        spr.setTextureRect(IntRect(10, 15, 50, 64));
        coord = FloatRect(64, 32 * 20, 50, 64);
    }

    void StuckX() {
        for (int i = coord.top / 32; i < (coord.top + coord.height) / 32; i++)
            for (int j = coord.left / 32; j < (coord.left + coord.width) / 32; j++) {
                if (FrameMap[i][j] != ' ' && FrameMap[i][j] != 'H' && FrameMap[i][j] != 'K') {
                    if (vx > 0)
                        coord.left = j * 32 - coord.width;
                    if (vx < 0)
                        coord.left = j * 32 + 32;
                }
                if (FrameMap[i][j] == 'H') {
                    buff = -0.000175;
                    FrameMap[i][j] = ' ';
                }
                if (FrameMap[i][j] == 'K') {
                    win = true;
                    FrameMap[i][j] = ' ';
                }
            }
    }

    void StuckY() {
        for (int i = coord.top / 32; i < (coord.top + coord.height) / 32; i++)
            for (int j = coord.left / 32; j < (coord.left + coord.width) / 32; j++) {
                if (FrameMap[i][j] != ' ' && FrameMap[i][j] != 'H' && FrameMap[i][j] != 'K') {
                    if (vy >= 0) {
                        coord.top = i * 32 - coord.height;
                        vy = 0;
                        on = true;
                    }
                    if (vy < 0 && k == 0) {
                        coord.top = i * 32 + 32;
                        k++;
                    }
                }
            }
        k = 0;
    }

    void checkup(float timer) {
        if (!end) {
            coord.left += vx * timer;
            StuckX();
            if (!on)
                vy = vy + g * timer;
            coord.top += vy * timer;
            on = false;
            StuckY();
            now += 0.00001 * timer;
            if (now > 4)
                now -= 4;
            if (vx > 0)
                spr.setTextureRect(IntRect(10 + 50 * int(now), 15, 50, 64));
            if (vx < 0)
                spr.setTextureRect(IntRect(60 + 50 * int(now), 15, -50, 64));
            spr.setPosition(coord.left - camx, coord.top - camy);
            vx = 0;
        }
    }
};