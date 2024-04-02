#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
#include <algorithm> 
#include <numeric> 

using namespace std;

int nextCarId = 1;
int nextWorkerId = 1;

struct Color {
    string Name;
};

struct Model {
    string BrandName;
    string Name;
};

struct Brand {
    string Name;
};

struct Dealership {
    int DealerId;
    string Address;
    string Name;
    string Logo;
};

struct CarStock {
    int Id;
    string BrandName;
    string Model;
    string Color;
    bool Condition;
    string Vin;
    int DealerId;
    int Year;
    float Mileage;
    float Price;
};

struct CarSales {
    int OrderId;
    int CarId;
    int BuyerId;
    int SellerId;
    int WorkerId;
    string OrderDate;
    string PurchaseDate;
    bool Status;
};

struct Buyer {
    int BuyerId;
    string FirstName;
    string MiddleName;
    string LastName;
};

struct Worker {
    int WorkerId;
    string Position;
    string FirstName;
    string MiddleName;
    string LastName;
    int PlaceInRate;
    int DealerId;
};

struct Position {
    int PositionId;
    string Name;
};

struct CarWorkerAssociation {
    int Id;
    int WorkerId;
    string role; // seller або cleaner
};

void saveDataToFile(const vector<CarStock>& carStocks, const vector<Buyer>& buyers, const vector<Worker>& workers) {
    ofstream masterFile("C:/Users/Admin/source/repos/DB_CarDealeship_Lab1/master_file.txt", ios::trunc);
    if (!masterFile.is_open()) {
        cout << "Unable to open master file" << endl;
        return;
    }

    masterFile << nextCarId << " " << nextWorkerId << endl;

    for (const auto& carStock : carStocks) {
        masterFile << "ID: " << carStock.Id << endl;
        masterFile << "Brand: " << carStock.BrandName << endl;
        masterFile << "Model: " << carStock.Model << endl;
        masterFile << "Color: " << carStock.Color << endl;
        if (carStock.Condition) {
            masterFile << "Condition: New" << endl;
        }
        else {
            masterFile << "Condition: Used" << endl;
            masterFile << "Mileage: " << carStock.Mileage << endl;
        }
        masterFile << "VIN: " << carStock.Vin << endl;
        masterFile << "Dealer ID: " << carStock.DealerId << endl;
        masterFile << "Year: " << carStock.Year << endl;
        masterFile << "Price: " << carStock.Price << endl << endl;
    }

    masterFile.close();

    ofstream workerFile("C:/Users/Admin/source/repos/DB_CarDealeship_Lab1/worker_file.txt", ios::trunc);
    if (!workerFile.is_open()) {
        cout << "Unable to open worker file" << endl;
        return;
    }

    for (const auto& worker : workers) {
        workerFile << "ID: " << worker.WorkerId << endl;
        workerFile << "Position: " << worker.Position << endl;
        workerFile << "First Name: " << worker.FirstName << endl;
        workerFile << "Middle Name: " << worker.MiddleName << endl;
        workerFile << "Last Name: " << worker.LastName << endl;
        workerFile << "Place in Rate: " << worker.PlaceInRate << endl;
        workerFile << "Dealer ID: " << worker.DealerId << endl << endl;
    }

    workerFile.close();
}

void saveDataToWorkerFile(const vector<Worker>& workers) {
    ofstream workerFile("C:/Users/Admin/source/repos/DB_CarDealeship_Lab1/worker_file.txt", ios::trunc);
    if (!workerFile.is_open()) {
        cout << "Unable to open worker file" << endl;
        return;
    }

    for (const auto& worker : workers) {
        workerFile << "ID: " << worker.WorkerId << endl;
        workerFile << "Position: " << worker.Position << endl;
        workerFile << "First Name: " << worker.FirstName << endl;
        workerFile << "Middle Name: " << worker.MiddleName << endl;
        workerFile << "Last Name: " << worker.LastName << endl;
        workerFile << "Place in Rate: " << worker.PlaceInRate << endl;
        workerFile << "Dealer ID: " << worker.DealerId << endl << endl;
    }

    workerFile.close();
}

