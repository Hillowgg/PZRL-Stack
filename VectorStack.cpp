#include "VectorStack.h"

VectorStack::VectorStack(const ValueType *valueArray, const size_t arraySize) {
    for (size_t i = 0; i < arraySize; ++i) {
        this->_data.pushBack(valueArray[i]);
    }
}

void VectorStack::push(const ValueType &value) {
    this->_data.pushBack(value);
}

void VectorStack::pop() {
    this->_data.popBack();
}

const ValueType &VectorStack::top() const {
    return this->_data[this->_data.size() - 1];
}

bool VectorStack::isEmpty() const {
    return this->size() == 0;
}

size_t VectorStack::size() const {
    return this->_data.size();
}
