#include "FlipFlop.h"
#include <QRandomGenerator>

FlipFlop::FlipFlop()
{
    startGame();
}

void FlipFlop::startGame()
{
    QRandomGenerator *rnd = QRandomGenerator::global();
    do {
        for (auto i = 0; i < 4; i++)
            for(auto j = 0; j < 4; j++) {
                table[i][j] = (rnd->bounded(100) >= 50);
                cpyTable[i][j] = table[i][j];
            }

    } while(isFinished());
}

void FlipFlop::restartGame()
{
            for (auto i = 0; i < 4; i++)
                for(auto j = 0; j < 4; j++) {
                    table[i][j] = cpyTable[i][j];
                }
}

bool FlipFlop::isFinished()
{
    for (auto i = 0; i < 4; i++)
        for(auto j = 0; j < 4; j++)
           if (table[i][j])
               return false;
    return true;
}

void FlipFlop::reCalc(int r, int c)
{
    for (auto i = 0; i < 4; i++)
        table[i][c] = ! table[i][c];
    for(auto j = 0; j < 4; j++)
        table[r][j] = ! table[r][j];
    table[r][c] = ! table[r][c];
}

bool FlipFlop::getItem(int i, int j) const
{
    return table[i][j];
}
