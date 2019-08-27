/***************************< File comment >*****************************/
/* file name : MVC.h                                                  */
/* file description :                                                   */
/*----------------------------------------------------------------------*/
/* version : 1.0                                                        */
/*----------------------------------------------------------------------*/
/* create : 07/14/2017                                                  */
/* programmer : Napath Pitaksirianan                                    */
/************************************************************************/

#ifndef __CPLEX_RMVC_H__
#define __CPLEX_RMVC_H__

/*----------------------------------------------------------------------*/
/*                           Include file                               */
/*----------------------------------------------------------------------*/

#include<iostream>
#include <vector>

#include "Occurance.h"
#include "Measure.h"
#include "util.h"

#include <ilcplex/ilocplex.h>

using namespace std;

#define IL_STD 1

/*CPLEX parameters*/
#define RelativeGap 0.00001
#define NumThreads 1
#define TimeLimit 86400
#define Positive_infinity 100000000
#define Negative_infinity -100000000

//ILOSTLBEGIN

/*----------------------------------------------------------------------*/
/*                              Class                                   */
/*----------------------------------------------------------------------*/

class CplexRMVC : public Measure{
    unsigned int support();
public:
    CplexRMVC(vector<Occurance> OccuranceList,vector<EdgeNEWFw> DFSList): Measure(OccuranceList,DFSList){
        double tstart, tstop;
        tstart = dtime();

        this-> value = support();

        tstop = dtime();
        this->m_time = tstop - tstart;
    };
};


#endif
