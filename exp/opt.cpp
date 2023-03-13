#include <iostream>
#include <cmath>

using namespace std;

string int_str(int a) {
    string s = "";
    while(a > 0) {
        s = static_cast<char>('0' + a % 2) + s;
        a /= 2;
    }
    while(s.size() < 8)
        s = '0' + s;
    return s;
}

int main()
{
    string s;
    for(int i = 0; i < 255; ++i) {
        s = "";
        for(int j = 0; j < 8; ++j) {
            int num = static_cast<int>(ceil(i / pow(2, j))) % 2;
            s = static_cast<char>(num + '0') + s;
        }
        cout<<s<<'\t';
        if(i > 0)
            cout<<int_str(255 ^ (i - 1))<<'\n';
        else
            cout<<"00000000\n";
    }
    return 0;
}
