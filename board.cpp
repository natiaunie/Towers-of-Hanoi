#include "board.h"
#include "Disk.h"
#include <iostream>
#include "mystack.h"
#include "myqueue.h"
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

Board::Board(int size)
{
    totalMoves = 0;
    parity = size%2;
    disks = size;
    start = temp = end;
    qstart = qtemp = qend;
}

void Board::moveLeft(char &c)
{
    totalMoves++;

    switch(c)
    {
        case 'A': c = 'C';
                  end.push(start.top());
                  start.pop();
                  break;
        case 'B': c = 'A';
                  start.push(temp.top());
                  temp.pop();
                  break;
        case 'C': c = 'B';
                  temp.push(end.top());
                  end.pop();
                  break;
    }
}

void Board::moveRight(char &c)
{
    totalMoves++;

    switch(c)
    {
        case 'A': c = 'B';
                  temp.push(start.top());
                  start.pop();
                  break;
        case 'B': c = 'C';
                  end.push(temp.top());
                  temp.pop();
                  break;
        case 'C': c = 'A';
                  start.push(end.top());
                  end.pop();
                  break;
    }
}

void Board::displayMove(Disk &d, string &s)
{
    cout << d << " moves to " << s << endl;
}

Disk Board::createDisk(stack<Disk> &stk, stack<Disk> &temp, int size)
{
    Disk newDisk;
    temp.push(newDisk);
    if(size > 1)
    {
        newDisk = createDisk(stk,temp,size-1);
    }
    stk.push(temp.top());
    temp.pop();
}

void Board::test()
{
    char A = 'A';
    char B = 'B';
    char C = 'C';
    moveLeft(A);
    moveRight(A);
    moveRight(C);
    moveRight(B);
}

void Board::startGame(char c)
{
    switch(c)
    {
        case 's':
        case 'S': createDisk(start,end,disks);
                  if(parity)
                    oddGame();
                  else
                    evenGame();
                  break;
        case 'q':
        case 'Q': qcreateDisk(qstart,qend,disks);
                  if(parity)
                    qoddGame();
                  else
                    qevenGame();
                  break;
    }
}

