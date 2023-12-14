#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "list.h"

template<class T>
class queue : public list<T>
{
public:
    queue() : head(NULL), tail(NULL) {} // ����������� �� ���������

    queue(std::initializer_list<T> list) : head(NULL), tail(NULL) { for (auto& i : list) this->push(i); } // ����������� � ���������������� �������

    queue(const queue& orig); // ����������� �����������

    queue(queue&& orig) : head(orig.head), tail(orig.tail) { orig.head = NULL; orig.tail = NULL; } // ����������� �����������

    queue& operator = (queue&& orig); // �������� ������������ �� �����������

    ~queue() { this->clean(); } // ����������

    queue& push(T e) override; // ���������� ��������

    queue& pop() override; // �������� ��������

    T& get_front() override { if (!head) throw std::runtime_error("������: ��������� �������� �� ������ �������"); return head->element; } // ��������� �������� �� �������

    const T& get_front() const override { if (!head) throw std::runtime_error("������: ��������� �������� �� ������ �������"); return head->element; } // ��������� �������� �� ������� (const)

    bool is_empty() const override { if (head) return false; return true; } // �������� �� �������

    size_t size() const override { size_t i = 0; for (node* n = head; n; n = n->next) ++i; return i; } // ��������� ��������� �������

    queue& operator = (const queue& orig); // �������� ������������

    void print(std::ostream& stream) const override; // ������

    queue& clean(); // ������� �������

private:
    typedef typename list<T>::node node;
    node* head, * tail; // ��������� �� �������
};

template<class T>
queue<T>::queue(const queue<T>& orig) : head(NULL), tail(NULL) /// ����������� �����������
{
    for (node* n = orig.head; n; n = n->next)
        this->push(n->element);
}

template<class T>
queue<T>& queue<T>::operator = (queue<T>&& orig) /// �������� ������������ �� �����������
{
    this->clean();

    tail = orig.tail;
    head = orig.head;

    orig.tail = orig.head = NULL;
    return *this;
}

template<class T>
queue<T>& queue<T>::push(T e) /// ���������� ��������
{
    node* n = new node;

    n->element = e;
    if (!head) head = n;
    else tail->next = n;
    tail = n;

    return *this;
}

template<class T>
queue<T>& queue<T>::pop() /// �������� ��������
{
    if (!head) return *this;

    node* del = head;

    if (!(head = head->next)) tail = NULL;
    delete del;
    return *this;
}

template<class T>
queue<T>& queue<T>::operator = (const queue<T>& orig) /// �������� ������������
{
    if (&orig == this) return *this;
    this->clean();

    for (node* n = orig.head; n; n = n->next)
        this->push(n->element);

    return *this;
}

template<class T>
void queue<T>::print(std::ostream& stream) const /// ������
{
    if (!head)
        stream << "������� ������";
    else
        for (node* n = (head); n; n = n->next)
            stream << n->element << " ";
}

template<class T>
queue<T>& queue<T>::clean() /// ������� �������
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