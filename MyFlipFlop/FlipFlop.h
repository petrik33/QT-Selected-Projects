#ifndef FLIPFLOP_H
#define FLIPFLOP_H


class FlipFlop
{
public:
    FlipFlop();
    void startGame();
    bool isFinished();
    void reCalc(int r, int c);
    bool getItem(int i, int j) const;
    void restartGame();
private:
    bool table [4][4];
    bool cpyTable[4][4];
};

#endif // FLIPFLOP_H
