// Copyright (C) 2005, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// $Id: hs071_nlp.cpp 2005 2011-06-06 12:55:16Z stefan $
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2005-08-16

#include "hs071_nlp.hpp"
#include "stdlib.h"
#include <time.h>

#include <cassert>
#include <iostream>
#include <cmath>

using namespace Ipopt;

// constructor
HS071_NLP::HS071_NLP()
{}

//destructor
HS071_NLP::~HS071_NLP()
{}


//  1 2 3
//  4 3 2
// input = [{0,1,1,1,0}, {0,0,1,1,1}]
// n = 5
// m = 2

// returns the size of the problem
bool HS071_NLP::get_nlp_info(Index& n, Index& m, Index& nnz_jac_g,
                             Index& nnz_h_lag, IndexStyleEnum& index_style)
{
    
  // The problem described in HS071_NLP.hpp has 4 variables, x[0] through x[3]
  n = this->Num_of_Variables;
  //std::cout<<"n="<<n<<std::endl;

  // one equality constraint and one inequality constraint
  m = this->Num_of_Const;
  //std::cout<<"m="<<m<<std::endl;

  // in this example the jacobian is dense and contains 8 nonzeros
  nnz_jac_g = 0;
  for(int i=0;i<Num_of_Const;i++){
      for(int j=0;j<Num_of_Variables;j++){
          //std::cout<<this->equationArray[i*Num_of_Variables + j]<<" ";
          if( this->equationArray[i*Num_of_Variables + j] == 1)
              nnz_jac_g++;          
      }
      //std::cout<<std::endl;
  }
  //std::cout<<"nnz_jac_g="<<nnz_jac_g<<std::endl;
  // the hessian is also dense and has 16 total nonzeros, but we
  // only need the lower left corner (since it is symmetric)
  nnz_h_lag = 0;

  // use the C style indexing (0-based)
  index_style = TNLP::C_STYLE;

  return true;
}

// returns the variable bounds
bool HS071_NLP::get_bounds_info(Index n, Number* x_l, Number* x_u,
                                Index m, Number* g_l, Number* g_u)
{
  // here, the n and m we gave IPOPT in get_nlp_info are passed back to us.
  // If desired, we could assert to make sure they are what we think they are.
  //assert(n == NUM_N);
  //assert(m == NUM_C);

  // the variables have lower bounds of x
  for (Index i=0; i<n; i++) {
    x_l[i] = 0.0;
    x_u[i] = 1.0;    
  }

  // the variables have upper bounds of constant
  for (Index i=0; i<m; i++) {
      g_l[i] = 1;
      g_u[i] = 1e19;

  }


  return true;
}

// returns the initial point for the problem
bool HS071_NLP::get_starting_point(Index n, bool init_x, Number* x,
                                   bool init_z, Number* z_L, Number* z_U,
                                   Index m, bool init_lambda,
                                   Number* lambda)
{
  // Here, we assume we only have starting values for x, if you code
  // your own NLP, you can provide starting values for the dual variables
  // if you wish
  assert(init_x == true);
  assert(init_z == false);
  assert(init_lambda == false);
  
  srand (time(NULL));

  // initialize to the given starting point
  for (Index i=0; i<n; i++) {
      x[i] = (float)(rand()%2)*1.0;
  }

  return true;
}


// returns the value of the objective function
bool HS071_NLP::eval_f(Index n, const Number* x, bool new_x, Number& obj_value)
{
  //assert(n == NUM_N);
    
  for (Index i=0; i<n; i++) {
      //std::cout<<"x"<<i<<"+";
      obj_value = x[i]+obj_value;
  }
  //std::cout<<std::endl;
  return true;
}


// return the gradient of the objective function grad_{x} f(x)
bool HS071_NLP::eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f)
{
  //assert(n == NUM_N);


  for(int i=0;i<n;i++) {
      grad_f[i] = 1;
  }

  return true;
}

