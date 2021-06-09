#include <SFML/Graphics.hpp>

using namespace sf;

int zemlya=500;

class hero {
public:
    float vx,vy,now;
    FloatRect rect;
    Sprite spr;
    bool on;

    hero(Texture & image){
        vx=vx=0;
        now=0;
        rect = FloatRect(15,15,50,70);
        spr.setTexture(image);
    }


};


int main() {
    RenderWindow scrn(VideoMode(500,500), "Game");

    Image heroim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");

    Texture hero;
    hero.loadFromImage(heroim);

    Sprite h;
    h.setTexture(hero);
    h.setTextureRect(IntRect(10,15,50,65));
    h.setPosition(50,100);

    Clock tik;

    float now=0;

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
            h.move(0.0002*timer,0);
            now += 0.00001*timer;
            if (now > 4)
                now -= 4;
            h.setTextureRect(IntRect(10+50*int(now),15,50,65));
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            h.move(-0.0002*timer,0);
            now += 0.00001*timer;
            if (now > 4)
                now -= 4;
            h.setTextureRect(IntRect(60+50*int(now),15,-50,65));
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            h.move(0,-0.1);
        }
        scrn.clear();
        scrn.draw(h);
        scrn.display();
    }
    return 0;
}
