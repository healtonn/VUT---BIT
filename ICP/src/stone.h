/**
  * Stone - Class for individuall stones, tells what color they are and where
  * they are placed, also contains methods to operate with stone
  *
  * @author     Jakub Jochlík - xjochl00
  *
  */
#ifndef STONE_H
#define STONE_H

class Stone;

#include <iostream>

/**
 * @brief The state enumerate deides if the field is empty or white/black
 */
enum stone_type{
    white,
    black,
    empty_field
};

class Stone
{
public:
    /**
     * Constructor for Stone
     *
     * @param x     position x
     * @param y     position y
     */
    Stone(int x, int y);

    /**
      * Destructor
      */
    ~Stone();

    /**
     * Method for flipping the stone
     */
    void flipStone();

    /**
     * Returns color of stone white/black/empty
     *
     * @return      Type of stone
     */
    stone_type getColor();

    /**
     * Sets stone to specific color
     *
     * @param color     Color to be set onto the stone
     */
    void setColor(stone_type color);

    /**
     * Checks, if there is stone in choosen place
     *
     * @return      True if stone is placed, false if emptz
     */
    bool isOwned2();

    /**
     * When text interface is used, return char as color -> W-white, B-black, E-empty_field
     */
    std::string toCLI();

    /**
     * Method needed by Board::save - "encode" color as number
     *
     * @return          integer as stone color. 0 - empty_field, 1 - white, 2 - black
     */
    int toInt();

    /**
     * contraty to toInt method
     */
    void fromInt(int col);


private:
    int _x;
    int _y;
    stone_type _stone_color;

};

#endif // STONE_H
