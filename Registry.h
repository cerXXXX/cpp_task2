#ifndef REGISTRY_H
#define REGISTRY_H

#include <algorithm>
#include <utility>
#include <vector>

template <typename T>
class Registry {
 public:
  void add(T item) { items_.push_back(std::move(item)); }

  std::size_t size() const { return items_.size(); }

  const T& operator[](std::size_t index) const { return items_.at(index); }

  std::vector<T>::const_iterator begin() const { return items_.cbegin(); }
  std::vector<T>::const_iterator end() const { return items_.cend(); }

  template <typename Predicate>
  bool removeFirst(Predicate matches) {
    auto it = std::find_if(items_.cbegin(), items_.cend(), matches);

    if (it == items_.cend()) {
      return false;
    }

    items_.erase(it);
    return true;
  }

 private:
  std::vector<T> items_;
};

#endif
