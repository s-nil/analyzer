#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull tile(int n){
    ull t[2];

    t[0] = 1;
    t[1] = 2;

    for(int i=3; i<=n; ++i){
	ull tmp = t[0] + t[1];
	t[0] = t[1];
	t[1] = tmp;
    }

    if(n == 0)	    return 0;
    else if(n == 1) return t[0];
    else	    return t[1];
}

int main(){
    int n;
    cin >> n;

    cout << tile(n) << '\n';

    return 0;
}
