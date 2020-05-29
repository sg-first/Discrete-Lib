#pragma once
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

class relation
{
public:
    vector< pair<int,int> > allPair;

    relation(){}
    relation(const relation &r)
    {
        this->allPair=r.allPair;
    }
    relation& operator=(const relation& r)
    {
        this->allPair=r.allPair;
    }

    void addPair(int a,int b)
    {
        allPair.push_back(make_pair(a,b));
    }

    void output()
    {
        for(auto i : this->allPair)
            cout<<i.first<<","<<i.second<<endl;
    }

    relation composite(const relation& r)
    {
        //fix:this与r关系的复合，返回复合后的新关系
    }

    bool isReflexivive()
    {
        //fix:this是否是自反的
    }

    bool isIrreflexive()
    {
        //fix:this是否是反自反的
    }

    bool isSymmetry()
    {
        //fix:this是否是对称的
    }

    bool isAntisymmetry()
    {
        //fix:this是否是反对称的
    }

    bool isTransitivity()
    {
        //fix:this是否是传递的
    }
};
