#include <iostream>
#include <queue>
#include <vector>

class MedianFinder {
private:
    std::priority_queue<int> maxHeap; // max-heap para la mitad menor
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // min-heap para la mitad mayor

public:
    /** initialize your data structure here. */
    MedianFinder() {}

    void addNum(int num) {
        // Insertar en el max-heap primero
        maxHeap.push(num);
        
        // Asegurarse de que el mayor del max-heap sea menor que el menor del min-heap
        if (!minHeap.empty() && maxHeap.top() > minHeap.top()) {
            int maxTop = maxHeap.top();
            maxHeap.pop();
            minHeap.push(maxTop);
        }

        // Balancear los heaps si es necesario
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            return maxHeap.top();
        }
    }
};

int main() {
    MedianFinder medianFinder;
    medianFinder.addNum(2);
    medianFinder.addNum(3);
    std::cout << "Mediana: " << medianFinder.findMedian() << std::endl; // 1.5
    medianFinder.addNum(4);
    std::cout << "Mediana: " << medianFinder.findMedian() << std::endl; // 2
    return 0;
}


/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
