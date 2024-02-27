/* FILE* RAII */
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

class FilePtr {
  public:
    explicit FilePtr(std::string name, std::string mode): name_(std::move(name)) {
        fp_ = fopen(name.c_str(), mode.c_str());
    }

    explicit FilePtr(FILE *fp = nullptr) : fp_{fp} {}
    ~FilePtr() {
        close_if_open();
    }
    FilePtr & operator=(FILE *fp) {
        close_if_open();
        fp_ = fp;
        return *this;
    }
    operator FILE* () const {
        return fp_;
    }
 
    /* nem másolható */
    FilePtr(FilePtr const &) = delete;
    FilePtr(FilePtr&& ref): fp_(ref.fp_), name_(std::move(ref.name_)){
        ref.fp_ = nullptr;
    }
    FilePtr & operator=(FilePtr const &) = delete;
    FilePtr & operator=(FilePtr&& ref) {
        if(this != &ref){
            close_if_open();
            fp_ = ref.fp_;
            name_ = std::move(ref.name_);

            ref.fp_ = nullptr;
        }
        return *this;
    }

  private:
    FILE *fp_;
    std::string name_;
    
    void close_if_open() {
        if (fp_ != nullptr)
            fclose(fp_);
        fp_ = nullptr;
    }
};
 
FilePtr open_for_writing(char const *name) {
    return FilePtr{name, "wt"};
}

/* ne lehessen ilyet csinálni (az operator FILE* miatt lehetne) */
void fclose(FilePtr) = delete;

int main (){
    FilePtr fp;
    fp = open_for_writing("hello.txt");
    fprintf(fp, "Hello vilag");
    fp = open_for_writing("hello2.txt");
    fprintf(fp, "Hello vilag");

    std::vector<FilePtr> files;
    files.push_back(open_for_writing("hello.txt"));
    files.push_back(open_for_writing("hello2.txt"));
    fprintf(files[0], "hello.txt");
    fprintf(files[1], "hello.txt");
    return 0;
}