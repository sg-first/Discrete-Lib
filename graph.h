#pragma once

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

    void output()
    {
        //fix:输出图，格式自定（如果实在想不出来怎么画直接输出邻接矩阵也行）
    }

};