void clearMasterFile() {
    char confirm;
    cout << "Are you sure you want to clear the master file? Type Y - yes / N - no: ";
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        ofstream file("C:/Users/Admin/source/repos/DB_CarDealeship_Lab1/master_file.txt");
        file.close();
        cout << "Master file cleared." << endl;
    }
    else {
        cout << "Clear operation cancelled." << endl;
    }
}

void clearWorkerFile() {
    char confirm;
    cout << "Are you sure you want to clear the worker file? Type Y - yes / N - no: ";
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
        ofstream file("C:/Users/Admin/source/repos/DB_CarDealeship_Lab1/worker_file.txt");
        file.close();
        cout << "Worker file cleared." << endl;
    }
    else {
        cout << "Clear operation cancelled." << endl;
    }
}

void loadMasterFile(vector<CarStock>& carStocks, vector<Buyer>& buyers, vector<Worker>& workers) {
    ifstream file("C:/Users/Admin/source/repos/DB_CarDealeship_Lab1/master_file.txt");
    if (!file.is_open()) {
        cout << "Unable to open master file" << endl;
        return;
    }

    string line;
    getline(file, line);
    stringstream ss(line);
    ss >> nextCarId >> nextWorkerId;

    while (getline(file, line)) {
        CarStock car;
        if (line.find("ID: ") != string::npos) {
            ss.clear();
            ss.str(line.substr(line.find("ID: ") + 4));
            ss >> car.Id;
            while (getline(file, line) && !line.empty()) {
                if (line.find("Brand: ") != string::npos) {
                    car.BrandName = line.substr(line.find("Brand: ") + 7);
                }
                else if (line.find("Model: ") != string::npos) {
                    car.Model = line.substr(line.find("Model: ") + 7);
                }
                else if (line.find("Color: ") != string::npos) {
                    car.Color = line.substr(line.find("Color: ") + 7);
                }
                else if (line.find("Condition: ") != string::npos) {
                    car.Condition = (line.substr(line.find("Condition: ") + 11) == "New");
                }
                else if (line.find("VIN: ") != string::npos) {
                    car.Vin = line.substr(line.find("VIN: ") + 5);
                }
                else if (line.find("Dealer ID: ") != string::npos) {
                    ss.clear();
                    ss.str(line.substr(line.find("Dealer ID: ") + 11));
                    ss >> car.DealerId;
                }
                else if (line.find("Year: ") != string::npos) {
                    ss.clear();
                    ss.str(line.substr(line.find("Year: ") + 6));
                    ss >> car.Year;
                }
                else if (line.find("Mileage: ") != string::npos) {
                    ss.clear();
                    ss.str(line.substr(line.find("Mileage: ") + 9));
                    ss >> car.Mileage;
                }
                else if (line.find("Price: ") != string::npos) {
                    ss.clear();
                    ss.str(line.substr(line.find("Price: ") + 7));
                    ss >> car.Price;
                }
            }
            carStocks.push_back(car);
        }
        else if (line.find("BuyerId") != string::npos) {
            Buyer buyer;
            ss.clear();
            ss.str(line.substr(line.find("BuyerId: ") + 9));
            ss >> buyer.BuyerId;
            getline(file, line);
            stringstream fullname(line);
            fullname >> buyer.FirstName >> buyer.MiddleName >> buyer.LastName;
            buyers.push_back(buyer);
        }
    }

    file.close();
}

void showStatistics(const vector<CarStock>& carStocks, const vector<Worker>& workers) {
    if (carStocks.empty() && workers.empty()) {
        cout << "No data available for statistics." << endl;
        return;
    }

    cout << "Number of cars in stock: " << carStocks.size() << endl;

    if (!carStocks.empty()) {
        float averagePrice = accumulate(carStocks.begin(), carStocks.end(), 0.0,
            [](float total, const CarStock& car) { return total + car.Price; }) / carStocks.size();
        cout << "Average price of cars: " << fixed << setprecision(2) << averagePrice << endl;

        //найдорожчі та найдешевший авто
        auto maxPriceCar = max_element(carStocks.begin(), carStocks.end(),
            [](const CarStock& car1, const CarStock& car2) { return car1.Price < car2.Price; });
        auto minPriceCar = min_element(carStocks.begin(), carStocks.end(),
            [](const CarStock& car1, const CarStock& car2) { return car1.Price < car2.Price; });
        cout << "Most expensive car: " << maxPriceCar->BrandName << " " << maxPriceCar->Model << " ($" << maxPriceCar->Price << ")" << endl;
        cout << "Cheapest car: " << minPriceCar->BrandName << " " << minPriceCar->Model << " ($" << minPriceCar->Price << ")" << endl;
    }

    cout << "Number of workers: " << workers.size() << endl;
}

