template <typename T>
class unic_ptr{
private:
    T* ptr;
public:
    unic_ptr(T* p = nullptr): ptr(p){}
    ~unic_ptr(){ delete ptr; }

    unic_ptr(const unic_ptr& ) = delete;
    unic_ptr(unic_ptr&& other): ptr(other.ptr){
        other.ptr = nullptr;
    }

    unic_ptr& operator=(const unic_ptr& ) = delete;

    unic_ptr& operator=(unic_ptr&& other ){
        if (this != &other){
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }
    T* operator->() const {
        return ptr;
    }

    T* get() const{
        return ptr;
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset( T* p = nullptr){
        if(ptr != p){
           delete ptr;
           ptr = p;
        }
    }

};

template <typename T>
class unic_ptr_arr{
private:
    T* ptr;
public:
    unic_ptr_arr(T* p = nullptr): ptr(p){}
    ~unic_ptr_arr(){ delete[] ptr; }

    unic_ptr_arr( const unic_ptr_arr& other ) = delete;
    unic_ptr_arr( unic_ptr_arr&& other ): ptr(other.ptr){
        other.ptr = nullptr;
    }
    unic_ptr_arr& operator=( const unic_ptr_arr&) = delete;

    unic_ptr_arr& operator=( unic_ptr_arr&& other){
        if(this != &other){
            delete[] ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator[]( std::size_t index ) const{
        return ptr[index];
    }

    T* get() const{
        return ptr;
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr){
        if(ptr != p){
            delete[] ptr;
            ptr = p;
        }
    }
};