/**
  * MainWindow
  *
  * @author     Jakub Jochlík - xjochl00
  *
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QSpinBox>
#include <QLabel>
#include <QPainter>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "stone.h"
using namespace std;


#define MAXIMUM 12
#define ICONSIZE 62
#define STARTINGSCORE 2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QPushButton *field_button[MAXIMUM][MAXIMUM];    //used as place for the stones
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * Get size of board
     *
     * @return      size of board as int
     */
    int getBoardSize();

    /**
     * @brief setStone
     * @param button        button to be changed
     * @param stone         stone wich is being "connected" to the button
     */
    void setStone(QPushButton *button, Stone* stone);

    /**
     * Display actual score
     */
    void setLCD();

private:
    Ui::MainWindow *ui;
    Board* playfield;

    /**
     * Start up the game
     */
    void start(int size);

    /**
     * renders playboard
     */
    void renderPlayboard();

    /**
     * sets icon onto passed button
     *
     * @param button    button wich is gonna recive the icon
     * @param img       Img to be used as icon
     */
    void setIcon(QPushButton *button, const char* imgPath);

    /**
     * swap players - swap icon at displayPlayerButton
     *
     * @param display           Display button
     */
    void swapDisplayPlayerButton(QPushButton *display);

    /**
     * check, if next plazer have any turns avilable, if not, skip his turn
     *
     * @return          True if there are turns avilable, false otherwise
     */
    bool canCurrentPlayerPlay();

    /**
     * Tells wich player won and quit the game/show startup menu
     */
    void gameOver();

    /**
     * Hide field buttons after game ends
     */
    void hideButtons();

    /**
     * Hide panels beside and above the game - also i accidentally swaped horizontal and vertical terms so... yeah...
     */
    void hideStart();

    /**
     * Set enemy
     */
    void setEnemy();

    /**
     * set difficulty
     */
    void setDifficulty();

    /**
     * Load data and set gui acording to them
     *
     * @param size       size of board
     */
    void loadGameGui();

private slots:

    /**
     * Creates buttons for playboard and overall creates gui for game
     */
    void makePlayboard();

    /**
     * Handles clicking button in playfield
     */
    void buttonClick();

    /**
     * handles save button
     */
    void buttonSave();

    /**
     * handles load button
     */
    void buttonLoad();

    /**
     * handles undo button
     */
    void buttonUndo();

    /**
     * handles Redo button
     */
    void buttonRedo();

    /**
     * handles exit button
     */
    void buttonExit();

    /**
     * @brief whoIsEnemy
     */
    void whoIsEnemy();
};

#endif // MAINWINDOW_H
