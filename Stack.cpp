#include "VectorStack.h"
#include "ListStack.h"

#include "Stack.h"


Stack::Stack(StackContainer container): _containerType(container) {
    switch (container) {
        case StackContainer::Vector:
            this->_pimpl = new VectorStack();
            break;
        case StackContainer::List:
            this->_pimpl = new ListStack();
            break;
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container): _containerType(container) {
    switch (container) {
        case StackContainer::Vector:
            this->_pimpl = new VectorStack(valueArray, arraySize);
            break;
        case StackContainer::List:
            this->_pimpl = new ListStack(valueArray, arraySize);
            break;
    }
}

Stack::Stack(const Stack& copyStack): _containerType(copyStack._containerType) {
    switch (copyStack._containerType) {
        case StackContainer::Vector:
            this->_pimpl = new VectorStack(*static_cast<VectorStack*>(copyStack._pimpl));
            break;
        case StackContainer::List:
            this->_pimpl = new ListStack(*static_cast<ListStack*>(copyStack._pimpl));
            break;
    }
}

Stack &Stack::operator=(const Stack &copyStack) {
    if (this == &copyStack) {
        return *this;
    }
    delete this->_pimpl;
    this->_containerType = copyStack._containerType;
    switch (copyStack._containerType) {
        case StackContainer::Vector:
            this->_pimpl = new VectorStack(*static_cast<VectorStack*>(copyStack._pimpl));
            break;
        case StackContainer::List:
            this->_pimpl = new ListStack(*static_cast<ListStack*>(copyStack._pimpl));
            break;
    }
    return *this;
}

Stack::Stack(Stack &&moveStack) noexcept: _containerType(moveStack._containerType) {
    this->_pimpl = moveStack._pimpl;
    moveStack._pimpl = nullptr;
}

Stack &Stack::operator=(Stack &&moveStack) noexcept {
    if (this == &moveStack) {
        return *this;
    }
    delete this->_pimpl;
    this->_containerType = moveStack._containerType;
    this->_pimpl = moveStack._pimpl;
    moveStack._pimpl = nullptr;
    return *this;
}

Stack::~Stack() {
    delete this->_pimpl;
}

void Stack::push(const ValueType &value) {
    this->_pimpl->push(value);
}

void Stack::pop() {
    this->_pimpl->pop();
}

const ValueType &Stack::top() const {
    return this->_pimpl->top();
}

bool Stack::isEmpty() const {
    return this->_pimpl->isEmpty();
}

size_t Stack::size() const {
    return this->_pimpl->size();
}