#pragma once
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

class relation
{
public:
    vector< pair<int, int> > allPair;

    relation() {}
    relation(const relation& r)
    {
        this->allPair = r.allPair;
    }
    relation& operator=(const relation& r)
    {
        this->allPair = r.allPair;
    }

    void addPair(int a, int b)
    {
        allPair.push_back(make_pair(a, b));
    }

    void output()
    {
        for (auto i : this->allPair)
            cout << i.first << "," << i.second << endl;
    }

    relation composite(const relation& r)
    {
        //fix:this与r关系的复合，返回复合后的新关系
        for (auto i : this->allPair)
        {
            int a = i.second;
            int b = i.first;
            for (auto j : r.allPair)
            {
                if (a == j.first)
                {
                    addPair(b, j.second);
                }
            }
        }
        output();
        return *this;

    }

    bool isReflexivive()
    {
        //fix:this是否是自反的
        for (auto i : this->allPair)
        {
            if (i.first != i.second)
            {
                cout << "NO" << endl;
                return  false;
            }
        }
        return true;
    }

    bool isIrreflexive()
    {
        //fix:this是否是反自反的
        for (auto i : this->allPair)
        {
            if (i.first == i.second)
            {
                cout << "NO" << endl;
                return  false;
            }
        }
        return true;
    }

    bool isSymmetry()
    {
        //fix:this是否是对称的
        bool ss = false;
        for (auto i : this->allPair)
        {
            int a, b;
            a = i.first;
            b = i.second;
            bool  ss =true;
            for (auto i : this->allPair)
            {
                if (i.first == b && i.second == a)
                {
            
                    ss = false;//false为对称关系；
                }
            }
        }
        return ss;
    }

    bool isAntisymmetry()
    {
        //fix:this是否是反对称的
        for (auto i : this->allPair)
        {
            int a, b;
            a = i.first;
            b = i.second;
            for (auto i : this->allPair)
            {
                if (i.first == b && i.second == a)
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool isTransitivity()
    {
        //fix:this是否是传递的
        bool ss = false;
        for (auto i : this->allPair)
        {
            int a, b;
            a = i.first;
            b = i.second;
            bool  ss = true;
            for (auto i : this->allPair)
            {
                if (i.first == b)//寻找<x,y><y,z>
                {
                    int c = i.second;
                    for (auto i : this->allPair)
                    {
                        if (i.first == a && i.second == c)//找到<x,z>
                        {
                            ss = false;//false表示为传递关系；
                        }            
                    }
                }
                
            }
        }
        return ss;
    }
};
