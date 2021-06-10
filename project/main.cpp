#include <SFML/Graphics.hpp>

using namespace sf;

int zemlya=400;
const int hm = 11;
const int lm = 36;

String  FrameMap[hm] {
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
"A                             A    A",
"A                             A    A",
"A                            A     A",
"A                           A      A",
"A                          A       A",
"A                         A        A",
"A                        A         A",
"A                                  A",
"A                                  A",
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
};

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
        spr.setTextureRect(IntRect(10,15,50,65));
        coord = FloatRect(0,zemlya+65,50,65);
    }

    void checkup(float timer){
        coord.left += vx*timer;
        if (!on)
            vy=vy+0.0000000005*timer;
        coord.top += vy*timer;
        if (coord.top > zemlya - coord.height) {
            coord.top = zemlya - coord.height;
            vy = 0;
            on = true;
        }
        else
            on = false;
        now += 0.00001*timer;
        if (now > 4)
            now -= 4;
        if (vx>0)
            spr.setTextureRect(IntRect(10+50*int(now),15,50,65));
        if (vx<0)
            spr.setTextureRect(IntRect(60+50*int(now),15,-50,65));
        spr.setPosition(coord.left,coord.top);
        vx=0;
    }

};


int main() {
    RenderWindow scrn(VideoMode(500,500), "Game");

    Image heroim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");

    Texture texture;
    texture.loadFromImage(heroim);

    hero h(texture);

    RectangleShape block;

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
        scrn.clear(Color::White);
        for (int i=0; i<hm; i++)
            for (int j=0; j<lm; j++){
                if (FrameMap[i][j] == 'A')
                    block.setFillColor(Color::Black);
                block.setSize({32.0,32.0});
                if (FrameMap[i][j] == ' ')
                    continue;
                block.setPosition(j*32,i*32);
                scrn.draw(block);
            }
        scrn.draw(h.spr);
        scrn.display();
    }
    return 0;
}
