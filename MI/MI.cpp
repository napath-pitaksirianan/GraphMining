/***************************< File comment >*****************************/  
/* file name : MI.cpp                                                 */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 03/02/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/


/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/

#include<iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <set>

#define MAXN 1000    /* Define this before including nauty.h */

#include "nauty.h"  
#include "util.h"
#include "MI.h"

unsigned int MI::support()
{
    double tstart, tstop, ttime;
    tstart = dtime();
    unsigned int min = 0xffffffff;
    
    if(OccuranceList.size() == 0)
        return 0;
    
    // preparing data for compute
    std::vector<int> pattenVector;
    std::map<int,int> patternLabel;
    for(int i=0;i<this->DFSList.size();i++) {
        if (std::find(pattenVector.begin(), pattenVector.end(), DFSList[i].fromId) == pattenVector.end()) {
            pattenVector.push_back(DFSList[i].fromId);
            patternLabel[DFSList[i].fromId] = DFSList[i].from;
        }
        if (std::find(pattenVector.begin(), pattenVector.end(), DFSList[i].toId) == pattenVector.end()) {
            pattenVector.push_back(DFSList[i].toId);
            patternLabel[DFSList[i].toId] = DFSList[i].to;
        }
    }
    std::vector<std::vector<int> > patternAdj;
    for(int i=0;i<pattenVector.size();i++) {
        std::vector<int> tmp;
        patternAdj.push_back(tmp);
    }
    for(int i=0;i<this->DFSList.size();i++) {
        if (std::find(patternAdj[DFSList[i].fromId].begin(), patternAdj[DFSList[i].fromId].end(), DFSList[i].toId) == patternAdj[DFSList[i].fromId].end()) {
            patternAdj[DFSList[i].fromId].push_back(DFSList[i].toId);
        }
    }
    
    
    std::set<std::set< Edge > > subGraph;
    connectedComponents(pattenVector,patternAdj,subGraph);
    
    std::set<std::set<int> > finalTranSet;
    
    
    //input for MNI
    for(int i=0;i<this->DFSList.size();i++) {
        {
            std::set<int> temp;
            temp.insert(DFSList[i].fromId);
            finalTranSet.insert(temp);
        }
        {
            std::set<int> temp;
            temp.insert(DFSList[i].toId);
            finalTranSet.insert(temp);
        }
    }
    
    //for all subgraph
    for (std::set<std::set< Edge > >::iterator it=subGraph.begin(); it!=subGraph.end(); ++it) {
    
        //in one subgraph
        std::vector<int> VectorNauty;
        for (std::set<Edge>::iterator itv=it->begin(); itv!=it->end(); ++itv) {
            int from,to;
            from = itv->fromId;
            to = itv->toId;
            if (std::find(VectorNauty.begin(), VectorNauty.end(), from) == VectorNauty.end()) {
              VectorNauty.push_back(from);
            }
            if (std::find(VectorNauty.begin(), VectorNauty.end(), to) == VectorNauty.end()) {
              VectorNauty.push_back(to);
            }
        }
                
        int n,m,v;
        n = it->size(); //edge
        int nautySize = VectorNauty.size(); //vertex
        //std::cout<<std::endl; 
        //for (std::set<Edge>::iterator itv=it->begin(); itv!=it->end(); ++itv)  
        //    std::cout<<"<"<<itv->fromId<<","<<itv->toId<<"> ";
        //std::cout<<std::endl; 
        
        //note nauty require vertex id start from 0
        std::map<int,int> reverseMapIdNauty; //contain forword map (vId to nautyId)
        //cout<<"mapNauty:"<<endl;
        for(int i=0;i<VectorNauty.size();i++) {
            reverseMapIdNauty[VectorNauty[i]] = i; // map to VectorNauty
            //std::cout<<VectorNauty[i]<<" -> "<<i<<std::endl;
        }
                
        
        
        graph g[MAXN*MAXM];
        int lab[MAXN],ptn[MAXN],orbits[MAXN];
        static DEFAULTOPTIONS_GRAPH(options);
        statsblk stats;
        
        options.defaultptn = FALSE;
        m = SETWORDSNEEDED(nautySize);
        EMPTYGRAPH(g,m,nautySize);     
        
        for (std::set<Edge>::iterator itv=it->begin(); itv!=it->end(); ++itv)
            ADDONEEDGE(g,reverseMapIdNauty[itv->fromId],reverseMapIdNauty[itv->toId],m);   
        
        std::map<int,std::vector<int> > colorLable;
       
        for (std::set<Edge>::iterator itv=it->begin(); itv!=it->end(); ++itv) {
            if ( colorLable.find(patternLabel[itv->fromId]) == colorLable.end() ) {
                //init map
                colorLable[patternLabel[itv->fromId]] = std::vector<int>();
            } 
            if ( colorLable.find(patternLabel[itv->toId]) == colorLable.end() ) {
                //init map
                colorLable[patternLabel[itv->toId]] = std::vector<int>();
            }
        }
        
        for (std::set<Edge>::iterator itv=it->begin(); itv!=it->end(); ++itv) {
            //cout<<"v="<<v<<endl;
            if (std::find(colorLable[patternLabel[itv->fromId]].begin(), colorLable[patternLabel[itv->fromId] ].end(), itv->fromId) 
                                                            == colorLable[patternLabel[itv->fromId] ].end()) {
                /// add vetex to map
                colorLable[patternLabel[itv->fromId]].push_back(itv->fromId);
                //cout<<pattern[v].fromId<<" "<<patternLabel[pattern[v].fromId]<<endl;
            }
            if (std::find(colorLable[patternLabel[itv->toId]].begin(), colorLable[patternLabel[itv->toId] ].end(), itv->toId) 
                                                            == colorLable[patternLabel[itv->toId] ].end()) {
                /// add vetex to map
                colorLable[patternLabel[itv->toId]].push_back(itv->toId);
                //cout<<pattern[v].toId<<" "<<patternLabel[pattern[v].toId]<<endl;
            }
        }
        
        int labI = 0;
        for (std::map<int,std::vector<int> >::iterator itc=colorLable.begin(); itc!=colorLable.end(); ++itc) {
            //cout<<"color:"<<itc->first<<": ";
            if(labI > n)
                std::cout<<"Error labI > n!!!!"<<std::endl;
            for(int i=0;i<itc->second.size();i++) {
                //cout<<itc->second[i]<<" ";
                lab[labI] = reverseMapIdNauty[itc->second[i]];
                if(i == itc->second.size()-1)
                    ptn[labI] = 0;
                else 
                    ptn[labI] = 1;
                labI++;
            } 
            //cout<<endl;
        }
        
        densenauty(g,lab,ptn,orbits,&options,&stats,m,nautySize,NULL);
        
        std::map<int, std::set<int> > transitiveSet;
        for(v=0;v<nautySize;v++) {
            if ( transitiveSet.find(orbits[v]) == transitiveSet.end() ) {
                //init map
                transitiveSet[orbits[v]] = std::set<int>();
                //cout<<"Malloc "<<orbits[v]<<endl;
            } 
        }
        //std::cout<<"generate T"<<std::endl;
        for(v=0;v<nautySize;v++) {
            //std::cout<<VectorNauty[v]<<" In "<<orbits[v]<<std::endl;
            transitiveSet[orbits[v]].insert(VectorNauty[v]);
            //std::cout<<"check:"<<orbits[v]<<" "<<transitiveSet[orbits[v]].back()<<std::endl;
        }
        
        for (std::map<int,std::set<int> >::iterator its=transitiveSet.begin(); its!=transitiveSet.end(); ++its) {
            finalTranSet.insert(its->second);
        }
    }
    
    
    //create map array for occurence
    std::map<int,std::vector<int> > mapOccurence;
    for(int i=0;i<this->DFSList.size();i++) {
        if ( mapOccurence.find(DFSList[i].toId) == mapOccurence.end() ) {
            // not found
            std::vector<int> temp;
            mapOccurence[DFSList[i].toId] = temp;
        } else {
            // found
            continue;
        }
        for(int j=0;j<OccuranceList.size();j++) {
            mapOccurence[DFSList[i].toId].push_back(OccuranceList[j].EdgeList[i].to);
        }
    }
    
    for(int i=0;i<this->DFSList.size();i++) {
        if ( mapOccurence.find(DFSList[i].fromId) == mapOccurence.end() ) {
            // not found
            std::vector<int> temp;
            mapOccurence[DFSList[i].fromId] = temp;
        } else {
            // found
            continue;
        }
        for(int j=0;j<OccuranceList.size();j++) {
            mapOccurence[DFSList[i].fromId].push_back(OccuranceList[j].EdgeList[i].to);
        }
    }
    
    //std::set<std::set<int> > finalTranSet;
    //calcuate mi from transitive set
    for (std::set<std::set<int> >::iterator it=finalTranSet.begin(); it!=finalTranSet.end(); ++it) {
        
        int tmpMin = 0;
        
        std::set<std::set<int> > node_id_counts;
        for(int j=0;j<OccuranceList.size();j++) {
            std::set<int> nodeTmp;
            for (std::set<int> ::iterator vId=it->begin(); vId!=it->end(); ++vId) {
                nodeTmp.insert(mapOccurence[*vId][j]);    
            }
            node_id_counts.insert(nodeTmp);
        }
        tmpMin = node_id_counts.size();
        //std::cout<<"TempMin="<<tmpMin<<std::endl;
        if(min > tmpMin) 
            min = tmpMin;
    }

    
    tstop = dtime();
    ttime = tstop - tstart;
    this->m_time = ttime;
    return min;
}


