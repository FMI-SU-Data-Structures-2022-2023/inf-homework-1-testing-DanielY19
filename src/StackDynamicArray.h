#ifndef DATASTRUCTURES_STACKDYNAMICARRAY_H
#define DATASTRUCTURES_STACKDYNAMICARRAY_H

#include <stdexcept>

template<typename T>
class StackDynamicArray {
public:
    StackDynamicArray();

    StackDynamicArray(const StackDynamicArray &other);

    void push(const T &value);

    void pop();

    bool empty() const {
        return this->size == 0;
    };

    const T &peek() const {
        if (this->empty())
            throw std::logic_error("Stack is empty!");
        return this->data[this->size - 1];
    };

    StackDynamicArray &operator=(const StackDynamicArray &other);

    ~StackDynamicArray();

private:
    T *data;
    size_t size;
    size_t capacity;

    void resize();

    void allocateMem();

    void copy(const T *data, size_t size);

    void destroy();
};

template<typename T>
StackDynamicArray<T>::StackDynamicArray()
        :data(nullptr), size(0), capacity(5) {
    this->allocateMem();
}

template<typename T>
StackDynamicArray<T>::StackDynamicArray(const StackDynamicArray &other)
        :size(other.size), capacity(other.capacity) {
    this->allocateMem();
    try {
        this->copy(other.data, other.size);
    }
    catch (...) {
        this->destroy();
        throw;
    }
}

template<typename T>
void StackDynamicArray<T>::push(const T &value) {
    if (this->size == this->capacity)
        this->resize();

    this->data[this->size++] = value;
}

template<typename T>
void StackDynamicArray<T>::pop() {
    if (this->empty())
        throw std::logic_error("Stack is empty!");
    --this->size;
}

template<typename T>
StackDynamicArray<T> &StackDynamicArray<T>::operator=(const StackDynamicArray &other) {
    if (this != &other) {
        T *oldData = this->data;
        size_t oldCap = this->capacity;
        this->capacity = other.capacity;

        try {
            this->allocateMem();
        }
        catch (std::bad_alloc &) {
            this->data = oldData;
            this->capacity = oldCap;
            throw;
        }

        try {
            this->copy(other.data, other.size);
        }
        catch (...) {
            this->destroy();
            this->data = oldData;
            this->capacity = oldCap;
            throw;
        }

        this->size = other.size;
        delete[] oldData;
    }

    return *this;
}

template<typename T>
StackDynamicArray<T>::~StackDynamicArray() {
    this->destroy();
}

template<typename T>
void StackDynamicArray<T>::resize() {
    T *oldData = this->data;
    this->capacity *= 2;

    try {
        this->allocateMem();
    }
    catch (std::bad_alloc &) {
        this->data = oldData;
        this->capacity /= 2;
        throw;
    }

    try {
        this->copy(oldData, this->size);
    }
    catch (...) {
        this->destroy();
        this->data = oldData;
        this->capacity /= 2;
        throw;
    }

    delete[] oldData;
}

template<typename T>
void StackDynamicArray<T>::allocateMem() {
    this->data = new T[this->capacity];
}

template<typename T>
void StackDynamicArray<T>::copy(const T *data, size_t size) {
    for (size_t i = 0; i < size; i++)
        this->data[i] = data[i];
}

template<typename T>
void StackDynamicArray<T>::destroy() {
    delete[] this->data;
}


#endif //DATASTRUCTURES_STACKDYNAMICARRAY_H
