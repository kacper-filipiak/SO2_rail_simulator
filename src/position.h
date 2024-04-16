#ifndef SO2_PROJECT_POSITION_H
#define SO2_PROJECT_POSITION_H


#include <atomic>

class Position {
public:
    Position(const Position &position);
    Position(int i, int i1);

    std::atomic<int> x;
    std::atomic<int> y;

    bool operator==(const Position &rhs) const;

    bool operator!=(const Position &rhs) const;
};


#endif //SO2_PROJECT_POSITION_H
