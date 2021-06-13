#ifndef PROJECT_ENEMY_H
#define PROJECT_ENEMY_H
#endif
#include <SFML/Graphics.hpp>
using namespace sf;
class enemy {
public:
    float vx, now;
    FloatRect coord;
    Sprite spr;
    bool living;
    enemy(Texture &image) {
        vx =  0.0002;
        now = 0;
        living = true;
        spr.setTexture(image);
        spr.setTextureRect(IntRect(0, 10, 27, 38));
        coord = FloatRect(32*25, 32*20+27, 27, 38);
    }
    void StuckX(){
        for (int i=coord.top/32; i<(coord.top+coord.height)/32; i++)
            for (int j=coord.left/32; j<(coord.left+coord.width)/32; j++){
                if (FrameMap[i][j] == 'A' || FrameMap[i][j] == 'D' || FrameMap[i][j] == 'C'){
                    if (vx>0) {
                        coord.left = j * 32 - coord.width;
                    }
                    if (vx<0) {
                        coord.left = j * 32 + 32;
                    }
                }
            }
    }
    void checkup(float timer) {
        coord.left += vx * timer;
        StuckX();
        if (coord.left+coord.width >= 32*35)
            vx=-0.0002;
        if (coord.left <= 19*32)
            vx=0.0002;
        now += 0.00001 * timer;
        if (now > 4)
            now -= 4;
        if (vx > 0)
            spr.setTextureRect(IntRect( 45 * int(now), 10, 45, 38));
        if (vx < 0)
            spr.setTextureRect(IntRect(45 + 45 * int(now), 10, -45, 38));
        if (!living)
            spr.setTextureRect(IntRect(0, 0, 0, 0));
        spr.setPosition(coord.left - camx,coord.top - camy);
    }
};