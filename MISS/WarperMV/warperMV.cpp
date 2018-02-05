
#ifdef __cplusplus
extern "C"{
#endif 

typedef unsigned int uint;

#include "libmv.h"

#ifdef __cplusplus
}
#endif

#include "warperMV.h"

WarperMVGraph *WarperMVGraph_init (unsigned int size) {
    Graph *graph =  Graph_init(size);
    return (WarperMVGraph*)graph;
}

void WarperMVGraph_add_edge (WarperMVGraph * g, unsigned int v1, unsigned int v2){
    Graph_add_edge((Graph*)g, v1,v2);
}

void WarperMVEdgeList_delete (WarperMVEdgeList * lst){
    EdgeList_delete((EdgeList*)lst);
}

void WarperMVGraph_delete (WarperMVGraph * g){
    Graph_delete((Graph*)g);
}

/**
 * Given a graph g, returns a maximum cardinality matching for g.
 * @return An EdgeList instance; the edges in the list form a maximum-cardinality matching.
 * @param g A graph.
 */
WarperMVEdgeList *WarperMVMV_MaximumCardinalityMatching (WarperMVGraph * g){
    return (WarperMVEdgeList*)MV_MaximumCardinalityMatching((Graph*)g);
}