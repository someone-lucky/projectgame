#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    RenderWindow scrn(VideoMode(500,500), "Game");
    Image heroim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");

    Texture hero;
    hero.loadFromImage(heroim);

    Sprite h;
    h.setTexture(hero);
    h.setPosition(50,100);
    while (scrn.isOpen()){
        //Event ev;
        //while (scrn.pollEvent(ev)){
        //    if (ev.type == Event::Closed);
        //    scrn.close();
        //}
        if (Keyboard::isKeyPressed(Keyboard::Right)){
            h.move(0.5,0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)){
            h.move(-0.5,0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)){
            h.move(0,-0.5);
        }
        scrn.clear();
        scrn.draw(h);
        scrn.display();
    }
    return 0;
}
