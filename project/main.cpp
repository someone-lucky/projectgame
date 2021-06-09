#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    RenderWindow scrn(VideoMode(500,500), "Game");
    Image heroim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");

    Texture hero;
    hero.loadFromImage(heroim);

    float now=0;

    Sprite h;
    h.setTexture(hero);
    h.setTextureRect(IntRect(10,15,50,65));
    h.setPosition(50,100);
    while (scrn.isOpen()){
        //Event ev;
        //while (scrn.pollEvent(ev)){
        //    if (ev.type == Event::Closed);
        //    scrn.close();
        //}
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            h.move(0.1,0);
            now += 0.005;
            if (now > 4)
                now -= 4;
            h.setTextureRect(IntRect(10+50*int(now),15,50,65));
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            h.move(-0.1,0);
            now += 0.005;
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
