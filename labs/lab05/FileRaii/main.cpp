#include <iostream>
#include <cstdio>

class FilePtr{
    FILE* ptr_;
public:
    FilePtr(): ptr_{nullptr} {}
    FilePtr(FILE* ptr): ptr_{ptr}{}
    operator FILE*() {
        return ptr_;
    }
    void operator=(FILE* ptr){
        if(ptr_ == nullptr)
            ptr_ = ptr;
    }
    FilePtr(const FilePtr&) = delete;
    FilePtr operator=(const FilePtr&) = delete;
    ~FilePtr() {
        fclose(ptr_);
        ptr_ = nullptr;
    }
};

int main() {
    FilePtr fp;

    fp = fopen("hello.txt", "wt");
    fprintf(fp, "Hello vilag");
    fclose(fp);
}

