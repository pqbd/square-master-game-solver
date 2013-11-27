#ifndef __CFIGURE__
#define __CFIGURE__

#include "CPoint.h"
#include <list>

class CFigure
{
  protected:
  int m_nId;
  public:
  std::list<CPoint> m_listPoint;

  public:
  CFigure( int nX, int nY, int nId);
  ~CFigure();
  
  int GetId();

  void AddPoint( int nX, int nY);
  void AddPoint( CPoint& point);

  void MoveLeft();
  void MoveRight();
  void MoveDown();
  void MoveUp();

  void Debug();
};

#endif

