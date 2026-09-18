#include <cstddef>

template<typename T>
class unique_ptr{
private:
    T* ptr;
public:
    unique_ptr(T* p = nullptr): ptr(p){}
    ~unique_ptr(){ delete ptr; }

    unique_ptr(const unique_ptr& ) = delete;

    unique_ptr(unique_ptr&& other): ptr(other.ptr){
        other.ptr = nullptr;
    }

    unique_ptr& operator=(const unique_ptr& ) = delete;

    unique_ptr& operator=(unique_ptr&& other ){
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

template<typename T>
class unique_ptr<T[]>{
private:
    T* ptr;
public:
    unique_ptr<T[]>(T* p = nullptr): ptr(p){}
    ~unique_ptr<T[]>(){ delete[] ptr; }

    unique_ptr<T[]>( const unique_ptr<T[]>& other ) = delete;
    unique_ptr<T[]>( unique_ptr<T[]>&& other ): ptr(other.ptr){
        other.ptr = nullptr;
    }
    unique_ptr<T[]>& operator=( const unique_ptr<T[]>&) = delete;

    unique_ptr<T[]>& operator=( unique_ptr<T[]>&& other){
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