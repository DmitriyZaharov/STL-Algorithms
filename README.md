# STL-Algorithms
Все алгоритмы будут приведены для стандарта языка от C\++11 до C++20, если другое явно не указано.

## Алгоритмы сортировки
Все рассматриваемые функции сортировки могут одним из параметров принимать компаратор. 
Компаратор это функция вида:
```cpp
 bool cmp(const Type1 &a, const Type2 &b);
```
Это нужно если мы хотим отсортировать последовательсность в порядке убывания, а не возрастания или хотим реализовать сравнение пользовательских типов данных по определенным критериям.

* Компаратор может быть одним из реализованных в стандартной библиотеке:
    * equal_to
    * not_equal_to
    * greater
    * less
    * greater_equal
    * less_equal
* Компаратор может быть реализован пользователем:
    * функтор (класс, для которого перегружен operator())  
    * свободная функция вида `bool compare(Type &t1, Type &t2)`
    * lambda-функция

Ниже мы увидим примеры использования компараторов.

### [`std::sort`](https://en.cppreference.com/w/cpp/algorithm/sort)

Всем известный алгоритм `sort`, сортирует последовательность заданную диапозоном [first, last) с помощью функции компаратора.

По умолчанию в роли компаратора выступает `operator<`, то есть если в функцию `sort` передать только начало и конец последовательности, то она будет отсортирована в порядке по возрастанию.

Два основных определения функции `sort`, описанных в [cppreference](https://en.cppreference.com):
```cpp
template< class RandomIt >
void sort( RandomIt first, RandomIt last );

template< class RandomIt, class Compare >
void sort( RandomIt first, RandomIt last, Compare comp );
```
В первом случае функция принимает итераторы на начало и конец последовательности, во втором дополнительно функцию компаратор.

Заголовочники и вспомогательная функция:
```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <functional>

/* перегрузка оператора вывода вектора, чтобы не писать цикл каждый раз, когда
 нужно вывести вектор */
std::ostream & operator<<(std::ostream &os, std::vector<int> const &v)
{
    for (auto a : v)
    {
       os << a << " ";
    }
    os << '\n';
    return os;
}
```
```cpp
// функция компаратор
bool custom_compare(int x, int y)
{
    return x > y;
}

void sort_algo()
{
    std::vector<int> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

    // сортировка по возрастанию, с помощью operator<
    std::cout << "Ascending sort: \n";
    std::sort(s.begin(), s.end());
    std::cout << s;

    // сортировка по убыванию с помощью компаратора стандарной библиотеки
    std::cout << "Descending  sort: \n";
    std::sort(s.begin(), s.end(), std::greater<int>());
    std::cout << s;

    // сортировка с помощью пользовательского функтора
    std::cout << "Custom functor  sort: \n";
    struct 
    {
        bool operator()(int a, int b) const
        {
            return a < b;
        }
    } customLess;

    std::sort(s.begin(), s.end(), customLess);
    std::cout << s;

    // сортировка с помощью пользовательской функции компаратора
    std::cout << "Custom comparator  sort: \n";
    std::sort(s.begin(), s.end(), custom_compare);
    std::cout << s;

    // сортировка с помощью лямбда функции
    std::cout << "Custom lambda  sort: \n";
    std::sort(s.begin(), s.end(), [](int a, int b) { return a < b; });

    std::cout << s;
}
```

### [`std::partial_sort`](https://en.cppreference.com/w/cpp/algorithm/partial_sort)
### Частичная сортировка
Если возникла необходимость найти 3 первых наименьших элемента последовательности в порядке возрастания или первая половина последовательсности должна содержать отсортированную часть наибольших элементов, для этих целей можно воспользоваться `std::partial_sort`

Два основных определения из [cppreference](https://en.cppreference.com/w/cpp/algorithm/partial_sort):
```cpp
template< class RandomIt >
void partial_sort( RandomIt first, RandomIt middle, RandomIt last );

template< class RandomIt, class Compare >
void partial_sort( RandomIt first, RandomIt middle, RandomIt last,
                   Compare comp );
```
В отличии от `std::sort` функция `std::partial_sort` принимает три итератора: итератор на начало последовательности, итератор на элемент до которого (не включая) выполнять сортировку и итератор на конец последовательности.

Все возможности параметра `Compare comp`(компаратора) описанные в начале справедливы и для `std::partial_sort`.
Пример использования:
```cpp
std::vector<int> p_s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
std::cout << "before partial_sort :\n";
std::cout << p_s;
std::partial_sort(p_s.begin(), p_s.begin() + 3, p_s.end());
std::cout << "after partial_sort :\n";
std::cout << p_s;
```
Вывод:
```sh
before partial_sort :
5 7 4 2 8 6 1 9 0 3 
after partial_sort :
0 1 2 7 8 6 5 9 4 3 
```

### [`std::nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element)

[Основные определения:](https://en.cppreference.com/w/cpp/algorithm/nth_element)
```cpp
template< class RandomIt >
void nth_element( RandomIt first, RandomIt nth, RandomIt last );
template< class RandomIt, class Compare >
void nth_element( RandomIt first, RandomIt nth, RandomIt last,
                  Compare comp );
```
`std::nth_element` переупорядочивает последовательность, ограниченную диапазоном [first,last), так что все элементы, меньшие чем тот, на который указывает итератор nth, оказываются перед ним, а все большие элементы - после. При этом не гарантируется, что элементы, расположенные по обе стороны от nth, упорядочены. 
Рассмотрим пример:
```cpp
std::vector<int> n_v{5, 6, 4, 3, 2, 6, 7, 9, 3, 8, 11, 0, 3, 12 };
std::cout << "n_v before nth_element: \n";
std::cout << n_v;
/* После вызова nth_element вся последовательность разделиться на две части
*/
std::nth_element(n_v.begin(), n_v.begin() + n_v.size()/2, n_v.end());
std::cout << "n_v after nth_element: \n";
std::cout << n_v;
std::cout << "The median is " << n_v[n_v.size()/2] << '\n';

std::nth_element(n_v.begin(), n_v.begin()+1, n_v.end(), std::greater<int>());
std::cout << "The second largest element is " << n_v[1] << '\n';
std::cout << n_v;
```





