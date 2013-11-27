#include "CVariant.h"
#include "CFigure.h"

#include <iostream>
using namespace std;

unsigned int CVariant::s_nStep = 0;
CSolution CVariant::s_solution;
time_t CVariant::s_seconds = time(NULL);


int main( int argc, char *argv[])
{
  CVariant variant( 4, 5);

  int nId = 1;
  // 1 point figures
  variant.AddFigure( CFigure( 0, 0, nId++));
  //variant.AddFigure( CFigure( 0, 1, nId++));
  variant.AddFigure( CFigure( 1, 1, nId++));
  variant.AddFigure( CFigure( 3, 0, nId++));
  //variant.AddFigure( CFigure( 3, 1, nId++));
  variant.AddFigure( CFigure( 2, 1, nId++));

  // 2 point figures
  //CFigure figure( 0, 2, nId++);
  //figure.AddPoint( 1, 2);
  //variant.AddFigure( figure);
  CFigure figure( 0, 1, nId++);
  figure.AddPoint( 0, 2);
  variant.AddFigure( figure);

  //figure = CFigure( 2, 2, nId++);
  //figure.AddPoint( 3, 2);
  //variant.AddFigure( figure);
  figure = CFigure( 3, 1, nId++);
  figure.AddPoint( 3, 2);
  variant.AddFigure( figure);

  //figure = CFigure( 1, 1, nId++);
  //figure.AddPoint( 2, 1);
  //variant.AddFigure( figure);
  figure = CFigure( 1, 2, nId++);
  figure.AddPoint( 2, 2);
  variant.AddFigure( figure);

  figure = CFigure( 0, 3, nId++);
  figure.AddPoint( 0, 4);
  variant.AddFigure( figure);

  figure = CFigure( 3, 3, nId++);
  figure.AddPoint( 3, 4);
  variant.AddFigure( figure);

  // 4 point figures
  figure = CFigure( 1, 3, nId++);
  figure.AddPoint( 1, 4);
  figure.AddPoint( 2, 3);
  figure.AddPoint( 2, 4);
  variant.AddFigure( figure);

  // End condition
  // 4 point figures
  figure = CFigure( 1, 0, ( nId - 1));
  figure.AddPoint( 1, 1);
  figure.AddPoint( 2, 0);
  figure.AddPoint( 2, 1);  
  variant.AddEndCondition( figure);

  std::list<CVariant> listVariant;
  listVariant.push_back( variant);

  for ( std::list<CVariant>::iterator i = listVariant.begin(), endi = listVariant.end(); i != endi; ++i)
  {
    i->Run( listVariant);
    endi = listVariant.end();
  }
    
  cout << "\ntest: " << variant.m_listFigure.size();
  
  int a;
  cin >> a;
	
  return 0;
}
