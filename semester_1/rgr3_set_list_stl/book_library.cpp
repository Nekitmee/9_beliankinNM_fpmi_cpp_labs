#include <iostream>
#include <list>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>

struct Author {
    std::string surname;
    std::string name;
    std::string patronymic;

    Author(const std::string& s, const std::string& n, const std::string& p)
        : surname(s), name(n), patronymic(p) {
    }

    bool operator<(const Author& other) const {
        return surname < other.surname;
    }

    bool operator==(const Author& other) const {
        return surname == other.surname &&
            name == other.name &&
            patronymic == other.patronymic;
    }

    std::string full_name() const {
        return surname + " " + name + " " + patronymic;
    }
};

struct Book {
    int udc_number;
    std::string title;
    int year;
    std::set<Author> authors;

    bool operator<(const Book& other) const {
        return title < other.title;
    }

    void print() const {
        std::cout << "УДК: " << udc_number << std::endl;
        std::cout << "Название: " << title << std::endl;
        std::cout << "Год издания: " << year << std::endl;
        std::cout << "Авторы: ";
        for (const auto& author : authors) {
            std::cout << author.full_name() << "; ";
        }
        std::cout << std::endl << std::endl;
    }
};

class Library {
private:
    std::list<Book> books;

public:
    void add_book(const Book& book) {
        auto it = std::lower_bound(books.begin(), books.end(), book);
        books.insert(it, book);
    }

    bool remove_book(const std::string& title) {
        auto it = std::find_if(books.begin(), books.end(),
            [&title](const Book& b) { return b.title == title; });

        if (it != books.end()) {
            books.erase(it);
            return true;
        }
        return false;
    }

    std::list<Book> find_by_title(const std::string& title) const {
        std::list<Book> result;
        for (const auto& book : books) {
            if (book.title.find(title) != std::string::npos) {
                result.push_back(book);
            }
        }
        return result;
    }

    std::list<Book> find_by_author(const std::string& surname) const {
        std::list<Book> result;
        for (const auto& book : books) {
            for (const auto& author : book.authors) {
                if (author.surname == surname) {
                    result.push_back(book);
                    break;
                }
            }
        }
        return result;
    }

    bool add_author_to_book(const std::string& title, const Author& author) {
        auto it = std::find_if(books.begin(), books.end(),
            [&title](const Book& b) { return b.title == title; });

        if (it != books.end()) {
            it->authors.insert(author);
            return true;
        }
        return false;
    }

    bool remove_author_from_book(const std::string& title, const Author& author) {
        auto it = std::find_if(books.begin(), books.end(),
            [&title](const Book& b) { return b.title == title; });

        if (it != books.end()) {
            auto author_it = it->authors.find(author);
            if (author_it != it->authors.end()) {
                it->authors.erase(author_it);
                return true;
            }
        }
        return false;
    }

    void load_from_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            Book book;
            std::string authors_str;

            ss >> book.udc_number;
            ss.ignore();
            std::getline(ss, book.title, ';');
            std::getline(ss, authors_str, ';');
            ss >> book.year;

            std::stringstream authors_ss(authors_str);
            std::string author_info;
            while (std::getline(authors_ss, author_info, ',')) {
                std::stringstream author_ss(author_info);
                std::string surname, name, patronymic;
                author_ss >> surname >> name >> patronymic;
                book.authors.insert(Author(surname, name, patronymic));
            }

            add_book(book);
        }

        file.close();
        std::cout << "Данные загружены из файла " << filename << std::endl;
    }

    void save_to_file(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл " << filename << std::endl;
            return;
        }

        for (const auto& book : books) {
            file << book.udc_number << " " << book.title << ";";

            bool first = true;
            for (const auto& author : book.authors) {
                if (!first) file << ",";
                file << author.surname << " " << author.name << " " << author.patronymic;
                first = false;
            }

            file << ";" << book.year << std::endl;
        }

        file.close();
        std::cout << "Данные сохранены в файл " << filename << std::endl;
    }

    void print_all() const {
        std::cout << "\n=== КАТАЛОГ БИБЛИОТЕКИ ===\n";
        for (const auto& book : books) {
            book.print();
        }
        std::cout << "Всего книг: " << books.size() << std::endl;
    }
};

