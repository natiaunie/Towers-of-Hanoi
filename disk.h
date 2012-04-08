#ifndef DISK_H
#define DISK_H
#include <fstream>
#include <cstdlib>

using namespace std;


class Disk
{
    public:
        Disk();
        ~Disk();
        Disk(const Disk& other);
        Disk& operator=(const Disk& other);
        int getSize();
        void createDisk(int s);
        void changeLocation(char c);
        char getLocation();

        friend
        ostream& operator<<(ostream& out, Disk &d);

        friend
        bool operator==(Disk& first, Disk& second);

        friend
        bool operator!=(const Disk& first, const Disk& second);

        friend
        bool operator>(const Disk& first,const Disk& second);

        friend
        bool operator<(const Disk& first,const Disk& second);

        friend
        bool operator>=(const Disk& first, const Disk& second);

        friend
        bool operator<=(const Disk& first, const Disk& second);

    protected:

    private:
        int size;
        int count;
        static int diskCount;
        char location;
};

#endif // DISK_H
