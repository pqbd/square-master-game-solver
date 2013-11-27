#include "CPoint.h"

CPoint::CPoint( int nX, int nY)
{
  this->SetX( nX);
  this->SetY( nY);
}
CPoint::~CPoint()
{
}
void CPoint::SetX( int nValue)
{
  this->m_nX = nValue;
}
void CPoint::SetY( int nValue)
{
  this->m_nY = nValue;
}
int CPoint::GetX()
{
  return this->m_nX;
}
int CPoint::GetY()
{
  return this->m_nY;
}