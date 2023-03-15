#include "gempuzzle.h"
#include "qmath.h"
#include <QRandomGenerator>

GemPuzzle::GemPuzzle(){
    startGame();
}

void GemPuzzle::startGame(){
    QRandomGenerator *rnd = QRandomGenerator::global();
    for(auto x = 0; x < 4; x++)
    {
        for(auto y = 0; y < 4; y++)
        {
            table[x][y] = x * 4 + y + 1;
        }
    }
    emptyX = 3;
    emptyY = 3;
    int randomMoves = 133;
    do
    {
        for(auto i = 0; i < randomMoves; i++)
        {
            int moveX,moveY;
            do
            {
                int randomDirection = rnd->bounded(4);//One of 4 directions
                float randomAngle = 90 * randomDirection;// gives 0, 90, 180 or 270 angle
                randomAngle = qDegreesToRadians(randomAngle); // convert to radians
                moveX = round(cos(randomAngle)); // so is always -1, 0, or 1
                moveY = round(sin(randomAngle)); // same here
            }
            while(moveCell(emptyX+moveX,emptyY+moveY));//Failed Movement is tried again
        }
        //Move The Empty In The corner
        for(int i = emptyX; i < 4; i++)
        {
           moveCell(emptyX+1,emptyY);
        }

        for(int i = emptyY; i < 4; i++)
        {
            moveCell(emptyX,emptyY+1);
        }
    }
    while(isFinished());//Imagine having the finished example in the end :(

    //Save Table
    for(auto x = 0; x < 4; x++)
    {
        for(auto y = 0; y < 4; y++)
        {
            copyTable[x][y] = table[x][y];
        }
    }
}

void GemPuzzle::restartGame(){
    for(auto x = 0; x < 4; x++)
    {
        for(auto y = 0; y < 4; y++)
        {
            table[x][y] = copyTable[x][y];
        }
    }
    emptyX = 3;
    emptyY = 3;
    movesNumber = 0;
}

bool GemPuzzle::isFinished() const{
    for(auto x = 0; x < 4; x++)
    {
        for(auto y = 0; y < 4; y++)
        {
            if(table[x][y] != x * 4 + y + 1)
            {
                return false;
            }
        }

    }
    return true;
}

int GemPuzzle::getCell(int x, int y) const{
    return table[x][y];
}

int GemPuzzle::getEmptyX() const{
    return emptyX;
}

int GemPuzzle::getEmptyY() const{
    return emptyY;
}

int GemPuzzle::getMovesNumber() const{
    return movesNumber;
}

void GemPuzzle::setCell(int x, int y, int val){
    table[x][y] = val;
}

void GemPuzzle::setEmptyCell(int x, int y){
    table[x][y] = 16;
    emptyX = x;
    emptyY = y;
}

bool GemPuzzle::moveCell(int x, int y){
    if(x >= 4 || x < 0 || y >= 4 || y < 0)
    {
        return false;
    }
    int moveDistance = abs(x - emptyX) + abs(y - emptyY);
    //Trying to move empty or inappropriate cell
    if(moveDistance != 1)
    {
        return false;
    }
    setCell(emptyX,emptyY,getCell(x,y));
    setEmptyCell(x,y);
    return true;
}

bool GemPuzzle::moveCellInGame(int x, int y){
    if(moveCell(x,y))
    {
        movesNumber++;
        return true;
    }
    else
    {
        return false;
    }
}

