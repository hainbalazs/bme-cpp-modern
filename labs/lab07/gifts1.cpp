#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main(){
    std::string s;
    std::fstream f("santa.txt");
    while(f >> s);

    std::pair <int, int> currentPos = {0,0};
    std::set<std::pair<int, int>> locations;
    locations.insert(currentPos);

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
        locations.insert(currentPos);
    }

    std::cout << locations.size();

    return 0;
}