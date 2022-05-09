#ifndef HELPERS_H
#define HELPERS_H

#include <random>

class Helpers {

    public:
        static int RandI(int _min, int _max){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(_min, _max);
            return dis(gen);
        }
};

#endif // HELPERS_H
