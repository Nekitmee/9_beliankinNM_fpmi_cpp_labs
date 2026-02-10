#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

struct Mark {
    std::string subject_; // предмет
    size_t mark_; // оценка 

    Mark(const std::string& subject, size_t mark) : subject_(subject), mark_(mark) {} // конструктор с инициальзиацией переменных
};

struct StudentData {
    std::string name_; // фамилия, инициалы
    size_t number_; // номер зачетки
    std::vector<Mark> marks_; // результаты сессии

    // константный метод average вычисляет средний балл
    double average() const {
        if (marks_.empty())
        {
            return 0;
        }
        double sum = 0;
        for (const auto& m : marks_) sum += m.mark_;
        return sum / marks_.size();
    }
};

class StudentManager {
private:
    std::map<size_t, StudentData> students_;

public:
    // чтение файла
    void ReadFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) { // проверка на открытие
            throw "Не удалось открыть файл\n";
        }

        std::string name; // имя, инициалы
        size_t number; // номер зачетки
        size_t markCount; // количество оценок
        while (file >> name >> number >> markCount) { // чтение до пробела/переноса
            StudentData student{ name, number, {} }; // создание обьекта студента
            for (size_t i = 0; i < markCount; ++i) { // запись прдметов и оценок
                std::string subject;
                size_t mark;
                file >> subject >> mark;
                student.marks_.emplace_back(subject, mark); // создаёт объект сразу в векторе
            }
            students_[number] = student; // сохранение в map
        }
    }

    // вызов студентов, отсортированных по зачетке
    void printSortedByNumber() {
        for (const auto& [num, data] : students_) {
            std::cout << num << " " << data.name_ << " ср.балл: " << data.average() << "\n";
        }
    }

    // вывод списка всех студентов в алфавитном порядке
    void printAllAlphabetical() {

        std::vector<std::pair<StudentData, size_t>> list;

        // копируем данные из map в вектор
        for (const auto& [num, data] : students_) {
            list.emplace_back(data, num);
        }

        std::sort(list.begin(), list.end(), [](const auto& a, const auto& b) {
            // если фамилии разные - сортируем по алфавиту
            if (a.first.name_ != b.first.name_)
                return a.first.name_ < b.first.name_;

            // если фамилии одинаковые - сортируем по убыванию среднего балла
            return a.first.average() > b.first.average();
            });

        size_t index = 1;
        // вывод списка
        for (const auto& [data, num] : list) {
            std::cout << index++ << ". " << data.name_ << " " << num
                << " " << data.average() << "\n";
        }
    }

    // вывод студентов, чей средний балл попадает в заданный диапазон
    void printByAverageRange(double min, double max) {

        std::vector<std::pair<StudentData, size_t>> filtered;

        for (const auto& [num, data] : students_) {
            // вычисляем средний балл текущего студента
            double avg = data.average();

            // проверяем диапазон
            if (avg >= min && avg <= max) {
                filtered.emplace_back(data, num);
            }
        }

        // сортируем отфильтрованных студентов по убыванию среднего балла
        std::sort(filtered.begin(), filtered.end(), [](const auto& a, const auto& b) {
            return a.first.average() > b.first.average();
            });

        // выводим список
        for (const auto& [data, num] : filtered) {
            std::cout << data.name_ << " " << num << " " << data.average() << "\n";
        }
    }

    // вывод всех студентов, которые сдавали заданный предмет
    void printBySubject(const std::string& subject) {

        for (const auto& [num, data] : students_) {

            for (const auto& mark : data.marks_) {

                if (mark.subject_ == subject) {
                    std::cout << data.name_ << " " << num << " " << mark.mark_ << "\n";
                    break;
                }
            }
        }
    }

    // подсчет и вывод статистики по каждому предмету
    void printSubjectStats() {
        std::map<std::string, std::pair<size_t, double>> subjectStats;

        // проходим по всем студентам и их оценкам
        for (const auto& [num, data] : students_) {
            for (const auto& mark : data.marks_) {
                // получаем ссылку на статистику для текущего предмета
                // если предмета еще нет в map, он автоматически создается
                auto& stats = subjectStats[mark.subject_];
                stats.first++;          // увеличиваем счетчик студентов
                stats.second += mark.mark_; // добавляем оценку к общей сумме
            }
        }

        // вектор для сортировки предметов по среднему баллу
        std::vector<std::pair<std::string, double>> averages;

        for (const auto& [subject, stats] : subjectStats) {
            averages.emplace_back(subject, stats.second / stats.first);
        }

        // сортируем предметы по убыванию среднего балла
        std::sort(averages.begin(), averages.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
            });

        // выводим отсортированную статистику
        for (const auto& [subject, avg] : averages) {
            std::cout << subject << ": " << avg << " ("
                << subjectStats[subject].first << " студентов)\n";
        }
    }

    // поиск и вывод студентов с максимальной суммой баллов
    void printMaxSum() {
        size_t maxSum = 0;

        for (const auto& [num, data] : students_) {
            size_t sum = 0;

            for (const auto& mark : data.marks_)
                sum += mark.mark_;

            if (sum > maxSum)
                maxSum = sum; // обновляем максимум если нашли больше
        }

        // второй проход по всем студентам: находим всех с максимальной суммой
        for (const auto& [num, data] : students_) {
            size_t sum = 0;
            for (const auto& mark : data.marks_)
                sum += mark.mark_;

            if (sum == maxSum)
                std::cout << data.name_ << " " << num << "\n";
        }
    }

    // вывод списка студентов с неудовлетворительными оценками (1, 2, 3)
    void printFailed() {
        for (const auto& [num, data] : students_) {
            // флаг, указывающий на наличие неудовлетворительных оценок
            bool hasFailed = false;

            for (const auto& mark : data.marks_) {
                if (mark.mark_ <= 3) {
                    hasFailed = true;  
                    break;      
                }
            }

            // если у студента есть неудовлетворительные оценки - выводим его
            if (hasFailed)
                std::cout << data.name_ << " " << num << "\n";
        }
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    try {
        StudentManager manager;
        manager.ReadFile("students.txt");

        std::cout << "2-3. Сортировка по номеру:\n";
        manager.printSortedByNumber();

        std::cout << "\n4. Все студенты (алфавит):\n";
        manager.printAllAlphabetical();

        std::cout << "\n5. Средний балл 4.0-5.0:\n";
        manager.printByAverageRange(4.0, 5.0);

        std::cout << "\n6. Сдавали математику:\n";
        manager.printBySubject("математика");

        std::cout << "\n7-8. Статистика по предметам:\n";
        manager.printSubjectStats();

        std::cout << "\n9. Макс сумма баллов:\n";
        manager.printMaxSum();

        std::cout << "\n10. Неудовлетворительные:\n";
        manager.printFailed();

        return 0;
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
        return 0;
    }
}