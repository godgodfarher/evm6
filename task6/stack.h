#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "list.h"

template<class T>
class stack : public list<T>
{
public:
    stack() : top(NULL) {} // Конструктор по умолчанию

    stack(std::initializer_list<T> list); // Конструктор с инициализаторным списком

    stack(const stack& orig); // Конструктор копирования

    stack(stack&& orig) : top(orig.top) { orig.top = NULL; } // Конструктор перемещения

    stack& operator = (stack&& orig); // Операция присваивания по перемещению

    ~stack() { this->clean(); } // Деструктор

    stack& push(T e) override; // Добавление элемента

    stack& pop() override; // Удаление элемента

    T& get_front() override { if (!top) throw std::runtime_error("Ошибка: получение элемента из пустого стека"); return top->element; } // Получение элемента из вершины

    const T& get_front() const override { if (!top) throw std::runtime_error("Ошибка: получение элемента из пустого стека"); return top->element; } // Получение элемента из вершины (const)

    bool is_empty() const override { if (top) return false; return true; } // Проверка на пустоту

    size_t size() const override { size_t i = 0; for (node* n = top; n; n = n->next) ++i; return i; } // Количесво элементов в стеке

    stack& operator = (const stack& orig); // Операция присваивания

    void print(std::ostream& stream) const override; // Печать

    stack& clean(); // Очистка стека

private:
    typedef typename list<T>::node node;
    node* top; // Указатель на вершину
};
template<class T>
stack<T>::stack(const stack<T>& orig) : top(NULL) /// Конструктор копирования
{
    node** in_copy = &top; // Указатель на указатель, куда будет помещён новый узел

    for (node* n = orig.top; n; n = n->next)
    {
        *in_copy = new node; // Выделение памяти под новый узел
        (*in_copy)->element = n->element; // Копирование данных
        in_copy = &((*in_copy)->next); // Присваивание адреса указателя на следующий узел
    }
    /* Последний указатель на следующий узел будет NULL, потому что конструктор для этого узла вызывался в new node */
}

template<class T>
stack<T>::stack(std::initializer_list<T> list) : top(NULL) /// Конструктор с инициализаторным списком
{
    node** in = &top;
    for (auto& i : list)
    {
        *in = new node;
        (*in)->element = i;
        in = &((*in)->next);
    }
}

template<class T>
stack<T>& stack<T>::operator = (stack<T>&& orig) /// Операция присваивания по перемещению
{
    this->clean(); // Удаление всех узлов

    top = orig.top;
    orig.top = NULL;

    return *this;
}

template<class T>
stack<T>& stack<T>::operator = (const stack<T>& orig) /// Операция присваивания
{
    if (&orig == this) return *this; // Контроль самоприсваивания

    this->clean(); // Удаление всех узлов

    node** in_copy = &top; // Указатель на указатель, куда будет помещён новый узел

    for (node* n = orig.top; n; n = n->next)
    {
        *in_copy = new node; // Выделение памяти под новый узел
        (*in_copy)->element = n->element; // Копирование данных
        in_copy = &((*in_copy)->next); // Присваивание адреса указателя на следующий узел
    }

    return *this;
}

template<class T>
stack<T>& stack<T>::push(T e) /// Добавление элемента
{
    node* n = new node;
    n->element = e;
    n->next = top; // Если стек был пустым, то n->next останется NULL
    top = n;
    return *this;
}

template<class T>
stack<T>& stack<T>::pop() /// Удаление элемента
{
    if (!top) return *this; // Если стек пустой

    node* del = top;
    top = del->next; // Если в стеке был один элемент, то top станет NULL
    delete del;
    return *this;
}

template<class T>
stack<T>& stack<T>::clean() /// Очистка стека
{
    if (!top) return *this;

    node* n = top, * n_next;
    while ((n_next = n->next))
    {
        delete n;
        n = n_next;
    }
    delete n;

    top = NULL;
    return *this;
}

template<class T>
void stack<T>::print(std::ostream& stream) const /// Печать
{
    if (!(top))
        stream << "стек пустой";
    else
        for (node* n = (top); n; n = n->next)
            stream << n->element << " ";
}

#endif // STACK_H_INCLUDED