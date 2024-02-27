#include <iostream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

int main(){
    std::map<std::string, int> m;
    std::string s;
    while (std::cin >> s)
        ++m[s];

    std::multimap<int, std::string> halmaz;
    for (auto p: m)
        halmaz.insert(std::make_pair(p.second, p.first));
    
    for (auto p : halmaz)
        std::cout << p.first << " " << p.second << std::endl;
    
    return 0;
}