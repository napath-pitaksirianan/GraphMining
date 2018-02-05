/***************************< File comment >*****************************/  
/* file name : MESIV.h                                                  */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 02/24/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/

#ifndef __MSEIV__
#define __MSEIV__

/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/

#include<iostream>
#include <vector>

#include "Occurance.h"
#include "Measure.h"
#include "util.h"

using namespace std;

/*----------------------------------------------------------------------*/ 
/*                              Class                                   */ 
/*----------------------------------------------------------------------*/ 

class MSEIV : public Measure{
    unsigned int support();
public:    
    MSEIV(vector<Occurance> OccuranceList,vector<Edge> DFSList): Measure(OccuranceList,DFSList){  
        double tstart, tstop;
        tstart = dtime();
        
        this-> value = support();
        
        tstop = dtime();
        this->m_time = tstop - tstart;
    };
};


#endif 