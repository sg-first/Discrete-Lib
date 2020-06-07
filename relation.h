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
                    result.addPair(b, j.second); //result��ʼ��thisһ��������ǰ�涼��this�������޸ľ���result
                }
            }
        }
        return result;
    }

    bool isReflexivive()
    {
        cout << "�Է���";
        //fix:�Է�ֻ��Ҫ��ÿ��Ԫ��a����<a,a>�����ų���<a,b>��ֻҪ��<b,b>����
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
                    if (i.first == r.first == r.second)//������ѭ���ĵ�һ����
                        break;
                    else
                    {
                        cout << "no";
                        return false;
                    }
                }
                for (auto s : this->allPair)
                {
                    if (i.second == s.first == s.second)//������ѭ���ĵڶ�����
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
        //fix:ͬ��
        cout << "���Է���";
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
                    if (i.first == r.first == r.second)//������ѭ���ĵ�һ����
                    {
                        cout << "no";
                        return false;
                    }
                    else
                        break;

                }
                for (auto s : this->allPair)
                {
                    if (i.second == s.first == s.second)//������ѭ���ĵڶ�����
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
        cout << "�Գ�:";
        for (auto s : this->allPair)
        {
            bool flag = false;
            for (auto i : this->allPair)
            {
                if (i.first == s.second && i.second == s.first)
                    flag = true; //�ҵ�һ���ԳƵľ��ǶԳ�
            }
            if (flag == false)
            {
                cout << "NO";
                return false;
            }
        }
        return true;
    }

    bool isAntisymmetry()//���Գ�
    {
        cout << "���Գƣ�";
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

    bool isTransitivity()//����
    {
        cout << "���ݣ�";
        for (auto f : this->allPair)
        {
            //<x,y>
            bool  ss = true;
            for (auto i : this->allPair)
            {
                if (i.first == f.second)//Ѱ��<y,z>
                {
                    for (auto s : this->allPair)
                    {
                        if (s.first == f.first && s.second == i.second)//�ҵ�<x,z>
                        {
                            ss = false;//false��ʾΪ���ݹ�ϵ��
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
    relation TransitiveClosure()//���ݱհ�
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

    relation reflexiveClosure()//�Է��հ�
    {
        relation result(*this);
        for (auto i : this->allPair)
        {
            result.addPair(i.first, i.first);
            result.addPair(i.second, i.second);
        }
        return result;
    }

    relation symmetricClosure()//�ԳƱհ�
    {
        relation result(*this);
        for (auto i : this->allPair)
            result.addPair(i.second, i.first);
        return result;
    }
};
