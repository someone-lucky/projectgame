#ifndef PROJECT_VOIDS_H
#define PROJECT_VOIDS_H
#endif

#include <SFML/Graphics.hpp>

using namespace sf;
//! Переменные, отвечающие за движения "камеры", следящей за игроком
float camx = 0, camy = 23 * 32 - 500;

//! Класс главного героя
/*! В нем описаны взаимдоействия героя с объектами карты, физика передвижений, анимация движений и прорисовка */
class hero {
public:
//! Скорость вдоль оси Оx
    float vx;
//! Скорость вдоль оси Оy
    float vy;
//! Переменная, отвечающая за анимацию героя
    float now;
//! Добавочная скорость
/*! Её можно получить при определенных условиях во время игры */
    float buff;
//! Гравитационная переменная
    float g;
//! Содержит координаты и размеры персонажа
    FloatRect coord;
//! Содержит текстуры персонажа
    Sprite spr;
//! Переменная, показывающая на земле ли стоит персонаж
    bool on;
//! Переменная, отвечающая за проигрыш
    bool end;
//! Переменная, отвечающая за победу
    bool win;
//! Описание основного героя
/*! Его состояние при старте игры */
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
//! Функция, отвеяающая за столкновения с объектами вдоль оси Ох
/*! В данной функции рассматриваются столкновения со стенами, а также различными игровыми объектами, по типу бонусов */
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
//! Функция, отвеяающая за столкновения с объектами вдоль оси Оy
/*! В данной функции рассматриваются столкновения с потолком и полом */
    void StuckY() {
        for (int i = coord.top / 32; i < (coord.top + coord.height) / 32; i++)
            for (int j = coord.left / 32; j < (coord.left + coord.width) / 32; j++) {
                if (FrameMap[i][j] != ' ' && FrameMap[i][j] != 'H' && FrameMap[i][j] != 'K') {
                    if (vy >= 0) {
                        coord.top = i * 32 - coord.height;
                        vy = 0;
                        on = true;
                    }
                    if (vy < 0) {
                        coord.top = i * 32 + 32;
                    }
                }
            }
    }
//! Функция, отвеяающая за изменения персонажа во время игры
/*! Данная функция отвечает за передвижение, смену кадров при движении */
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