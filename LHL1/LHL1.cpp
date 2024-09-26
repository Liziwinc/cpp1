#include <iostream>
#include <cstdlib>
#include <locale.h>

using namespace std;

template <class DataType> class Queue
{
protected:
    int count = 0;
public:
    virtual ~Queue() {};
    virtual int Empty(void) = 0;
    virtual int Full(void) = 0;
    virtual DataType Front(void) = 0;
    virtual int EnQueue(DataType x) = 0;
    virtual DataType DeQueue(void) = 0;
    int Get()
    {
        return count;
    }
};


template <class DataType> class QueueVector : public Queue<DataType>
{
    int front, rear; //индексы головы и хвоста
    int maxlength;  //размер массива
    DataType* data; //массив для хранения элементов
public:
    QueueVector(int n) : maxlength(n)
    {
        data = new DataType[maxlength];
        front = 0;
        rear = maxlength - 1;
    }
    ~QueueVector()
    {
        delete[] data;
    }

    int Empty(void)//проверка на пустоту
    {
        return (rear + 1) % maxlength == front;
    }
    int Full(void)//проверка на полноту заполнения
    {
        return (rear + 2) % maxlength == front;
    }
    DataType Front(void)//неразрушающее чтение элемента
    {
        return data[front];
    }
    int EnQueue(DataType x)//добавление элемента в очередь
    {
        if (Full()) return 0;
        this->count++;
        rear = (rear + 1) % maxlength;
        data[rear] = x;
        return 1;
    }
    DataType DeQueue(void)//извлечение элемента из очереди
    {
        if (Empty()) return 0;
        this->count--;
        int temp = front;
        front = (front + 1) % maxlength;
        return data[temp];
    }
};

template <class T> void MENU();
template <class T> void Print(Queue<T>* q);
template <class T> T Seek(Queue<T>* q);


int main(void)
{
    setlocale(LC_ALL, "rus");
    int menu;
    cout << "Выберите тип данных\n1.unsigned char\n2.int\n";

    do
        cin >> menu;
    while (menu != 1 && menu != 2 );

    switch (menu)
    {
    case 2: MENU<int>(); break; // float
    case 1: MENU<unsigned char>(); break;
    }
}

template <class T> void MENU()
{
    QueueVector<T> a(10);

    Queue<T>* q;
    T num;
    int menu, a1;
    q = &a;
    int m;

    do
    {
        system("cls");
        cout << "1.Добавить элемент\n2.Удалить элемент\n3.Поиск максимального отрицательного элемента в массиве.\n4.Вывод всех элементов\n5.Выход\n";
        cin >> menu;
        system("cls");
        switch (menu)
        {
        case 1: cout << "Введите число\n";
            if (typeid(num) == typeid(unsigned char))
            {
                do
                    cin >> a1;
                while (a1 < 0 || a1>255 || a1 == -0 || cin.fail());
                num = a1;
                q->EnQueue(int(num));
            }
            else
            {
                do
                    cin >> a1;
                while (a1 < 0 || a1>255 || a1 == -0 || cin.fail());
                num = a1;
                q->EnQueue(int(num));
            }
            system("pause"); break;
        case 2: q->DeQueue(); system("pause"); break;
        case 3:
            if (typeid(num) == typeid(unsigned char))
            {
                cout << "не может быть отрицательного числа в выбранном типе данных" << endl;
            }
            else {
                m = Seek(q); cout << m << endl;
            } system("pause"); break;
        case 4: Print(q); system("pause"); break;
        }
    } while (menu != 5);
}

template <class T> T Seek(Queue<T>* q)
{
    int count2 = q->Get();
    T cur, min = q->Front();
    for (; count2; count2--)
    {
        cur = q->DeQueue();
        if (cur < 0 && cur < min) min = cur;
        q->EnQueue(cur);
    }
    return min;
}


template <class T> void Print(Queue<T>* q)
{
    int count2 = q->Get();
    T cur;
    for (; count2; count2--)
    {
        cur = q->DeQueue();
        if (typeid(cur) == typeid(unsigned char))
            cout << int(cur) << " ";
        else
            cout << cur << " ";
        q->EnQueue(cur);
    }
}
