/***************************< File comment >*****************************/  
/* file name : util.cpp                                                 */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 02/15/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/

#ifndef __UTIL__
#define __UTIL__

/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/

#include <sys/time.h>
#include <sstream>
#include <string>
#include <fstream>

/*----------------------------------------------------------------------*/ 
/*                              Function                                */ 
/*----------------------------------------------------------------------*/ 

double dtime()
{
    double tseconds = 0.0;
    struct timeval mytime;
    gettimeofday(&mytime,(struct timezone*)0);
    tseconds = (double)(mytime.tv_sec +
                        mytime.tv_usec*1.0e-6);
    return( tseconds );
}

int verifyInputFile(char *filename){
    std::ifstream infile(filename);
    unsigned long long int lineNumber = 0;
    std::string line;
    while (std::getline(infile, line))
    {
        lineNumber++;
        std::istringstream iss(line);
        std::istringstream iss2(line);
        int a, b, c, d,e;
        if (!(iss >> a >> b >> c>> d)) { return lineNumber; } // error
        if (iss >> a >> b >> c>> d >> e) { return lineNumber; } // error

        // process pair (a,b)
    }
    return 0;
}

#endif 