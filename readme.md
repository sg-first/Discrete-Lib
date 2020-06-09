Discrete Lib
=============
relation
---------
### void addPair(int a, int b)
* 向关系添加一个二元组
* `a`:二元组的第一个元素 `b`:二元组的第二个元组
* 返回值：无

### relation composite(const relation& r)

 - 关系的复合
 - `r`：一个新关系
 - 返回值：两个关系复合后的新关系

### bool isReflexivive()

 - 判断关系是否自反
 - 返回值：该关系是否为自反

### bool isIrreflexive()
 - 判断关系是否为反自反
 - 返回值：该关系是否为反自反
 
 ### bool isSymmetry()
  
 - 判断关系是否为对称
 - 返回值：该关系是否为对称
 
### bool isAntisymmetry()
 
 - 判断该关系是否为反对称
 - 返回值：该关系是否为反对称
 
 ### bool isTransitivity()
  
 - 判断该关系是否为传递
 - 返回值：该关系是否为传递
 
### relation TransitiveClosure()
 
 - 添加二元组，形成关系的传递闭包
 - 返回值：具有传递闭包的新关系
 
### relation reflexiveClosure()
 
 - 添加二元组，形成关系的自反闭包
 - 返回值：具有传递闭包的新关系
 
### relation symmetricClosure()
 
 - 添加二元组，形成关系的对称闭包
 - 返回值：具有对称闭包的新关系

graph
--------
### int getWeight(unsigned int i,unsigned int j) const
 - 获取某条边的权重
 - `i`:该边出发节点 `j`:该边到达节点
 - 返回值：该边权重

### void setEdge(unsigned int n1, unsigned int n2, int weight=1)
 - 设置某条边的权重
 - `n1`:该边出发节点 `n1`:该边到达节点 `weight`:设置的权重
 - 返回值：无

### unsigned int getNodeNum() const
 - 获得该图的节点数量
 - 返回值：该图的节点数量

### bool isCompleted() const
 - 判断该图是否是完全图
 - 返回值：该图是否是完全图

### void DFS(unsigned int i) const
 - 对该图进行深度优先遍历
 - `i`:起始节点
 - 返回值：无

### void BFS(unsigned int i) const
 - 对该图进行广度优先遍历
 - `i`:起始节点
 - 返回值：无

### bool isConnected() const
 - 判断该图是否联通
 - 返回值：该图是否联通

### int getDegree(int j) const
 - 获取一个节点的度
 - `i`:要获取的节点
 - 返回值：该节点的度

### graph minimumSpanningTree() const
 - 计算该图的最小生成树
 - 返回值：该图的最小生成树

### int shortestPath(unsigned int v,unsigned int vi, bool isReset=false)
 - 计算两个节点间最短路径长度
 - `v`:起始节点 `vi`:到达节点 `isReset`:是否重新计算（计算一个节点`v`的最短路径后会将其到其它所有节点的最短路径缓存，下次再查询`v`到某点的最短路径时直接使用。这个参数指示是否抛弃当前的缓存重新计算）
 - 返回值：两点间的最短路径长度

### bool isIsolated(unsigned int v) const
 - 判断一个节点是否与其它节点都不连接
 - `v`:要判断的节点
 - 返回值：该节点是否孤立

### int getEdgeNum() const
 - 得到该图边的总数
 - 返回值：该图边的总数

### bool isPlanar()
 - 判断该图是否是对偶图
 - 返回值：该图是否是对偶图

test
----------
* code:
``` cpp
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
    cout << "TransitiveClosure:" << endl;
    auto L= A.TransitiveClosure();
    L.output();
    cout << "reflexiveClosure:" << endl;
    auto F=A.reflexiveClosure();
    F.output();
    cout << "symmetricClosure:" << endl;
    auto D= A.symmetricClosure();
    D.output();
    B.addPair(2, 5);
    cout << "composite" << endl;
    auto C=A.composite(B);
    C.output();
}
```

* result:
```
0 2 1 0 0 0
2 0 3 4 0 0
1 3 0 4 1 0
0 4 4 0 5 0
0 0 1 5 0 1
0 0 0 0 1 0
connection:1
complete:0
zero:0
3 degree:3
mini tree:
0 2 1 0 0 0
2 0 0 4 0 0
1 0 0 0 1 0
0 4 0 0 0 0
0 0 1 0 0 1
0 0 0 0 1 0
0 5 path:3
planar:1
Reflexivive:0
Irreflexive:0
Symmetry:1
Antisymmetry:0
Transitivity:0
TransitiveClosure:
1,1
1,2
1,3
2,1
2,2
2,3
3,1
3,2
3,3
reflexiveClosure:
1,1
1,2
2,1
2,2
2,3
3,2
3,3
symmetricClosure:
1,1
1,2
2,1
2,2
2,3
3,2
composite
1,1
1,2
1,5
2,1
2,2
2,3
2,5
3,2
3,5
```