/***************************< File comment >*****************************/  
/* file name : Occurance.h                                              */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 02/15/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/

#ifndef __OCCURANCE_H__
#define __OCCURANCE_H__

/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/

#include<iostream>
#include <fstream>
#include <vector>

#include <sys/time.h>


/*----------------------------------------------------------------------*/ 
/*                              Class                                   */ 
/*----------------------------------------------------------------------*/ 

class EdgeNEWFw{
public:    
    int fromId;
    int toId;    
    int from;
    int to;
    int label;
    EdgeNEWFw(int fromId, int toId, int from, int to, int label){
        this->from = from;
        this->to = to;
        this->fromId = fromId;
        this->toId = toId;        
        this->label = label;
    }
    bool operator<(const EdgeNEWFw& a) const {
        return (a.fromId < this->fromId || a.toId < this->toId);
    }
    
    bool operator>(const EdgeNEWFw& a) const {
        return (a.fromId > this->fromId || a.toId > this->toId);
    }
    
    bool operator==(const EdgeNEWFw& a) const {
        return (a.fromId == this->fromId || a.toId == this->toId);
    }
    
    bool operator!=(const EdgeNEWFw& a) const {
        return (a.fromId != this->fromId || a.toId != this->toId);
    }
};

class Occurance{
public:    
    std::vector<EdgeNEWFw> EdgeList;
    Occurance(std::vector<EdgeNEWFw> EdgeList) {
        this->EdgeList = EdgeList;
    }
};

#endif 