void changeCar(vector<CarStock>& carStocks) {
    int id;
    cout << "Enter Car ID to change: ";
    cin >> id;

    auto it = find_if(carStocks.begin(), carStocks.end(), [id](const CarStock& car) { return car.Id == id; });
    if (it != carStocks.end()) {
        CarStock& car = *it;

        cout << "Car found. Here are the car details: " << endl;
        cout << "1. Brand Name: " << car.BrandName << endl;
        cout << "2. Model Name: " << car.Model << endl;
        cout << "3. Color: " << car.Color << endl;
        cout << "4. Condition (1 for New, 0 for Used): " << car.Condition << endl;
        cout << "5. VIN: " << car.Vin << endl;
        cout << "6. Dealer Id: " << car.DealerId << endl;
        cout << "7. Year: " << car.Year << endl;
        cout << "8. Mileage: " << car.Mileage << endl;
        cout << "9. Price: " << car.Price << endl;

        int choice;
        cout << "Enter the number of the field you want to change: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter new Brand Name: ";
            cin >> car.BrandName;
            break;
        case 2:
            cout << "Enter new Model Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, car.Model);
            break;
        case 3:
            cout << "Enter new Color: ";
            getline(cin, car.Color);
            break;
        case 4:
            cout << "Enter new Condition (1 for New, 0 for Used): ";
            cin >> car.Condition;
            break;
        case 5:
            cout << "Enter new VIN (exactly 17 characters): ";
            cin >> car.Vin;
            break;
        case 6:
            cout << "Enter new Dealer Id: ";
            cin >> car.DealerId;
            break;
        case 7:
            cout << "Enter new Year: ";
            cin >> car.Year;
            break;
        case 8:
            cout << "Enter new Mileage: ";
            cin >> car.Mileage;
            break;
        case 9:
            cout << "Enter new Price: ";
            cin >> car.Price;
            break;
        default:
            cout << "Invalid choice. No changes made." << endl;
            return;
        }

        cout << "Car data updated successfully." << endl;
    }
    else {
        cout << "Car with ID " << id << " not found." << endl;
    }
}


void changeWorker(vector<Worker>& workers) {
    int id;
    cout << "Enter Worker ID to change: ";
    cin >> id;

    auto it = find_if(workers.begin(), workers.end(), [id](const Worker& worker) { return worker.WorkerId == id; });
    if (it != workers.end()) {
        Worker& worker = *it;

        cout << "Worker found. Here are the worker details: " << endl;
        cout << "1. Position: " << worker.Position << endl;
        cout << "2. First Name: " << worker.FirstName << endl;
        cout << "3. Middle Name: " << worker.MiddleName << endl;
        cout << "4. Last Name: " << worker.LastName << endl;
        cout << "5. Place in Rate: " << worker.PlaceInRate << endl;
        cout << "6. Dealer ID: " << worker.DealerId << endl;

        int choice;
        cout << "Enter the number of the field you want to change: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter new Position: ";
            cin >> worker.Position;
            break;
        case 2:
            cout << "Enter new First Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, worker.FirstName);
            break;
        case 3:
            cout << "Enter new Middle Name: ";
            getline(cin, worker.MiddleName);
            break;
        case 4:
            cout << "Enter new Last Name: ";
            getline(cin, worker.LastName);
            break;
        case 5:
            cout << "Enter new Place in Rate: ";
            cin >> worker.PlaceInRate;
            break;
        case 6:
            cout << "Enter new Dealer ID: ";
            cin >> worker.DealerId;
            break;
        default:
            cout << "Invalid choice. No changes made." << endl;
            return;
        }

        cout << "Worker data updated successfully." << endl;
    }
    else {
        cout << "Worker with ID " << id << " not found." << endl;
    }
}

