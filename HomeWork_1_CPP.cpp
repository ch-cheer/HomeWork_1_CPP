#include <iostream>
#include <stdexcept>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Node {
    int data;
    Node* next;
};

class QueueList {
private:
    Node* front;
    Node* rear;
    int size;
    long long operationCount;
public:
    QueueList() : front(nullptr), rear(nullptr), size(0), operationCount(0) {}

    long long getOperationCount() const {
        return operationCount;
    }

    void resetOperationCount() {
        operationCount = 0;
    }

    ~QueueList() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    // O(1)
    void enqueue(int value) {
        Node* newNode = new Node{ value, nullptr };
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    // O(1)
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
    }

    // O(1)
    int getFront() const {
        if (!isEmpty()) {
            return front->data;
        }
        throw runtime_error("Queue is empty");
    }

    // O(1)
    int getSize() const {
        return size;
    }

    // O(n)
    void display() {
        Node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Функция для узла с индексом - O(n)
    Node* nodeAtIndex(int index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }

        Node* current = front;
        for (int count = 0; count < index; ++count) {
            current = current->next;
        }
        return current;
    }

    // Оценка сложности – O(N^2) для худшего случая, без учета рекурсии
    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

private:
    // Функция смены двух элементов - O(1)
    void swap(int* a, int* b) {
        int t = *a;
        *a = *b;
        *b = t;
        operationCount += 3; // 3 присваивания
    }

    // Функция разделения для быстрой сортировки - O(n)
    int partition(int low, int high) {
        int pivotValue = nodeAtIndex(high)->data;
        int i = low - 1;
        operationCount += high - low + 1;

        for (int j = low; j < high; j++) {
            if (nodeAtIndex(j)->data <= pivotValue) {
                i++;
                swap(&nodeAtIndex(i)->data, &nodeAtIndex(j)->data);
            }
        }
        swap(&nodeAtIndex(i + 1)->data, &nodeAtIndex(high)->data);
        return i + 1;
    }
};

void fillQueue(QueueList& queue, int n) {
    queue.resetOperationCount();
    for (int i = n; i > 0; --i)
        queue.enqueue(i);
}

void benchmarkQuickSort(int n) {
    QueueList queue;
    fillQueue(queue, n);

    auto start = high_resolution_clock::now();

    queue.quickSort(0, n - 1);

    auto end = high_resolution_clock::now();

    duration<double, milli> elapsed = end - start;

    cout << "n = " << n << "," << endl;
    cout << "time(ms/s): " << elapsed.count() << "/" << elapsed.count() / 1000 << endl;
    cout << "NOP: " << queue.getOperationCount() << ";" << endl << endl;
}

void exampleWorkQuickSortQueueList() {
    QueueList queueList;

    queueList.enqueue(10);
    queueList.enqueue(60);
    queueList.enqueue(30);
    queueList.enqueue(20);
    queueList.enqueue(50);

    cout << "Original queue: ";
    queueList.display();

    queueList.quickSort(0, queueList.getSize() - 1);

    cout << "Sorted queue: ";
    queueList.display();
}

int main() {
    //exampleWorkQuickSortQueueList();
    
    int testSizes[] = { 300, 600, 900, 1200, 1500, 1800, 2100, 2400, 2700, 3000 };
    for (int n : testSizes) {
        benchmarkQuickSort(n);
    }

    return 0;
}