#ifndef __CSOLUTION__
#define __CSOLUTION__

#include <list>
#include <vector>
#include "CSolutionItem.h"

class CSolution
{
  protected:
  std::list<CSolutionItem> m_listSolution;

  public:
  CSolution();
  ~CSolution();
  
  bool IsSolution( std::vector< std::vector<int> > rPlane);
  void AddSolution( std::vector< std::vector<int> > rPlane);
  CSolutionItem MakeSolutionItem( std::vector< std::vector<int> > rPlane);
  bool IsSolutionItemMatch( CSolutionItem testItem, CSolutionItem solutionItem);
};

#endif

