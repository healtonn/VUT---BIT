/**
  * Stone - Class for individuall stones, tells what color they are and where
  * they are placed
  *
  * @author     Jakub Jochlík - xjochl00
  *
  */

#include "stone.h"
#include <iostream>
using namespace std;


Stone::Stone(int x, int y)
{
    _x = x;
    _y = y;
    _stone_color = empty_field;
}

Stone::~Stone(){
    delete(this);
}

stone_type Stone::getColor()
{
    return this->_stone_color;
}

void Stone::flipStone()
{
    if(_stone_color == white)
        _stone_color = black;
    else
        _stone_color = white;
}

void Stone::setColor(stone_type color){
    _stone_color = color;
}

bool Stone::isOwned2(){
    if(_stone_color == white || _stone_color == black){
        return true;
    }else{      //stone can be placed here
        return false;
    }
}

std::string Stone::toCLI(){
    switch(_stone_color){
    case white:
        return "W";
        break;
    case black:
        return "B";
        break;
    default:
        return "E";
    }
}

int Stone::toInt(){
    switch(_stone_color){
    case white:
        return 1;
        break;
    case black:
        return 2;
        break;
    default:
        return 0;
    }
}

void Stone::fromInt(int col){
    switch(col){
    case 1:
        _stone_color = white;
        break;
    case 2:
        _stone_color = black;
        break;
    default:
        _stone_color = empty_field;
    }
}
