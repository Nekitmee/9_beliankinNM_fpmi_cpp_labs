#include "forward_list_impl.h"

#include <iostream>
#include <algorithm>
#include <memory>

ForwardList::ForwardList() : head_(nullptr), size_(0) {
}

ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr), size_(0) {
    if (rhs.head_ == nullptr) {
        return;
    }

    Node* current = rhs.head_;
    Node* prev_copy = nullptr;
    Node* new_head = nullptr;

    while (current != nullptr) {
        Node* new_node = new Node(current->value_);

        if (prev_copy == nullptr) {
            new_head = new_node;
        }
        else {
            prev_copy->next_ = new_node;
        }

        prev_copy = new_node;
        current = current->next_;
        size_++;
    }

    head_ = new_head;
}

ForwardList::ForwardList(size_t count, int32_t value) : head_(nullptr), size_(0) {
    for (size_t i = 0; i < count; ++i) {
        PushFront(value);
    }
}

ForwardList::ForwardList(std::initializer_list<int32_t> init) : head_(nullptr), size_(0) {
    for (auto it = init.begin(); it != init.end(); ++it) {
        PushFront(*it);
    }

    if (head_ != nullptr && head_->next_ != nullptr) {
        Node* prev = nullptr;
        Node* current = head_;
        Node* next = nullptr;

        while (current != nullptr) {
            next = current->next_;
            current->next_ = prev;
            prev = current;
            current = next;
        }

        head_ = prev;
    }
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) {
        return *this;
    }

    Clear();

    if (rhs.head_ != nullptr) {
        Node* current = rhs.head_;
        Node* prev_copy = nullptr;
        Node* new_head = nullptr;

        while (current != nullptr) {
            Node* new_node = new Node(current->value_);

            if (prev_copy == nullptr) {
                new_head = new_node;
            }
            else {
                prev_copy->next_ = new_node;
            }

            prev_copy = new_node;
            current = current->next_;
        }

        head_ = new_head;
        size_ = rhs.size_;
    }

    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

void ForwardList::PushFront(int32_t value) {
    Node* new_node = new Node(value);
    new_node->next_ = head_;
    head_ = new_node;
    size_++;
}

void ForwardList::PopFront() {
    if (head_ == nullptr) {
        return;
    }

    Node* to_delete = head_;
    head_ = head_->next_;
    delete to_delete;
    size_--;
}

void ForwardList::Remove(int32_t value) {
    if (head_ == nullptr) {
        return;
    }

    while (head_ != nullptr && head_->value_ == value) {
        Node* to_delete = head_;
        head_ = head_->next_;
        delete to_delete;
        size_--;
    }

    if (head_ == nullptr) {
        return;
    }

    Node* current = head_;
    while (current->next_ != nullptr) {
        if (current->next_->value_ == value) {
            Node* to_delete = current->next_;
            current->next_ = current->next_->next_;
            delete to_delete;
            size_--;
        }
        else {
            current = current->next_;
        }
    }
}

void ForwardList::Clear() {
    while (head_ != nullptr) {
        Node* to_delete = head_;
        head_ = head_->next_;
        delete to_delete;
    }
    size_ = 0;
}

bool ForwardList::FindByValue(int32_t value) {
    Node* current = head_;
    while (current != nullptr) {
        if (current->value_ == value) {
            return true;
        }
        current = current->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) {
    Node* current = head_;
    bool first = true;

    while (current != nullptr) {
        if (!first) {
            out << " ";
        }
        out << current->value_;
        first = false;
        current = current->next_;
    }
}

int32_t ForwardList::Front() const {
    if (head_ == nullptr) {
        return 0;
    }
    return head_->value_;
}

size_t ForwardList::Size() const {
    return size_;
}