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

#include "CplexRMVC.h"

unsigned int CplexRMVC::support()
{
    IloEnv env;
    IloModel model(env);
    IloCplex cplex(model);
    IloObjective objfunc(env);
    IloNumVarArray var_x(env);
    IloExpr Expr(env);

    int min = 0;
    if(OccuranceList.size() == 0)
        return 0;
    if(DFSList.size() == 0)
        return 0;

    float fmin = 0;

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

    var_x = IloNumVarArray(env, Num_of_Variables);

    for (int i = 0; i < Num_of_Variables; i++) {
        var_x[i] = IloNumVar(env, 0.0, 1, ILOFLOAT);
    }

    for (int l = 0; l < Num_of_Const; l++) {
        Expr.clear();
        for (int m = 0; m < Num_of_VariablesEachConst; m++) {
            //define p from vector;
            int p = OccurenceArray[l][m];
            Expr +=  var_x[p];
        }
        model.add(Expr >= 1);
    }

    Expr.clear();
    for (int m = 0; m < Num_of_Variables; m++) {
        Expr +=  var_x[m];
    }

    objfunc = IloMinimize(env, Expr);
    Expr.clear();
    model.add(objfunc);
    cplex.extract(model);

    cplex.setParam(IloCplex::TiLim, TimeLimit);
    cplex.setParam(IloCplex::Threads, NumThreads);
    cplex.setParam(IloCplex::EpGap, RelativeGap);
    cplex.setOut(env.getNullStream());


    if (cplex.solve()) {
        //for (int i = 0; i < 2; i++) {
            //ObjValue = cplex.getObjValue();
        //}
        for (int i = 0; i < Num_of_Variables; i++) {
            fmin=fmin+cplex.getValue(var_x[i]);
            //Opt_X_Value[i] = cplex.getValue(var_x[i]);
            //cout<<cplex.getValue(var_x[i])<<" ";
        }
        min = (int)ceil(fmin);
    }

    return min;
}
