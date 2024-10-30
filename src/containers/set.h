#ifndef CPP2_S21_CONTAINERS_SET_SET_H_
#define CPP2_S21_CONTAINERS_SET_SET_H_

#include "../RedBlackTree/RedBlackTree.h"

namespace s21 {
template <typename Key>
class set {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

  using RedBlackTreeType = RedBlackTree<Key>;
  using iterator = typename RedBlackTreeType::const_iterator;
  using const_iterator = typename RedBlackTreeType::const_iterator;

  using size_type = std::size_t;

 public: /* Member */
  set() = default;

  set(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) insert(item);
  };

  set(const set &other) { copy_from(other); }

  set(set &&other) noexcept { this->RBT_ = std::move(other.RBT_); }

  ~set() = default;

 public: /* Operators */
  set<Key> &operator=(const set &other) {
    if (this != &other) {
        this->RBT_ = other.RBT_;
        copy_from(other);
    }
    return *this;
  }

  set<Key> &operator=(set &&other) noexcept {
    if (this != &other) {
      this->RBT_.Clear();
      this->RBT_ = std::move(other.RBT_);
    }
    return *this;
}


 public: /* Iterators */
  iterator begin() { return RBT_.begin(); }

  const_iterator begin() const { return RBT_.begin(); }

  iterator end() { return RBT_.end(); }

  const_iterator end() const { return RBT_.end(); }

 public: /* Modifiers */
  void clear() { RBT_.Clear(); }

  void erase(const value_type &value) { RBT_.Remove(value); }

  void swap(set &other) { std::swap(RBT_, other.RBT_); }

  void merge(set &other) {
    for (const auto &item : other) insert(item);
    other.clear();
  }

  std::pair<iterator, bool> insert(const Key &value) {
    std::pair<iterator, bool> result{};
    result.first = this->find(value);
    if (result.first == this->end()) {
      result.first = this->RBT_.Insert(value);
      result.second = true;
    }
    return result;
  }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::initializer_list<value_type> items = {std::forward<Args>(args)...};
    std::vector<std::pair<iterator, bool>> result{};

    for (const_reference item : items) {
      std::pair<iterator, bool> pair = this->insert(item);
      result.push_back(pair);
    }
    return result;
  }
  
 public: /* Capacity */
  [[nodiscard]] size_t max_size() const { return RBT_.GetMaxSize(); }

  [[nodiscard]] bool empty() const { return RBT_.IsEmpty(); }

  [[nodiscard]] size_t size() const { return RBT_.GetSize(); }

 public: /* Lookup */
  [[nodiscard]] iterator find(const value_type &value) const {
    Node<Key> *node = RBT_.Search(value);
    return (node == nullptr) ? end() : iterator(node, RBT_.GetNil());
  }

  [[nodiscard]] bool contains(const value_type &value) const {
    return RBT_.Search(value) != nullptr;
  }

  private:
  void copy_from(const set &other) {
    for (iterator cur = other.begin(); cur != other.end(); ++cur) insert(*cur);
  }
 
 protected:
  RedBlackTreeType RBT_;

};


}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SET_SET_H_