#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>

class Vector {
private:
    int* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    //Метод для реаллокации
    void Reallocate(size_t new_capacity) {
        if (new_capacity <= capacity) {
            return;
        }
        int* new_data = new int[new_capacity]();
        if (data) {
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
        }
        data = new_data;
        capacity = new_capacity;
    }

public:

    //Конструктор по умолчанию
    Vector() = default;

    //Конструктор, принимающий размер вектора
    Vector(int size_value) {
        if (size_value < 0) {
            throw std::invalid_argument("Размер массива должен быть неотрицательным.");
        }
        this->size = static_cast<size_t>(size_value);
        this->capacity = size;
        if (this->size > 0) {
            this->data = new int[capacity]();
        }
    }

    //Конструктор, принимающий std::initializer_list<int>
    Vector(std::initializer_list<int> list)
        : size(list.size()), capacity(list.size()) {
        if (size > 0) {
            data = new int[capacity];
            std::copy(list.begin(), list.end(), data);
        }
    }

    //Конструктор копирования
    Vector(const Vector& other)
        : size(other.size), capacity(other.size) {
        if (this->size > 0 && other.data != nullptr) {
            this->data = new int[capacity];
            for (size_t i = 0; i < this->size; i++) {
                this->data[i] = other.data[i];
            }
        }
        else {
            this->data = nullptr;
            this->capacity = 0;
        }
    }

    //Оператор присваивания копированием
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        Vector temp(other);
        Swap(temp);
        return *this;
    }

    //Деструктор
    ~Vector() {
        delete[] data;
    }

    //Метод Swap
    void Swap(Vector& other) {
        std::swap(this->data, other.data);
        std::swap(this->size, other.size);
        std::swap(this->capacity, other.capacity);
    }

    //Операторы индексирования (конст и нет)
    int& operator[](size_t index) {
        return data[index];
    }
    const int& operator[](size_t index) const {
        return data[index];
    }

    //Метод At (конст и не конст)
    int& At(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Индекс вне границ вектора");
        }
        return data[index];
    }
    const int& At(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс вне границ вектора");
        }
        return data[index];
    }

    //Метод Size
    size_t Size() const {
        return size;
    }

    //Метод Capacity
    size_t Capacity() const {
        return capacity;
    }

    //Метод PushBack
    void PushBack(int value) {
        if (size >= capacity) {
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            Reallocate(new_capacity);
        }
        data[size++] = value;
    }

    //Метод PopBack
    void PopBack() {
        if (size > 0) {
            --size;
        }
    }

    //Метод Clear
    void Clear() {
        size = 0;
    }

    //Метод Reserve
    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity) {
            Reallocate(new_capacity);
        }
    }
};

//Оператор вывода
std::ostream& operator<<(std::ostream& os, const Vector& vec) {
    os << "[";
    for (size_t i = 0; i < vec.Size(); ++i) {
        os << vec[i];
        if (i != vec.Size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int main() {
    setlocale(LC_ALL, "Ru");
    try {
        //Ну тут тестики разные были я просто не успел в разные файлы закинуть этот класс
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}