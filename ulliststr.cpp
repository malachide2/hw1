#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val) {
  if (empty()) {
    head_ = new Item(ARRSIZE / 2); // Allows for more efficient push back and front
    tail_ = head_;
  }
  else if (tail_->last == ARRSIZE) {
    // New item
    tail_->next = new Item();
    tail_->next->prev = tail_;
    tail_ = tail_->next;
  }

  tail_->val[tail_->last++] = val;
  size_++;
}

void ULListStr::pop_back() {
  if (empty()) return;
  
  tail_->last--;
  size_--;

  if (empty()) {
    delete tail_;
    head_ = nullptr;
    tail_ = nullptr;
  }
  else if (tail_->last - tail_->first == 0) {
    tail_ = tail_->prev;
    delete tail_->next;
    tail_->next = nullptr;
  }
}

void ULListStr::push_front(const std::string& val) {
  if (empty()) {
    head_ = new Item(ARRSIZE / 2); // Allows for more efficient push back and front
    tail_ = head_;
  }
  else if (head_->first == 0) {
    // New item
    head_->prev = new Item(ARRSIZE);
    head_->prev->next = head_;
    head_ = head_->prev;
  }

  head_->val[--(head_->first)] = val;
  size_++;
}

void ULListStr::pop_front() {
  if (empty()) return;

  head_->first++;
  size_--;

  if (empty()) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
  }
  else if (head_->last - head_->first == 0) {
    head_ = head_->next;
    delete head_->prev;
    head_->prev = nullptr;
  }
}

std::string const& ULListStr::back() const {
  if (empty()) return NULL;
  return tail_->val[tail_->last - 1];
}

std::string const& ULListStr::front() const {
  if (empty()) return NULL;
  return head_->val[head_->front];
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
  if (loc >= size_) return NULL;

  size_t count = 0;
  Item* currentNode = head_;
  size_t currentIdx = 0;
  while (count++ < loc) {
    if (currentNode->first + (++currentIdx) == currentNode->last) {
      currentNode = currentNode->next;
      currentIdx = 0;
    }
  }

  return &(currentNode->val[currentNode->first + currentIdx]);
}