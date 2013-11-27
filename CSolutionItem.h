#ifndef __CSOLUTIONITEM_H__
#define __CSOLUTIONITEM_H__

#include <vector>

class CSolutionItem
{
  public:
  std::vector<int> m_vectorRow;
  std::vector<int> m_vectorCol;

  std::vector< std::vector<int> > m_arPlane;

  public:
  CSolutionItem();
  ~CSolutionItem();
};

#endif

