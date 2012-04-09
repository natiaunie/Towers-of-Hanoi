#ifndef BOARD_H
#define BOARD_H
#include "Disk.h"
#include "mystack.h"
#include "myqueue.h"
#include <fstream>
#include <cstdlib>


using namespace std;


class Board
{
    public:
        Board(int size);
        void displayMove(Disk &d, string &s);
        void test();
        void startGame(char c);

        //Stack Functions
        Disk createDisk(stack<Disk> &stk, stack<Disk> &temp, int size);
        void oddGame();
        void evenGame();
        bool checkStack(char peg);
        void moveLeft(char &c);
        void moveRight(char &c);
        void moveDiskLeft(char pegArray[], int d);
        void moveDiskRight(char pegArray[], int d);
        void evenMoveSequence(char pegArray[], ofstream &outfile);
        void oddMoveSequence(char pegArray[], ofstream &outfile);


        //Queue Functions
        Disk qcreateDisk(queue<Disk> &stk, queue<Disk> &tmp, int size);
        void qoddGame();
        void qevenGame();
        bool checkQueue(char peg);
        void qmoveLeft(char &c);
        void qmoveRight(char &c);
        void qmoveDiskLeft(char pegArray[], int d);
        void qmoveDiskRight(char pegArray[], int d);
        void qevenMoveSequence(char pegArray[], ofstream &outfile);
        void qoddMoveSequence(char pegArray[], ofstream &outfile);

    protected:

    private:
        stack<Disk> start, temp, end;
        queue<Disk> qstart, qtemp, qend;
        int disks, lastDisk, totalMoves;
        int parity;     // 0 for even, 1 for odd

};

#endif // BOARD_H
