#include <SFML/Graphics.hpp>
#include "map.h"

using namespace sf;

float camx=0, camy=23*32-500;


class hero {
public:
    float vx,vy,now;
    FloatRect coord;
    Sprite spr;
    bool on;

    hero(Texture & image){
        vx=vy=0;
        now=0;
        spr.setTexture(image);
        spr.setTextureRect(IntRect(10,15,50,64));
        coord = FloatRect(64,32*20,50,64);
    }
    void StuckX(){
        for (int i=coord.top/32; i<(coord.top+coord.height)/32; i++)
            for (int j=coord.left/32; j<(coord.left+coord.width)/32; j++){
                if (FrameMap[i][j] == 'A' || FrameMap[i][j] == 'D' || FrameMap[i][j] == 'C'){
                    if (vx>0)
                        coord.left=j*32-coord.width;
                    if (vx<0)
                        coord.left=j*32+32;
                }
            }
    }
    void StuckY(){
        for (int i=coord.top/32; i<(coord.top+coord.height)/32; i++)
            for (int j=coord.left/32; j<(coord.left+coord.width)/32; j++){
                if (FrameMap[i][j] == 'B' || FrameMap[i][j] == 'C' || FrameMap[i][j] == 'D'){
                    if (vy>=0) {
                        coord.top = i*32-coord.height;
                        vy = 0;
                        on = true;
                    }
                    if (vy<0) {
                        coord.top = i*32+32;
                        vy = 0;
                    }
                }
            }
    }

    void checkup(float timer){
        coord.left += vx*timer;
        StuckX();
        if (!on)
            vy=vy+0.0000000005*timer;
        coord.top += vy*timer;
        on=false;
        StuckY();
        now += 0.00001*timer;
        if (now > 4)
            now -= 4;
        if (vx>0)
            spr.setTextureRect(IntRect(10+50*int(now),15,50,64));
        if (vx<0)
            spr.setTextureRect(IntRect(60+50*int(now),15,-50,64));
        spr.setPosition(coord.left - camx,coord.top - camy);
        vx=0;
    }

};
class enemy {
public:
    float vx, now;
    FloatRect coord;
    Sprite spr;
    bool living;

    enemy(Texture &image) {
        vx =  0;
        now = 0;
        spr.setTexture(image);
        spr.setTextureRect(IntRect(10, 15, 50, 64));
        coord = FloatRect(64, 32 * 20, 50, 64);
    }
    void StuckX(){
        for (int i=coord.top/32; i<(coord.top+coord.height)/32; i++)
            for (int j=coord.left/32; j<(coord.left+coord.width)/32; j++){
                if (FrameMap[i][j] == 'A'){
                    if (vx>0)
                        coord.left=j*32-coord.width;
                    if (vx<0)
                        coord.left=j*32+32;
                }
            }
    }

    void checkup(float timer) {
        coord.left += vx * timer;
        StuckX();
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
};


int main() {
    RenderWindow scrn(VideoMode(500,500), "Game");

    Image heroim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");
    heroim.createMaskFromColor(Color(229, 159, 159));
    Image block1;
    block1.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\Industrial.png");
    block1.createMaskFromColor(Color(255, 255, 255));

    Texture texture;
    texture.loadFromImage(heroim);
    Texture t1;
    t1.loadFromImage(block1);
    Sprite bs1,bs2,bs3,bs4;
    bs1.setTexture(t1);

    hero h(texture);

    Clock tik;

    while (scrn.isOpen()){
        float timer = tik.getElapsedTime().asMicroseconds();
        tik.restart();
        Event ev;
        while (scrn.pollEvent(ev)){
            if (ev.type == Event::Closed)
            scrn.close();
        }
        scrn.setActive();
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            h.vx=0.0002;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            h.vx=-0.0002;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            if (h.on){
                h.vy=-0.00035;
                h.on = false;
            }
        }
        h.checkup(timer);
        if ((h.coord.left>250) && (h.coord.left<36*32-250))
            camx = h.coord.left - 500/2;
        if (h.coord.top<=23*32-250)
            camy = h.coord.top - 500/2;
        scrn.clear(Color::White);
        for (int i=0; i<hm; i++)
            for (int j=0; j<lm; j++){
                if (FrameMap[i][j] == 'A')
                    bs1.setTextureRect(IntRect(64,0,32,32));
                if (FrameMap[i][j] == 'B')
                    bs1.setTextureRect(IntRect(0,0,32,32));
                if (FrameMap[i][j] == 'C')
                    bs1.setTextureRect(IntRect(96,0,32,32));
                if (FrameMap[i][j] == 'D')
                    bs1.setTextureRect(IntRect(32,0,32,32));
                if (FrameMap[i][j] == ' ')
                    continue;
                bs1.setPosition(j*32 - camx,i*32-camy);
                scrn.draw(bs1);
            }
        scrn.draw(h.spr);
        scrn.display();
    }
    return 0;
}
