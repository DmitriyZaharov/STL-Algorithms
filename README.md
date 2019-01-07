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
Представьте что последовательсность уже отсортирована и nth указывает именно на элемент в уже отсортированной последовательности. То есть с помощью `std::nth_element` можно разбить последовательность на части, например, слева все элементы больше третьего по величине, а справа остальные элементы.
Причем не гарантируется что элементы справа и слева будут отсортированы.
Рассмотрим пример:
```cpp
std::vector<int> n_v{5, 6, 4, 3, 2, 6, 7, 9, 3, 8, 11, 0, 3, 12 };

std::nth_element(n_v.begin(), n_v.begin() + n_v.size()/2, n_v.end());
std::cout << "n_v after nth_element: \n";
std::cout << n_v;
std::cout << "The median is " << n_v[n_v.size()/2] << '\n';
```
Что произойдет при выполнении `std::nth_element(n_v.begin(), n_v.begin() + n_v.size()/2, n_v.end())`:
* представляем что последовательсность отсортирована и видим, что в отсортированном виде под элементом с индексом `n_v[n_v.size()/2]` находится 6 (отсортированная последовательсноть "0 2 3 3 3 4 5 6 6 7 8 9 11 12")
* в правой части последовательности будут находится все элементы меньше 6
* элемент 6 будет находится под индексом `n_v[n_v.size()/2]`
* в левой части будут находится все элементы больше или равные 6

Так будет выглядеть вывод:
```sh
n_v after nth_element: 
2 0 3 3 3 4 5 6 7 8 6 9 11 12 
The median is 6
```
Элемент 9 имеет индекс `11`, а элемент с индексом ` n_v[n_v.size()/2]` теперь равен 6.

Еще один пример, рассмотрим последовательность
```cpp
std::vector<int> n_v{9, 6, 4, 10, 2, 1, 7, 5, 3, 12, 11, 13, 14, 8 };
```
В отсортированном виде:
```sh
1 2 3 4 5 6 7 8 9 10 11 12 13 14 
```

Выполним:
```cpp
std::nth_element(n_v.begin(), n_v.begin()+1, n_v.end(), std::greater<int>());
std::cout << "The second largest element is " << n_v[1] << '\n';
std::cout << n_v;
```
Посмотрим на вывод:
```sh
The second largest element is 13
14 13 12 8 11 10 9 6 7 1 2 5 4 3 
```
Так как в `std::nth_element(n_v.begin(), n_v.begin()+1, n_v.end(), std::greater<int>());` мы использовали компаратор ` std::greater<int>()`, то последовательсноть была отсортирована по убыванию и элемент с индексом `1` является вторым по величине элементом последовательности, в данном случае это число 13.
В результате мы получили первые два элемента последовательности отсортированные по убыванию, все остальные элементы меньше второго по величине элемента, но не отсортированы.

## Partitioning operations (Алгоритмы структурирования)

### [`std::partition`](https://en.cppreference.com/w/cpp/algorithm/partition)
[Основные определения:](https://en.cppreference.com/w/cpp/algorithm/partition)
```cpp
template< class ForwardIt, class UnaryPredicate >
ForwardIt partition( ForwardIt first, ForwardIt last, UnaryPredicate p );
```
В отличие от всех рассмотренных ранее алгоритмов `std::partition` имеет возвращаемый тип `ForwardIt`, то есть итератор на элемент.
`UnaryPredicate p` - функция вида:
```cpp
 bool predicate(const Type1 &a);
```
В отличие от компаратора, принимает один элемент последовательсноти.

Данный алгоритм используется когда нужно разбить последовательность на две части по определенному критерию.
Рассмотрим пример, необходимо разбить последовательность таким образом, чтобы слева находились все четные элементы, а справа соотвестенно нечетные:

```cpp
std::vector<int> v = {0,1,2,3,4,5,6,7,8,9};
std::cout << "Original vector:\n    ";
for(int elem : v) std::cout << elem << ' ';

auto it = std::partition(v.begin(), v.end(), [](int i){return i % 2 == 0;});

std::cout << "\nPartitioned vector:\n    ";
std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, " "));
std::cout << " * ";
std::copy(it, std::end(v), std::ostream_iterator<int>(std::cout, " "));
```
Обратите внимание, `it` итератор на элемент не удовлетворяющий условию, то есть первый нечетный.

### [`std::partition_point`](https://en.cppreference.com/w/cpp/algorithm/partition_point)
Основные определения:
```cpp
template< class ForwardIt, class UnaryPredicate >
ForwardIt partition_point( ForwardIt first, ForwardIt last, UnaryPredicate p );
```
Алгоритм работает аналогично `std::partition`, единственное отличие которое я нашла это сложность алгоритмов.
Для `std::partition` сложность 
> Given N = std::distance(first,last), <br> 1) Exactly N applications of the predicate. At most N/2 swaps if ForwardIt meets the requirements of LegacyBidirectionalIterator, and at most N swaps otherwise. <br> 2) O(N log N) swaps and O(N) applications of the predicate.

