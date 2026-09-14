template<typename T>
class share_ptr{
private:
    T* ptr;
    std::size_t* ref_count;
public:
    share_ptr(T* p = nullptr): ptr(p){
        if(ptr == nullptr){
            ref_count = nullptr;
        }else{
            ref_count = new std::size_t(1);
        }
    }

    ~share_ptr(){
        if(ref_count != nullptr && --(*ref_count) == 0){
            delete ptr;
            delete ref_count;
        }
    }

    share_ptr(const share_ptr& other): ptr(other.ptr), ref_count(other.ref_count){
        ++(*ref_count);
    }

    share_ptr(share_ptr&& other): ptr(other.ptr), ref_count(other.ref_count){
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    share_ptr& operator=(const share_ptr& other){
        if(this != &other){
            if(ref_count != nullptr && --(*ref_count) == 0){
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    share_ptr& operator=(share_ptr&& other){
        if(this != &other){
            if(ref_count != nullptr && --(*ref_count) == 0){
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;

            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    T& operator*() const{
        return *ptr;
    }
    T* operator->() const{
        return ptr;
    }

    T* get() const{
        return ptr;
    } 

    void reset( T* p = nullptr ){
        if(p != ptr){
            if(ref_count != nullptr && --(*ref_count) == 0){
                delete ptr;
                delete ref_count;
            }
            ptr = p;
            if(p != nullptr){
                ref_count = new std::size_t(1);
            }else{
                ref_count = nullptr;
            }
        }
    }    
};

template<typename T>
class share_ptr_arr{
private:
    T* ptr;
    std::size_t* ref_count;
public:
    share_ptr_arr(T* p = nullptr): ptr(p){
        if(ptr == nullptr){
            ref_count = nullptr;
        }else{
            ref_count = new std::size_t(1);
        }
    }

    ~share_ptr_arr(){
        if(ref_count != nullptr && --(*ref_count) == 0){
            delete[] ptr;
            delete ref_count;
        }
    }

    share_ptr_arr(const share_ptr_arr& other): ptr(other.ptr), ref_count(other.ref_count){
        ++(*ref_count);
    }

    share_ptr_arr(share_ptr_arr&& other): ptr(other.ptr), ref_count(other.ref_count){
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    share_ptr_arr& operator=(const share_ptr_arr& other){
        if(this != &other){
            if(ref_count != nullptr && --(*ref_count) == 0){
                delete[] ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }

    share_ptr_arr& operator=(share_ptr_arr&& other){
        if(this != &other){
            if(ref_count != nullptr && --(*ref_count) == 0){
                delete[] ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;

            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    T& operator[](std::size_t index){
        return ptr[index];
    }

    T* get(){
        return ptr;
    }

    void reset(T* p = nullptr){
        if(p != ptr){
            if(ref_count != nullptr && --(*ref_count) == 0){
                delete[] ptr;
                delete ref_count;
            }
            ptr = p;
            if(p != nullptr){
                ref_count = new std::size_t(1);
            }else{
                ref_count = nullptr;
            }
        }
    }

};