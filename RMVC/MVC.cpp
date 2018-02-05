/***************************< File comment >*****************************/  
/* file name : MVC.cpp                                               */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 07/14/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/


/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/


#include<iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

#include "IpIpoptApplication.hpp"
#include "hs071_nlp.hpp"

#include "MVC.h"

unsigned int MVC::support()
{

    int min = 0;
    if(OccuranceList.size() == 0)
        return 0;
    if(DFSList.size() == 0)
        return 0;

    std::vector< std::vector<int> > OccurenceArray;
    std::set<int> AllVariable;
    
    unsigned long long maxVar = 0;
    for(int j=0;j<OccuranceList.size();j++) {
        std::vector<int> tmp;
        OccurenceArray.push_back(tmp);
        for(int i=0;i<this->DFSList.size();i++) {
            if(i==0) { 
                OccurenceArray[j].push_back(OccuranceList[j].EdgeList[i].from);
                AllVariable.insert(OccuranceList[j].EdgeList[i].from);
                if(maxVar < OccuranceList[j].EdgeList[i].from)
                    maxVar = OccuranceList[j].EdgeList[i].from;
            }
            OccurenceArray[j].push_back(OccuranceList[j].EdgeList[i].to);
            AllVariable.insert(OccuranceList[j].EdgeList[i].to);
            if(maxVar < OccuranceList[j].EdgeList[i].to)
                maxVar = OccuranceList[j].EdgeList[i].to;
        }
    }

    int Num_of_Variables = maxVar+1;
    int Num_of_VariablesEachConst = this->DFSList.size()+1;
    int Num_of_Const = OccuranceList.size();

    SmartPtr<TNLP> mynlp = new HS071_NLP(OccurenceArray,AllVariable,Num_of_Variables,Num_of_VariablesEachConst,Num_of_Const,&min);

    // Create a new instance of IpoptApplication
    //  (use a SmartPtr, not raw)
    // We are using the factory, since this allows us to compile this
    // example with an Ipopt Windows DLL
    SmartPtr<IpoptApplication> app = IpoptApplicationFactory();
    app->RethrowNonIpoptException(true);

    // Change some options
    // Note: The following choices are only examples, they might not be
    //       suitable for your optimization problem.
    app->Options()->SetNumericValue("tol", 1e-7);
    app->Options()->SetStringValue("mu_strategy", "adaptive");
    app->Options()->SetIntegerValue("print_level", 0);
    app->Options()->SetStringValue("sb","yes");
    //app->Options()->SetStringValue("output_file", "ipopt.out");
    // The following overwrites the default name (ipopt.opt) of the
    // options file
    // app->Options()->SetStringValue("option_file_name", "hs071.opt");

    // Initialize the IpoptApplication and process the options
    ApplicationReturnStatus status;
    status = app->Initialize();
    if (status != Solve_Succeeded) {
      std::cout << std::endl << std::endl << "*** Error during initialization!" << std::endl;
      return (int) status;
    }

    // Ask Ipopt to solve the problem
    status = app->OptimizeTNLP(mynlp);

    if (status == Solve_Succeeded) {
      //std::cout << std::endl << std::endl << "*** The problem solved!" << std::endl;
    }
    else {
      std::cout << std::endl << std::endl << "*** The problem FAILED!" << std::endl;
    }


    return min;
}

