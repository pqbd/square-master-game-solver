#include "CSolution.h"

CSolution::CSolution()
{
}
CSolution::~CSolution()
{
}

bool CSolution::IsSolution( std::vector< std::vector<int> > rPlane)
{
  CSolutionItem testSolutionItem = this->MakeSolutionItem( rPlane);
  bool bAnswer = false;
  for ( std::list<CSolutionItem>::iterator i = this->m_listSolution.begin(), endi = this->m_listSolution.end();(( i != endi) && !bAnswer); i++)
  {
    if ( this->IsSolutionItemMatch( testSolutionItem, *i))
      bAnswer = true;
  }
  return bAnswer;
}

bool CSolution::IsSolutionItemMatch( CSolutionItem testItem, CSolutionItem solutionItem)
{
  bool bAnswer = true;

  std::vector<int> vectorRow = solutionItem.m_vectorRow;
  std::vector<int> vectorCol = solutionItem.m_vectorCol;

  std::vector<int> testRow = testItem.m_vectorRow;
  std::vector<int> testCol = testItem.m_vectorCol;
  for ( unsigned int i = 0; (( i < solutionItem.m_arPlane.size()) && bAnswer); i++)
  {
    for ( unsigned int j = 0; (( j < solutionItem.m_arPlane[i].size()) && bAnswer); j++)
    {
      if ( solutionItem.m_arPlane[i][j] != testItem.m_arPlane[i][j])
        bAnswer = false;
    }
  }
  //for ( unsigned int i = 0;(( i < vectorRow.size()) && bAnswer); i++)
  //{
  //  if ( vectorRow[i] != testRow[i])
  //    bAnswer = false;
  //}
  //if ( bAnswer)
  //{
  //  for ( unsigned int i = 0;(( i < vectorCol.size()) && bAnswer); i++)
  //  {
  //    if ( vectorCol[i] != testCol[i])
  //      bAnswer = false;
  //  }
  //}
  return bAnswer;
}

void CSolution::AddSolution( std::vector< std::vector<int> > rPlane)
{
  this->m_listSolution.push_back( this->MakeSolutionItem( rPlane));
}

CSolutionItem CSolution::MakeSolutionItem( std::vector< std::vector<int> > rPlane)
{
  CSolutionItem solutionItem;
  std::vector<int> vectorRow;
  std::vector<int> vectorCol;

  solutionItem.m_arPlane = rPlane;

  int ik = 0;
  for ( std::vector< std::vector<int> >::iterator i = rPlane.begin(), endi = rPlane.end(); i != endi; i++, ik++)
  {
    vectorRow.push_back( 0);
    int jk = 0;
    for ( std::vector<int>::iterator j = i->begin(), endj = i->end(); j != endj; j++, jk++)
    {
      vectorRow[ik] += *j;
      if ( ik == 0)
        vectorCol.push_back( *j);
      else
        vectorCol[jk] += *j;
    }
  }
  
  solutionItem.m_vectorRow = vectorRow;
  solutionItem.m_vectorCol = vectorCol;

  return solutionItem;
}