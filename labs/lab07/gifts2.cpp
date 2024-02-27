#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
struct cmp {
    bool operator()(std::pair<std::pair<int, int>, int> a, std::pair<std::pair<int, int>, int> b){
        return a.second < b.second;
    }
}comp;

int main(){
    std::string s;
    std::fstream f("santa.txt");
    while(f >> s);

    std::pair <int, int> currentPos = {0,0};
    std::map<std::pair<int, int>, int> locations;
    ++locations[currentPos];

    for(auto c : s){
        switch (c)
        {
        case '^':
            currentPos.second++;
            break;
        case '>':
            currentPos.first++;
            break;
        case 'v':
            currentPos.second--;
            break;
        case '<':
            currentPos.first--;
            break;
        
        default:
            break;
        }
        ++locations[currentPos];
    }

    std::cout << locations.size() << std::endl; 
    auto p = std::max_element(locations.begin(), locations.end(), comp);
    std::cout << p->second << " ajandek, a (" << p->first.first << ", " << p->first.second << ") pozicioban" << std::endl;

    return 0;
}