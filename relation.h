#pragma once
#include <utility>
#include <set>
#include <iostream>
using namespace std;

class relation
{
private:
    set< pair<int, int> > allPair;

    bool isExist(int i,int j)
    {
        for(auto k : this->allPair)
        {
            if(k.first==i && k.second==j)
                return true;
        }
        return false;
    }

public:
    relation() {}
    relation(const relation& r)
    {
        this->allPair = r.allPair;
    }
    relation& operator=(const relation& r)
    {
        this->allPair = r.allPair;
        return *this;
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
        for(auto j : this->allPair)
        {
            if(j.first != j.second)
            {
                if(!isExist(j.first,j.first))
                    return false;
                if(!isExist(j.second,j.second))
                    return false;
            }
        }
        return true;
    }


    bool isIrreflexive()
    {
        for (auto i : this->allPair)
        {
            if (i.second == i.first)
                return false;
        }
        return true;
    }

    bool isSymmetry()
    {
        for (auto s : this->allPair)
        {
            if(!isExist(s.second,s.first))
                return false;
        }
        return true;
    }

    bool isAntisymmetry()//反对称
    {
        for (auto s : this->allPair)
        {
            if(isExist(s.second,s.first))
                return false;
        }
        return true;
    }

    bool isTransitivity()//传递
    {
        for (auto f : this->allPair)
        {
            //<x,y>
            bool  ss = false;
            for (auto i : this->allPair)
            {
                if (i!=f && i.first == f.second)//寻找<y,z>
                {
                    if(!isExist(f.first,i.second))
                        return false;
                }
            }
        }
        return true;
    }

    relation TransitiveClosure()//传递闭包
    {
        relation result(*this);
        for (auto i : this->allPair)
        {
            for (auto s : this->allPair)
            {
                if(i!=s)
                    result.addPair(i.first, s.second);
            }
        }
        return result;
    }

    relation reflexiveClosure()//自反闭包
    {
        relation result(*this);
        for (auto i : this->allPair)
        {
            result.addPair(i.first, i.first);
            result.addPair(i.second, i.second);
        }
        return result;
    }

    relation symmetricClosure()//对称闭包
    {
        relation result(*this);
        for (auto i : this->allPair)
            result.addPair(i.second, i.first);
        return result;
    }
};