void loadWorkersFile(vector<Worker>& workers) {
    ifstream file("C:/Users/Admin/source/repos/DB_CarDealeship_Lab1/worker_file.txt");
    if (!file.is_open()) {
        cout << "Unable to open worker file" << endl;
        return;
    }

    cout << "Loading workers from file..." << endl;

    string line;
    while (getline(file, line)) {
        Worker worker;
        stringstream ss(line);
        string firstName, middleName, lastName;

        if (!(ss >> worker.WorkerId >> worker.Position >> firstName >> middleName >> lastName >> worker.PlaceInRate >> worker.DealerId)) {
            cout << "Error reading worker data. Skipping line." << endl;
            continue;
        }

        worker.FirstName = firstName;
        worker.MiddleName = middleName;
        worker.LastName = lastName;

        cout << "ID: " << worker.WorkerId << endl;
        cout << "Position: " << worker.Position << endl;
        cout << "Name: " << worker.FirstName << " " << worker.MiddleName << " " << worker.LastName << endl;
        cout << "Place in Rate: " << worker.PlaceInRate << endl;
        cout << "Dealer ID: " << worker.DealerId << endl;
        cout << endl;

        workers.push_back(worker);
    }

    file.close();
    cout << "Workers loaded successfully." << endl;
}


CarStock inputCar() {
    CarStock car;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Brand Name: ";
    getline(cin, car.BrandName);
    cout << "Enter Model Name: ";
    getline(cin, car.Model);
    cout << "Enter Color: ";
    getline(cin, car.Color);
    while (true) {
        cout << "Enter Condition (1 for New, 0 for Used): ";
        cin >> car.Condition;
        if (cin.fail() || (car.Condition != 0 && car.Condition != 1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 1 for New or 0 for Used." << endl;
        }
        else {
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter VIN (exactly 17 characters): ";
    getline(cin, car.Vin);
    while (car.Vin.size() != 17) {
        cout << "Please enter exactly 17 characters for VIN: ";
        getline(cin, car.Vin);
    }

    cout << "Enter Dealer Id: ";
    cin >> car.DealerId;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Year: ";
    while (true) {
        cin >> car.Year;
        if (cin.fail() || car.Year < 1900 || car.Year > 2024) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid year (1900-2024)." << endl;
        }
        else {
            break;
        }
    }

    if (car.Condition == 0) {
        cout << "Enter Mileage: ";
        while (true) {
            cin >> car.Mileage;
            if (cin.fail() || car.Mileage < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a positive value for mileage." << endl;
            }
            else {
                break;
            }
        }
    }
    else {
        car.Mileage = 0;
    }

    cout << "Enter Price: ";
    while (true) {
        cin >> car.Price;
        if (cin.fail() || car.Price < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a positive value for price." << endl;
        }
        else {
            break;
        }
    }

    car.Id = nextCarId++;
    return car;
}

Worker inputWorker() {
    Worker worker;
    worker.WorkerId = nextWorkerId++;
    cout << "Enter Position: ";
    cin >> worker.Position;
    cout << "Enter First Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, worker.FirstName);
    cout << "Enter Middle Name: ";
    getline(cin, worker.MiddleName);
    cout << "Enter Last Name: ";
    getline(cin, worker.LastName);
    cout << "Enter Place in Rate: ";
    cin >> worker.PlaceInRate;
    cout << "Enter Dealer Id: ";
    cin >> worker.DealerId;
    return worker;
}

void deleteCarById(vector<CarStock>& carStocks, int id) {
    auto it = find_if(carStocks.begin(), carStocks.end(), [id](const CarStock& car) { return car.Id == id; });
    if (it != carStocks.end()) {
        carStocks.erase(it);
        cout << "Car with ID " << id << " deleted successfully." << endl;
    }
    else {
        cout << "Car with ID " << id << " not found." << endl;
    }
}

void deleteWorkerById(vector<Worker>& workers, int id) {
    auto it = find_if(workers.begin(), workers.end(), [id](const Worker& worker) { return worker.WorkerId == id; });
    if (it != workers.end()) {
        workers.erase(it);
        cout << "Worker with ID " << id << " deleted successfully." << endl;
    }
    else {
        cout << "Worker with ID " << id << " not found." << endl;
    }
}

void displayCarStock(const vector<CarStock>& carStocks) {
    cout << "Car Stock: " << endl;
    for (const auto& car : carStocks) {
        cout << "ID: " << car.Id << endl;
        cout << "Brand: " << car.BrandName << endl;
        cout << "Model: " << car.Model << endl;
        cout << "Color: " << car.Color << endl;
        if (car.Condition) {
            cout << "Condition: New" << endl;
        }
        else {
            cout << "Condition: Used" << endl;
            cout << "Mileage: " << car.Mileage << endl;
        }
        cout << "VIN: " << car.Vin << endl;
        cout << "Dealer ID: " << car.DealerId << endl;
        cout << "Year: " << car.Year << endl;
        cout << "Price: " << car.Price << endl << endl;
    }
}

void displayWorkers(const vector<Worker>& workers) {
    cout << "Workers: " << endl;
    for (const auto& worker : workers) {
        cout << "ID: " << worker.WorkerId << endl;
        cout << "Position: " << worker.Position << endl;
        cout << "First Name: " << worker.FirstName << endl;
        cout << "Middle Name: " << worker.MiddleName << endl;
        cout << "Last Name: " << worker.LastName << endl;
        cout << "Place in Rate: " << worker.PlaceInRate << endl;
        cout << "Dealer ID: " << worker.DealerId << endl << endl;
    }
}

int main() {
    vector<CarStock> carStocks;
    vector<Buyer> buyers;
    vector<Worker> workers;
    vector<CarWorkerAssociation> carWorkerAssociations;
    loadMasterFile(carStocks, buyers, workers);

    int choice;
    do {
        cout << "========== Menu ==========" << endl;
        cout << "1. Add Car" << endl;
        cout << "2. Add Worker" << endl;
        cout << "3. Change Car" << endl;
        cout << "4. Change Worker" << endl;
        cout << "5. Delete Car" << endl;
        cout << "6. Delete Worker" << endl;
        cout << "7. Display Car Stock" << endl;
        cout << "8. Display Workers" << endl;
        cout << "9. Save Data to File" << endl;
        cout << "10. Clear Master File" << endl;
        cout << "11. Clear Worker File" << endl;
        cout << "12. Show Statistics" << endl;
        cout << "13. Exit" << endl;
        cout << "14. Add Worker to Car" << endl;
        cout << "15. Remove Worker from Car" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << endl;
            carStocks.push_back(inputCar());
            break;
        case 2:
            cout << endl;
            workers.push_back(inputWorker());
            break;
        case 3:
            cout << endl;
            changeCar(carStocks);
            break;
        case 4:
            cout << endl;
            changeWorker(workers);
            break;
        case 5:
            cout << endl;
            int deleteCarId;
            cout << "Enter Car ID to delete: ";
            cin >> deleteCarId;
            deleteCarById(carStocks, deleteCarId);
            break;
        case 6:
            cout << endl;
            int deleteWorkerId;
            cout << "Enter Worker ID to delete: ";
            cin >> deleteWorkerId;
            deleteWorkerById(workers, deleteWorkerId);
            break;
        case 7:
            cout << endl;
            displayCarStock(carStocks);
            break;
        case 8:
            cout << endl;
            displayWorkers(workers);
            break;
        case 9:
            cout << endl;
            saveDataToFile(carStocks, buyers, workers);
            break;
        case 10:
            cout << endl;
            clearMasterFile();
            break;
        case 11:
            cout << endl;
            clearWorkerFile();
            break;
        case 12:
            cout << endl;
            showStatistics(carStocks, workers);
            break;
        default:
            cout << endl << "Invalid choice. Please enter a number between 1 and 13." << endl;
        }
        cout << endl;
    } while (choice != 13);

    return 0;
}
