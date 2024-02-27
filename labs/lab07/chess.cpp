#include <iostream>
#include <vector>
#include <algorithm>

void draw(std::vector<int> t){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++)
            std::cout << ((t[i] - 1 == j) ? 'X' : '.');
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool goodSolution(std::vector<int> t) {
    for(int y = 0; y < 8; y++){
        bool ittMarVolt = false;
        for(int atlo = 0; atlo < 8; atlo++)
            if(t[y+atlo]-1 == atlo){
                if(ittMarVolt)
                    return false;
            }
    }

    for(int y = 8; y > 0; y--){
        bool ittMarVolt = false;
        for(int atlo = 0; atlo < 8; atlo++)
            if(t[y+atlo]-1 == atlo){
                if(ittMarVolt)
                    return false;
            }
    }

    return true;
}

int main(){
    std::vector<int> table = {1, 2, 3, 4, 5, 6, 7, 8};
    while(std::next_permutation(table.begin(), table.end())){
        if(goodSolution(table))
            draw(table);
    }
    return 0;
}