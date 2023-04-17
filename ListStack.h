#pragma once

#include <list>
#include "StackImplementation.h"

using Value = double;

class ListStack : public IStackImplementation {
public:
    ListStack() = default;

    ListStack(const ValueType* valueArray, const size_t arraySize);

    // виртуальный деструктор
    ~ListStack() override = default;

    // добавление в хвост
    void push(const ValueType &value) override;

    // удаление с хвоста
    void pop() override;

    // посмотреть элемент в хвосте
    const ValueType &top() const override;

    // проверка на пустоту
    bool isEmpty() const override;

    // размер
    size_t size() const override;
private:
    std::list<Value> _data;
};


