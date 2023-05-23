#include <estd/string_util.h>
#include <iostream>

using namespace estd::string_util;
using namespace std;

int main(){
    cout << replace_all("test string", "s", "S") << endl;
    cout << joinAll(splitAll("hello world t r s 2 3 a  23", " "), "-") << endl;
    return 0;
}