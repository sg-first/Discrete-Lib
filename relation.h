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
        auto haveReflexivive=[this](int i)
        {
            for(auto j : this->allPair)
            {
                if(j.first==i && j.second==i)
                    return true;
            }
            return false;
        };
        for(auto j : this->allPair)
        {
            if(j.first != j.second)
            {
                if(haveReflexivive(j.first))
                    return false;
                if(haveReflexivive(j.second))
                    return false;
            }
        }
        return true;
    }


    bool isIrreflexive()
    {
        //fix:同上
        for (auto i : this->allPair)
        {
            if (i.second == i.first)
            {
                return false;
            }
            else
            {
                for (auto r : this->allPair)
                {
                    if (i.first == r.first && r.first == r.second && i.first == r.second)//测试外循环的第一个数
                    {
                        return false; 
                    }
                }
                for (auto s : this->allPair)
                {
                    if (i.second == s.first && s.first == s.second && i.second == s.second)//测试内循环的第二个数
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool isSymmetry()
    {
        for (auto s : this->allPair)
        {
            bool flag = false;
            for (auto i : this->allPair)
            {
                if (i.first == s.second && i.second == s.first)
                    flag = true; //找到一个对称的就是对称
            }
            if (flag == false)
            {
                return false;
            }
        }
        return true;
    }

    bool isAntisymmetry()//反对称
    {
        for (auto s : this->allPair)
        {
            for (auto i : this->allPair)
            {
                if (i.first == s.second && i.second == s.first)
                {
                    return false;
                }
            }
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
                if (i.first == f.second)//寻找<y,z>
                {
                    for (auto s : this->allPair)
                    {
                        if (s.first == f.first && s.second == i.second)//找到<x,z>
                        {
                            ss = true;
                        }
                        if (ss == false)
                        {
                            return false;
                        }
                    }
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
