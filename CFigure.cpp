#include "CFigure.h"

CFigure::CFigure( int nX, int nY, int nId)
{
  this->AddPoint( nX, nY);
  this->m_nId = nId;
}
CFigure::~CFigure()
{
}
int CFigure::GetId()
{
  return this->m_nId;
}

void CFigure::MoveLeft()
{
  for ( std::list<CPoint>::iterator iterator =  this->m_listPoint.begin(), end = this->m_listPoint.end(); iterator != end; iterator++)
    iterator->SetX( iterator->GetX() - 1);
}
void CFigure::MoveRight()
{
  for ( std::list<CPoint>::iterator iterator =  this->m_listPoint.begin(), end = this->m_listPoint.end(); iterator != end; iterator++)
    iterator->SetX( iterator->GetX() + 1);
}
void CFigure::MoveDown()
{
  for ( std::list<CPoint>::iterator iterator =  this->m_listPoint.begin(), end = this->m_listPoint.end(); iterator != end; iterator++)
    iterator->SetY( iterator->GetY() + 1);
}
void CFigure::MoveUp()
{
  for ( std::list<CPoint>::iterator iterator =  this->m_listPoint.begin(), end = this->m_listPoint.end(); iterator != end; iterator++)
    iterator->SetY( iterator->GetY() - 1);
}

void CFigure::AddPoint( int nX, int nY)
{
  this->m_listPoint.push_back( CPoint( nX, nY));
}
void CFigure::AddPoint( CPoint& point)
{
  this->m_listPoint.push_back( point);
}

#include <iostream>
void CFigure::Debug()
{
  for ( std::list<CPoint>::iterator iterator =  this->m_listPoint.begin(), end = this->m_listPoint.end(); iterator != end; iterator++)
    std::cout << "( " << iterator->GetX() << ", " << iterator->GetY() << ") ";
  std::cout << "\n";
}