#include "Vector.h"



Vector::Vector(const Value *rawArray, const size_t size, float coef) {
    this->_multiplicativeCoef = coef;
    this->_size = size;
    this->_capacity = size;
    this->_data = new Value[size];
    for (int i = 0; i < size; i++) {
        this->_data[i] = rawArray[i];
    }
}

Vector::~Vector() {
    if (this->_data == nullptr) {
        return;
    }
    delete[] this->_data;
}


Vector::Vector(const Vector &other) {
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other._size;
    this->_capacity = other._size;
    this->_data = new Value[other._size];
    for (int i = 0; i < other._size; i++) {
        this->_data[i] = other._data[i];
    }
}

Vector& Vector::Vector::operator=(const Vector &other) {
    if (this == &other) {
        return *this;
    }
    delete[] this->_data;
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other._size;
    this->_capacity = other._size;
    this->_data = new Value[other._size];
    for (int i = 0; i < other._size; i++) {
        this->_data[i] = other._data[i];
    }
    return *this;
}

Vector::Vector(Vector &&other) noexcept {
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other._size;
    other._size = 0;
    this->_capacity = other._capacity;
    other._capacity = 0;
    this->_data = other._data;
    other._data = nullptr;
}

Vector& Vector::operator=(Vector &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete[] this->_data;
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other._size;
    other._size = 0;
    this->_capacity = other._capacity;
    other._capacity = 0;
    this->_data = other._data;
    other._data = nullptr;
}

void Vector::pushBack(const Value &value) {
    if (this->_size == 0) {
        this->reserve(this->_multiplicativeCoef);
    } else if (this->_size == this->_capacity) {
        this->reserve(this->_size * this->_multiplicativeCoef);
    }
    this->_data[this->_size] = value;
    this->_size++;
}

void Vector::pushFront(const Value &value) {
    if (this->_capacity == 0) {
        this->reserve(this->_multiplicativeCoef);
    } else if (this->_size == this->_capacity) {
        this->reserve(this->_size * this->_multiplicativeCoef);
    }

    for (int i = this->_size; i > 0; i--) {
        this->_data[i] = this->_data[i - 1];
    }
    this->_data[0] = value;
    this->_size++;
}

void Vector::popBack() {
    if (this->_size == 0) {
        throw std::underflow_error("0 elements");
    }
    this->_size--;
}

void Vector::popFront() {
    if (this->_size == 0) {
        throw std::underflow_error("0 elements");
    }
    for (int i = 0; i < this->_size - 1; i++) {
        this->_data[i] = this->_data[i + 1];
    }
    this->_size--;
    if (this->_size < this->_capacity / this->_multiplicativeCoef) {
        this->shrinkToFit();
    }
}

void Vector::insert(const Value &value, const size_t idx) {
    if (idx > this->_size) {
        throw std::invalid_argument("more than size");
    }
    if (this->_size == this->_capacity) {
        this->reserve(this->_size * this->_multiplicativeCoef);
    }
    for (int i = this->_size; i > idx; i--) {
        this->_data[i] = this->_data[i - 1];
    }
    this->_data[idx] = value;
    this->_size++;
}

void Vector::insert(const Value *values, size_t size, size_t pos) {
    if (values == nullptr) {
        return;
    }

    if (pos > this->_size) {
        throw std::invalid_argument("more than size");
    }
    if (this->_size + size > this->_capacity) {
        this->reserve(this->_size * this->_multiplicativeCoef);
    }
    for (int i = this->_size + size - 1; i >= pos + size; i--) {
        this->_data[i] = this->_data[i - size];
    }
    for (int i = 0; i < size; i++) {
        this->_data[pos + i] = values[i];
    }
    this->_size += size;
}

void Vector::insert(const Vector &vector, size_t pos) {
    this->insert(vector._data, vector._size, pos);
}


void Vector::erase(size_t pos, size_t count) {
    if (pos + count > this->_size) {
        count = this->_size - pos;
    }
    for (int i = pos; i < this->_size - count; i++) {
        this->_data[i] = this->_data[i + count];
    }
    this->_size -= count;

    if (this->_size < this->_capacity / this->_multiplicativeCoef) {
        this->shrinkToFit();
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos) {
    if (beginPos > endPos) {
        throw std::invalid_argument("beginPos > endPos");
    }
    this->erase(beginPos, endPos - beginPos);
}

size_t Vector::size() const {
    return this->_size;
}

size_t Vector::capacity() const {
    return this->_capacity;
}

double Vector::loadFactor() const {
    return this->_size / this->_capacity;
}

Value& Vector::operator[](size_t idx) {
    return this->_data[idx];
}

const Value& Vector::operator[](size_t idx) const {
    return this->_data[idx];
}

long long Vector::find(const Value &value) const {
    for (int i = 0; i < this->_size; i++) {
        if (this->_data[i] == value) {
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity) {
    if (capacity == 0) {
        return;
    }
    Value *newData = new Value[capacity];
    for (int i = 0; i < this->_size; i++) {
        newData[i] = this->_data[i];
    }
    delete[] this->_data;
    this->_data = newData;
    this->_capacity = capacity;
}

void Vector::shrinkToFit() {
    if (this->_size == 0 and this->_capacity == 0) {
        return;
    }

    Value *newData = new Value[this->_size];
    for (int i = 0; i < this->_size; i++) {
        newData[i] = this->_data[i];
    }
    this->_data = newData;
    this->_capacity = this->_size;
}


Vector::Iterator::Iterator(Value *ptr) {
    this->_ptr = ptr;
}

Vector::Iterator Vector::Iterator::operator++() {
    this->_ptr++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    Iterator tmp = *this;
    this->_ptr++;
    return tmp;
}

Value& Vector::Iterator::operator*() {
    return *this->_ptr;
}

const Value& Vector::Iterator::operator*() const {
    return *this->_ptr;
}

bool Vector::Iterator::operator==(const Iterator &other) const {
    return this->_ptr == other._ptr;
}

bool Vector::Iterator::operator!=(const Iterator &other) const {
    return this->_ptr != other._ptr;
}

Value* Vector::Iterator::operator->() {
    return this->_ptr;
}

const Value* Vector::Iterator::operator->() const {
    return this->_ptr;
}


Vector::Iterator Vector::begin() {
    return Vector::Iterator(this->_data);
}

// mb need -1
Vector::Iterator Vector::end() {
    return Vector::Iterator(this->_data + this->_size);
}


