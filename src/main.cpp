#include <estd/string_util.h>
#include <iostream>

using namespace estd::string_util;
using namespace std;

int main(){
    cout << replace_all("test string", "s", "S") << endl;
    return 0;
}