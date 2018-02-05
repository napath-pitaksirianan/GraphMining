/***************************< File comment >*****************************/  
/* file name : MVC.h                                                  */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 07/14/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/

#ifndef __MVC_H__
#define __MVC_H__

/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/

#include<iostream>
#include <vector>

#include "Occurance.h"
#include "Measure.h"
#include "util.h"

/*----------------------------------------------------------------------*/ 
/*                              Class                                   */ 
/*----------------------------------------------------------------------*/ 

class MVC : public Measure{
    unsigned int support();
public:    
    MVC(std::vector<Occurance> OccuranceList,std::vector<Edge> DFSList): Measure(OccuranceList,DFSList){  
        double tstart, tstop;
        tstart = dtime();
        
        this-> value = support();
        
        tstop = dtime();
        this->m_time = tstop - tstart;
    };
};


#endif 