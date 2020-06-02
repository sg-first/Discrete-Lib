#pragma once
#include <utility>
#include <set>
#include <iostream>
using namespace std;

class relation
{
public:
    set< pair<int, int> > allPair;

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
        allPair.insert(make_pair(a, b));
    }

    void output()
    {
        for (auto i : this->allPair)
            cout << i.first << "," << i.second << endl;
    }

    relation composite(const relation& r)
    {
        relation result(*this);
        for (auto i : this->allPair)
        {
            int a = i.second;
            int b = i.first;
            for (auto j : r.allPair)
            {
                if (a == j.first)
                {
                    result.addPair(b, j.second); //result开始和this一样，所以前面都用this，这里修改就用result
                }
            }
        }
        return result;
    }

    bool isReflexivive()
    {
        //fix:自反只是要求每个元素a都有<a,a>，不排斥有<a,b>，只要有<b,b>就行
        for (auto i : this->allPair)
        {
            if (i.first != i.second)
                return false;
        }
        return true;
    }

    bool isIrreflexive()
    {
        //fix:同上
        for (auto i : this->allPair)
        {
            if (i.first == i.second)
                return false;
        }
        return true;
    }

    bool isSymmetry()
    {
        for (auto i : this->allPair)
        {
            int a, b;
            a = i.first;
            b = i.second;
            bool flag=false;
            for (auto i : this->allPair)
            {
                if (i.first == b && i.second == a)
                    flag=true; //找到一个对称的就是对称
            }
            if(flag==false)
                return false;
        }
        return true;
    }

    bool isAntisymmetry()
    {
        for (auto i : this->allPair)
        {
            int a, b;
            a = i.first;
            b = i.second;
            for (auto i : this->allPair)
            {
                if (i.first == b && i.second == a)
                    return false;
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

    relation reflexiveClosure()
    {
        relation result(*this);
        for (auto i : this->allPair)
        {
            result.addPair(i.first,i.first);
            result.addPair(i.second,i.second);
        }
        return result;
    }

    relation symmetricClosure()
    {
        relation result(*this);
        for (auto i : this->allPair)
            result.addPair(i.second,i.first);
        return result;
    }
};
