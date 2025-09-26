#ifndef __SET_CPP__
#define __SET_CPP__

#include "../headers/Set.hpp"
#include <algorithm>
#include <cassert>
#include <limits>

template <typename Data>
Set<Data>::Set()
    : root_(NULL)
{}

template <typename Data>
template <typename InputIterator>
Set<Data>::Set(InputIterator first, InputIterator last)
{
    while (first != last) {
        insert(*first);
        ++first;
    }
}

template <typename Data>
Set<Data>::Set(const Set<Data>& rhv)
    : root_(NULL)
{
    insert(rhv.begin(), rhv.end());
}

template <typename Data>
Set<Data>::~Set()
{
    clear();
}

template <typename Data>
typename Set<Data>::const_iterator
Set<Data>::begin() const
{
    return const_iterator(getLeftMost(root_));
}

template <typename Data>
typename Set<Data>::const_iterator
Set<Data>::end() const
{
    return const_iterator(NULL);
}

template <typename Data>
typename Set<Data>::iterator
Set<Data>::begin()
{
    return iterator(getLeftMost(root_));
}

template <typename Data>
typename Set<Data>::iterator
Set<Data>::end()
{
    return iterator(NULL);
}

template <typename Data>
void
Set<Data>::clear()
{
    clearNode(root_);
    root_ = NULL;
}

template <typename Data>
bool
Set<Data>::empty() const
{
    return NULL == root_;
}

template <typename Data>
typename Set<Data>::size_type
Set<Data>::size() const
{
    size_type i = 0;
    const_iterator it = begin();
    while (it != end()) {
        ++i;
        ++it;
    }
    return i;
}

template <typename Data>
typename Set<Data>::size_type
Set<Data>::max_size() const
{
    return std::numeric_limits<size_t>::max() / sizeof(Node);
}

template <typename Data>
bool
Set<Data>::operator==(const Set<Data>& rhv) const
{
    if (this == &rhv) return true;
    if (size() != rhv.size()) return false;
    const_iterator it1 = begin();
    const_iterator it2 = rhv.begin();
    for (; it1 != end(); ++it1, ++it2) {
        if (*it1 != *it2) return false;
    }
    return true;
}

template <typename Data>
bool
Set<Data>::operator!=(const Set<Data>& rhv) const
{
    return !(*this == rhv);
}

template <typename Data>
bool
Set<Data>::operator<(const Set<Data>& rhv) const
{
    if (this == &rhv) return false;
    const_iterator it1 = begin();
    const_iterator it2 = rhv.begin();
    for (; it1 != end() || it2 != rhv.end(); ++it1, ++it2) {
        if (*it1 < *it2) return true;
        if (*it1 > *it2) return false;
    }
    return it1 == end() && it2 != rhv.end();
}

template <typename Data>
bool
Set<Data>::operator>(const Set<Data>& rhv) const
{
    return (rhv < *this);
}

template <typename Data>
bool
Set<Data>::operator>=(const Set<Data>& rhv) const
{
    return !(*this < rhv);
}

template <typename Data>
bool
Set<Data>::operator<=(const Set<Data>& rhv) const
{
    return !(*this > rhv);
}

template <typename Data>
std::pair<typename Set<Data>::iterator, bool>
Set<Data>::insert(const value_type& x)
{
    return insertHelper(iterator(root_), x);
}

template <typename Data>
typename Set<Data>::iterator
Set<Data>::insert(iterator it, const value_type& x)
{
    return insertHelper(it, x).first;
}

template <typename Data>
template <typename InputIterator>
void
Set<Data>::insert(InputIterator first, InputIterator last)
{
    while (first != last) {
        insert(*first);
        ++first;
    }
}

template <typename Data>
std::pair<typename Set<Data>::iterator, bool>
Set<Data>::insertHelper(iterator it, const value_type& x)
{
    if (empty()) {
        root_ = new Node(x);
        return std::make_pair(begin(), true);
    }
    goUp(it, x);
    const bool isAdded = goDownAndInsert(it, x);
    if (isAdded) balance(it);
    return std::make_pair(it, isAdded);
}

