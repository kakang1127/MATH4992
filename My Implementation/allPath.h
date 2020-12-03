#include <iostream>
#include "path.h"
using namespace std;

class allPath{
    public:
        allPath(Block* start);
        ~allPath();

        int getSize() const;
        int getStep() const;
        int getShortestDistance() const;
        int existEndPath() const;
        int endPathWithSD() const;
        void oneStepFurther(int** board, int boardSize, Block ** Nodes, int end);
        void print() const;
        void findShortestPath(int** board, int boardSize, Block** Nodes, int end);

    private:
        path** paths;
        int size;
        int steps;

};