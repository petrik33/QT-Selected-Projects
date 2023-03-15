#ifndef GEMPUZZLE_H
#define GEMPUZZLE_H

class GemPuzzle
{
public:
    GemPuzzle();
    void startGame();
    void restartGame();
    bool isFinished() const;
    bool moveCell(int x,int y);//Doesn't increment movesNumber
    bool moveCellInGame(int x, int y);//Increments movesNumber
    void setCell(int x, int y, int val);
    void setEmptyCell(int x, int y);
    int getEmptyX() const;
    int getEmptyY() const;
    int getMovesNumber() const;
    int getCell(int x,int y) const;
private:
    int emptyX;
    int emptyY;
    int table[4][4];
    int copyTable[4][4];
    int movesNumber;
};

#endif // GEM_PUZZLE_H
