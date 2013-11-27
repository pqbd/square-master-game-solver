#ifndef __CVARIANT__
#define __CVARIANT__

#include <list>
#include <vector>
#include "CFigure.h"
#include "CSolution.h"
#include <string>
#include <time.h>

class CVariant
{
  public:
    std::list<CFigure> m_listFigure;
    std::list<CFigure> m_listEndCondition;
    std::vector< std::vector<int> > m_arPlane;
    int m_nM;
    int m_nN;
    std::string m_strPath;    
  
  public:
  static CSolution s_solution;
  static unsigned int s_nStep;
  static time_t s_seconds;

  public:
  CVariant( int nM, int nN);
  ~CVariant();

  void SetM( int nValue);
  void SetN( int nValue);
  int GetM();
  int GetN();  

  void AddPath( std::string strValue);
  std::string GetPath();

  void InitPlane();

  void AddFigure( CFigure& figure);
  void PasteFigure( CFigure& figure);
  void CutFigure( CFigure& figure);
  void SetFigure( int nId, CFigure& figure);
  CFigure* FindFigure( int nId);

  void AddEndCondition( CFigure &rFigure);
  bool IsEndCondition();

  void Run( std::list<CVariant> &listVariant);

  std::list<CVariant> MoveFigure( CFigure figure);
  bool CanBeMovedLeft( CFigure &rFigure);
  bool CanBeMovedRight( CFigure &rFigure);
  bool CanBeMovedUp( CFigure &rFigure);
  bool CanBeMovedDown( CFigure &rFigure);

  CVariant CloneIt( CVariant variant);

  std::vector< std::vector<int> > MakePlane();

  void Draw( std::vector< std::vector<int> > arPlane);
};

#endif

