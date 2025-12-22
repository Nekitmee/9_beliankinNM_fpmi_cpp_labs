#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>

enum TrainType {
    PASSENGER,
    FREIGHT,
    HIGH_SPEED
};

class Train {
private:
    int id_;
    TrainType type_;
    std::string destination_;
    int dispatch_hour_;
    int dispatch_minute_;
    int travel_hours_;
    int travel_minutes_;

public:
    Train() : id_(0), type_(PASSENGER), dispatch_hour_(0), dispatch_minute_(0),
        travel_hours_(0), travel_minutes_(0) {
    }

    Train(int id, TrainType type, const std::string& dest,
        int d_hour, int d_min, int t_hours, int t_min)
        : id_(id), type_(type), destination_(dest),
        dispatch_hour_(d_hour), dispatch_minute_(d_min),
        travel_hours_(t_hours), travel_minutes_(t_min) {
    }

    int getId() const { return id_; }
    TrainType getType() const { return type_; }
    std::string getDestination() const { return destination_; }
    int getDispatchHour() const { return dispatch_hour_; }
    int getDispatchMinute() const { return dispatch_minute_; }
    int getTravelHours() const { return travel_hours_; }
    int getTravelMinutes() const { return travel_minutes_; }

    int getTotalDispatchMinutes() const {
        return dispatch_hour_ * 60 + dispatch_minute_;
    }

    int getTotalTravelMinutes() const {
        return travel_hours_ * 60 + travel_minutes_;
    }

    int getArrivalMinutes() const {
        return getTotalDispatchMinutes() + getTotalTravelMinutes();
    }

    std::string getDispatchTime() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << dispatch_hour_ << ":"
            << std::setw(2) << std::setfill('0') << dispatch_minute_;
        return oss.str();
    }

    std::string getTravelTime() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << travel_hours_ << ":"
            << std::setw(2) << std::setfill('0') << travel_minutes_;
        return oss.str();
    }

    std::string getArrivalTime() const {
        int total_minutes = getArrivalMinutes();
        int hours = total_minutes / 60 % 24;
        int minutes = total_minutes % 60;
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes;
        return oss.str();
    }

    static TrainType stringToType(const std::string& type_str) {
        if (type_str == "PASSENGER") return PASSENGER;
        if (type_str == "FREIGHT") return FREIGHT;
        if (type_str == "HIGH_SPEED") return HIGH_SPEED;
        return PASSENGER;
    }

    static std::string typeToString(TrainType type) {
        switch (type) {
        case PASSENGER: return "ПАССАЖИРСКИЙ";
        case FREIGHT: return "ГРУЗОВОЙ";
        case HIGH_SPEED: return "СКОРОСТНОЙ";
        default: return "НЕИЗВЕСТЕН";
        }
    }

    void print() const {
        std::cout << "Поезд #" << id_
            << " Тип: " << typeToString(type_)
            << " Назначение: " << destination_
            << " Отправление: " << getDispatchTime()
            << " Время в пути: " << getTravelTime()
            << " Прибытие: " << getArrivalTime()
            << " (в пути минут: " << getTotalTravelMinutes() << ")"
            << std::endl;
    }

    bool operator<(const Train& other) const {
        return getTotalDispatchMinutes() < other.getTotalDispatchMinutes();
    }
};

void part2() {
    std::cout << "\n=== Часть 1.2: Работа с вектором Train ===" << std::endl;

    try {
        std::vector<Train> trains;
        std::string filename;

        std::cout << "Введите имя файла с данными (например: trains.txt): ";
        std::cin >> filename;

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw "Не удалось открыть файл!";
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            int id, dispatch_h, dispatch_m, travel_h, travel_m;
            std::string type_str, destination;

            if (!(iss >> id >> type_str >> destination >> dispatch_h >> dispatch_m >> travel_h >> travel_m)) {
                throw "Ошибка формата данных в файле!";
            }

            TrainType type = Train::stringToType(type_str);
            trains.emplace_back(id, type, destination, dispatch_h, dispatch_m, travel_h, travel_m);
        }
        file.close();

        if (trains.empty()) {
            throw "Файл пуст или данные не загружены!";
        }

        std::cout << "\nЗагружено " << trains.size() << " поездов." << std::endl;

        std::sort(trains.begin(), trains.end());
        std::cout << "\n1. Поезда отсортированы по времени отправления:" << std::endl;
        for (const auto& train : trains) {
            train.print();
        }

        int start_h, start_m, end_h, end_m;
        std::cout << "\n2. Введите диапазон времени для поиска поездов:" << std::endl;
        std::cout << "Начало (ЧЧ ММ): ";
        if (!(std::cin >> start_h >> start_m)) throw "Ошибка ввода времени!";
        std::cout << "Конец (ЧЧ ММ): ";
        if (!(std::cin >> end_h >> end_m)) throw "Ошибка ввода времени!";

        int start_minutes = start_h * 60 + start_m;
        int end_minutes = end_h * 60 + end_m;

        std::cout << "\nПоезда в диапазоне времени "
            << std::setw(2) << std::setfill('0') << start_h << ":"
            << std::setw(2) << std::setfill('0') << start_m << " - "
            << std::setw(2) << std::setfill('0') << end_h << ":"
            << std::setw(2) << std::setfill('0') << end_m << ":" << std::endl;

        bool found = false;
        for (const auto& train : trains) {
            int dispatch_minutes = train.getTotalDispatchMinutes();
            if (dispatch_minutes >= start_minutes && dispatch_minutes <= end_minutes) {
                train.print();
                found = true;
            }
        }
        if (!found) std::cout << "Поездов в заданном диапазоне не найдено." << std::endl;

        std::cin.ignore();
        std::string target_destination;
        std::cout << "\n3. Введите пункт назначения для поиска: ";
        std::getline(std::cin, target_destination);

        std::cout << "\nПоезда, следующие в " << target_destination << ":" << std::endl;
        found = false;
        for (const auto& train : trains) {
            if (train.getDestination() == target_destination) {
                train.print();
                found = true;
            }
        }
        if (!found) std::cout << "Поездов в указанный пункт назначения не найдено." << std::endl;

        std::string target_type_str;
        std::cout << "\n4. Введите тип поезда (PASSENGER, FREIGHT, HIGH_SPEED): ";
        std::cin >> target_type_str;

        TrainType target_type = Train::stringToType(target_type_str);
        std::cout << "\nПоезда типа " << Train::typeToString(target_type)
            << ", следующие в " << target_destination << ":" << std::endl;

        found = false;
        for (const auto& train : trains) {
            if (train.getType() == target_type && train.getDestination() == target_destination) {
                train.print();
                found = true;
            }
        }
        if (!found) std::cout << "Поездов с заданными параметрами не найдено." << std::endl;

        std::cout << "\n5. Самый быстрый поезд в " << target_destination << ":" << std::endl;
        int min_travel_time = 1000000;
        Train fastest_train;
        found = false;

        for (const auto& train : trains) {
            if (train.getDestination() == target_destination) {
                int travel_time = train.getTotalTravelMinutes();
                if (travel_time < min_travel_time) {
                    min_travel_time = travel_time;
                    fastest_train = train;
                    found = true;
                }
            }
        }

        if (found) {
            fastest_train.print();
            std::cout << "Время в пути: " << min_travel_time << " минут" << std::endl;
        }
        else {
            std::cout << "Поездов в указанный пункт назначения не найдено." << std::endl;
        }

    }
    catch (const char* error_msg) {
        std::cout << "Ошибка: " << error_msg << std::endl;
    }
}

int main() {
    part1();
    part2();
    return 0;
}   