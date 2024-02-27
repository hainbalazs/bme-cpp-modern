#include <iostream>
#include <string>
#include <set>
#include <cstdlib>

int usedChunks = 0;

void * operator new(size_t siz){
    if(siz > 1024)
        throw std::bad_alloc();
    void *allocatedMemory = malloc(siz);
    if(allocatedMemory == nullptr)
        throw std::bad_alloc();
    std::cout << "Allocated [" << siz << " bytes] @ " << allocatedMemory << std::endl;
    usedChunks++;
    return allocatedMemory;
}
void * operator new[](size_t siz){
    if(siz > 1024)
        throw std::bad_alloc();
    void *allocatedMemory = malloc(siz);
    if(allocatedMemory == nullptr)
        throw std::bad_alloc();
    std::cout << "Allocated (array) [" << siz << " bytes] @ " << allocatedMemory << std::endl;
    usedChunks++;
    return allocatedMemory;
}
void operator delete(void *data) noexcept{
    std::cout << "Freed memory @ " << data << std::endl;
    usedChunks--;
    free(data);
}
void operator delete[](void *data) noexcept{
    std::cout << "Freed memory (array) @ " << data << std::endl;
    usedChunks--;
    free(data);
}

void showMemLeaks() {
    std::cout << "Ennyi memoriaterulet nem lett felszabaditva a programban: " << usedChunks;
}


int main()
{
    int* n = new int;
    std::cout << n;
    delete n;
    std::cout << "-------------------" << std::endl;

   /* int *tomb = new int[100];
    delete[] tomb;
    std::cout << "-------------------" << std::endl;

    std::string h = "helllo vilag alma korte barack dinnye banan narancs kolbasz";
    std::string *g = new std::string{"helllo vilag alma korte barack"};
    delete g;
    std::cout << "-------------------" << std::endl;

    std::set<int> *halmaz = new std::set<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    delete halmaz;
    std::cout << "-------------------" << std::endl;
*/

    try{
        int *m = new int[2000];
    }
    catch(std::bad_alloc& e){
        std::cout << "Memoriafoglalasi problema!" << std::endl;
    }

    std::cout << "cpp -v: " << __cplusplus << std::endl;
    
    atexit(showMemLeaks);
    return 0;
}
