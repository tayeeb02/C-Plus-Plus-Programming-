#include <iostream>
using namespace std;


int main(){

    int x = 100;
    int &ref = x;

    int *y = &ref + sizeof(long double);

    cout << &x << endl;
    cout << &y << endl;

    cout << x << endl;
    cout << *y << endl;




    return 0;
}