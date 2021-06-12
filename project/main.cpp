#include <SFML/Graphics.hpp>
#include "map.h"
using namespace sf;
float camx=0, camy=23*32-500, buff=0;
bool beg=false, win=false;
class hero {
private:
    int k=0;
public:
    float vx,vy,now;
    FloatRect coord;
    Sprite spr;
    bool on,end;
    hero(Texture & image){
        vx=vy=0;
        now=0;
        end = false;
        spr.setTexture(image);
        spr.setTextureRect(IntRect(10,15,50,64));
        coord = FloatRect(64,32*20,50,64);
    }
    void StuckX(){
        for (int i=coord.top/32; i<(coord.top+coord.height)/32; i++)
            for (int j=coord.left/32; j<(coord.left+coord.width)/32; j++){
                if (FrameMap[i][j] != ' ' && FrameMap[i][j] != 'H' && FrameMap[i][j] != 'K'){
                    if (vx>0)
                        coord.left=j*32-coord.width;
                    if (vx<0)
                        coord.left=j*32+32;
                }
                if (FrameMap[i][j] == 'H'){
                    buff=-0.000175;
                    FrameMap[i][j]=' ';
                }
                if (FrameMap[i][j] == 'K'){
                    win=true;
                    FrameMap[i][j]=' ';
                }
            }
    }
    void StuckY(){
        for (int i=coord.top/32; i<(coord.top+coord.height)/32; i++)
            for (int j=coord.left/32; j<(coord.left+coord.width)/32; j++){
                if (FrameMap[i][j] != ' ' && FrameMap[i][j] != 'H' && FrameMap[i][j] != 'K'){
                    if (vy>=0) {
                        coord.top = i*32-coord.height;
                        vy = 0;
                        on = true;
                    }
                    if (vy<0 && k==0) {
                        coord.top = i*32+32;

                        k++;
                    }
                }
            }
        k=0;
    }
    void checkup(float timer){
        if (!end) {
            coord.left += vx * timer;
            StuckX();
            if (!on)
                vy = vy + 0.0000000005 * timer;
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
int main() {
    RenderWindow scrn(VideoMode(500,500), "Game");
    Image heroim, evilim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");
    heroim.createMaskFromColor(Color(229, 159, 159));
    evilim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\evil.png");
    evilim.createMaskFromColor(Color(255, 255, 255));
    Image block1;
    block1.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\Industrial.png");
    block1.createMaskFromColor(Color(255, 255, 255));
    Texture texture, texture1;
    texture.loadFromImage(heroim);
    texture1.loadFromImage(evilim);
    Texture t1;
    t1.loadFromImage(block1);
    Sprite bs1;
    bs1.setTexture(t1);
    hero h(texture);
    enemy evil(texture1);
    Clock tik;
    Font font,font2;
    font.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\font.TTF");
    font2.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\begin.TTF");
    Text losttxt("You lost\n Unlucky:(",font, 50);
    losttxt.setColor(Color::White);
    losttxt.setStyle(Text::Bold);
    losttxt.setPosition(h.coord.left,h.coord.left);
    Text wtxt("You WON!?\n o_O\n   Gtatz!:)",font, 50);
    wtxt.setColor(Color::White);
    wtxt.setStyle(Text::Bold);
    wtxt.setPosition(h.coord.left,h.coord.left);
    Text txt("Your task is to pick up the dollar\n on the top of the map\n good luck:)\n\n\n\n\n\n\n\n\n\n\n\n\n(P.S. press Enter)",font2, 20);
    txt.setColor(Color::Black);
    txt.setStyle(Text::Bold);
    txt.setPosition(h.coord.left,h.coord.left);
    while (scrn.isOpen()){
        float timer = tik.getElapsedTime().asMicroseconds();
        tik.restart();
        Event ev;
        while (scrn.pollEvent(ev)){
            if (ev.type == Event::Closed)
            scrn.close();
        }
        scrn.setActive();
        if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)){
            h.vx=0.0002;
        }
        if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)){
            h.vx=-0.0002;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space ) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)){
            if (h.on){
                h.vy=-0.0002+buff;
                h.on = false;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)){
            beg=true;
        }
        if (!beg){
            scrn.clear(Color::White);
            scrn.draw(txt);
            scrn.display();
        }
        if (beg){
            if (!win){
                h.checkup(timer);
                evil.checkup(timer);
                if ((h.coord.left>250) && (h.coord.left<36*32-250))
                    camx = h.coord.left - 500/2;
                if (h.coord.top<=23*32-250)
                    camy = h.coord.top - 500/2;
                scrn.clear(Color::Cyan);
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
                        if (FrameMap[i][j] == 'E')
                            bs1.setTextureRect(IntRect(128,0,32,32));
                        if (FrameMap[i][j] == 'F')
                            bs1.setTextureRect(IntRect(160,0,32,32));
                        if (FrameMap[i][j] == 'G')
                            bs1.setTextureRect(IntRect(192,0,32,32));
                        if (FrameMap[i][j] == 'H')
                            bs1.setTextureRect(IntRect(224, 0, 18, 18));
                        if (FrameMap[i][j] == 'K')
                            bs1.setTextureRect(IntRect(244, 0, 24, 24));
                        if (FrameMap[i][j] == ' ')
                            continue;
                        bs1.setPosition(j*32 - camx,i*32-camy);
                        scrn.draw(bs1);
                    }
                scrn.draw(evil.spr);
                scrn.draw(h.spr);
                if (h.coord.intersects(evil.coord)){
                    if (evil.living) {
                        if (h.vy > 0) {
                            evil.vx = 0;
                            evil.living = false;
                            h.vy = -0.00035;
                            h.on = false;
                        } else {
                            scrn.clear(Color(255, 0, 0));
                            evil.vx=0;
                            h.end = true;
                            scrn.draw(losttxt);
                        }
                    }
                }
                scrn.display();
            }
            if (win){
                scrn.clear(Color::Blue);
                scrn.draw(wtxt);
                scrn.display();
            }
        }
    }
    return 0;
}
