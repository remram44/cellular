#include "Cell.h"

Cell::Cell()
  : m_iState(0)
{
}

void Cell::setFutureState(unsigned int nextstate)
{
    m_iFutureState = nextstate;
}

void Cell::tick()
{
    m_iState = m_iFutureState;
    m_iFutureState = 0;
}