template <typename Data>
void
Set<Data>::goUp(iterator& it, const value_type& x)
{
    if (!it.parent() || x == *it) return;
    const const_iterator temp = (x < *it) 
                              ? it.firstLeftParent()
                              : it.firstRightParent();
    if (isRoot(temp)) return;
    const bool isRightPlace = (x < *it) 
                            ? (*temp < x) 
                            : (*temp > x);
    if (isRightPlace) return;
    it.ptr_ = temp.ptr_;
    goUp(it, x);
}

template <typename Data>
bool
Set<Data>::goDownAndInsert(iterator& it, const value_type& x)
{
    if (it && x < *it) {
        if (!it.left()) {
            it.createLeft(x);
            return true;
        }
        return goDownAndInsert(it.moveLeft(), x);
    }
    if (it && x > *it) {
        if (!it.right()) {
            it.createRight(x);
            return true;
        }
        return goDownAndInsert(it.moveRight(), x);
    }
    return false;
}

template <typename Data>
typename Set<Data>::iterator
Set<Data>::find(const key_type& key) const
{
    Node* current = root_;
    while (NULL != current) {
        if (key < current->data_) {
            current = current->left_;
        } else if (key > current->data_) {
            current = current->right_;
        } else {
            return iterator(current);
        }
    }
    return iterator(NULL);
}

template <typename Data>
typename Set<Data>::size_type
Set<Data>::count(const key_type& key) const
{
    return (iterator(NULL) == find(key)) ? 0 : 1;
}

template <typename Data>
typename Set<Data>::iterator
Set<Data>::lower_bound(const key_type& key) const
{
    Node* current = root_;
    Node* result = NULL;

    while (NULL != current) {
        if (!(current->data_ < key)) {
            result = current;
            current = current->left_;
        } else {
            current = current->right_;
        }
    }
    return (NULL == result) ? iterator(NULL) : iterator(result);
}

template <typename Data>
typename Set<Data>::iterator
Set<Data>::upper_bound(const key_type& key) const
{
    Node* current = root_;
    Node* result = NULL;

    while (NULL != current) {
        if (key < current->data) {
            result = current;
            current = current->left_;
        } else {
            current = current->right_;
        }
    }
    return (NULL == result) ? iterator(NULL) : iterator(result);
}

template <typename Data>
std::pair<typename Set<Data>::iterator, typename Set<Data>::iterator>
Set<Data>::equal_range(const key_type& key) const
{
    return std::make_pair(lower_bound(key), upper_bound(key));
}

/*
template <typename Data>
void
Set<Data>::balance(iterator& it)
{
    if (!it) return;
    const int factor = it.balance();
    if (factor > 1) {
        iterator itLeft = it.left();
        if (itLeft.balance() < 0) rotateRight(itLeft);
        rotateLeft(it);
        return;
    } 
    if (factor < -1) {
        iterator itRight = it.right();
        if (itRight.balance() > 0) rotateLeft(itRight);
        rotateRight(it);
        return;
    }
    balance(it.goParent()); 
}
*/

template <typename Data>
typename Set<Data>::Node*
Set<Data>::getRightMost(Node* ptr) const
{
    if (NULL == ptr) return NULL;
    while (ptr->right_ != NULL) ptr = ptr->right_;
    return ptr;
}


template <typename Data>
typename Set<Data>::Node*
Set<Data>::getLeftMost(Node* ptr) const
{
    if (NULL == ptr) return NULL;
    while (ptr->left_ != NULL) ptr = ptr->left_;
    return ptr;
}

template <typename Data>
void
Set<Data>::clearNode(Node* ptr)
{
    if (NULL == ptr) return;
    clearNode(ptr->left_);
    clearNode(ptr->right_);
    delete ptr;
}