void Board::oddGame()                                   // First disk goes left
{                                                       // Odd ordinal disks go left, even go right
    ofstream outfile ("output.txt");                    // Create output file
    outfile << "Solving for " << disks << " disks." <<endl <<endl;
    cout << "You chose " << disks << " disks." <<endl;

    char pegArray[disks+1];
    char A = 'A';
    for(int i = 1; i < disks+1; i++)
    {
        pegArray[i] = A;
    }

    oddMoveSequence(pegArray,outfile);
    while(totalMoves < (pow(2.0,disks)-1))
    {
        char location;
        if( (disks > 3) && (totalMoves < (pow(2.0,disks)-1)))
        {
            for(int i = 1; i <= disks; i++)
            {
                if((pegArray[i] != pegArray[1]) && !checkStack(pegArray[i]))
                {
                    if((i%2) == 0 )
                    {
                        location = pegArray[i];
                        moveRight(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                    else
                    {
                        location = pegArray[i];
                        moveLeft(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                }
            }
        }
        oddMoveSequence(pegArray,outfile);
    }

    outfile << "\nTotal moves were: " <<totalMoves <<endl;
    outfile.close();
    system("start output.txt");
    cout << "Total moves were: " << totalMoves <<endl;

}

void Board::evenGame()                                  // First disk goes right
{                                                       // Odd ordinal disks go right, even go left
    cout << "You chose " << disks << " disks." <<endl;
    ofstream outfile ("output.txt");                    // Create output file
    outfile << "Solving for " << disks << " disks." <<endl <<endl;

    char pegArray[disks+1];
    char A = 'A';
    for(int i = 1; i < disks+1; i++)
    {
        pegArray[i] = A;
    }

    evenMoveSequence(pegArray,outfile);

    while(totalMoves < (pow(2.0,disks)-1))
    {
        char location;
        if( (disks > 3) && (totalMoves < (pow(2.0,disks)-1)))
        {
            for(int i = 1; i <= disks; i++)
            {
                if((pegArray[i] != pegArray[1]) && !checkStack(pegArray[i]))
                {
                    if((i%2) == 0 )
                    {
                        location = pegArray[i];
                        moveLeft(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                    else
                    {
                        location = pegArray[i];
                        moveRight(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                }
            }
        }
        evenMoveSequence(pegArray,outfile);
    }

    outfile << "\nTotal moves were: " <<totalMoves <<endl;
    outfile.close();
    system("start output.txt");
    cout << "Total moves were: " << totalMoves <<endl;
}

bool Board::checkStack(char peg)
{
    switch(peg)
    {
        case 'A': return start.empty();
        case 'B': return temp.empty();
        case 'C': return end.empty();
    }
}

void Board::oddMoveSequence(char pegArray[], ofstream &outfile)
{
	moveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskRight(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
    moveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskLeft(pegArray,3);
	outfile << "Disk " << 3 << " -> " << "Peg " <<pegArray[3]<<endl;
    moveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskRight(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
	moveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
}

void Board::evenMoveSequence(char pegArray[], ofstream &outfile)
{
	moveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskLeft(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
    moveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskRight(pegArray,3);
	outfile << "Disk " << 3 << " -> " << "Peg " <<pegArray[3]<<endl;
    moveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	moveDiskLeft(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
	moveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
}

void Board::moveDiskLeft(char pegArray[], int d)
{
    char location;
	location = pegArray[d];
	moveLeft(location);
	pegArray[d] = location;
}

void Board::moveDiskRight(char pegArray[], int d)
{
    char location;
	location = pegArray[d];
	moveRight(location);
	pegArray[d] = location;
}


// Queue Functions

Disk Board::qcreateDisk(queue<Disk> &stk, queue<Disk> &tmp, int size)
{
    Disk newDisk;
    tmp.enqueue(newDisk);
    if(size > 1)
    {
        newDisk = qcreateDisk(stk,tmp,size-1);
    }
    stk.enqueue(tmp.top());
    tmp.dequeue();
}

void Board::qoddGame()                                   // First disk goes left
{                                                       // Odd ordinal disks go left, even go right
    ofstream outfile ("output.txt");                    // Create output file
    outfile << "Solving for " << disks << " disks." <<endl <<endl;
    cout << "You chose " << disks << " disks." <<endl;

    char pegArray[disks+1];
    char A = 'A';

    for(int i = 1; i < disks+1; i++)
    {
        pegArray[i] = A;
    }

    qoddMoveSequence(pegArray,outfile);
    while(totalMoves < (pow(2.0,disks)-1))
    {
        char location;
        if( (disks > 3) && (totalMoves < (pow(2.0,disks)-1)))
        {
            for(int i = 1; i <= disks; i++)
            {
                if((pegArray[i] != pegArray[1]) && !checkQueue(pegArray[i]))
                {
                    if((i%2) == 0 )
                    {
                        location = pegArray[i];
                        qmoveRight(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                    else
                    {
                        location = pegArray[i];
                        qmoveLeft(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                }
            }
        }
        qoddMoveSequence(pegArray,outfile);
    }

    outfile << "\nTotal moves were: " <<totalMoves <<endl;
    outfile.close();
    system("start output.txt");
    cout << "Total moves were: " << totalMoves <<endl;

}

void Board::qevenGame()                                  // First disk goes right
{                                                       // Odd ordinal disks go right, even go left
    cout << "You chose " << disks << " disks." <<endl;
    ofstream outfile ("output.txt");                    // Create output file
    outfile << "Solving for " << disks << " disks." <<endl <<endl;

    char pegArray[disks+1];
    char A = 'A';
    for(int i = 1; i < disks+1; i++)
    {
        pegArray[i] = A;
    }

    qevenMoveSequence(pegArray,outfile);

    while(totalMoves < (pow(2.0,disks)-1))
    {
        char location;
        if( (disks > 3) && (totalMoves < (pow(2.0,disks)-1)))
        {
            for(int i = 1; i <= disks; i++)
            {
                if((pegArray[i] != pegArray[1]) && !checkQueue(pegArray[i]))
                {
                    if((i%2) == 0 )
                    {
                        location = pegArray[i];
                        qmoveLeft(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                    else
                    {
                        location = pegArray[i];
                        qmoveRight(location);
                        pegArray[i] = location;
                        outfile << "Disk " << i << " -> " << "Peg " <<location<<endl;
                        i = disks;
                    }
                }
            }
        }
        qevenMoveSequence(pegArray,outfile);
    }

    outfile << "\nTotal moves were: " <<totalMoves <<endl;
    outfile.close();
    system("start output.txt");
    cout << "Total moves were: " << totalMoves <<endl;
}

bool Board::checkQueue(char peg)
{
    switch(peg)
    {
        case 'A': return qstart.empty();
        case 'B': return qtemp.empty();
        case 'C': return qend.empty();
    }
}

void Board::qmoveLeft(char &c)
{
    totalMoves++;
    switch(c)
    {
        case 'A': c = 'C';
                  qend.enqueue(qstart.top());
                  qstart.dequeue();
                  break;
        case 'B': c = 'A';
                  qstart.enqueue(qtemp.top());
                  qtemp.dequeue();
                  break;
        case 'C': c = 'B';
                  qtemp.enqueue(qend.top());
                  qend.dequeue();
                  break;
    }
}

void Board::qmoveRight(char &c)
{
    totalMoves++;

    switch(c)
    {
        case 'A': c = 'B';
                  qtemp.enqueue(qstart.top());
                  qstart.dequeue();
                  break;
        case 'B': c = 'C';
                  qend.enqueue(qtemp.top());
                  qtemp.dequeue();
                  break;
        case 'C': c = 'A';
                  qstart.enqueue(qend.top());
                  qend.dequeue();
                  break;
    }
}

void Board::qoddMoveSequence(char pegArray[], ofstream &outfile)
{
	qmoveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskRight(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
    qmoveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskLeft(pegArray,3);
	outfile << "Disk " << 3 << " -> " << "Peg " <<pegArray[3]<<endl;
    qmoveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskRight(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
	qmoveDiskLeft(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
}

void Board::qevenMoveSequence(char pegArray[], ofstream &outfile)
{
	qmoveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskLeft(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
    qmoveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskRight(pegArray,3);
	outfile << "Disk " << 3 << " -> " << "Peg " <<pegArray[3]<<endl;
    qmoveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
	qmoveDiskLeft(pegArray,2);
	outfile << "Disk " << 2 << " -> " << "Peg " <<pegArray[2]<<endl;
	qmoveDiskRight(pegArray,1);
	outfile << "Disk " << 1 << " -> " << "Peg " <<pegArray[1]<<endl;
}

void Board::qmoveDiskLeft(char pegArray[], int d)
{
    char location;
	location = pegArray[d];
	qmoveLeft(location);
	pegArray[d] = location;
}

void Board::qmoveDiskRight(char pegArray[], int d)
{
    char location;
	location = pegArray[d];
	qmoveRight(location);
	pegArray[d] = location;
}