Для `std::partition_point`:
> Given N = std::distance(first, last), performs O(log N) applications of the predicate p. <br>
However, for non-LegacyRandomAccessIterators, the number of iterator increments is O(N).

## Modifying sequence operations (Преобразования последовательностей)
### [`std::rotate`](https://en.cppreference.com/w/cpp/algorithm/rotate)
Основные определения:
```cpp
template< class ForwardIt >
ForwardIt rotate( ForwardIt first, ForwardIt n_first, ForwardIt last );
```
Возвращает итератор на элемент `first + (last - n_first)`.
Алгоритм изменяет последовательность следующим образом:
* разделяет последовательность на две части [first, n_first) и [n_first, last)
* меняет их местами, то есть получим [n_first, last) и [first, n_first)

Рассмотрим простой пример:
```cpp
std::vector<int> v{2, 4, 2, 0, 5, 10, 7, 3, 7, 1};
std::cout << "befor simple rotate left  : \n";
std::cout << v;
std::rotate(v.begin(), v.begin() + 2, v.end());
std::cout << "simple rotate left  : \n";
std::cout << v;
```
Вывод:
```sh
befor simple rotate left  : 
2 4 2 0 5 10 7 3 7 1 
simple rotate left  : 
2 0 5 10 7 3 7 1 2 4 
```
![](https://i.imgur.com/2tLOR6W.jpg)
Алгоритм `std::rotate` часто используется как вспомогательный для построения более сложных алгоритмов.
### [`std::reverse`](https://en.cppreference.com/w/cpp/algorithm/reverse)
Основное определение:
```cpp
template< class BidirIt >
void reverse( BidirIt first, BidirIt last );
```
Ещё один знакомый многим алгоритм, принимает два итератора на начало и конец последовательности. Преобразует порядок элементов в последовательности на обратный.

Пример:
```cpp
std::vector<int> v_r{1,2,3, 4, 5, 6};
std::cout << "before reverse :\n";
std::cout << v_r;

std::reverse(std::begin(v_r), std::end(v_r));
std::cout << "after reverse :\n";
std::cout << v_r;
```
Вывод:
```sh
before reverse :
1 2 3 4 5 6 
after reverse :
6 5 4 3 2 1 
```

## `stable_*`
У некоторых алгоритмов есть версии, названия которых начинаются со `stable_`, рассмотрим их.

### [`std::stable_sort`](https://en.cppreference.com/w/cpp/algorithm/stable_sort)
Основные определения:
```cpp
template< class RandomIt >
void stable_sort( RandomIt first, RandomIt last );

template< class RandomIt, class Compare >
void stable_sort( RandomIt first, RandomIt last, Compare comp );
```
Определения полностью совпадают с алгоритмом `std::sort`. Аналогично `std::sort` алгоритм `std::stable_sort` возвращает отсортированную последовательность элементов. Разница в том, что `std::stable_sort` сохраняет относительный порядок равных элементов после сортировки.

Рассмотрим как это выглядит на примере:
```cpp
struct Employee
{
    int age;
    std::string name;  // поле не принимает участие в сортировке
};

//перегруженный оператор сравнения для структуры Employee, сравнение только по полю age
bool operator<(const Employee & lhs, const Employee & rhs)
{
    return lhs.age < rhs.age;
}
```

Создадим последовательсность структур:
```cpp
    std::vector<Employee> v =
            {
                    {1, "1Zaphod"},
                    {2, "1Arthur"},
                    {3, "1Ford"},
                    {4, "1Ali"},
                    {5, "1Klack"},
                    {6, "1Djo"},
                    {7, "1Lue"},

                    {1, "2Zaphod"},
                    {2, "2Arthur"},
                    {3, "2Ford"},
                    {4, "2Ali"},
                    {5, "2Klack"},
                    {6, "2Djo"},
                    {7, "2Lue"},

                    {1, "3Zaphod"},
                    {2, "3Arthur"},
                    {3, "3Ford"},
                    {4, "3Ali"},
                    {5, "3Klack"},
                    {6, "3Djo"},
                    {7, "3Lue"},
            };

```
Отсортируем её с помощью `std::stable_sort`
```cpp
    std::cout << "before stable sort :\n";

    for (const Employee & e : v)
        std::cout << e.age << ", " << e.name << '\n';

    std::stable_sort(v.begin(), v.end());
    
    std::cout << "after stable sort :\n";
    for (const Employee & e : v)
        std::cout << e.age << ", " << e.name << '\n';
```
и посмотрим вывод:
```sh
1, 1Zaphod
1, 2Zaphod
1, 3Zaphod
2, 1Arthur
2, 2Arthur
2, 3Arthur
3, 1Ford
3, 2Ford
3, 3Ford
4, 1Ali
4, 2Ali
4, 3Ali
5, 1Klack
5, 2Klack
5, 3Klack
6, 1Djo
6, 2Djo
6, 3Djo
7, 1Lue
7, 2Lue
7, 3Lue
```
Элементы с одинаковыми значениями, в данном случае элементы `Employee` с одинаковым полем `age` в отсортированном векторе располагаются именно в той последовательности, в какой они были в оригинальном векторе.

Теперь для этой же последовательности посмотрим что получится если заменить `std::stable_sort` на `std::sort`:
```cpp
    std::sort(v.begin(), v.end());
    
    std::cout << "after sort :\n";
    for (const Employee & e : v)
        std::cout << e.age << ", " << e.name << '\n';
```

Вывод:
```sh
1, 3Zaphod
1, 2Zaphod
1, 1Zaphod
2, 1Arthur
2, 3Arthur
2, 2Arthur
3, 1Ford
3, 3Ford
3, 2Ford
4, 2Ali
4, 3Ali
4, 1Ali
5, 2Klack
5, 1Klack
5, 3Klack
6, 2Djo
6, 1Djo
6, 3Djo
7, 2Lue
7, 1Lue
7, 3Lue
```
Как видим элементы отсортированы, но порядок элементов с одинаковыми значениями не всегда совпадает с порядком в оригинальном векторе.

Алгоритм `std::stable_sort` работает медленее чем `std::sort`.

### [`std::stable_partition`](https://en.cppreference.com/w/cpp/algorithm/stable_partition)
Определение:
```cpp
template< class BidirIt, class UnaryPredicate >
BidirIt stable_partition( BidirIt first, BidirIt last, UnaryPredicate p );
```
В отличие от своего собрата `std::partition` алгоритм `std::stable_sort` сохраняет оригинальную последовательность элементов с одинаковыми значениями.
Вернемся к примеру со структурой `Employee`
```cpp
std::vector<Employee> v =
        {
                {1, "1Zaphod"},
                {2, "1Arthur"},
                {3, "1Ford"},
                {4, "1Ali"},
                {5, "1Klack"},
                {6, "1Djo"},
                {7, "1Lue"},

                {1, "2Zaphod"},
                {2, "2Arthur"},
                {3, "2Ford"},
                {4, "2Ali"},
                {5, "2Klack"},
                {6, "2Djo"},
                {7, "2Lue"},

                {1, "3Zaphod"},
                {2, "3Arthur"},
                {3, "3Ford"},
                {4, "3Ali"},
                {5, "3Klack"},
                {6, "3Djo"},
                {7, "3Lue"},
        };
```
Выполним:
```cpp
std::stable_partition(v.begin(), v.end(), [](Employee n){return n.age>3;});
std::cout << "after stable partition :\n";
for (const Employee & e : v)
    std::cout << e.age << ", " << e.name << '\n';
```
Вывод:
```sh
4, 1Ali
5, 1Klack
6, 1Djo
7, 1Lue
4, 2Ali
5, 2Klack
6, 2Djo
7, 2Lue
4, 3Ali
5, 3Klack
6, 3Djo
7, 3Lue
1, 1Zaphod
2, 1Arthur
3, 1Ford
1, 2Zaphod
2, 2Arthur
3, 2Ford
1, 3Zaphod
2, 3Arthur
3, 3Ford
```










