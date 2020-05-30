#include <iostream>
#include "graph.h"
#include "relation.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    relation  A;
    relation  B;
    int a, b, m, n;
    cin >> a >> b >> m>>n;
    A.addPair(a, b);
    A.addPair(m ,n);
    int s, g;
    cin >> s >> g;
    B.addPair(s, g);
    A.output(); 
    cout << "复合后结果：" << endl;
    A.composite(B);
    return 0;
}
