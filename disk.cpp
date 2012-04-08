#include "disk.h"
#include <fstream>
#include <iostream>
#include <cstdlib>


using namespace std;

int Disk::diskCount = 0;

Disk::Disk()
{
    size = ++diskCount;
}

Disk::~Disk()
{
}

Disk::Disk(const Disk& other)
{
    size = other.size;
}

Disk& Disk::operator=(const Disk& other)
{
    if (this == &other) return *this; // handle self assignment
    size = other.size;
    return *this;
}

int Disk::getSize()
{
    return size;
}

ostream& operator<<(ostream& out, Disk& d)
{
    out<< "Disk " << d.size;
    return out;
}

bool operator==(Disk& first, Disk& second)
{
    return first.size == second.size;
}

void Disk::changeLocation(char c)
{
    location = c;
}

char Disk::getLocation()
{
    return location;
}


bool operator!=(const Disk& first, const Disk& second)
{
    return first.size != second.size;
}

bool operator>(const Disk& first, const Disk& second)
{
    return first.size > second.size;
}


bool operator<(const Disk& first, const Disk& second)
{
    return first.size < second.size;
}


bool operator>=(const Disk& first, const Disk& second)
{
    return first.size >= second.size;
}


bool operator<=(const Disk& first, const Disk& second)
{
    return first.size <= second.size;
}
