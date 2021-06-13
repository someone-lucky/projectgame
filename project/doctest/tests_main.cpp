#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../herotest.h"
#include "../enemy.h"
float timer;

TEST_CASE("Checkup run tests: moving") {
    Image heroim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");
    heroim.createMaskFromColor(Color(229, 159, 159));
    Texture texture;
    texture.loadFromImage(heroim);
    hero hero(texture);
    hero.vx = 10;
    timer = 10;
    hero.coord = FloatRect(64,640,50,64);
    hero.checkup(timer);
    REQUIRE(hero.coord.left == 164);
    REQUIRE(hero.coord.left != 163);
    hero.vx = -7;
    hero.checkup(timer);
    REQUIRE(hero.coord.left == 94);
    REQUIRE(hero.coord.left != 163);
    hero.vy = -7;
    hero.checkup(timer);
    REQUIRE(hero.coord.left == 94);
    REQUIRE(hero.coord.top == 570);
    REQUIRE(hero.coord.top != 480);
    hero.vx = 3;
    hero.vy = -7;
    hero.checkup(timer);
    REQUIRE(hero.coord.left == 124);
    REQUIRE(hero.coord.top == 500);
    REQUIRE(hero.coord.top != 480);
    REQUIRE(hero.coord.left != 70);
}
TEST_CASE("Checkup run tests: gravity") {
    Image heroim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");
    heroim.createMaskFromColor(Color(229, 159, 159));
    Texture texture;
    texture.loadFromImage(heroim);
    hero hero(texture);
    hero.vx = 10;
    hero.vy = -10;
    hero.g = 0.5;
    hero.on = false;
    timer = 10;
    hero.coord = FloatRect(64,640,50,64);
    hero.checkup(timer);
    REQUIRE(hero.coord.left == 164);
    REQUIRE(hero.coord.top == 590);  // 640 - 100 = 540, но учитывая гравитацию +50 = 590 - верно!
    REQUIRE(hero.coord.top != 480);
    REQUIRE(hero.coord.left != 70);
    hero.vy = -5;
    hero.g = 0.5;
    hero.on = false;
    hero.checkup(timer);
    REQUIRE(hero.coord.top == 590);  // 590 - 50 = 540, но учитывая гравитацию +50 = 590 - верно! - в итоге не сдвинулся
    REQUIRE(hero.coord.top != 480);
    hero.coord = FloatRect(64,640,50,64);
    hero.vy = -5;
    for (int i=0; i<30; i++){
        hero.g = 0.5;
        timer = 1;
        hero.on = false;
        hero.checkup(timer);
    }
    REQUIRE(hero.coord.top == 640);
    REQUIRE(hero.on);
}
TEST_CASE("Checkup collision tests") {
    Image heroim;
    heroim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\main.png");
    heroim.createMaskFromColor(Color(229, 159, 159));
    Texture texture;
    texture.loadFromImage(heroim);
    hero hero(texture);
    hero.coord = FloatRect(64,640,50,64);
    for (int i=0; i<100; i++){
        hero.vx = 10;
        timer = 1;
        hero.checkup(timer);
    }
    REQUIRE(hero.coord.left != 1064);
    for (int i=0; i<50; i++){
        hero.vy = -10;
        timer = 1;
        hero.checkup(timer);
    }
    REQUIRE(hero.coord.top != 140);
    hero.coord = FloatRect(64,650,50,64);
    hero.checkup(timer);
    REQUIRE(hero.coord.top == 640);
}
TEST_CASE("Checkup enemy tests") {
    Image evilim;
    evilim.loadFromFile("C:\\Users\\66236\\CLionProjects\\projectgame\\project\\evil.png");
    evilim.createMaskFromColor(Color(229, 159, 159));
    Texture texture1;
    texture1.loadFromImage(evilim);
    enemy evil(texture1);
    evil.living = true;
    evil.vx = 10;
    timer = 10;
    evil.coord = FloatRect(64,640,45, 38);
    evil.checkup(timer);
    REQUIRE(evil.coord.left == 164);
    REQUIRE(evil.coord.left != 163);
    evil.vx = -7;
    evil.checkup(timer);
    REQUIRE(int(evil.coord.left) == 94);
    REQUIRE(evil.coord.left != 163);
    evil.checkup(timer);
    REQUIRE(int(evil.coord.left) == 94);
    evil.vx = 3;
    evil.checkup(timer);
    REQUIRE(int(evil.coord.left) == 124);
    REQUIRE(evil.coord.left != 70);
    evil.vx = 3;
    evil.checkup(timer);
    REQUIRE(evil.vx == float(0.0002));
    evil.coord = FloatRect(500,640,45, 38);
    for (int i=0; i<50; i++){
        evil.vx = -10;
        timer = 1;
        evil.checkup(timer);
    }
    REQUIRE(evil.coord.top != 140);
    REQUIRE(evil.vx == float(0.0002));
}