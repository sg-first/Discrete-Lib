#pragma once
#include <vector>
#include <stdio.h>
#include <queue>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

class graph
{
private:
    int nodeNum;
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

    bool DFS(int i, vector<bool>& visited, int ii=-1) const //是否能找到ii（找到返回true）。如果ii=-1永远返回false且输出遍历过程
    {
        if(ii==-1)
            printf("v%d->",i); //输出当前遍历过的结点

        visited[i] = true; //设置当前结点的布尔值为真
        for(int j=0; j<this->nodeNum; j++)
        {
            if(this->m[i][j]!=0 && !visited[j]) //判断当前边是否存在。如果存在并且没被访问过，就根据该节点进行DFS深搜。
            {
                bool result=DFS(j,visited,ii);
                if(j==ii || result==false)
                    return true;
            }
        }
        return false;
    }

    bool BFS(int start, vector<bool>& visited, int ii=-1) const
    {
        queue<int> q;
        int q_top;

        if(ii==-1)
            printf("v%d->",start);

        visited[start] = true;

        //访问一个节点连接到的节点
        auto visitNode=[&q,&visited,ii,this](int start)
        {
            for (int i = 0; i < this->nodeNum; i++ )
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
        for(int i=0;i<this->nodeNum;i++)
            visited.push_back(false);
        return visited;
    }

    static set<int> getSetDiff(set<int> A, set<int> B)
    {
        set<int> C;
        set_difference( A.begin(), A.end(),B.begin(), B.end(),inserter( C, C.begin() ) );
        return C;
    }

    void Dijkstra(int v) //找v到vi最短路径
    {
        vector< vector<int> > table; //Dijkstra表
        vector< vector<int> > path; //存每行的路径（表头列）
        for(int i=0;i<this->nodeNum;i++) //添加行向量
        {
            table.push_back(vector<int>());
            path.push_back(vector<int>());
        }
        int gonePathLen=0; //已经走过的路径长度
        //初始化第一行
        path[0].push_back(v);
        for(int i=0;i<this->nodeNum;i++)
            table[0].push_back(this->m[0][i]); //把到自身的也放进里面去，但是不用（因为不支持添加只想自己的边所以不用特判）。这里注意，0代表长度为INF而不是最短
        //找一行中最小值的函数
        auto findMin=[&table,this](int sub)
        {
            int min=0;
            int node=-1;
            for(int i=0;i<this->nodeNum;i++)
            {
                if(table[sub][i]!=0) //有边
                {
                    if(table[sub][i]<min || min==0)
                    {
                        min=table[sub][i];
                        node=i;
                    }
                }
            }
            return make_pair(min,node);
        };
        //判断元素是否存在于path[sub]中
        auto isExist=[&path](int sub, int node)
        {
            for(int i : path[sub])
            {
                if(node==i)
                    return true;
            }
            return false;
        };
        //填充后面的行
        for(int ii=1;ii<this->nodeNum-1;ii++)
        {
            path[ii]=path[ii-1]; //基于上一行已经走到的节点继续走
            //看看这一步往哪走
            int min,node;
            auto result=findMin(ii-1);
            min=result.first;
            node=result.second;
            //根据这一步要走的节点更新
            gonePathLen+=min;
            path[ii].push_back(node);
            //填充table
            for(int i=0;i<this->nodeNum;i++)
            {
                int pushVal=0;
                if(!isExist(ii,i)) //确认目前没走过这个点才能添加，否则添加0（不能重复走）
                    pushVal=this->m[node][i]+gonePathLen;
                table[ii].push_back(pushVal);
            }
        }
        //竖着查table，找到每个节点的最短路径长度并放在table[0]（因为要的是路径不是长度所以这里注释掉）
        /*for(int i=0;i<this->nodeNum;i++) //找每个节点的最短路径
        {
            int min=0;
            for(int j=1;j<this->nodeNum;j++) //对每个节点访问每一行（因为要对第0行更新，所以从第一行开始查就行了）
            {
                if(table[j][i]!=0) //有边
                {
                    if(table[j][i]<min || min==0)
                        min=table[j][i];
                }
            }
            table[0][i]=min;
        }
        //记录结果
        this->dijkstraV=v;
        this->allShortPath=table[0];*/

        this->allShortPath.clear();
        for(int i=0;i<this->nodeNum;i++)
            this->allShortPath.push_back(vector<int>());
        for(vector<int> i : path)
        {
            int node=*(i.end()); //最后一个节点就是该路径的终点
            this->allShortPath[node]=i; //以终点为索引
        }
    }

    //Dijkstra记忆化
    int dijkstraV=-1;
    vector< vector<int> > allShortPath;

public:
    graph(int nodeNum) : nodeNum(nodeNum)
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

    int getNodeNum() const { return this->nodeNum; }
    int getWeight(int i,int j) const { return this->m[i][j]; }

    void setEdge(int n1, int n2, int weight)
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

    void DFS(int i) const
    {
        auto visited=this->genVisited();
        this->DFS(i,visited);
    }

    void BFS(int i) const
    {
        auto visited=this->genVisited();
        this->BFS(i,visited);
    }

    bool isConnected() const
    {
        for(int v = 0;v<this->nodeNum-1;v++) // 从0开始搜索，如果能遍访所有顶点 则说明连通
        {
            for(int vi=1;vi<this->nodeNum;vi++)
            {
                auto visited=this->genVisited();
                if(DFS(v,visited,vi)==false) //从一个点出发遍历看能不能到某点
                    return false;
            }
        }
        return true;
    }

    int getDegree(int j) const
    {
        int result=0;
        for (int i = 0; i < this->nodeNum; i++ )
        {
            if(this->m[j][i]!=0)
                result+=1;
        }
        return result;
    }

    graph minimumSpanningTree() const //Prim算法最小生成树
    {
        graph result(this->nodeNum);
        set<int> allNodeSet; //所有节点的集合
        for(int i=0;i<this->nodeNum;i++)
            allNodeSet.insert(i);
        set<int> nodeSet; //结果树中已包含的节点集合
        nodeSet.insert(0); //0作为起始点

        while(nodeSet.size()!=allNodeSet.size())
        {
            set<int> diffSet=getSetDiff(allNodeSet,nodeSet); //计算量集合差集
            //从差集中找到另一点b使得点b到集合nodeSet中任意一点的权值最小，
            int minW=0;
            int nodeSetI;
            int diffSetJ;

            for(int i : nodeSet)
            {
                for(int j : diffSet)
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

    vector<int> shortestPath(int v,int vi, bool isReset=false)
    {
        if(v!=this->dijkstraV || isReset)
            this->Dijkstra(v);
        return this->allShortPath[vi];
    }

    bool isIsolated(int v) const
    {
        for(int i=0;i<this->nodeNum;i++)
        {
            if(this->m[v][i]!=0)
                return false;
        }
        return true;
    }

    int getEdgeNum() const
    {
        int num=0;
        for ( int i = 0; i <= this->getNodeNum(); ++i )
        {
            for(int j=0;j<this->getNodeNum();j++)
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
                printf("%g ", m[i][j]);
            }
            printf("\n");
        }
    }

    bool isPlanar();
};
