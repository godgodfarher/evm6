#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "list.h"

template<class T>
class stack : public list<T>
{
public:
    stack() : top(NULL) {} // ����������� �� ���������

    stack(std::initializer_list<T> list); // ����������� � ���������������� �������

    stack(const stack& orig); // ����������� �����������

    stack(stack&& orig) : top(orig.top) { orig.top = NULL; } // ����������� �����������

    stack& operator = (stack&& orig); // �������� ������������ �� �����������

    ~stack() { this->clean(); } // ����������

    stack& push(T e) override; // ���������� ��������

    stack& pop() override; // �������� ��������

    T& get_front() override { if (!top) throw std::runtime_error("������: ��������� �������� �� ������� �����"); return top->element; } // ��������� �������� �� �������

    const T& get_front() const override { if (!top) throw std::runtime_error("������: ��������� �������� �� ������� �����"); return top->element; } // ��������� �������� �� ������� (const)

    bool is_empty() const override { if (top) return false; return true; } // �������� �� �������

    size_t size() const override { size_t i = 0; for (node* n = top; n; n = n->next) ++i; return i; } // ��������� ��������� � �����

    stack& operator = (const stack& orig); // �������� ������������

    void print(std::ostream& stream) const override; // ������

    stack& clean(); // ������� �����

private:
    typedef typename list<T>::node node;
    node* top; // ��������� �� �������
};
template<class T>
stack<T>::stack(const stack<T>& orig) : top(NULL) /// ����������� �����������
{
    node** in_copy = &top; // ��������� �� ���������, ���� ����� ������� ����� ����

    for (node* n = orig.top; n; n = n->next)
    {
        *in_copy = new node; // ��������� ������ ��� ����� ����
        (*in_copy)->element = n->element; // ����������� ������
        in_copy = &((*in_copy)->next); // ������������ ������ ��������� �� ��������� ����
    }
    /* ��������� ��������� �� ��������� ���� ����� NULL, ������ ��� ����������� ��� ����� ���� ��������� � new node */
}

template<class T>
stack<T>::stack(std::initializer_list<T> list) : top(NULL) /// ����������� � ���������������� �������
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
stack<T>& stack<T>::operator = (stack<T>&& orig) /// �������� ������������ �� �����������
{
    this->clean(); // �������� ���� �����

    top = orig.top;
    orig.top = NULL;

    return *this;
}

template<class T>
stack<T>& stack<T>::operator = (const stack<T>& orig) /// �������� ������������
{
    if (&orig == this) return *this; // �������� ����������������

    this->clean(); // �������� ���� �����

    node** in_copy = &top; // ��������� �� ���������, ���� ����� ������� ����� ����

    for (node* n = orig.top; n; n = n->next)
    {
        *in_copy = new node; // ��������� ������ ��� ����� ����
        (*in_copy)->element = n->element; // ����������� ������
        in_copy = &((*in_copy)->next); // ������������ ������ ��������� �� ��������� ����
    }

    return *this;
}

template<class T>
stack<T>& stack<T>::push(T e) /// ���������� ��������
{
    node* n = new node;
    n->element = e;
    n->next = top; // ���� ���� ��� ������, �� n->next ��������� NULL
    top = n;
    return *this;
}

template<class T>
stack<T>& stack<T>::pop() /// �������� ��������
{
    if (!top) return *this; // ���� ���� ������

    node* del = top;
    top = del->next; // ���� � ����� ��� ���� �������, �� top ������ NULL
    delete del;
    return *this;
}

template<class T>
stack<T>& stack<T>::clean() /// ������� �����
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
void stack<T>::print(std::ostream& stream) const /// ������
{
    if (!(top))
        stream << "���� ������";
    else
        for (node* n = (top); n; n = n->next)
            stream << n->element << " ";
}

#endif // STACK_H_INCLUDED