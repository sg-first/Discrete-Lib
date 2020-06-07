#include <iostream>
#include"relation.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    relation  A;
    relation  B;
    int a, b, m, n, s, f, g, h;
    cin >> a >> b >> m >> n >> s >> f >> g >> h;
    A.addPair(a, b);
    A.addPair(m, n);
    A.addPair(s, f);
    A.addPair(g, h);
    A.isReflexivive();//自反
    A.isIrreflexive();//反自反
    A.isSymmetry();//对称
    A.isAntisymmetry();//反对称
    A.isTransitivity();//传递
    int ss, gg;
    cin >> ss >> gg;
    B.addPair(ss, gg);
    A.output();
    cout << "composite" << endl;
    A.composite(B);
    return 0;
}