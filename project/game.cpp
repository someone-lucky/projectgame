#include <SFML/Graphics.hpp>
#include "map.h"
#include "hero.h"
#include "enemy.h"
using namespace sf;
bool beg=false;
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
                h.vy=-0.0002+h.buff;
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
            if (!h.win){
                h.checkup(timer);
                evil.checkup(timer);
                if ((h.coord.left>250) && (h.coord.left<36*32-250))
                    camx = h.coord.left - 250;
                if (h.coord.top<=23*32-250)
                    camy = h.coord.top - 250;
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
            if (h.win){
                scrn.clear(Color::Blue);
                scrn.draw(wtxt);
                scrn.display();
            }
        }
    }
    return 0;
}
