#include <iostream>

template <class type>
class SharedPtr {
    public:
        SharedPtr(type* ptr) : ptr(ptr){
            count = new int(1);
        }

        SharedPtr (const SharedPtr& b) : ptr(b.ptr) {
            count = b.count;
            (*count)++;
        }

        ~SharedPtr() {
            if (*count == 1) {
                delete count;
                //delete //????
            }
            else {
                (*count)--;
            }
        }

        SharedPtr& operator=(const SharedPtr& b) {
            if (this == &b){  
                return;
            } 
            else {
                ~SharedPtr();
                ptr = b.ptr;
                count = b.count;
                *(count)++;
            }
            return *this;
        }


    private:
        int *count = nullptr;
        void *ptr = nullptr;
}

int main(void) {

}