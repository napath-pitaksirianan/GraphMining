/***************************< File comment >*****************************/  
/* file name : MIS.h                                                    */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 02/15/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/

#ifndef __MEASURE__
#define __MEASURE__


/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/

#include<iostream>
#include <vector>

#include "Occurance.h"


/*----------------------------------------------------------------------*/ 
/*                              Class                                   */ 
/*----------------------------------------------------------------------*/ 

class Measure{
protected:
    std::vector<Occurance> OccuranceList;
    std::vector<EdgeNEWFw> DFSList;
    virtual unsigned int support() = 0;
public:    
    double m_time;
    unsigned int value;
    Measure(std::vector<Occurance> OccuranceList,std::vector<EdgeNEWFw> DFSList){ 
        this->OccuranceList = OccuranceList;
        this->DFSList = DFSList;
    };
};


#endif 