// input = [{0,1,1,1,0}, {0,0,1,1,1}]

// return the value of the constraints: g(x)
bool HS071_NLP::eval_g(Index n, const Number* x, bool new_x, Index m, Number* g)
{
    //assert(n == NUM_N);
    //assert(m == NUM_C);


    for(int i=0;i<Num_of_Const;i++){
        int firstT = 1;
        for(int j=0;j<Num_of_Variables;j++){
            if( this->equationArray[i*Num_of_Variables + j] == 1) {
                //std::cout<<"x"<<j<<"+";
                if(firstT == 1){
                    firstT = 0;
                    g[i]=x[j];
                }
                else
                    g[i]=g[i]+x[j];
            }
        }
        //std::cout<<std::endl;
    }

    return true;
}

// jac = [{0,1,1,1,0}, 
//        {0,0,1,1,1}]

// return the structure or values of the jacobian
bool HS071_NLP::eval_jac_g(Index n, const Number* x, bool new_x,
                           Index m, Index nele_jac, Index* iRow, Index *jCol,
                           Number* values)
{
  if (values == NULL) {
    // return the structure of the jacobian

    // this particular jacobian is dense
    int inDex = 0;
    for(int i=0;i<Num_of_Const;i++){
        for(int j=0;j<Num_of_Variables;j++){
            if( this->equationArray[i*Num_of_Variables + j] == 1) {
                //std::cout<<__LINE__<<" "<<i<<" "<<j<<" "<<inDex<<std::endl;
                iRow[inDex] = i; jCol[inDex] = j;
                inDex++;
            }
        }
    }
  }
  else {
    // return the values of the jacobian of the constraints

    for(int i=0;i<nele_jac;i++){
       values[i] = 1;
    }
  }

  return true;
}

//return the structure or values of the hessian
bool HS071_NLP::eval_h(Index n, const Number* x, bool new_x,
                       Number obj_factor, Index m, const Number* lambda,
                       bool new_lambda, Index nele_hess, Index* iRow,
                       Index* jCol, Number* values)
{
  if (values == NULL) {
    // return the structure. This is a symmetric matrix, fill the lower left
    // triangle only.

    // the hessian for this problem is actually dense
    assert(idx == nele_hess);
  }
  else {
    // return the values. This is a symmetric matrix, fill the lower left
    // triangle only

  }

  return true;
}

void HS071_NLP::finalize_solution(SolverReturn status,
                                  Index n, const Number* x, const Number* z_L, const Number* z_U,
                                  Index m, const Number* g, const Number* lambda,
                                  Number obj_value,
				  const IpoptData* ip_data,
				  IpoptCalculatedQuantities* ip_cq)
{
  // here is where we would store the solution to variables, or write to a file, etc
  // so we could use the solution.

  // For this example, we write the solution to the console
  //std::cout << std::endl << std::endl << "Solution of the primal variables, x" << std::endl;
  float tmp=0;
  for (Index i=0; i<n; i++) {
     //std::cout << "x[" << i << "] = " << x[i] << std::endl;     
     
     tmp = tmp + x[i];
  }
  *mAnswer = (int) std::ceil(tmp);
#if 0
  std::cout << std::endl << std::endl << "Solution of the bound multipliers, z_L and z_U" << std::endl;
  for (Index i=0; i<n; i++) {
    std::cout << "z_L[" << i << "] = " << z_L[i] << std::endl;
  }
  for (Index i=0; i<n; i++) {
    std::cout << "z_U[" << i << "] = " << z_U[i] << std::endl;
  }

  std::cout << std::endl << std::endl << "Objective value" << std::endl;
  std::cout << "f(x*) = " << obj_value << std::endl;

  std::cout << std::endl << "Final value of the constraints:" << std::endl;
  for (Index i=0; i<m ;i++) {
    std::cout << "g(" << i << ") = " << g[i] << std::endl;
  }
#endif
}
