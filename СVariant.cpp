#include "CVariant.h"

CVariant::CVariant( int nM, int nN)
{
  this->m_nM = nM;
  this->m_nN = nN;
  this->InitPlane();
  this->m_strPath = "";
}
CVariant::~CVariant()
{
}

int CVariant::GetM()
{
  return this->m_nM;
}
int CVariant::GetN()
{
  return this->m_nN;
}

void CVariant::InitPlane()
{
  std::vector<int> vector;  
  for ( int i = 0; i < this->GetN(); i++)
  {
    std::vector<int> tmpVector = vector;
    this->m_arPlane.push_back( tmpVector);
    for ( int j = 0; j < this->GetM(); j++)
      this->m_arPlane[i].push_back( 0);
  }
}

void CVariant::AddFigure( CFigure& figure)
{
  this->m_listFigure.push_back( figure);
  this->PasteFigure( figure);
}
void CVariant::PasteFigure( CFigure& figure)
{
  for ( std::list<CPoint>::iterator i = figure.m_listPoint.begin(), endi = figure.m_listPoint.end(); i != endi; i++)
  {
    this->m_arPlane[ i->GetY()][ i->GetX()] = figure.GetId();
  }
}
void CVariant::CutFigure( CFigure& figure)
{
  for ( std::list<CPoint>::iterator i = figure.m_listPoint.begin(), endi = figure.m_listPoint.end(); i != endi; i++)
  {
    this->m_arPlane[i->GetY()][i->GetX()] = 0;
  }
}
void CVariant::SetFigure( int nId, CFigure& figure)
{
  bool bNext = true;
  for ( std::list<CFigure>::iterator i = this->m_listFigure.begin(), endi = this->m_listFigure.end();( bNext && ( i != endi)); i++)
  {
    if ( i->GetId() == figure.GetId())
    {
      *i = figure;
      //figure.Debug();
      this->PasteFigure( figure);
      bNext = false;
    }
  }
}

CFigure* CVariant::FindFigure( int nId)
{
  bool bNext = true;
  CFigure* figure = NULL;
  for ( std::list<CFigure>::iterator i = this->m_listFigure.begin(), endi = this->m_listFigure.end(); i != endi; i++)
  {
    if ( i->GetId() == nId)
    {
      bNext = false;
      figure = &*i;
    }
  }
  return figure;
}
void CVariant::AddEndCondition( CFigure &rFigure)
{
  this->m_listEndCondition.push_back( rFigure);
}

bool CVariant::IsEndCondition()
{
  bool bAnswer = false;
  for ( std::list<CFigure>::iterator i = this->m_listEndCondition.begin(), endi = this->m_listEndCondition.end(); i != endi; i++)
  {
    CFigure* pTestFigure = this->FindFigure( i->GetId());
    if ( pTestFigure != NULL)
    {
      if ( i->m_listPoint.size() == pTestFigure->m_listPoint.size())
      {
        bAnswer = true;
        for ( std::list<CPoint>::iterator j = i->m_listPoint.begin(), endj = i->m_listPoint.end(), k = pTestFigure->m_listPoint.begin(); j != endj; j++, k++)
        {
          if (( j->GetX() != k->GetX()) || ( j->GetY() != k->GetY()))
            bAnswer = false;
        }
      }
    }
  }
  return bAnswer;
}

