#include "ListStack.h"

ListStack::ListStack(const ValueType *valueArray, const size_t arraySize) {
    for (size_t i = 0; i < arraySize; ++i) {
        _data.push_back(valueArray[i]);
    }
}

void ListStack::push(const ValueType &value) {
    _data.push_back(value);
}

void ListStack::pop() {
    _data.pop_back();
}

const ValueType &ListStack::top() const {
    return _data.back();
}

bool ListStack::isEmpty() const {
    return _data.empty();
}

size_t ListStack::size() const {
    return _data.size();
}