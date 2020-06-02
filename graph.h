#pragma once
#include <vector>
#include <stdio.h>
#include <queue>
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

    bool DFS(int i, vector<bool>& visited, int ii=-1) //是否能找到ii（找到返回true）。如果ii=-1永远返回false且输出遍历过程
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

    bool BFS(int start, vector<bool>& visited, int ii=-1)
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
            printf("v%d->",q_top);
            bool result=visitNode(q_top); //准备访问后面节点的队列
            if(result==true)
                return true;
        }
        return false;
    }

    vector<bool> genVisited()
    {
        vector<bool>visited;
        for(int i=0;i<this->nodeNum;i++)
            visited.push_back(false);
        return visited;
    }

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

    void setEdge(int n1, int n2, int weight)
    {
        //无向图，两边都设
        this->m[n1][n2]=weight;
        this->m[n2][n1]=weight;
    }

    bool zeroGraph()
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

    bool isCompletedGraph()
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

    void DFS(int i)
    {
        auto visited=this->genVisited();
        this->DFS(i,visited);
    }

    void BFS(int i)
    {
        auto visited=this->genVisited();
        this->BFS(i,visited);
    }

    bool isConnected()
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

    int getDegree(int j)
    {
        int result=0;
        for (int i = 0; i < this->nodeNum; i++ )
        {
            if(this->m[j][i]!=0)
                result+=1;
        }
        return result;
    }

    void output()
    {
        //fix:输出图，格式自定（如果实在想不出来怎么画直接输出邻接矩阵也行）
    }

};
