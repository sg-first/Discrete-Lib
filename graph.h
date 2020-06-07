#pragma once
#include <vector>
#include <stdio.h>
#include <queue>
#include <set>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

class graph
{
private:
    unsigned int nodeNum;
    int **m;

    void malloc()
    {
        this->m = new int*[nodeNum]; //给第一维分配空间
        for (unsigned int i = 0; i < nodeNum; i++)
            this->m[i] = new int[nodeNum]; //给第二维分配空间
    }

    void copy(const graph& m2)
    {
        this->nodeNum = m2.nodeNum;
        this->malloc();
        for (unsigned int i = 0; i < nodeNum; i++)
        {
            for (unsigned int j = 0; j < nodeNum; j++)
                this->m[i][j] = m2.m[i][j];
        }
    }

    void free()
    {
        for (unsigned int i = 0; i < nodeNum; i++)
                delete[] m[i];
        delete[] m;
    }

    bool DFS(unsigned int i, vector<bool>& visited, int ii=-1) const //是否能找到ii（找到返回true）。如果ii=-1永远返回false且输出遍历过程
    {
        if(ii==-1)
            printf("v%d->",i); //输出当前遍历过的结点

        visited[i] = true; //设置当前结点的布尔值为真
        for (unsigned int j=0; j<this->nodeNum; j++)
        {
            if(this->m[i][j]!=0 && !visited[j]) //判断当前边是否存在。如果存在并且没被访问过，就根据该节点进行DFS深搜。
            {
                if(j==ii)
                    return true; //这个就找到了
                bool result=DFS(j,visited,ii);
                if(result==true) //搜索之后找到了
                    return true;
            }
        }
        return false;
    }

    bool BFS(unsigned int start, vector<bool>& visited, int ii=-1) const
    {
        queue<unsigned int> q;
        unsigned int q_top;

        if(ii==-1)
            printf("v%d->",start);

        visited[start] = true;

        //访问一个节点连接到的节点
        auto visitNode=[&q,&visited,ii,this](unsigned int start)
        {
            for (unsigned int i = 0; i < this->nodeNum; i++ )
            {
                if(this->m[start][i] == 1 && visited[i] == false)
                {
                    q.push(i); //把准备新访问的放到队列里
                    visited[i] = true;
                    if(i==ii && ii!=-1)
                        return true; //搜索模式找到节点，准备返回
                }
            }
            return false;
        };

        bool result=visitNode(start); //准备第一个队列
        if(result==true)
            return true;

        while(!q.empty())
        {
            q_top = q.front();
            q.pop();

            if(ii==-1)
                printf("v%d->",q_top);

            bool result=visitNode(q_top); //准备访问后面节点的队列
            if(result==true)
                return true;
        }
        return false;
    }

    vector<bool> genVisited() const
    {
        vector<bool>visited;
        for(unsigned int i=0;i<this->nodeNum;i++)
            visited.push_back(false);
        return visited;
    }

    const int INF = 0x3f3f3f;//不能取得太大（dijikstra中会用到，其余情况没边用0表示即可）

    void dijkstra(unsigned int beg)
    {
        vector<int> lowcost; //如果有需要也可以保存这个
        vector<int> pre;
        vector< vector<int> > path;
        dijkstraV=beg;

        unsigned int N = this->nodeNum;
        vector<bool> visited(N, false);
        for (unsigned int i = 0;i < N;++i) {//初始化lowcost和pre
            lowcost.push_back(INF);
            pre.push_back(-1);
            path.push_back(vector<int>());
        }

        lowcost[beg] = 0;//出发点到自己的最短路径是0

        vector<int>nowPath;

        for (unsigned int i = 0;i < N;++i)
        {
            int newNode = -1;//下一个要被选中的点的编号, 初始化为 - 1
            int MinWeight=INF;//与当前节点相邻的边的最小权值
            //第一个for，遍历所有的未被访问过的节点，选中节点（已选节点之外的离出发点距离最短的点）
            for (unsigned int j = 0;j < N;++j) {
                if (!visited[j] && lowcost[j] < MinWeight) {
                    MinWeight = lowcost[j];
                    newNode = j;
                }
            }

            if(-1==newNode)
                break;//图不连通时，退出

            visited[newNode] = true;//将中间点标记为已访问状态
            nowPath.push_back(newNode);

            for (unsigned int j = 0;j < N;++j) {
                if (!visited[j] && this->m[newNode][j]!=0)
                {
                    if(lowcost[newNode] + this->m[newNode][j] < lowcost[j])
                    {
                        lowcost[j] = lowcost[newNode] + this->m[newNode][j]; //到newNode之后再到j的距离
                        pre[j] = newNode;
                        path[j] = nowPath;
                    }
                }
            }
        }

        //保存
        //this->path=path;
        this->lowcost=lowcost;
        this->dijkstraV=beg;
    }

