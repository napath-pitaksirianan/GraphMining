/***************************< File comment >*****************************/  
/* file name : MSEI.h                                                   */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 02/15/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/

#ifndef __MI__
#define __MI__

/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/

#include<iostream>
#include <vector>
#include <set>

#include "Occurance.h"
#include "Measure.h"


/*----------------------------------------------------------------------*/ 
/*                              Class                                   */ 
/*----------------------------------------------------------------------*/ 


class MI : public Measure{
    unsigned int support();
public:    
    double m_time;
    unsigned int value;
    MI(std::vector<Occurance> OccuranceList,std::vector<Edge> DFSList): Measure(OccuranceList,DFSList){  
        this-> value = support();   
    };
    void DFSUtil(int v, bool visited[], std::vector<int> pattenVector,std::vector<std::vector<int> > patternAdj, std::set<std::set<Edge> > &subGraph, int previousV, std::set<Edge> currentSub);
    void connectedComponents(std::vector<int> pattenVector,std::vector<std::vector<int> > patternAdj, std::set<std::set<Edge> > &subGraph);
};


#endif 