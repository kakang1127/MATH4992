#include <iostream>
#include <cmath>
using namespace std;


class Block{
    public:
        Block(int n);
        bool visited() const;
        int whatn() const;
        void visiting();

    private:
        bool visit;
        int number;
};