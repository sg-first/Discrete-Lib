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
        cout << "自反：";
        //fix:自反只是要求每个元素a都有<a,a>，不排斥有<a,b>，只要有<b,b>就行
        for (auto i : this->allPair)
        {
            if (i.second == i.first)
            {
                break;
            }
            else
            {
                for (auto r : this->allPair)
                {
                    if (i.first == r.first == r.second)//测试外循环的第一个数
                        break;
                    else
                    {
                        cout << "no";
                        return false;
                    }
                }
                for (auto s : this->allPair)
                {
                    if (i.second == s.first == s.second)//测试内循环的第二个数
                        break;
                    else
                    {
                        cout << "no";
                        return false;
                    }
                }
            }
        }
        return true;
    }


    bool isIrreflexive()
    {
        //fix:同上
        cout << "反自反：";
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
                    if (i.first == r.first == r.second)//测试外循环的第一个数
                    {
                        cout << "no";
                        return false;
                    }
                    else
                        break;

                }
                for (auto s : this->allPair)
                {
                    if (i.second == s.first == s.second)//测试内循环的第二个数
                    {
                        cout << "no";
                        return false;
                    }
                    else
                        break;
                }
            }
        }
        return true;
    }

    bool isSymmetry()
    {
        cout << "对称:";
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
                cout << "NO";
                return false;
            }
        }
        return true;
    }

    bool isAntisymmetry()//反对称
    {
        cout << "反对称：";
        for (auto s : this->allPair)
        {
            for (auto i : this->allPair)
            {
                if (i.first == s.second && i.second == s.first)
                {
                    cout << "NO";
                    return false;
                }
            }
        }
        return true;
    }

    bool isTransitivity()//传递
    {
        cout << "传递：";
        for (auto f : this->allPair)
        {
            //<x,y>
            bool  ss = true;
            for (auto i : this->allPair)
            {
                if (i.first == f.second)//寻找<y,z>
                {
                    for (auto s : this->allPair)
                    {
                        if (s.first == f.first && s.second == i.second)//找到<x,z>
                        {
                            ss = false;//false表示为传递关系；
                        }
                        if (ss == true)
                        {
                            cout << "NO";
                            return true;
                        }
                    }
                }

            }
        }
        return false;
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
