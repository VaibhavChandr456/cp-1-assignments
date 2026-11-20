#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    int employeeId;
    string employeeName;
    static int totalEmployees;

public:
    Employee() {
        employeeId = 0;
        employeeName = "Unknown";
        totalEmployees++;
    }

    Employee(int id, string name) {
        employeeId = id;
        employeeName = name;
        totalEmployees++;
    }

    virtual ~Employee() {}

    static int getTotalEmployees() {
        return totalEmployees;
    }

    virtual double calculateSalary() {
        return 0.0;
    }

    virtual void display() {
        cout << "Employee ID   : " << employeeId << "\n";
        cout << "Employee Name : " << employeeName << "\n";
    }
};

int Employee::totalEmployees = 0;

class FullTimeEmployee : public Employee {
private:
    double basicSalary;

public:
    FullTimeEmployee() : Employee() {
        basicSalary = 0.0;
    }

    FullTimeEmployee(int id, string name, double salary) : Employee(id, name) {
        basicSalary = salary;
    }

    double calculateSalary() {
        double hra = 0.20 * basicSalary;
        double da = 0.10 * basicSalary;
        return basicSalary + hra + da;
    }

    void display() {
        Employee::display();
        cout << "Type          : Full-Time\n";
        cout << "Basic Salary  : " << basicSalary << "\n";
        cout << "Total Salary  : " << calculateSalary() << "\n";
    }
};

class PartTimeEmployee : public Employee {
private:
    double hoursWorked;
    double hourlyRate;

public:
    PartTimeEmployee() : Employee() {
        hoursWorked = 0.0;
        hourlyRate = 0.0;
    }

    PartTimeEmployee(int id, string name, double hours, double rate) : Employee(id, name) {
        hoursWorked = hours;
        hourlyRate = rate;
    }

    double calculateSalary() {
        return hoursWorked * hourlyRate;
    }

    void display() {
        Employee::display();
        cout << "Type          : Part-Time\n";
        cout << "Hours Worked  : " << hoursWorked << "\n";
        cout << "Hourly Rate   : " << hourlyRate << "\n";
        cout << "Total Salary  : " << calculateSalary() << "\n";
    }
};

int main() {
    const int MAX = 100;
    Employee *employees[MAX];
    int n;

    cout << "How many employees? ";
    cin >> n;
    while (n < 1 || n > MAX) {
        cout << "Enter a number between 1 and " << MAX << ": ";
        cin >> n;
    }

    for (int i = 0; i < n; i++) {
        int type, id;
        string name;

        cout << "\nEmployee " << i + 1 << "\n";
        cout << "Type (1 - Full-Time, 2 - Part-Time): ";
        cin >> type;
        while (type != 1 && type != 2) {
            cout << "Enter 1 or 2: ";
            cin >> type;
        }

        cout << "Employee ID: ";
        cin >> id;
        cout << "Employee Name: ";
        cin.ignore();
        getline(cin, name);

        if (type == 1) {
            double salary;
            cout << "Basic Salary: ";
            cin >> salary;
            while (salary < 0) {
                cout << "Basic salary cannot be negative. Re-enter: ";
                cin >> salary;
            }
            employees[i] = new FullTimeEmployee(id, name, salary);
        } else {
            double hours, rate;
            cout << "Hours Worked: ";
            cin >> hours;
            while (hours < 0 || hours > 200) {
                cout << "Hours must be between 0 and 200. Re-enter: ";
                cin >> hours;
            }
            cout << "Hourly Rate: ";
            cin >> rate;
            while (rate < 0) {
                cout << "Hourly rate cannot be negative. Re-enter: ";
                cin >> rate;
            }
            employees[i] = new PartTimeEmployee(id, name, hours, rate);
        }
    }

    cout << "\nEmployee Details\n";
    double totalPayroll = 0.0;
    int highest = 0;
    for (int i = 0; i < n; i++) {
        cout << "\n";
        employees[i]->display();
        totalPayroll += employees[i]->calculateSalary();
        if (employees[i]->calculateSalary() > employees[highest]->calculateSalary()) {
            highest = i;
        }
    }

    cout << "\nTotal Payroll: " << totalPayroll << "\n";
    cout << "\nHighest-Paid Employee:\n";
    employees[highest]->display();
    cout << "\nTotal Employees: " << Employee::getTotalEmployees() << "\n";

    for (int i = 0; i < n; i++) {
        delete employees[i];
    }

    return 0;
}
