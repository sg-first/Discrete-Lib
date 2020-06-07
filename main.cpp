#include <iostream>
#include "relation.h"
#include "graph.h"
using namespace std;

int main()
{
    graph g(6);
    g.setEdge(0,1,2);
    g.setEdge(0,2);
    g.setEdge(1,2,3);
    g.setEdge(1,3,4);
    g.setEdge(3,2,4);
    g.setEdge(2,4);
    g.setEdge(3,4,5);
    g.setEdge(4,5);
    g.output();

    cout<<"connection:"<<g.isConnected()<<endl;
    cout<<"complete:"<<g.isCompleted()<<endl;
    cout<<"zero:"<<g.isZero()<<endl;
    cout<<"3 degree"<<g.getDegree(3)<<endl;
    cout<<"mini tree:"<<endl;
    auto miniTree=g.minimumSpanningTree();
    miniTree.output();
    cout<<"0 5 path:"<<g.shortestPath(0,5)<<endl;
    cout<<"planar:"<<g.isPlanar()<<endl;

    relation  A;
    relation  B;
    A.addPair(1, 2);
    A.addPair(1, 1);
    A.addPair(2, 2);
    A.addPair(2, 3);
    A.addPair(3, 2);
    A.addPair(2, 1);
    cout<<"Reflexivive:"<<A.isReflexivive()<<endl;
    cout<<"Irreflexive:"<<A.isIrreflexive()<<endl;
    cout<<"Symmetry:"<<A.isSymmetry()<<endl;
    cout<<"Antisymmetry:"<<A.isAntisymmetry()<<endl;
    cout<<"Transitivity:"<<A.isTransitivity()<<endl;
    B.addPair(2, 5);
    cout << "composite" << endl;
    auto C=A.composite(B);
    C.output();
}
