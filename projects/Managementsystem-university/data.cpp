#include <iostream>
#include <fstream>
#include <unistd.h>  // For usleep()
using namespace std;

class University {
private:
    string RollNo, Name, Stream, Address;

public:
    University() : RollNo(""), Name(""), Stream(""), Address("") {}

    void setRollNo(string rollNo) {
        RollNo = rollNo;
    }

    void setName(string name) {
        Name = name;
    }

    void setStream(string stream) {
        Stream = stream;
    }

    void setAddress(string address) {
        Address = address;
    }

    string getRollNo() {
        return RollNo;
    }

    string getName() {
        return Name;
    }

    string getStream() {
        return Stream;
    }

    string getAddress() {
        return Address;
    }
};

void add(University student) {
    string rollNo, name, stream, address;

    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;
    student.setRollNo(rollNo);

    cout << "\tEnter Name Of Student: ";
    cin >> name;
    student.setName(name);

    cout << "\tEnter Stream Of Student: ";
    cin >> stream;
    student.setStream(stream);

    cout << "\tEnter Address Of Student: ";
    cin >> address;
    student.setAddress(address);

    ofstream out("university.txt", ios::app);
    if (!out) {
        cout << "\tError: File Can't Open!" << endl;
    } else {
        out << "\t" << student.getRollNo() << " : " << student.getName() << " : " << student.getStream()
            << " : " << student.getAddress() << endl << endl;
    }
    out.close();
    cout << "\tStudent Added Successfully!" << endl;
}

void search() {
    string rollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;

    ifstream in("university.txt");
    if (!in) {
        cout << "\tError: File Can't Open!" << endl;
    }
    string line;
    bool found = false;
    while (getline(in, line)) {
        int data = line.find(rollNo);
        if (data != string::npos) {
            cout << "\t" << line << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "\tStudent Not Found!" << endl;
    }
    in.close();
}

void update(University student) {
    string rollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;

    ifstream infile("university.txt");
    ofstream outfile("university_temp.txt");
    if (!infile || !outfile) {
        cout << "\tError: File Can't Open!" << endl;
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        int pos = line.find(rollNo);
        if (pos != string::npos) {
            string address;
            cout << "\tEnter New Address: ";
            cin >> address;
            student.setAddress(address);

            int newPos = line.find_last_of(':');
            line.replace(newPos + 2, string::npos, student.getAddress());
            found = true;
        }
        outfile << line << endl;
    }
    if (!found) {
        cout << "\tStudent Not Found!" << endl;
    }
    outfile.close();
    infile.close();
    remove("university.txt");
    rename("university_temp.txt", "university.txt");
    cout << "\tData Updated!" << endl;
}

int main() {
    University student;

    bool exit = false;
    while (!exit) {
        system("clear");  // Clear screen on macOS
        int val;
        cout << "\tWelcome To University Management System" << endl;
        cout << "\t***************************************" << endl;
        cout << "\t1. Add Student." << endl;
        cout << "\t2. Search Student." << endl;
        cout << "\t3. Update Data Of Student." << endl;
        cout << "\t4. Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> val;

        if (val == 1) {
            system("clear");
            add(student);
            usleep(6000000);  // Sleep for 6 seconds
        } else if (val == 2) {
            system("clear");
            search();
            usleep(6000000);  // Sleep for 6 seconds
        } else if (val == 3) {
            system("clear");
            update(student);
            usleep(6000000);  // Sleep for 6 seconds
        } else if (val == 4) {
            system("clear");
            exit = true;
            cout << "\tGood Luck!" << endl;
            usleep(3000000);  // Sleep for 3 seconds
        }
    }
}

