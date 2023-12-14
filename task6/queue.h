#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "list.h"

template<class T>
class queue : public list<T>
{
public:
    queue() : head(NULL), tail(NULL) {} // Конструктор по умолчанию

    queue(std::initializer_list<T> list) : head(NULL), tail(NULL) { for (auto& i : list) this->push(i); } // Конструктор с инициализаторным списком

    queue(const queue& orig); // Конструктор копирования

    queue(queue&& orig) : head(orig.head), tail(orig.tail) { orig.head = NULL; orig.tail = NULL; } // Конструктор перемещения

    queue& operator = (queue&& orig); // Операция присваивания по перемещению

    ~queue() { this->clean(); } // Деструктор

    queue& push(T e) override; // Добавление элемента

    queue& pop() override; // Удаление элемента

    T& get_front() override { if (!head) throw std::runtime_error("Ошибка: получение элемента из пустой очереди"); return head->element; } // Получение элемента из вершины

    const T& get_front() const override { if (!head) throw std::runtime_error("Ошибка: получение элемента из пустой очереди"); return head->element; } // Получение элемента из вершины (const)

    bool is_empty() const override { if (head) return false; return true; } // Проверка на пустоту

    size_t size() const override { size_t i = 0; for (node* n = head; n; n = n->next) ++i; return i; } // Количесво элементов очереди

    queue& operator = (const queue& orig); // Операция присваивания

    void print(std::ostream& stream) const override; // Печать

    queue& clean(); // Очистка очереди

private:
    typedef typename list<T>::node node;
    node* head, * tail; // Указатель на вершину
};

template<class T>
queue<T>::queue(const queue<T>& orig) : head(NULL), tail(NULL) /// Конструктор копирования
{
    for (node* n = orig.head; n; n = n->next)
        this->push(n->element);
}

template<class T>
queue<T>& queue<T>::operator = (queue<T>&& orig) /// Операция присваивания по перемещению
{
    this->clean();

    tail = orig.tail;
    head = orig.head;

    orig.tail = orig.head = NULL;
    return *this;
}

template<class T>
queue<T>& queue<T>::push(T e) /// Добавление элемента
{
    node* n = new node;

    n->element = e;
    if (!head) head = n;
    else tail->next = n;
    tail = n;

    return *this;
}

template<class T>
queue<T>& queue<T>::pop() /// Удаление элемента
{
    if (!head) return *this;

    node* del = head;

    if (!(head = head->next)) tail = NULL;
    delete del;
    return *this;
}

template<class T>
queue<T>& queue<T>::operator = (const queue<T>& orig) /// Операция присваивания
{
    if (&orig == this) return *this;
    this->clean();

    for (node* n = orig.head; n; n = n->next)
        this->push(n->element);

    return *this;
}

template<class T>
void queue<T>::print(std::ostream& stream) const /// Печать
{
    if (!head)
        stream << "очередь пустая";
    else
        for (node* n = (head); n; n = n->next)
            stream << n->element << " ";
}

template<class T>
queue<T>& queue<T>::clean() /// Очистка очереди
{
    if (!head) return *this;

    node* n = head, * n_next;

    while ((n_next = n->next))
    {
        delete n;
        n = n_next;
    }
    delete n;

    head = tail = NULL;
    return *this;
}

#endif // QUEUE_H_INCLUDED