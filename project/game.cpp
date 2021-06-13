#include <SFML/Graphics.hpp>
#include "hero.h"
#include "enemy.h"

using namespace sf;
//! Переменная, отвечающая за начало игры

bool beg = false;

//! Основная функция игры
/*! В данной функции описана сама игра, в том числе взаимодествие персонажей между собой и игрока
 * с главным героем, а также отрисовку персонажей и саму карту. Она отвечает за старт и конец игры */
int main() {
    RenderWindow scrn(VideoMode(500, 500), "Game");
/**
@code
    Image heroim, evilim;
@endcode
 */
//! Изображения персонажей.
/*! Переменные, в которых содержится изображения главного героя и противника */
    Image heroim, evilim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");
    heroim.createMaskFromColor(Color(229, 159, 159));
    evilim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\evil.png");
    evilim.createMaskFromColor(Color(255, 255, 255));
/**
@code
    Image block1;
@endcode
*/
//! Изображения блоков карты.
/*! Переменная, в которых содержится изображения объектов карты */
    Image block1;
    block1.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\Industrial.png");
    block1.createMaskFromColor(Color(255, 255, 255));
/**
@code
    Texture texture, texture1;
@endcode
*/
//! Текстуры персонажей.
/*! Переменные, в которых загружаются изображения главного героя и противника */
    Texture texture, texture1;
    texture.loadFromImage(heroim);
    texture1.loadFromImage(evilim);
/**
@code
    Texture t1;
@endcode
*/
//! Текстуры блоков карты.
/*! Переменные, в которых загружаются изображения объектов карты */
    Texture t1;
    t1.loadFromImage(block1);
/**
@code
    Sprite bs1;
@endcode
*/
//! Спрайт блоков карты.
/*! Переменные, в которых загружаются текстуры объектов карты, с ним в основном уже и
 * работают в коде */
    Sprite bs1;
    bs1.setTexture(t1);
/**
@code
    hero h(texture);
    enemy evil(texture1);
@endcode
*/
//! Игрок и враг.
/*! Основные персонажы, описанные в соответствующих классах */
    hero h(texture);
    enemy evil(texture1);
    /**
   @code
       Clock tik;
   @endcode
   */
//! Время с начала игры.
    Clock tik;
/**
@code
    Font font, font2;
@endcode
*/
//! Два вида шрифвтов для текстов в игре.
    Font font, font2;
    font.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\font.TTF");
    font2.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\begin.TTF");
/**
@code
    Text losttxt("You lost\n Unlucky:(", font, 50);
@endcode
*/
//! Текст, который выводится при проигрыше.
    Text losttxt("You lost\n Unlucky:(", font, 50);
    losttxt.setColor(Color::White);
    losttxt.setStyle(Text::Bold);
    losttxt.setPosition(h.coord.left, h.coord.left);
/**
@code
    Text wtxt("You WON!?\n o_O\nGtatz!:)", font, 50);
@endcode
*/
//! Текст, который выводится при победе.
    Text wtxt("You WON!?\n o_O\nGtatz!:)", font, 50);
    wtxt.setColor(Color::White);
    wtxt.setStyle(Text::Bold);
    wtxt.setPosition(h.coord.left, h.coord.left);
/**
@code
    Text txt("...:)", font2, 20);
@endcode
*/
//! Текст, который выводится при старте игры.
    Text txt(
            "Your task is to pick up the dollar\n on the top of the map\n good luck:)\n\n\n\n\n\n\n\n\n\n\n\n\n(P.S. press Enter)",
            font2, 20);
    txt.setColor(Color::Black);
    txt.setStyle(Text::Bold);
    txt.setPosition(h.coord.left, h.coord.left);
    while (scrn.isOpen()) {
/**
@code
    float timer = tik.getElapsedTime().asMicroseconds();
@endcode
*/
//! Счетчик времени, который измеряется в милисикундах
/*! getElapsedTime() - позволяет показывать время от его рестарта*/
        float timer = tik.getElapsedTime().asMicroseconds();
        tik.restart();
/**
@code
    Event ev;
@endcode
*/
//! Определяет системные события и его параметры
        Event ev;
        while (scrn.pollEvent(ev)) {
            if (ev.type == Event::Closed)
                scrn.close();
        }
        scrn.setActive();
        if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right)) {  //в данной части описывается считывание клавиш
            h.vx = 0.0002;                                                                              // и что проиходит при их нажатии
        }
        if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
            h.vx = -0.0002;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::W) ||
            Keyboard::isKeyPressed(Keyboard::Up)) {
            if (h.on) {
                h.vy = -0.0002 + h.buff;
                h.on = false;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space)) {
            beg = true;
        }
        if (!beg) {
            scrn.clear(Color::White);
            scrn.draw(txt);
            scrn.display();
        }
        if (beg) {
            if (!h.win) {
                h.checkup(timer);
                evil.checkup(timer);
                if ((h.coord.left > 250) && (h.coord.left < 36 * 32 -
                                                            250))  // идея с camx и camy была позаимствована, т.к. не смог нормально реализовать свою задумку
                    camx = h.coord.left - 250;
                if (h.coord.top <= 23 * 32 - 250)
                    camy = h.coord.top - 250;
                scrn.clear(Color::Cyan);
                for (int i = 0; i < hm; i++)  //отрисовка карты
                    for (int j = 0; j < lm; j++) {
                        if (FrameMap[i][j] == 'A')
                            bs1.setTextureRect(IntRect(64, 0, 32, 32));
                        if (FrameMap[i][j] == 'B')
                            bs1.setTextureRect(IntRect(0, 0, 32, 32));
                        if (FrameMap[i][j] == 'C')
                            bs1.setTextureRect(IntRect(96, 0, 32, 32));
                        if (FrameMap[i][j] == 'D')
                            bs1.setTextureRect(IntRect(32, 0, 32, 32));
                        if (FrameMap[i][j] == 'E')
                            bs1.setTextureRect(IntRect(128, 0, 32, 32));
                        if (FrameMap[i][j] == 'F')
                            bs1.setTextureRect(IntRect(160, 0, 32, 32));
                        if (FrameMap[i][j] == 'G')
                            bs1.setTextureRect(IntRect(192, 0, 32, 32));
                        if (FrameMap[i][j] == 'H')
                            bs1.setTextureRect(IntRect(224, 0, 18, 18));
                        if (FrameMap[i][j] == 'K')
                            bs1.setTextureRect(IntRect(244, 0, 24, 24));
                        if (FrameMap[i][j] == ' ')
                            continue;
                        bs1.setPosition(j * 32 - camx, i * 32 - camy);
                        scrn.draw(bs1);
                    }
                scrn.draw(evil.spr);
                scrn.draw(h.spr);
                if (h.coord.intersects(evil.coord)) {  //взаимодействие персонажей
                    if (evil.living) {
                        if (h.vy > 0) {
                            evil.vx = 0;
                            evil.living = false;
                            h.vy = -0.00035;
                            h.on = false;
                        } else {
                            scrn.clear(Color(255, 0, 0));
                            evil.vx = 0;
                            h.end = true;
                            scrn.draw(losttxt);
                        }
                    }
                }
                scrn.display();
            }
            if (h.win) {
                scrn.clear(Color::Blue);
                scrn.draw(wtxt);
                scrn.display();
            }
        }
    }
    return 0;
}