/////////////////////              const_iterator
template <typename Data>
Set<Data>::const_iterator::const_iterator()
    : ptr_(NULL)
{}



template <typename Data>
Set<Data>::const_iterator::const_iterator(const const_iterator& rhv)
    : ptr_(rhv.getPtr())
{}

template <typename Data>
Set<Data>::const_iterator::const_iterator(Node* ptr)
    : ptr_(ptr)
{}

template <typename Data>
Set<Data>::const_iterator::~const_iterator()
{
    ptr_ = NULL;
}

template <typename Data>
typename Set<Data>::const_iterator&
Set<Data>::const_iterator::operator=(const const_iterator& rhv)
{
    if (this == &rhv) return *this;
    ptr_ = rhv.getPtr();
    return *this;
}

template <typename Data>
const typename Set<Data>::value_type&
Set<Data>::const_iterator::operator*() const
{
    return ptr_->data_;
}

template <typename Data>
const typename Set<Data>::value_type*
Set<Data>::const_iterator::operator->() const
{
    return &(ptr_->data_);
}

template <typename Data>
bool
Set<Data>::const_iterator::isLeftParent() const
{
    return ptr_->parent_ != NULL && ptr_->parent_->right_ == ptr_;
}

template <typename Data>
bool
Set<Data>::const_iterator::isRightParent() const
{
    return ptr_->parent_ != NULL && ptr_->parent_->left_ == ptr_;
}


template <typename Data>
typename Set<Data>::const_iterator&
Set<Data>::const_iterator::operator++()
{
    if (NULL == this->getPtr()->right_) { 
        while (this->isLeftParent()) {
            this->moveParent();
        }
        this->moveParent();
        return *this;
    }
    this->setPtr(getLeftMost(this->getPtr()->right_));
    return *this;
}

template <typename Data>
typename Set<Data>::const_iterator&
Set<Data>::const_iterator::operator--()
{
    if (NULL == this->getPtr()->left_) { 
        while (this->isRightParent()) {
            this->moveParent();
        }
        this->moveParent();
        return *this;
    }
    this->setPtr(getRightMost(this->getPtr()->left_));
    return *this;
}



