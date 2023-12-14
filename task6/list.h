#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <ostream>
#include <istream>
#include <iostream>
#include <exception>

template<class T>
class list
{
public:

    virtual ~list() {} // Деструктор

    virtual list& push(T e) = 0; // Добавление элемента

    virtual list& pop() = 0; // Удаление элемента

    virtual T& get_front() = 0; // Получение элемента

    virtual const T& get_front() const = 0; // Получение элемента (const)

    virtual bool is_empty() const = 0; // Проверка на пустоту

    virtual size_t size() const = 0; // Размер списка

    template<class M>
    friend std::ostream& operator << (std::ostream& stream, const list<M>& l) { l.print(stream); return stream; } // Вывод

    template<class M>
    friend std::istream& operator >> (std::istream& stream, list<M>& l) { M e; stream >> e; l.push(e); return stream; } // Ввод

protected:

    class node
    {
    public:
        node() : next(NULL) {}; // Конструктор по умолчанию
        node* next;
        T element;
    };

    virtual void print(std::ostream& stream) const = 0; // Печать  
};

#endif // LIST_H_INCLUDED