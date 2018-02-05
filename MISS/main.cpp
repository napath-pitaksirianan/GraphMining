/***************************< File comment >*****************************/  
/* file name : main.h                                                   */ 
/* file description :                                                   */ 
/*----------------------------------------------------------------------*/ 
/* version : 1.0                                                        */ 
/*----------------------------------------------------------------------*/ 
/* create : 02/15/2017                                                  */ 
/* programmer : Napath Pitaksirianan                                    */ 
/************************************************************************/


/*----------------------------------------------------------------------*/ 
/*                           Include file                               */ 
/*----------------------------------------------------------------------*/

#include<iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "Occurance.h"
#include "MSEIV.h"
#include "util.h"

using namespace std;

int printAll(vector<Occurance> OccuranceList) {
    for(int i=0;i<OccuranceList.size();i++) {
        for(int j=0;j<OccuranceList[i].EdgeList.size();j++) {
            cout<<OccuranceList[i].EdgeList[j].from<<" "<<OccuranceList[i].EdgeList[j].to;
            if(j!=OccuranceList[i].EdgeList.size()-1){
                cout<<" :: ";
            }
        }
        cout<<endl;
    }
    return 0;
}

int printDFS(Occurance Occurance) {
    for(int j=0;j<Occurance.EdgeList.size();j++) {
        cout<<Occurance.EdgeList[j].fromId<<" "<<Occurance.EdgeList[j].toId;
        if(j!=Occurance.EdgeList.size()-1){
            cout<<" :: ";
        }
    }
    cout<<endl;
    return 0;
}

int printDFSLabel(Occurance Occurance) {
    for(int j=0;j<Occurance.EdgeList.size();j++) {
        cout<<Occurance.EdgeList[j].from<<" "<<Occurance.EdgeList[j].to;
        if(j!=Occurance.EdgeList.size()-1){
            cout<<" :: ";
        }
    }
    cout<<endl;
    return 0;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout<<"Usage:"<<argv[0]<<" filename"<<endl;
        return -1;
    }
    
    int verifyFlag = verifyInputFile(argv[1]);
    if(verifyFlag != 0) {
        cout<<"Error in verify inputfile on line "<<verifyFlag<<endl;
        return -1;
    }
    //cerr<<"Start working!!!"<<endl;
    
    std::ifstream infile(argv[1]);
    int from, to;
    int fromId, toId;
    //cerr<<"OCCsize, PatternSize, MNI, MNI time, MIS, MIS time, MISUB, MISUB time, MSEI, MSEI time, MIsubV, MIsubV time, MSEIV, MSEIV time"<<endl;
    cerr<<"OCCsize, PatternSize, MNI, MNI time, MIS, MIS time, MSEI, MSEI time, MI, MI time"<<endl;
    while(1) {
        int DFSCODE = 1;
        vector<Occurance> OccuranceList;
        vector<Edge> DFSList;
        vector<Edge> EdList;
        while (infile >> fromId >> toId >> from >> to)
        {
            if(from == -2 && to == -2 && DFSCODE == 0) {
                if(EdList.size() == DFSList.size()) {
                    Occurance tmpOC(EdList);
                    OccuranceList.push_back(tmpOC);
                    EdList.clear();
                }
            }
            else if(from == -2 && to == -2 && DFSCODE == 1) {
                DFSCODE = 0;
            }
            else if(from == -3 && to == -3) {
                if(DFSList.size()==0){ 
                    break;
                }
                //printDFS(DFSList);
                //printDFSLabel(DFSList);
                //cout<<"********"<<endl;
                //printAll(OccuranceList);
                std::cout << std::fixed;
                std::cout << std::setprecision(5);
                
                cerr<<OccuranceList.size()<<",";
                cerr<<DFSList.size()<<",";
                
                /*
                
                MNI tmp(OccuranceList,DFSList);
                cerr<<tmp.value<<","<<tmp.m_time<<",";               
                
                if(OccuranceList.size() < 20000) {
                    MIS tmp2(OccuranceList,DFSList);
                
                    if(tmp2.value == 0) {
                        cerr<<"N/A, N/A,";               
                    }
                    else{
                        cerr<<tmp2.value<<","<<tmp2.m_time<<",";       
                    }    
                }
                else {
                    cerr<<"N/A, N/A,";               
                }
                */
                                
                //MIsub tmp3(OccuranceList,DFSList);
                //cerr<<tmp3.value<<","<<tmp3.m_time<<",";                
                
                //MVCsub tmp4(OccuranceList,DFSList);
                
                //MSEI tmp5(OccuranceList,DFSList);
                //cerr<<tmp5.value<<","<<tmp5.m_time<<",";               
                
                //MIsubV tmp6(OccuranceList,DFSList);
                //cerr<<tmp6.value<<","<<tmp6.m_time<<",";                
                
                MSEIV tmp7(OccuranceList,DFSList);
                cerr<<tmp7.value<<","<<tmp7.m_time<<",";
                 
                
                //MI tmp8(OccuranceList,DFSList);
                //cerr<<tmp8.value<<","<<tmp8.m_time<<",";
                
                cout<<endl;
                break;
            }
            else if(from == -4 && to == -4) {
                cerr<<"Done"<<endl;
                return 0;
            }
            else if(DFSCODE == 1) {
                Edge Ed(fromId,toId,from,to, 0);
                DFSList.push_back(Ed);
            }
            else {
                Edge Ed(fromId,toId,from,to, 0);
                EdList.push_back(Ed);
            }
        }
    }
}

