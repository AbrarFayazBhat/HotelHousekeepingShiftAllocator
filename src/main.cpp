#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
using namespace std;

class Employee
{
private:
    int employeeId = 0;
    string name = "";
    string shift = "";
    int floor = 0;
    static int totalEmployees;
public:
    Employee()
    {
        employeeId = 0;
        name = "";
        shift = "";
        floor = 0;
    }
    Employee(int id, string n, string s, int f)
    {
        employeeId = id;
        name = n;
        shift = s;
        floor = f;
    }
    Employee(const Employee &e)
    {
        employeeId = e.employeeId;
        name = e.name;
        shift = e.shift;
        floor = e.floor;
    }
    bool input()
    {
        cout << "\nEnter Employee ID: ";
        cin >> employeeId;
        cout << "Enter Employee Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Shift (Morning/Evening/Night): ";
        cin >> shift;
        cout << "Enter Floor Number: ";
        cin >> floor;
        return isValid();
    }
    bool isValid() const
    {
        if (employeeId <= 0 || floor <= 0 || name == "" || name.length() >= 50)
            return false;
        if (shift != "Morning" && shift != "Evening" && shift != "Night")
            return false;
        return true;
    }
    void display() const
    {
        cout << "\nEmployee ID   : " << employeeId;
        cout << "\nEmployee Name : " << name;
        cout << "\nShift         : " << shift;
        cout << "\nFloor         : " << floor << endl;
    }
    inline int getEmployeeId() const
    {
        return employeeId;
    }
    void setShift(string shift)
    {
        this->shift = shift;
    }
    void setFloor(int floor)
    {
        this->floor = floor;
    }
    static int getTotalEmployees()
    {
        return totalEmployees;
    }
    static void increaseCount()
    {
        totalEmployees++;
    }
    string getName() const
    {
        return name;
    }
    string getShift() const
    {
        return shift;
    }
    int getFloor() const
    {
        return floor;
    }
    friend void displayEmployeeDetails(const Employee &e)
    {
        cout << "\nEmployee ID   : " << e.employeeId;
        cout << "\nEmployee Name : " << e.name;
        cout << "\nShift         : " << e.shift;
        cout << "\nFloor         : " << e.floor << endl;
    }
    ~Employee()
    {
    }
};

int Employee::totalEmployees = 0;

class EmployeeFile
{
public:
    int employeeId;
    char name[50];
    char shift[50];
    int floor;
};

