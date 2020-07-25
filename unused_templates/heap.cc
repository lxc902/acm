
// Min Heap (or Low Priority Queue)
template<typename T = int, typename Compare = std::less<T>>
class heap {
  /**
  Usage 1: min int heap, i.e. top() gives minimum:
    heap h; h.make({1,7,40,6,2,100,300});
    assert(h.c == (vector<int>{1, 2, 40, 6, 7, 100, 300}));

  Usage 2: custom comparator (becomes max int heap):
    auto cmp = [&](auto i, auto j) { return i > j; };
    heap h(cmp); h.make({1,7,40,6,2,100,300});
    assert(h.c == (vector<int>{300, 7, 100, 6, 2, 1, 40}));

  Usage 3: custom type and comparator (becomes max double heap):
    auto cmp = [&](auto i, auto j) { return i > j; };
    heap<double, decltype(cmp)> h(cmp);
    h.make({1,7,40,6,2,100,300});
    assert(h.c == (vector<double>{300, 7, 100, 6, 2, 1, 40}));
  */
 public:
  heap(Compare comp = Compare()):comp_(comp) {}
  void make(const vector<T>& in) { c = in; make(); }
  void make(initializer_list<T> in) { c = in; make(); }

  const T& top() { assert(!c.empty()); return c[0]; }
  T&& pop() { pop_heap(all(c)); T t=c.back(); c.pop_back(); return move(t); }
  void push(T v) { c.push_back(v); push_heap(all(c)); }
  
  // Duh... still cannot remove unless use a map[] to track indexes.
  // So better just *multiset.begin() ...

  vector<T> c;  // DNS private
 private:
  void make(){ 
    auto minheap = [&](auto i, auto j) { return !comp_(i,j); };
    make_heap(all(c), minheap);  // make_heap() default to max heap.
  }
  Compare comp_;
};
