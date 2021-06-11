#ifndef PROJECT_HEALTHBAR_H
#define PROJECT_HEALTHBAR_H
#endif //PROJECT_HEALTHBAR_H
#include <SFML/Graphics.hpp>
#include "vector"
using namespace sf;
class HealthBar{
public:
    RectangleShape barh,bard;
    int max;
    HealthBar(){
        barh.setFillColor(Color(255,0,0));
        barh.setSize({30,100});
        bard.setFillColor(Color(0,0,0));
        max=100;
    }
    void checkup(int i){
        if (i>0)
            if (i<max)
                bard.setSize(Vector2f(30, (max-i)*70/max));
    }
    void draw(RenderWindow &scrn, FloatRect coord, float vx, float vy, float timer){
        if ((coord.left<250) || (coord.left>36*32-250)) {
            barh.setPosition(camx, camy);
            bard.setPosition(camx, camy);
        }
        else if (coord.top>23*32-250) {
            barh.setPosition(camx, camy);
            bard.setPosition(camx, camy);
        }
        else{
            barh.setPosition(camx-vx*timer, camy-vy*timer);
            //bard.setPosition(2*coord.left-camx, coord.left-camy);
        }
        scrn.draw(barh);
        scrn.draw(bard);
    }
}