#include <iostream>
#include <cassert>
#include "book_library.cpp"

void test_library() {
    Library library;

    Book book1;
    book1.udc_number = 1001;
    book1.title = "Тестовая книга 1";
    book1.year = 2020;
    book1.authors.insert(Author("Иванов", "Иван", "Иванович"));
    book1.authors.insert(Author("Петров", "Петр", "Петрович"));

    Book book2;
    book2.udc_number = 1002;
    book2.title = "Аннотация к программированию";
    book2.year = 2021;
    book2.authors.insert(Author("Сидоров", "Сидор", "Сидорович"));

    library.add_book(book1);
    library.add_book(book2);

    auto found = library.find_by_title("Тест");
    assert(found.size() == 1);
    assert(found.front().title == "Тестовая книга 1");

    found = library.find_by_author("Иванов");
    assert(found.size() == 1);

    library.add_author_to_book("Тестовая книга 1", Author("Новый", "Автор", "Авторович"));

    found = library.find_by_author("Новый");
    assert(found.size() == 1);

    bool removed = library.remove_book("Аннотация к программированию");
    assert(removed);

    found = library.find_by_title("Аннотация");
    assert(found.empty());

    std::cout << "Все тесты библиотеки пройдены успешно!" << std::endl;
}

int main() {
    test_library();
    return 0;
}