//find sub graph
void MI::connectedComponents(std::vector<int> pattenVector,std::vector<std::vector<int> > patternAdj, std::set<std::set<Edge> > &subGraph)
{
    // Mark all the vertices as not visited
    int V = pattenVector.size();
    
    for (int v=0; v<V; v++)
    {
        bool *visited = new bool[V];
        for(int v = 0; v < V; v++)
            visited[v] = false;
 
        //if (visited[v] == false)
        {
            // print all reachable vertices
            // from v
            std::set<Edge> currentSub;
            DFSUtil(v, visited, pattenVector, patternAdj, subGraph, -1, currentSub);
 
            //cout << endl;
        }
    }
}

void MI::DFSUtil(int v, bool visited[], std::vector<int> pattenVector,std::vector<std::vector<int> > patternAdj, std::set<std::set<Edge> > &subGraph, int previousV, std::set<Edge> currentSub)
{
    int V = pattenVector.size();
    // Mark the current node as visited and print it
    visited[v] = true;
    //subGraph[subGraph.size()-1].push_back(v);
    if( previousV != -1){
        Edge tmp(previousV, v, previousV, v,0); //use only fromId toId
        currentSub.insert(tmp);
        subGraph.insert(currentSub);
    }
    //cout << v << " ";
 
    // Recur for all the vertices
    // adjacent to this vertex
    std::vector<int>::iterator i;
    for(i = patternAdj[v].begin(); i != patternAdj[v].end(); ++i)
        if(!visited[*i])
            DFSUtil(*i, visited, pattenVector, patternAdj, subGraph, v, currentSub);
}
