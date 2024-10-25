#include <iostream>
#include <string>
#include <chrono> 
#include <ctime>
#include <thread>
#include <functional>
#include <cstdlib>
#include <time.h>

int rrand(int range_min, int range_max)
{
    return rand() % (range_max - range_min + 1) + range_min;
}
const unsigned int ARRSIZE = 10000000;
int arr[ARRSIZE];


int f1(int* arr, int n, int& x)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (i >= 0 and i < n/2)
        sum += arr[i];
    }
    return sum;
}

int f2(int* arr, int n, int& x)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if(i>=n/2 and i<n)
        sum += arr[i];
    }
    return sum;
}

int main()
{
    setlocale(LC_ALL, "Rus");

    srand(static_cast<unsigned int>(time(NULL)));

    // инициализация массива случайными значениями из диапазона -ABSLIMIT..ABSLIMIT
    for (unsigned int i = 0; i < ARRSIZE; i++)
    {
        arr[i] = rrand(1, 20);
    }
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << '\n';

    auto start = std::chrono::high_resolution_clock::now();
 
    int x = 0;

    int a = f1(arr, n, x);     
    std::thread t1(f1, arr, n, std::ref(a));
    t1.join();

    int b = f2(arr, n, x);
    std::thread t2(f2, arr, n, std::ref(b));
    t2.join();

    int Sum = a + b;
    std::cout << Sum << '\n';
    
    auto finish = std::chrono::high_resolution_clock::now();
    // сохраняем время конца работы	
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " sec" << std::endl; // вычисляем продолжительность работы в сек. и выводим на экран
    return 0;
}