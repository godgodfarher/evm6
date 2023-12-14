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

    virtual ~list() {} // ����������

    virtual list& push(T e) = 0; // ���������� ��������

    virtual list& pop() = 0; // �������� ��������

    virtual T& get_front() = 0; // ��������� ��������

    virtual const T& get_front() const = 0; // ��������� �������� (const)

    virtual bool is_empty() const = 0; // �������� �� �������

    virtual size_t size() const = 0; // ������ ������

    template<class M>
    friend std::ostream& operator << (std::ostream& stream, const list<M>& l) { l.print(stream); return stream; } // �����

    template<class M>
    friend std::istream& operator >> (std::istream& stream, list<M>& l) { M e; stream >> e; l.push(e); return stream; } // ����

protected:

    class node
    {
    public:
        node() : next(NULL) {}; // ����������� �� ���������
        node* next;
        T element;
    };

    virtual void print(std::ostream& stream) const = 0; // ������  
};

#endif // LIST_H_INCLUDED