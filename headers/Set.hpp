#ifndef __SET_HPP__
#define __SET_HPP__

#include <cstddef>
#include <ostream>

template <typename Data>
class Set
{
template <typename T>
friend std::ostream& operator<<(std::ostream& out, const Set<T>& rhv);

struct Node {
    Node(const Data& data = Data(), Node* left = NULL, Node* right = NULL, Node* parent = NULL)
        : parent_(parent)
        , left_(left)
        , right_(right)
        , data_(data)
    {}
    Node* parent_;
    Node* left_;
    Node* right_;
    Data data_;
};

public:
    typedef Data value_type;
    typedef Data key_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

public:
    class const_iterator {
    friend class Set<Data>;
    public:
        const_iterator();
        const_iterator(const const_iterator& rhv);
        ~const_iterator();

        const_iterator&   operator=(const const_iterator& rhv);
        const value_type& operator*() const;
        const value_type* operator->() const;

        const_iterator& operator++();
        const_iterator  operator++(int);
        const_iterator& operator--();
        const_iterator  operator--(int);
        bool operator!() const;
        bool operator==(const const_iterator& rhv) const;
        bool operator!=(const const_iterator& rhv) const;

    protected:
        void setPtr(Node* ptr);
        Node* getPtr()          const;
        const_iterator right()  const;
        const_iterator left()   const;
        const_iterator parent() const;
        bool isRightParent()    const;
        bool isLeftParent()     const;
        const_iterator firstLeftParent()  const;
        const_iterator firstRightParent() const;
        void setParent(const_iterator it);
        void setLeft(const_iterator it);
        void setRight(const_iterator it);
        void createRight(const value_type& x);
        void createLeft(const value_type& x);
        void moveLeft();
        void moveRight();
        void moveParent();

    private:
        explicit const_iterator(Node* ptr);
    private:
        Node* ptr_;
    };

public:
    class iterator :public const_iterator {
    friend class Set<Data>;
    public:
        iterator();
        iterator(const iterator& rhv);
        ~iterator();
        iterator& operator=(const iterator& rhv);
        value_type& operator*();
        value_type* operator->();
        bool operator==(const iterator& rhv) const;
        bool operator!=(const iterator& rhv) const;

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

    private:
        iterator firstLeftParent()  const;
        iterator firstRightParent() const;

    private:
        explicit iterator(Node* ptr);
    };

public:
    Set();
    Set(const Set<Data>& rhv);
    template <typename InputIterator>
    Set(InputIterator first, InputIterator last); 

    ~Set(); ////////////////
    const Set& operator=(const Set& rhv); //////////////
    void swap(Set& rhv);       ///////////////
    void clear();

////////
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
////////////////

//////
    size_type size() const;
    size_type max_size() const;
    bool empty() const;
//////

    bool operator==(const Set& rhv) const;
    bool operator!=(const Set& rhv) const;
    bool operator< (const Set& rhv) const;
    bool operator<=(const Set& rhv) const;
    bool operator> (const Set& rhv) const;
    bool operator>=(const Set& rhv) const;

    std::pair<iterator, bool> insert(const value_type& value);
    iterator  insert(iterator pos, const value_type& value);
    template <class InputIterator>
    void      insert(InputIterator first, InputIterator last);
    void      erase(iterator pos);                /////////////////
    size_type erase(const key_type& key);        ////////////////
    void      erase(iterator first, iterator last);       ////////////////
    iterator  find(const key_type& key)        const;
    size_type count(const key_type& key)       const;
    iterator  lower_bound(const key_type& key) const;
    iterator  upper_bound(const key_type& key) const;
    std::pair<iterator, iterator> equal_range(const key_type& key) const;

private:
    void copyHelper();   ///////////////

    void clearNode(Node* ptr);
    void goUp(iterator& it, const value_type& x);


    Node* getLeftMost(Node* ptr)  const;
    Node* getRightMost(Node* ptr) const;
    bool goDownAndInsert(iterator& it, const value_type& x);
    std::pair<typename Set<Data>::iterator, bool>
    insertHelper(iterator it, const value_type& x);


private:
    Node* root_;
};

#include "../sources/Set.cpp"

#endif // __SET_HPP__


