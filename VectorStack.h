#pragma once

#include "Vector.h"
#include "StackImplementation.h"


class VectorStack : public IStackImplementation {
public:
    VectorStack() = default;

    VectorStack(const ValueType* valueArray, const size_t arraySize);

    // виртуальный деструктор
    ~VectorStack() override = default;

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
    Vector _data;
};