void print_menu() {
    std::cout << "\n=== МЕНЮ БИБЛИОТЕКИ ===\n";
    std::cout << "1. Показать все книги\n";
    std::cout << "2. Добавить книгу\n";
    std::cout << "3. Удалить книгу\n";
    std::cout << "4. Найти книгу по названию\n";
    std::cout << "5. Найти книги по автору\n";
    std::cout << "6. Добавить автора к книге\n";
    std::cout << "7. Удалить автора из книги\n";
    std::cout << "8. Загрузить из файла\n";
    std::cout << "9. Сохранить в файл\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

int main() {
    Library library;
    int choice;

    do {
        print_menu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: {
            library.print_all();
            break;
        }
        case 2: {
            Book book;
            std::cout << "Введите номер УДК: ";
            std::cin >> book.udc_number;
            std::cin.ignore();

            std::cout << "Введите название книги: ";
            std::getline(std::cin, book.title);

            std::cout << "Введите год издания: ";
            std::cin >> book.year;
            std::cin.ignore();

            int author_count;
            std::cout << "Сколько авторов у книги? ";
            std::cin >> author_count;
            std::cin.ignore();

            for (int i = 0; i < author_count; ++i) {
                std::string surname, name, patronymic;
                std::cout << "Автор " << i + 1 << ":\n";
                std::cout << "Фамилия: ";
                std::getline(std::cin, surname);
                std::cout << "Имя: ";
                std::getline(std::cin, name);
                std::cout << "Отчество: ";
                std::getline(std::cin, patronymic);

                book.authors.insert(Author(surname, name, patronymic));
            }

            library.add_book(book);
            std::cout << "Книга добавлена успешно!\n";
            break;
        }
        case 3: {
            std::string title;
            std::cout << "Введите название книги для удаления: ";
            std::getline(std::cin, title);

            if (library.remove_book(title)) {
                std::cout << "Книга удалена успешно!\n";
            }
            else {
                std::cout << "Книга не найдена!\n";
            }
            break;
        }
        case 4: {
            std::string title;
            std::cout << "Введите название (или часть названия) для поиска: ";
            std::getline(std::cin, title);

            auto result = library.find_by_title(title);
            if (result.empty()) {
                std::cout << "Книги не найдены!\n";
            }
            else {
                std::cout << "\nНайдено " << result.size() << " книг:\n";
                for (const auto& book : result) {
                    book.print();
                }
            }
            break;
        }
        case 5: {
            std::string surname;
            std::cout << "Введите фамилию автора: ";
            std::getline(std::cin, surname);

            auto result = library.find_by_author(surname);
            if (result.empty()) {
                std::cout << "Книги не найдены!\n";
            }
            else {
                std::cout << "\nНайдено " << result.size() << " книг:\n";
                for (const auto& book : result) {
                    book.print();
                }
            }
            break;
        }
        case 6: {
            std::string title;
            std::cout << "Введите название книги: ";
            std::getline(std::cin, title);

            std::string surname, name, patronymic;
            std::cout << "Фамилия нового автора: ";
            std::getline(std::cin, surname);
            std::cout << "Имя: ";
            std::getline(std::cin, name);
            std::cout << "Отчество: ";
            std::getline(std::cin, patronymic);

            if (library.add_author_to_book(title, Author(surname, name, patronymic))) {
                std::cout << "Автор добавлен успешно!\n";
            }
            else {
                std::cout << "Книга не найдена!\n";
            }
            break;
        }
        case 7: {
            std::string title;
            std::cout << "Введите название книги: ";
            std::getline(std::cin, title);

            std::string surname, name, patronymic;
            std::cout << "Фамилия автора для удаления: ";
            std::getline(std::cin, surname);
            std::cout << "Имя: ";
            std::getline(std::cin, name);
            std::cout << "Отчество: ";
            std::getline(std::cin, patronymic);

            if (library.remove_author_from_book(title, Author(surname, name, patronymic))) {
                std::cout << "Автор удален успешно!\n";
            }
            else {
                std::cout << "Книга или автор не найдены!\n";
            }
            break;
        }
        case 8: {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::getline(std::cin, filename);
            library.load_from_file(filename);
            break;
        }
        case 9: {
            std::string filename;
            std::cout << "Введите имя файла: ";
            std::getline(std::cin, filename);
            library.save_to_file(filename);
            break;
        }
        case 0: {
            std::cout << "Выход из программы\n";
            break;
        }
        default: {
            std::cout << "Неверный выбор!\n";
            break;
        }
        }
    } while (choice != 0);

    return 0;
}