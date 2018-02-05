#ifndef WARPERMV_H
#define WARPERMV_H

#if 0
    unsigned int size=8;
    WarperMVGraph *graph = WarperMVGraph_init(size);
    WarperMVGraph_add_edge(graph, 0, 1);
    WarperMVGraph_add_edge(graph, 0, 4);
    WarperMVGraph_add_edge(graph, 2, 3);
    WarperMVGraph_add_edge(graph, 3, 4);
    WarperMVGraph_add_edge(graph, 4, 5);
    WarperMVGraph_add_edge(graph, 3, 7);
    WarperMVGraph_add_edge(graph, 6, 7);

    WarperMVEdgeList *lst = WarperMVMV_MaximumCardinalityMatching(graph);
    WarperMVEdgeListIterator *itr = lst->first;
    int count=0;
    while (itr != 0) {
    	WarperMVEdge edge = itr->value;
	    count++;
    	itr = itr->next;
    }
    WarperMVEdgeList_delete(lst);
    std::cout<<count<<std::endl;
    WarperMVGraph_delete(graph);
    
    return 0; 
#endif

typedef struct {} WarperMVGraph;

typedef struct
{
  unsigned int v1, v2;
} WarperMVEdge;

typedef struct WarperMVEdgeListIterator
{
  WarperMVEdge value;
  struct WarperMVEdgeListIterator *next;
} WarperMVEdgeListIterator;

typedef struct
{
  WarperMVEdgeListIterator *first, *last;
} WarperMVEdgeList;

WarperMVGraph *WarperMVGraph_init (unsigned int size);

void WarperMVGraph_add_edge (WarperMVGraph * g, unsigned int v1, unsigned int v2);

void WarperMVEdgeList_delete (WarperMVEdgeList * lst);
void WarperMVGraph_delete (WarperMVGraph * g);

/**
 * Given a graph g, returns a maximum cardinality matching for g.
 * @return An EdgeList instance; the edges in the list form a maximum-cardinality matching.
 * @param g A graph.
 */
WarperMVEdgeList *WarperMVMV_MaximumCardinalityMatching (WarperMVGraph * g);

#endif // LIBMV_H