template <typename Data>
typename Set<Data>::const_iterator
Set<Data>::const_iterator::operator++(int)
{
    assert(ptr_ != NULL && ptr_ != getRightMost(root_));
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename Data>
typename Set<Data>::const_iterator
Set<Data>::const_iterator::operator--(int)
{
    assert(ptr_ != NULL && ptr_ != getLeftMost(root_));
    const_iterator temp = *this;
    --(*this);
    return temp;
}

template <typename Data>
bool
Set<Data>::const_iterator::operator==(const const_iterator& rhv) const
{
    return rhv.getPtr() == getPtr();
}


template <typename Data>
bool
Set<Data>::const_iterator::operator!=(const const_iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename Data>
typename Set<Data>::Node*
Set<Data>::const_iterator::getPtr() const
{
    return ptr_;
}

template <typename Data>
typename Set<Data>::const_iterator
Set<Data>::const_iterator::parent() const
{
    return const_iterator(ptr_->parent_);
}

template <typename Data>
typename Set<Data>::const_iterator
Set<Data>::const_iterator::left() const
{
    return const_iterator(ptr_->left_);
}

template <typename Data>
typename Set<Data>::const_iterator
Set<Data>::const_iterator::right() const
{
    return const_iterator(ptr_->right_);
}

template <typename Data>
void
Set<Data>::const_iterator::setPtr(Node* ptr)
{
    assert(ptr != NULL);
    ptr_ = ptr;
}

template <typename Data>
void
Set<Data>::const_iterator::setParent(const_iterator it)
{
    ptr_->parent_ = it.getPtr();
}

template <typename Data>
void
Set<Data>::const_iterator::setLeft(const_iterator it)
{
    ptr_->left_ = it.getPtr();
}

template <typename Data>
void
Set<Data>::const_iterator::setRight(const_iterator it)
{
    ptr_->right_ = it.getPtr();
}

template <typename Data>
void
Set<Data>::const_iterator::createLeft(const value_type& x)
{
    ptr_->left_ = new Node(x, ptr_);
}

template <typename Data>
void
Set<Data>::const_iterator::createRight(const value_type& x)
{
    ptr_->right_ = new Node(x, ptr_);
}


template <typename Data>
void
Set<Data>::const_iterator::moveRight()
{
    ptr_ = ptr_->right_;
}

template <typename Data>
void
Set<Data>::const_iterator::moveLeft()
{
    ptr_ = ptr_->left_;
}

template <typename Data>
void
Set<Data>::const_iterator::moveParent()
{
    ptr_ = ptr_->parent_;
}

template <typename Data>
bool
Set<Data>::const_iterator::operator!() const
{
    return NULL == ptr_;
}

template <typename Data>
typename Set<Data>::const_iterator
Set<Data>::const_iterator::firstLeftParent() const
{
    if (!parent()) return const_iterator(NULL);
    const_iterator nodeParent = parent();
    if (nodeParent.right() == *this) return nodeParent;
    return nodeParent.firstLeftParent();
}

template <typename Data>
typename Set<Data>::const_iterator
Set<Data>::const_iterator::firstRightParent() const
{
    if (!parent()) return const_iterator(NULL);
    const_iterator nodeParent = parent();
    if (nodeParent.left() == *this) return nodeParent;
    return nodeParent.firstRightParent();
}


/////////////////////iterator

template <typename Data>
Set<Data>::iterator::iterator()
    : const_iterator()
{}

template <typename Data>
Set<Data>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv.getPtr())
{}

template <typename Data>
Set<Data>::iterator::iterator(Node* ptr)
    : const_iterator(ptr)
{}

template <typename Data>
Set<Data>::iterator::~iterator()
{}

template <typename Data>
typename Set<Data>::value_type&
Set<Data>::iterator::operator*()
{
    return this->getPtr()->data_;
}

template <typename Data>
typename Set<Data>::value_type*
Set<Data>::iterator::operator->()
{
    return &(this->getPtr()->data_);
}

template <typename Data>
bool
Set<Data>::iterator::operator==(const iterator& rhv) const
{
    return rhv.getPtr() == this->getPtr();
}


template <typename Data>
bool
Set<Data>::iterator::operator!=(const iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename Data>
typename Set<Data>::iterator&
Set<Data>::iterator::operator++()
{
    assert(this->ptr_ != NULL && this->ptr_ != getRightMost(root_));
    if (this->ptr_->right_ != NULL) {
        this->ptr_ = getLeftMost(this->ptr_->right_);
        return *this;
    }
    while (isLeftParent(this->ptr_->parent_)) this->ptr_ = this->ptr_->parent_;
    this->ptr_ = this->ptr_->parent_;
    return *this;
}

template <typename Data>
typename Set<Data>::iterator
Set<Data>::iterator::operator++(int)
{
    assert(this->ptr_ != NULL && this->ptr_ != getRightMost(root_));
    iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename Data>
typename Set<Data>::iterator&
Set<Data>::iterator::operator--()
{
    assert(this->ptr_ != NULL && this->ptr_ != getLeftMost(root_));
    if (this->ptr_->left_ != NULL) {
        this->ptr_ = getRightMost(this->ptr_->left_);
        return *this;
    }
    while (isRightParent(this->ptr_->parent_)) this->ptr_ = this->ptr_->parent_;
    this->ptr_ = this->ptr_->parent_;
    return *this;
}

template <typename Data>
typename Set<Data>::iterator
Set<Data>::iterator::operator--(int)
{
    assert(this->ptr_ != NULL && this->ptr_ != getLeftMost(root_));
    iterator temp = *this;
    --(*this);
    return temp;
}

#endif /// __SET_CPP__



