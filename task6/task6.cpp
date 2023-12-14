#include <iostream>
#include "queue.h"
#include "stack.h"

int main()
{
    setlocale(LC_CTYPE, "Russian");

    try
    {
        stack<int> s({ 4,8 ,-7 ,1  });
        std::cout << s << std::endl;

        queue<int> q({ 4,8 ,-7 ,1 });
        std::cout << q << std::endl;

        q.clean();
        q.get_front() = 5;

        q.push(3); // Не будет выполняться
        std::cout << q << std::endl; // Не будет выполняться
    }
    catch (std::exception const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cout << "Ошибка произошла успешно!" << std::endl;

    return 0;
}