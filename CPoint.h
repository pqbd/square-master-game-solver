#ifndef __CPOINT__
#define __CPOINT__

class CPoint
{
  protected:
  int m_nX;
  int m_nY;

  public:
  CPoint( int nX, int nY);
  ~CPoint();
  
  void SetX( int);
  void SetY( int);
  int GetX();
  int GetY();
};
#endif

