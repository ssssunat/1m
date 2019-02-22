/*Дан массив целых чисел A[0..n), n не превосходит 100 000.
Так же задан размер некотрого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n. 
Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне. Скорость работы O(n log n), память O(n).*/

#include<bits/stdc++.h>
//(дефайн максимальный макс)
/*Создадим структуру(elem) , в которой будем хранить два значения: значение элемента из исходного массива(его приоритет) и индекс элемента в исходном массиве.
Реализуем класс Heap на основе динамического массива состоящего из elem. Конструктор класса преобразует обычный массив из elem в Heap. 
Считаем исходный массив в новый массив A состоящий из elem.
Создадим кучу(H) на первых k элементах массива A. Выведем макс элемент из кучи H. Далее в цикле будем добавлять следующий элемент из A в H. Далее будем проверять:
если индекс макс элемента кучи H лежит в окне, выведем значение макс элемента, если индекс макс элемента вне окна, то удалим этот макс элемент из кучи и повторим этот алгоритм.
В итоге мы будем выводить только макс элемент из окна*/


int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

struct elem
{
    int index;
    int priority;
};

class Heap
{
public:

    Heap (elem* arr, int n)
    {
        size_ = n;
        realsize_ = n;
        heap_ = new elem [n];
        for (int i = 0; i < n; i++)
            heap_[i] = arr[i];
        for (int i = size_ / 2 - 1; i >= 0; i--)
            siftdown(i);
    }

    ~Heap()
    {
        delete[] heap_;
    }

    void siftup(int i)
    {
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (heap_[i].priority <= heap_[parent].priority)
                return;
            std::swap(heap_[i], heap_[parent]);
            i = parent;
        }
    }

    void siftdown(int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < size_ && heap_[left].priority > heap_[largest].priority)
            largest = left;
        if (right < size_ && heap_[right].priority > heap_[largest].priority)
            largest = right;
        if (largest != i)
        {
            std::swap(heap_[i], heap_[largest]);
            siftdown(largest);
        }
    }

    void add(elem element)
    {
        if (size_ == realsize_)
        {
            int newrealsize_ = max(realsize_ * 2, 1);
            elem* newheap_ = new elem [newrealsize_];
            for (int i = 0; i < size_; i++)
                newheap_[i] = heap_[i];
            delete[] heap_;
            heap_ = newheap_;
            realsize_ = newrealsize_;
        }
        heap_[size_] = element;
        siftup(size_);
        size_++;
    }

    elem showmax()
    {
        return heap_[0];
    }

    void popmax()
    {
        assert(size_ > 0);
        heap_[0] = heap_[size_ - 1];
        size_--;
        if (size_ > 0)
            siftdown(0);
    }

    int getsize()
    {
        return size_;
    }

    elem& operator[](int index)
    {
        assert(size_ > index);
        return heap_[index];
    }

private:
    elem* heap_;
    int size_;
    int realsize_;
};

void moving_maximum(elem* A, int n, int k)
{
    elem* arr = new elem [k];
    for (int i = 0; i < k; i++)
        arr[i] = A[i];
    Heap H(arr, k);
    elem element = H.showmax();
    std::cout<<element.priority << " ";
    for (int i = k; i < n; i++)
    {
        H.add(A[i]);
        element = H.showmax();
        while (element.index <= i - k)
             {
                 H.popmax();
                 element = H.showmax();
             }
        std::cout<<element.priority << " ";
    }

    delete[] arr;
}


int main()
{
    int n = 0;
    std::cin >> n;
    elem* A = new elem [n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> A[i].priority;
        A[i].index = i;
    }
    int k = 0;
    std::cin >> k;
    moving_maximum(A, n, k);
    delete[] A;
    return 0;
}
