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

public:
    void addWarranty() {
        Warranty newWarranty;
        newWarranty.inputDetails();
        warranties.push_back(newWarranty);
        saveToFile(newWarranty);
    }

    void saveToFile(const Warranty& warranty) const {
        string segment = warranty.getSegment();
        ofstream out(segment + "_warranties.txt", ios::app);
        if (out.is_open()) {
            out << warranty.getDetails() << endl;
            out << "---------------------" << endl;
            out.close();
        } else {
            cerr << "Error opening file for segment: " << segment << endl;
        }
    }

    void displayWarrantiesBySegment() {
        string segment;
        cout << "Enter the Segment Name to Display Warranties: ";
        cin.ignore();
        getline(cin, segment);

        ifstream in(segment + "_warranties.txt");
        if (!in.is_open()) {
            cout << "No warranties found for the segment: " << segment << endl;
            return;
        }

        string line;
        cout << "\nWarranties for Segment: " << segment << endl;
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
        cout << "\nWarranty Management System\n";
        cout << "1. Add Warranty\n";
        cout << "2. Display Warranties by Segment\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                wm.addWarranty();
                break;
            case 2:
                wm.displayWarrantiesBySegment();
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

