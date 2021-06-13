#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H
#endif
#include <SFML/Graphics.hpp>
using namespace sf;
//! Высота карты
const int hm = 23;
//! Длина карты
const int lm = 36;
//! Каркас карты
/*! Он представлен в виде матрицы, составленной из различных букв */
String  FrameMap[hm] {
        "A                                  A",
        "A                                  A",
        "A                                  A",
        "A                                  A",
        "A                                  A",
        "A      K                           A",
        "ADDDDDDDDDDDDDDDDDDD       D       A",
        "A                                 DA",
        "A                                  A",
        "A                                  A",
        "A                                  A",
        "A      DDDD                    DDDDA",
        "A                                  A",
        "A                                  A",
        "ADD                    D           A",
        "A                                  A",
        "A             D                    A",
        "A     D                            A",
        "A                         D        A",
        "A                                  A",
        "A                EE                A",
        "CG         G    EFF              H C",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};