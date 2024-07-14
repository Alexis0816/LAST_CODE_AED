#include <iostream>
#include <vector>
using namespace std;

class minHeap
{
private:
    int size;
    int capacity;
    vector<int> heap;
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    minHeap(int capacity) : size(0), capacity(capacity), heap(vector<int>(capacity)) {}

    void insert(int k)
    {
        if (size == capacity)
        {
            cout << "MIN HEAP LLENO" << endl;
            return;
        }
        size++;
        int i = size - 1;
        heap[i] = k;

        // update minHeap
        while (i != 0 && heap[parent(i)] > heap[i])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if ((l < size) && (heap[l] < heap[smallest]))
        {
            smallest = l;
        }
        if ((r < size) && (heap[r] < heap[smallest]))
        {
            smallest = r;
        }

        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

    int extractMin()
    {
        if (size == 0)
        {
            cout << "EMPTY" << endl;
            return INT_MAX;
        }
        else if (size == 1)
        {
            size--;
            return heap[0];
        }
        else
        {
            int min = heap[0];
            heap[0] = heap[size - 1];
            size--;
            heapify(0);
            return min;
        }
    }

    int getMin()
    {
        if (size == 0)
        {
            return INT_MAX;
        }
        return heap[0];
    }

    int getSize()
    {
        return size;
    }

    void printHeap()
    {
        int power = 0;
        int value = 1;
        for (int i = 0; i < size; i++)
        {
            if (i == value)
            {
                cout << endl;
                power += 1;
                value += (1 << power);
            }
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

class maxHeap
{
private:
    int size;
    int capacity;
    vector<int> heap;
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    maxHeap(int capacity) : size(0), capacity(capacity), heap(vector<int>(capacity)) {}

    void insert(int k)
    {
        if (size == capacity)
        {
            cout << "MAX HEAP LLENO" << endl;
            return;
        }
        size++;
        int i = size - 1;
        heap[i] = k;

        // update maxHeap
        while (i != 0 && heap[parent(i)] < heap[i])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if ((l < size) && (heap[l] > heap[largest]))
        {
            largest = l;
        }
        if ((r < size) && (heap[r] > heap[largest]))
        {
            largest = r;
        }

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }

    int extractMax()
    {
        if (size == 0)
        {
            cout << "EMPTY" << endl;
            return INT_MIN;
        }
        else if (size == 1)
        {
            size--;
            return heap[0];
        }
        else
        {
            int max = heap[0];
            heap[0] = heap[size - 1];
            size--;
            heapify(0);
            return max;
        }
    }

    int getMax()
    {
        if (size == 0)
        {
            return INT_MIN;
        }
        return heap[0];
    }

    int getSize()
    {
        return size;
    }

    void printHeap()
    {
        int power = 0;
        int value = 1;
        for (int i = 0; i < size; i++)
        {
            if (i == value)
            {
                cout << endl;
                power += 1;
                value += (1 << power);
            }
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

class MedianFinder
{
private:
    maxHeap *lowerHalf;
    minHeap *upperHalf;

public:
    MedianFinder()
    {
        lowerHalf = new maxHeap(1000); // Adjust capacity as needed
        upperHalf = new minHeap(1000); // Adjust capacity as needed
    }

    void addNum(int num)
    {
        lowerHalf->insert(num);

        if (lowerHalf->getSize() > 0 && upperHalf->getSize() > 0 && lowerHalf->getMax() > upperHalf->getMin())
        {
            int maxTop = lowerHalf->extractMax();
            upperHalf->insert(maxTop);
        }

        if (lowerHalf->getSize() > upperHalf->getSize() + 1)
        {
            upperHalf->insert(lowerHalf->extractMax());
        }
        else if (upperHalf->getSize() > lowerHalf->getSize())
        {
            lowerHalf->insert(upperHalf->extractMin());
        }
    }

    double findMedian()
    {
        if (lowerHalf->getSize() == upperHalf->getSize())
        {
            return (lowerHalf->getMax() + upperHalf->getMin()) / 2.0;
        }
        else
        {
            return lowerHalf->getMax();
        }
    }
};

int main(){

    MedianFinder medianFinder;
    medianFinder.addNum(2);
    medianFinder.addNum(3);
    cout << "Mediana: " << medianFinder.findMedian() << endl; // 2.5
    medianFinder.addNum(4);
    cout << "Mediana: " << medianFinder.findMedian() << endl; // 3
    return 0;
}