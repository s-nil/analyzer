#include <iostream>
#include <cmath>
#include "idfa.h"

#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

using namespace std;

int main(int argc, char **argv)
{
    // if(argc < 2){
    //     cout << argv[0] << " Version " <<  idfa_VERSION_MAJOR << "."
    //         << idfa_VERSION_MINOR << endl;
    //     cout << "Usage: " << argv[0] << " number" << endl;
    // }

    double n;
    cin >> n;

    // using a library
    #ifdef USE_MYMATH
        cout << "My Math\n";
        cout << n << " is " << mysqrt(n);
    // not using a library
    #else 
        cout << n << " is " << sqrt(n);
    #endif

    return 0;
}
