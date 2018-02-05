/***************************< File comment >*****************************/  
/* file name : MIsubV.cpp                                               */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 02/24/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/


/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/


#include<iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "MSEIV.h"

typedef unsigned int uint;
#include "warperMV.h"

using namespace std;

unsigned int MSEIV::support()
{
    int min = 0xffffffff;
    if(OccuranceList.size() == 0)
        return 0;
    if(DFSList.size() == 0)
        return 0;
    
    // preparing data for compute
    std::vector<int> pattenVector;
    std::map<int, int> pattenIndex;
    for(int i=0;i<this->DFSList.size();i++) {
        if (std::find(pattenVector.begin(), pattenVector.end(), DFSList[i].fromId) == pattenVector.end()) {
            pattenVector.push_back(DFSList[i].fromId);
        }
        if (std::find(pattenVector.begin(), pattenVector.end(), DFSList[i].toId) == pattenVector.end()) {
            pattenVector.push_back(DFSList[i].toId);
        }
        if(DFSList[i].to != -1) {
            pattenIndex[DFSList[i].toId] = (i*2)+1;
            //cout<<"pattenIndex:"<<DFSList[i].toId<<"::"<<(i*2)+1<<endl;
        }
        if(DFSList[i].from != -1) {
            pattenIndex[DFSList[i].fromId] = i*2;
            //cout<<"pattenIndex:"<<DFSList[i].fromId<<"::"<<(i*2)<<endl;
        }
    }
    
    for(int i=0;i<pattenVector.size();i++) {
        for(int j=i+1;j<pattenVector.size();j++) {
            //cout<<endl;
            //cout<<"Cal "<<i<<" "<<j<<endl;
            //cout<<"Map "<<pattenVector[i]<<" "<<pattenVector[j]<<endl;
            
            int fromIndex = pattenIndex[pattenVector[i]];
            int toIndex = pattenIndex[pattenVector[j]];
            
            //cout<<"index "<<fromIndex<<" "<<toIndex<<endl;
            
            int tmpMin=0;
            vector<Edge> EdgeList_tmp;
            vector<int> Vector_tmp;
            for(int k=0;k<OccuranceList.size();k++) {
                int from,to;
                if(fromIndex % 2 == 0) { // use from
                    from = OccuranceList[k].EdgeList[fromIndex/2].from;
                }
                else {
                    from = OccuranceList[k].EdgeList[fromIndex/2].to;
                }
                
                if(toIndex % 2 == 0) { // use from
                    to = OccuranceList[k].EdgeList[toIndex/2].from;
                }
                else {
                    to = OccuranceList[k].EdgeList[toIndex/2].to;
                }
                
                Edge tmpEdge(from,to,from,to,0);
                EdgeList_tmp.push_back(tmpEdge);
                if (std::find(Vector_tmp.begin(), Vector_tmp.end(), from) == Vector_tmp.end()) {
                  Vector_tmp.push_back(from);
                }
                if (std::find(Vector_tmp.begin(), Vector_tmp.end(), to) == Vector_tmp.end()) {
                  Vector_tmp.push_back(to);
                }
            }
            
            //create dumpy input
            map<int,int> reverseMapId;
            for(int i=0;i<Vector_tmp.size();i++) {
                reverseMapId[Vector_tmp[i]] = i;
            }
            vector< vector<int> > tmpIntput;
            WarperMVGraph *graph = WarperMVGraph_init(Vector_tmp.size());
            for(int i=0;i<Vector_tmp.size();i++) {
                vector<int> tmp;
                tmpIntput.push_back(tmp);
            }
            for(auto const &it : EdgeList_tmp) {
                //cout<< it.from<< " " <<it.to << ":"<< reverseMapId[it.from] <<" "<<reverseMapId[it.to]<<endl;
                if (std::find(tmpIntput[reverseMapId[it.from]].begin(), tmpIntput[reverseMapId[it.from]].end(), it.to)  == tmpIntput[reverseMapId[it.from]].end() 
                    && reverseMapId[it.from] != reverseMapId[it.to] 
                    && std::find(tmpIntput[reverseMapId[it.to]].begin(), tmpIntput[reverseMapId[it.to]].end(), it.from) == tmpIntput[reverseMapId[it.to]].end()         
                    ) {
                        //cout<< "g["<< reverseMapId[it.from] <<"].add("<< reverseMapId[it.to] <<");"<<endl;
                    tmpIntput[reverseMapId[it.from]].push_back(reverseMapId[it.to]);
                    WarperMVGraph_add_edge(graph, reverseMapId[it.from], reverseMapId[it.to]);
                }
            }
        
            //tmpMin = MSEI::maxMatching(tmpIntput);
            WarperMVEdgeList *lst = WarperMVMV_MaximumCardinalityMatching(graph);
            WarperMVEdgeListIterator *itr = lst->first;
            int count=0;
            while (itr != 0) {
        	    count++;
            	itr = itr->next;
            }
            tmpMin = count;
            //cout<<tmpMin<<endl;
            if(min == -1)
                min = tmpMin;
            else if(min > tmpMin) 
                min = tmpMin;
        }
    }
    return min;
}

