#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Warranty {
private:
    string deviceName;
    string segment;
    string brand;
    string warrantyID;
    string purchaseLocation;
    string purchaseDate;
    string buyerName;
    int coverageYears;

public:
    Warranty() : coverageYears(0) {}

    void inputDetails() {
        cout << "Enter Device Name: ";
        cin.ignore();
        getline(cin, deviceName);

        cout << "Enter Segment (e.g., Phone, AirPods, Laptop): ";
        getline(cin, segment);

        cout << "Enter Brand: ";
        getline(cin, brand);

        cout << "Enter Warranty ID: ";
        getline(cin, warrantyID);

        cout << "Enter Purchase Location: ";
        getline(cin, purchaseLocation);

        cout << "Enter Purchase Date (YYYY-MM-DD): ";
        getline(cin, purchaseDate);

        cout << "Enter Buyer Name: ";
        getline(cin, buyerName);

        cout << "Enter Coverage Period (in years): ";
        cin >> coverageYears;
    }

    string getSegment() const {
        return segment;
    }

    string getDetails() const {
        return "Device: " + deviceName + "\nBrand: " + brand + "\nWarranty ID: " + warrantyID +
               "\nPurchase Location: " + purchaseLocation + "\nPurchase Date: " + purchaseDate +
               "\nBuyer Name: " + buyerName + "\nCoverage Years: " + to_string(coverageYears);
    }
};

class WarrantyManager {
private:
    vector<Warranty> warranties;

    string getUserFileName(const string& user, const string& segment) const {
        return user + "_" + segment + "_warranties.txt";
    }

public:
    void addWarranty(const string& user) {
        Warranty newWarranty;
        newWarranty.inputDetails();
        warranties.push_back(newWarranty);
        saveToFile(user, newWarranty);
    }

    void saveToFile(const string& user, const Warranty& warranty) const {
        string segment = warranty.getSegment();
        ofstream out(getUserFileName(user, segment), ios::app);
        if (out.is_open()) {
            out << warranty.getDetails() << endl;
            out << "---------------------" << endl;
            out.close();
        } else {
            cerr << "Error opening file for user: " << user << ", segment: " << segment << endl;
        }
    }

    void displayWarrantiesBySegment(const string& user) {
        string segment;
        cout << "Enter the Segment Name to Display Warranties: ";
        cin.ignore();
        getline(cin, segment);

        ifstream in(getUserFileName(user, segment));
        if (!in.is_open()) {
            cout << "No warranties found for the segment: " << segment << " under user: " << user << endl;
            return;
        }

        string line;
        cout << "\nWarranties for User: " << user << ", Segment: " << segment << endl;
        cout << "---------------------" << endl;
        while (getline(in, line)) {
            cout << line << endl;
        }
        in.close();
    }
};

int main() {
    WarrantyManager wm;
    bool exit = false;

    while (!exit) {
        int choice;
        string user;
        cout << "\nEnter the User Name : ";
        cin >> user;

        cout << "\nWarranty Management System\n";
        cout << "1. Add Warranty\n";
        cout << "2. Display Warranties by Segment\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                wm.addWarranty(user);
                break;
            case 2:
                wm.displayWarrantiesBySegment(user);
                break;
            case 3:
                exit = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

