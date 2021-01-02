#include <memory>
#include <iostream>
#include <stdlib.h>
#include "allocator.hpp"

template <typename T, typename ALLOCATOR>
class Queue{
private:
    struct Node{
        using allocator_type = typename ALLOCATOR::template rebind<Node>::other;

        T value;
        std::shared_ptr<Node> next;

        Node(){
            next = nullptr;
        }

        Node(const T value){
            this->value = value;
            next = nullptr;
        }


        Node &operator=(const Node &op){
            value = op.value;
            next = std::move(op.next);
            return *this;
        }

        bool operator!=(const Node &op){
            return &value != &op.value;
        }

        static allocator_type& get_allocator(){
            static allocator_type allocator;
            return allocator;
        }

        void* operator new(size_t size){
            return get_allocator().allocate();
        }

        void operator delete(void *pointer){
            get_allocator().destroy((Node*)pointer);
            get_allocator().deallocate((Node*)pointer);
        }
    };

    size_t size = 0;
    std::shared_ptr<Node> head, tail;

public:
    class iterator{
    private:
        Node* iter;

    public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = T &;
        using pointer = T*;
        using iterator_category = std::forward_iterator_tag;

        iterator(){
            iter = nullptr;
        }

        iterator(Node* iter){
            this->iter = iter;
        }

        iterator &operator++(){
            if (iter != nullptr){
                iter = iter->next.get();
            }
            else{
                iter = nullptr;
            }
            return *this;
        }

        reference operator*(){
            return iter->value;
        }

        pointer operator->(){
            return &(iter->value);
        }

        iterator& operator=(const iterator &op){
            iter = op.iter;
        }

        bool operator!=(const iterator &op){
            return iter != op.iter;
        }

        bool operator!=(const iterator &&op){
            return iter = op.iter;
        }

        bool operator==(const iterator &op){
            return iter == op.iter;
        }

        bool operator==(const iterator &&op){
            return iter == op.iter;
        }
    };

    Queue(){
        head = nullptr;
        tail = nullptr;
    }

    ~Queue(){}

    int Size() const {
        return size;
    }

    iterator Begin() const {
        return head.get();
    }

    iterator End() const {
        return tail->next.get();
    }

    T Top() const {
        if (head != nullptr){
            return head->value;
        }
        throw std::runtime_error("Queue is empty");
    }

    void Pop(){
        if (head != nullptr){
            head = head->next;
            size--;
        }
        else{
            throw std::runtime_error("Queue is empty");
        }
    }

    void Push(const T& val){
        Node* new_node = new Node(val);
        std::shared_ptr<Node> pointer(new_node);
        if (size == 0){
            tail = pointer;
            head = tail;
        }
        else if (size == 1){
            head->next = tail;
            tail->next = pointer;
            tail = pointer;
        }
        else{
            tail->next = pointer;
            tail = pointer;
        }
        size++;
    }

    void Erase(iterator &it){
        if(it == nullptr){
            throw std::runtime_error("nullptr");
        }
        for(iterator iter = it; iter != End(); ++iter){
            iterator i = iter;
            *iter = *(i++);
        }
        Pop();
    }
};
