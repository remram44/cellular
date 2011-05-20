#ifndef CELL_H
#define CELL_H

class Cell {

private:
    unsigned int m_iState;
    unsigned int m_iFutureState;

public:
    Cell();
    void tick();
    void setFutureState(unsigned int nextstate);
    inline unsigned int getState()
    { return m_iState; }

};

#endif
