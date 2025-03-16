#include <bits/stdc++.h>

using namespace std;

class MinHeap {
private:
  vector<int> heap;

public:
  void heapify(const vector<int> &nums) {
    heap.push_back(0);
    for (const int &num : nums)
      insert(num);
  }

  MinHeap() { heap.push_back(0); }
  MinHeap(const vector<int> &nums) { heapify(nums); }

  void insert(int num) {
    heap.push_back(num);
    int i = heap.size() - 1;
    while (i > 1 && heap[i] < heap[i >> 1]) {
      swap(heap[i], heap[i >> 1]);
      i >>= 1;
    }
  }

  void remove() {
    heap[1] = heap[heap.size() - 1];
    heap.pop_back();
    int i = 1;
    while (i < heap.size()) {
      int left = i << 1, right = (i << 1) + 1, smallest = i;
      if (left < heap.size() && heap[left] < heap[smallest])
        smallest = left;
      if (right < heap.size() && heap[right] < heap[smallest])
        smallest = right;
      if (smallest == i)
        break;
      swap(heap[i], heap[smallest]);
      i = smallest;
    }
  }

  int top() { return heap[1]; }

  int size() { return heap.size() - 1; }

  bool empty() { return heap.size() == 1; }

  void replace(int num) {
    heap[1] = num;
    int i = 1;
    while (i < heap.size()) {
      int left = i << 1, right = (i << 1) + 1, smallest = i;
      if (left < heap.size() && heap[left] < heap[smallest])
        smallest = left;
      if (right < heap.size() && heap[right] < heap[smallest])
        smallest = right;
      if (smallest == i)
        break;
      swap(heap[i], heap[smallest]);
      i = smallest;
    }
  }
};

class MaxHeap {
private:
  vector<int> heap;

public:
  void heapify(const vector<int> &nums) {
    heap.push_back(0);
    for (const int &num : nums)
      insert(num);
  }

  MaxHeap() { heap.push_back(0); }
  MaxHeap(const vector<int> &nums) { heapify(nums); }

  void insert(int num) {
    heap.push_back(num);
    int i = heap.size() - 1;
    while (i > 1 && heap[i] > heap[i >> 1]) {
      swap(heap[i], heap[i >> 1]);
      i >>= 1;
    }
  }

  void remove() {
    heap[1] = heap[heap.size() - 1];
    heap.pop_back();
    int i = 1;
    while (i < heap.size()) {
      int left = i << 1, right = (i << 1) + 1, largest = i;
      if (left < heap.size() && heap[left] > heap[largest])
        largest = left;
      if (right < heap.size() && heap[right] > heap[largest])
        largest = right;
      if (largest == i)
        break;
      swap(heap[i], heap[largest]);
      i = largest;
    }
  }

  int top() { return heap[1]; }

  int size() { return heap.size() - 1; }

  bool empty() { return heap.size() == 1; }

  void replace(int num) {
    heap[1] = num;
    int i = 1;
    while (i < heap.size()) {
      int left = i << 1, right = (i << 1) + 1, largest = i;
      if (left < heap.size() && heap[left] > heap[largest])
        largest = left;
      if (right < heap.size() && heap[right] > heap[largest])
        largest = right;
      if (largest == i)
        break;
      swap(heap[i], heap[largest]);
      i = largest;
    }
  }
};

int main() {
  MaxHeap heap;
  heap.insert(3);
  heap.insert(2);
  heap.insert(1);

  while (!heap.empty()) {
    cout << heap.top() << endl;
    heap.remove();
  }
}
