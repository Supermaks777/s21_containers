#ifndef CPP2_S21_CONTAINERS_MULTISET_MULTISET_H_
#define CPP2_S21_CONTAINERS_MULTISET_MULTISET_H_

#include "../RedBlackTree/RedBlackTree.h"

namespace s21 {
template <typename Key>
class multiset {
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;

  using RedBlackTreeType = RedBlackTree<Key>;
  using iterator = typename RedBlackTreeType::const_iterator;
  using const_iterator = typename RedBlackTreeType::const_iterator;

  using size_type = std::size_t;

 public: /* Member */
  multiset() = default;

  multiset(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) insert(item);
  };

  multiset(const multiset &other) { copy_from(other); }

  multiset(multiset &&other) noexcept { this->RBT_ = std::move(other.RBT_); }

 public: /* Operators */
  multiset<Key> &operator=(const multiset &other) {
    if (this != &other) {
        this->RBT_ = other.RBT_;
        copy_from(other);
    }
    return *this;
  }

  multiset<Key> &operator=(multiset &&other) noexcept {
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

  void swap(multiset &other) { std::swap(RBT_, other.RBT_); }

  void merge(multiset &other) {
    for (const auto &item : other) insert(item);
    other.clear();
  }

  iterator insert(const value_type &value) {
    return this->RBT_.Insert(value);
  }

  //   iterator insert(const value_type &value) {
  //   iterator result = this->RBT_.Insert(value);
  //   return result;
  // } // все равно ошибка

  template <typename... Args>
  std::vector<iterator> insert_many(Args &&...args) {
    std::initializer_list<value_type> items = {std::forward<Args>(args)...};
    std::vector<iterator> result{};

    for (const_reference item : items) result.push_back(insert(item));
    return result;
  }

  // template <typename... Args> //все равно ошибка
  // std::vector<iterator> insert_many(Args &&...args) {
  //   std::initializer_list<value_type> items = {std::forward<Args>(args)...};
  //   std::vector<iterator> result{};

  //   for (const_reference item : items) {
  //     result.push_back(insert(item));
  //   }
  //   return result;
  // }

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

  std::pair<iterator, iterator> equal_range(const value_type &data) const {
    auto lower = lower_bound(data);
    auto upper = upper_bound(data);
    return {lower, upper};
  }

  iterator lower_bound(const value_type &data) const {
    return this->RBT_.GetLowerBoundIterator(data);
  }

  iterator upper_bound(const value_type &data) const {
    return this->RBT_.GetUpperBoundIterator(data);
  }

  private:
  void copy_from(const multiset &other) {
    for (iterator cur = other.begin(); cur != other.end(); ++cur) insert(*cur);
  }


 protected:
  RedBlackTreeType RBT_;


};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_MULTISET_MULTISET_H_