class ShiftAllocator
{
private:
    Employee employees[100];
    int count = 0;
    Employee *currentEmployee = nullptr;
public:
    int getFileEmployeeCount()
    {
        EmployeeFile record;
        int total = 0;
        ifstream file("employees.dat", ios::binary);
        if (!file)
            return 0;
        while (file.read((char *)&record, sizeof(record)))
            total++;
        file.close();
        return total;
    }
    bool saveEmployee(EmployeeFile record)
    {
        ofstream file("employees.dat", ios::binary | ios::app);
        if (!file)
        {
            cout << "\nUnable to open file!\n";
            return false;
        }
        file.write((char *)&record, sizeof(record));
        file.close();
        return true;
    }
    void addEmployee()
    {
        if (getFileEmployeeCount() >= 100 || count >= 100)
        {
            cout << "\nEmployee list is full!\n";
            return;
        }
        Employee newEmployee;
        cout << "\n----- Add Employee -----\n";
        if (newEmployee.input() == false)
        {
            cout << "\nInvalid employee details!\n";
            return;
        }
        if (isDuplicate(newEmployee.getEmployeeId()))
        {
            cout << "\nEmployee ID already exists!\n";
            return;
        }
        EmployeeFile record{};
        record.employeeId = newEmployee.getEmployeeId();
        strcpy(record.name, newEmployee.getName().c_str());
        strcpy(record.shift, newEmployee.getShift().c_str());
        record.floor = newEmployee.getFloor();
        if (saveEmployee(record))
        {
            employees[count] = newEmployee;
            currentEmployee = &employees[count];
            count++;
            Employee::increaseCount();
            cout << "\nEmployee added successfully!\n";
        }
    }
    void viewEmployeesFromFile()
    {
        EmployeeFile record;
        ifstream file("employees.dat", ios::binary);
        if (!file)
        {
            cout << "\nFile not found!\n";
            return;
        }
        int total = 0;
        cout << "\n----- Employee Records -----\n";
        while (file.read((char *)&record, sizeof(record)))
        {
            cout << "\nEmployee ID   : " << record.employeeId;
            cout << "\nEmployee Name : " << record.name;
            cout << "\nShift         : " << record.shift;
            cout << "\nFloor         : " << record.floor;
            cout << "\n------------------------\n";
            total++;
        }
        if (total == 0)
            cout << "\nNo employee records available!\n";
        file.close();
    }
    void searchEmployee(int id)
    {
        EmployeeFile record;
        bool found = false;
        ifstream file("employees.dat", ios::binary);
        if (!file)
        {
            cout << "\nFile not found!\n";
            return;
        }
        file.seekg(0, ios::beg);
        while (file.read((char *)&record, sizeof(record)))
        {
            if (record.employeeId == id)
            {
                cout << "\nEmployee Found!";
                cout << "\nEmployee ID   : " << record.employeeId;
                cout << "\nEmployee Name : " << record.name;
                cout << "\nShift         : " << record.shift;
                cout << "\nFloor         : " << record.floor;
                found = true;
                break;
            }
        }
        if (found == false)
            cout << "\nEmployee not found!\n";
        file.close();
    }
    void updateEmployee(int id)
    {
        EmployeeFile record;
        int position = 0;
        bool found = false;
        fstream file("employees.dat", ios::in | ios::out | ios::binary);
        if (!file)
        {
            cout << "\nFile not found!\n";
            return;
        }
        while (file.read((char *)&record, sizeof(record)))
        {
            if (record.employeeId == id)
            {
                found = true;
                cout << "\nEmployee Found!";
                cout << "\nName: " << record.name;
                cout << "\nCurrent Shift: " << record.shift;
                cout << "\nCurrent Floor: " << record.floor;
                string newShift;
                int newFloor;
                cout << "\nEnter New Shift: ";
                cin >> newShift;
                cout << "Enter New Floor: ";
                cin >> newFloor;
                if (newShift != "Morning" && newShift != "Evening" && newShift != "Night")
                {
                    cout << "\nInvalid shift!\n";
                    break;
                }
                if (newFloor <= 0)
                {
                    cout << "\nInvalid floor number!\n";
                    break;
                }
                strcpy(record.shift, newShift.c_str());
                record.floor = newFloor;
                file.seekp(position * sizeof(record), ios::beg);
                file.write((char *)&record, sizeof(record));
                cout << "\nEmployee updated successfully!\n";
                break;
            }
            position++;
        }
        if (found == false)
            cout << "\nEmployee not found!\n";
        file.close();
    }
    bool isDuplicate(int id)
    {
        EmployeeFile record;
        ifstream file("employees.dat", ios::binary);
        if (!file)
            return false;
        while (file.read((char *)&record, sizeof(record)))
        {
            if (record.employeeId == id)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    void displayEmployeeCount()
    {
        cout << "\nTotal Employees: " << getFileEmployeeCount() << endl;
    }
};

int main()
{
    ShiftAllocator allocator;
    int choice;
    do
    {
        cout << "\n===== HOTEL HOUSEKEEPING SHIFT ALLOCATOR =====\n";
        cout << "1. Add Employee\n";
        cout << "2. View All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Display Total Employees\n";
        cout << "5. Update Employee\n";
        cout << "6. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            allocator.addEmployee();
            break;
        case 2:
            allocator.viewEmployeesFromFile();
            break;
        case 3:
        {
            int id;
            cout << "\nEnter Employee ID: ";
            cin >> id;
            allocator.searchEmployee(id);
            break;
        }
        case 4:
            allocator.displayEmployeeCount();
            break;
        case 5:
        {
            int id;
            cout << "\nEnter Employee ID to update: ";
            cin >> id;
            allocator.updateEmployee(id);
            break;
        }
        case 6:
            cout << "\nThank you for using the system!\n";
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != 6);
    return 0;
}