    //Dijkstra记忆化
    int dijkstraV=-1;
    vector<int> lowcost;
    vector< vector<int> > path;

public:
    graph(unsigned int nodeNum) : nodeNum(nodeNum)
    {
        this->malloc();
        //初始化为零矩阵
        for (unsigned int i = 0; i < nodeNum; i++)
        {
            for (unsigned int j = 0; j < nodeNum; j++)
                this->m[i][j] = 0;
        }
    }

    ~graph()
    {
        this->free();
    }

    graph(const graph& v)
    {
        this->copy(v);
    }

    graph& operator=(const graph& m2)
    {
        this->free();
        this->copy(m2);
        return *this;
    }

    unsigned int getNodeNum() const { return this->nodeNum; }
    int getWeight(unsigned int i,unsigned int j) const { return this->m[i][j]; }

    void setEdge(unsigned int n1, unsigned int n2, int weight=1)
    {
        if(n1==n2)
            throw string("不支持自环");
        //无向图，两边都设
        this->m[n1][n2]=weight;
        this->m[n2][n1]=weight;
    }

    bool isZero() const
    {
        for (unsigned int i = 0; i < nodeNum; i++)
        {
            for (unsigned int j = 0; j < nodeNum; j++)
            {
                if(this->m[i][j]!=0)
                    return false;
            }
        }
        return true;
    }

    bool isCompleted() const
    {
        for (unsigned int i = 0; i < nodeNum; i++)
        {
            for (unsigned int j = 0; j < nodeNum; j++)
            {
                if(this->m[i][j]==0)
                    return false;
            }
        }
        return true;
    }

    void DFS(unsigned int i) const
    {
        auto visited=this->genVisited();
        this->DFS(i,visited);
    }

    void BFS(unsigned int i) const
    {
        auto visited=this->genVisited();
        this->BFS(i,visited);
    }

    bool isConnected() const
    {
        for(unsigned int v = 0;v<this->nodeNum-1;v++) // 从0开始搜索，如果能遍访所有顶点 则说明连通
        {
            for(unsigned int vi=1;vi<this->nodeNum;vi++)
            {
                if(vi==v)
                    continue; //不检测自环
                else
                {
                    auto visited=this->genVisited();
                    if(DFS(v,visited,vi)==false) //从一个点出发遍历看能不能到某点
                        return false;
                }
            }
        }
        return true;
    }

    int getDegree(int j) const
    {
        int result=0;
        for (unsigned int i = 0; i < this->nodeNum; i++ )
        {
            if(this->m[j][i]!=0)
                result+=1;
        }
        return result;
    }

    graph minimumSpanningTree() const //Prim算法最小生成树
    {
        graph result(this->nodeNum);
        set<unsigned int> allNodeSet; //所有节点的集合
        for(unsigned int i=0;i<this->nodeNum;i++)
            allNodeSet.insert(i);
        set<unsigned int> nodeSet; //结果树中已包含的节点集合
        nodeSet.insert(0); //0作为起始点

        auto getSetDiff=[](set<unsigned int> A, set<unsigned int> B)
        {
            set<unsigned int> C;
            set_difference( A.begin(), A.end(),B.begin(), B.end(),inserter( C, C.begin() ) );
            return C;
        };

        while(nodeSet.size()!=allNodeSet.size())
        {
            set<unsigned int> diffSet=getSetDiff(allNodeSet,nodeSet); //计算量集合差集
            //从差集中找到另一点b使得点b到集合nodeSet中任意一点的权值最小，
            int minW=0;
            unsigned int nodeSetI;
            unsigned int diffSetJ;

            for(auto i : nodeSet)
            {
                for(auto j : diffSet)
                {
                    if(this->m[i][j]!=0)
                    {
                        if(this->m[i][j]<minW || minW==0)
                        {
                            minW=this->m[i][j];
                            nodeSetI=i;
                            diffSetJ=j;
                        }
                    }
                }
            }
            //将b点也加入集合nodeSet
            nodeSet.insert(diffSetJ);
            //将两点的连接加入result图
            result.setEdge(nodeSetI,diffSetJ,minW);
        }

        return result;
    }

    int shortestPath(unsigned int v,unsigned int vi, bool isReset=false)
    {
        if(v!=this->dijkstraV || isReset)
            this->dijkstra(v);
        return this->lowcost[vi];
    }

    bool isIsolated(unsigned int v) const
    {
        for(unsigned int i=0;i<this->nodeNum;i++)
        {
            if(this->m[v][i]!=0)
                return false;
        }
        return true;
    }

    int getEdgeNum() const
    {
        int num=0;
        for (unsigned int i = 0; i <= this->getNodeNum(); ++i )
        {
            for(unsigned int j=0;j<this->getNodeNum();j++)
            {
                if(this->getWeight(i,j)!=0)
                    num++;
            }
        }
        return num;
    }

    //graph toDual();

    void output() const
    {
        for (unsigned int i = 0; i < this->nodeNum; i++)
        {
            for (unsigned int j = 0; j < this->nodeNum; j++)
            {
                printf("%d ", m[i][j]);
            }
            printf("\n");
        }
    }

    bool isPlanar();
};