#include <iostream>
#include <windows.h>
void SetColor( int text, int background)
{
  HANDLE hStdOut = GetStdHandle( STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute( hStdOut, (WORD)(( background << 4) | text));
}
void ClearScreen()
{
  SetColor( 0, 0);
  system( "cls");
}
#include <fstream>
void CVariant::Run( std::list<CVariant> &listVariant)
{
  CVariant::s_nStep++;
  ClearScreen();
  SetColor( 15, 0);
  std::cout << CVariant::s_nStep << ", \n";  
  this->Draw( this->m_arPlane);
  if ( this->IsEndCondition())
  {
    SetColor( 15, 0);
    std::cout << this->m_strPath << "\n";
    std::fstream outFile;
    time_t seconds = time( NULL);    
    outFile.open( "result.txt", std::ios::app);
    outFile << "Step: " << CVariant::s_nStep << "\n";
    outFile << "Time: " << ((float)( seconds - CVariant::s_seconds)/(float)60) << "\n";
    outFile << "Path: start" << this->m_strPath << "\n";
    outFile.close();
    int k;
    std::cin >> k;
  }
  else
  {
    for ( std::list<CFigure>::iterator i = this->m_listFigure.begin(), endi = this->m_listFigure.end(); i != endi; i++)
    {
      std::list<CVariant> listFigureVariant = this->MoveFigure( *i);
      if ( listFigureVariant.size() != 0)
      {
        for ( std::list<CVariant>::iterator j = listFigureVariant.begin(), endj = listFigureVariant.end(); j != endj; j++)
        {
          
          listVariant.push_back( *j);        
        }
      }
    }
  }
}

std::list<CVariant> CVariant::MoveFigure( CFigure figure)
{
  std::list<CVariant> listVariant;
  std::string strPath = "";
  char strId[20];
  _itoa_s( figure.GetId(), strId, 10);
  if ( this->CanBeMovedDown( figure))
  {
    //std::cout << figure.GetId() << "DOWN";    
    
    CFigure tmpFigure = figure;
    CVariant variant = this->CloneIt( *this);
    strPath = "->" + (std::string)strId + "(down)";
    variant.AddPath( strPath);
    //variant->m_strPath .= '->'.$tmpFigure->GetId().'(up)';
    variant.CutFigure( tmpFigure);
    tmpFigure.MoveDown();
    variant.SetFigure( tmpFigure.GetId(), tmpFigure);      
    if ( !CVariant::s_solution.IsSolution( variant.MakePlane()))//.m_arPlane))
    {
      CVariant::s_solution.AddSolution( variant.MakePlane());//.m_arPlane);
      listVariant.push_back( variant);
    }      
  }
  if ( this->CanBeMovedUp( figure))
  {
    //std::cout << figure.GetId() << "UP";
    CFigure tmpFigure = figure;
    CVariant variant = this->CloneIt( *this);
    strPath = "->" + (std::string)strId + "(up)";
    variant.AddPath( strPath);
    //variant->m_strPath .= '->'.$tmpFigure->GetId().'(up)';
    variant.CutFigure( tmpFigure);
    tmpFigure.MoveUp();
    variant.SetFigure( tmpFigure.GetId(), tmpFigure);      
    if ( !CVariant::s_solution.IsSolution( variant.MakePlane()))//.m_arPlane))
    {
      CVariant::s_solution.AddSolution( variant.MakePlane());//.m_arPlane);
      listVariant.push_back( variant);
    }      
  }
  if ( this->CanBeMovedLeft( figure))
  {
    //std::cout << figure.GetId() << "LEFT";
    CFigure tmpFigure = figure;
    CVariant variant = this->CloneIt( *this);
    strPath = "->" + (std::string)strId + "(left)";
    variant.AddPath( strPath);
    //variant->m_strPath .= '->'.$tmpFigure->GetId().'(up)';
    variant.CutFigure( tmpFigure);
    tmpFigure.MoveLeft();
    variant.SetFigure( tmpFigure.GetId(), tmpFigure);      
    if ( !CVariant::s_solution.IsSolution( variant.MakePlane()))//.m_arPlane))
    {
      CVariant::s_solution.AddSolution( variant.MakePlane());//.m_arPlane);
      listVariant.push_back( variant);
    }      
  }
  if ( this->CanBeMovedRight( figure))
  {
    //std::cout << figure.GetId() << "RIGHT";
    CFigure tmpFigure = figure;
    CVariant variant = this->CloneIt( *this);
    strPath = "->" + (std::string)strId + "(right)";
    variant.AddPath( strPath);
    //variant->m_strPath .= '->'.$tmpFigure->GetId().'(up)';
    variant.CutFigure( tmpFigure);
    tmpFigure.MoveRight();
    variant.SetFigure( tmpFigure.GetId(), tmpFigure);   
    //this->Draw( variant.MakePlane());
    if ( !CVariant::s_solution.IsSolution( variant.MakePlane()))//.m_arPlane))
    {
      //std::cout << "RIGHTED";
      CVariant::s_solution.AddSolution( variant.MakePlane());//.m_arPlane);
      listVariant.push_back( variant);
    }      
  }
  return listVariant;
}

CVariant CVariant::CloneIt( CVariant variant)
{
  CVariant cloneVariant = variant;
  return cloneVariant;
}

bool CVariant::CanBeMovedDown( CFigure &rFigure)
{
  bool bAnswer = true;
  for ( std::list<CPoint>::iterator i = rFigure.m_listPoint.begin(), endi = rFigure.m_listPoint.end(); i != endi; i++)
  {
    if ( i->GetY() + 1 < this->GetN())
    {
      if ( this->m_arPlane[i->GetY() + 1][i->GetX()] != 0)
      if ( this->m_arPlane[i->GetY() + 1][i->GetX()] != rFigure.GetId())
        bAnswer = false;
    }
    else
      bAnswer = false;
  }
  return bAnswer;
}
bool CVariant::CanBeMovedLeft( CFigure &rFigure)
{
  bool bAnswer = true;
  for ( std::list<CPoint>::iterator i = rFigure.m_listPoint.begin(), endi = rFigure.m_listPoint.end(); i != endi; i++)
  {
    if ( i->GetX() > 0)
    {
      if ( this->m_arPlane[i->GetY()][i->GetX() - 1] != 0)
      if ( this->m_arPlane[i->GetY()][i->GetX() - 1] != rFigure.GetId())
        bAnswer = false;
    }
    else
      bAnswer = false;
  }
  return bAnswer;
}
bool CVariant::CanBeMovedRight( CFigure &rFigure)
{
  bool bAnswer = true;
  for ( std::list<CPoint>::iterator i = rFigure.m_listPoint.begin(), endi = rFigure.m_listPoint.end(); i != endi; i++)
  {
    if ( i->GetX() + 1 < this->GetM())
    {
      if ( this->m_arPlane[i->GetY()][i->GetX() + 1] != 0)
      if ( this->m_arPlane[i->GetY()][i->GetX() + 1] != rFigure.GetId())
        bAnswer = false;
    }
    else
      bAnswer = false;
  }
  return bAnswer;
}
bool CVariant::CanBeMovedUp( CFigure &rFigure)
{
  bool bAnswer = true;
  for ( std::list<CPoint>::iterator i = rFigure.m_listPoint.begin(), endi = rFigure.m_listPoint.end(); i != endi; i++)
  {
    if ( i->GetY() > 0)
    {
      if ( this->m_arPlane[i->GetY() - 1][i->GetX()] != 0)
      if ( this->m_arPlane[i->GetY() - 1][i->GetX()] != rFigure.GetId())
        bAnswer = false;
    }
    else
      bAnswer = false;
  }
  return bAnswer;
}

#include <string.h>
std::string ToString( int nValue)
{
  char strValue[4];
  _itoa_s( nValue, strValue, 10);
  std::string strReturn = (std::string)strValue;
  if ( nValue < 10)
    strReturn = "0" + strReturn;
  return strReturn;
}
void CVariant::Draw( std::vector< std::vector<int> > arPlane)
{  
  for ( int i = 0; i < this->GetN(); i++)
  {
    std::cout << "\n";
    for ( int j = 0; j < this->GetM(); j++)
    {
      SetColor( 0, arPlane[i][j]);
      std::cout << ToString( arPlane[i][j]);
    }
  }
}

void CVariant::AddPath( std::string strValue)
{
  this->m_strPath += strValue;
}

std::string CVariant::GetPath()
{
  return this->m_strPath;
}

std::vector< std::vector<int> > CVariant::MakePlane()
{
  std::vector< std::vector<int> > arPlane;// = this->m_arPlane;
  std::vector<int> vector;  
  for ( int i = 0; i < this->GetN(); i++)
  {
    std::vector<int> tmpVector = vector;
    arPlane.push_back( tmpVector);
    for ( int j = 0; j < this->GetM(); j++)
      arPlane[i].push_back( 0);
  }
  for ( std::list<CFigure>::iterator i = this->m_listFigure.begin(), endi = this->m_listFigure.end(); i != endi; i++)
  {
    for ( std::list<CPoint>::iterator j = i->m_listPoint.begin(), endj = i->m_listPoint.end(); j != endj; j++)
    {
      arPlane[ j->GetY()][ j->GetX()] = i->m_listPoint.size();//GetId();
    }
  }
  return arPlane;
}