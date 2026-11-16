#include <iostream>
#include <string>
#include<fstream>
#include<cstring>
using namespace std;
// Employee Class
class Employee
{
private:
    int employeeId = 0;
    string name = "";
    string shift = "";
    int floor = 0;
    static int totalEmployees;
public:
    Employee(){
        employeeId=0;
        name="";
        shift="";
        floor=0;
    }
    Employee(int id, string n, string s, int f){
     employeeId = id;
     name = n;
     shift = s;
     floor = f;
    }
    Employee(const Employee& e){
        employeeId=e.employeeId;
        name=e.name;
        shift=e.shift;
        floor=e.floor;
    }
    // Input employee details
    bool input()
    {
        cout << "\nEnter Employee ID: ";
        cin >> employeeId;
        cout << "Enter Employee Name: ";
        cin.ignore();
        getline(cin,name);
        cout << "Enter Shift (Morning/Evening/Night): ";
        cin >> shift;
        cout << "Enter Floor Number: ";
        cin >> floor;
        return isValid();
    }
    // Validate employee details
    bool isValid() const
    {
        if (employeeId <= 0 || floor <= 0 || name == "")
        {
            return false;
        }
        if (shift != "Morning" &&
            shift != "Evening" &&
            shift != "Night")
        {
            return false;
        }
        return true;
    }
    // Display employee details
    void display() const
    {
        cout << "\nEmployee ID   : " << employeeId;
        cout << "\nEmployee Name : " << name;
        cout << "\nShift         : " << shift;
        cout << "\nFloor         : " << floor;
        cout << "\n";
    }
    // Inline getter function
    inline int getEmployeeId() const
    {
        return employeeId;
    }
    // Setter functions using this pointer
    void setShift(string shift)
    {
        this->shift = shift;
    }
    void setFloor(int floor)
    {
        this->floor = floor;
    }
    // Static function
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
    // Friend function
    friend void displayEmployeeDetails(const Employee &e)
    {
        cout << "\nEmployee ID   : " << e.employeeId;
        cout << "\nEmployee Name : " << e.name;
        cout << "\nShift         : " << e.shift;
        cout << "\nFloor         : " << e.floor;
        cout << "\n";
    }
    ~Employee(){
    }
};
int Employee::totalEmployees=0;
class EmployeeFile{
    public:
    int employeeId;
    char name[50];
    char shift[50];
    int floor;
};
// Shift Allocator Class
class ShiftAllocator
{
    Employee employees[100];
    int count = 0;
    Employee *currentEmployee = nullptr;
public:
    void saveEmployee(EmployeeFile record)
    {
        ofstream file("employees.dat", ios::binary | ios::app);
        file.write((char*)&record, sizeof(record));
        file.close();
    }
    // Add employee
    void addEmployee()
    {
        if (count == 100)
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
        employees[count] = newEmployee;
        EmployeeFile record;
        record.employeeId = newEmployee.getEmployeeId();
        strcpy(record.name, newEmployee.getName().c_str());
        strcpy(record.shift, newEmployee.getShift().c_str());
        record.floor = newEmployee.getFloor();
        saveEmployee(record);
        count++;
        Employee::increaseCount();
        cout << "\nEmployee added successfully!\n";
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

    cout << "\n----- Employee Records -----\n";

    while (file.read((char*)&record, sizeof(record)))
    {
        cout << "\nEmployee ID: " << record.employeeId;
        cout << "\nEmployee Name: " << record.name;
        cout << "\nShift: " << record.shift;
        cout << "\nFloor: " << record.floor;
        cout << "\n------------------------\n";
    }

    file.close();
}

    // Display all employees
    void viewEmployees()
    {
        cout << "\n----- Employee Records -----\n";
        if (count == 0)
        {
            cout << "\nNo employee records available!\n";
            return;
        }
        else{
        for (int i = 0; i < count; i++)
        {
            employees[i].display();
        }
        }
        cout << "\nTotal Records: " << count << endl;
    }
    // Search employee by ID
   
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

    while (file.read((char*)&record, sizeof(record)))
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

    if (!found)
    {
        cout << "\nEmployee not found!\n";
    }

    file.close();
}

    // Check duplicate employee ID
    bool isDuplicate(int id) const
    {
        for (int i = 0; i < count; i++)
        {
            if (employees[i].getEmployeeId() == id)
            {
                return true;
            }
        }
        return false;
    }
    // Display total employees
    void displayEmployeeCount() const
    {
        cout << "\nTotal Employees: "
             << Employee::getTotalEmployees() << endl;
    }
};
// Main Function
int main()
{
    ShiftAllocator allocator;
    int choice;
    do
    {
        cout << " HOTEL HOUSEKEEPING SHIFT ALLOCATOR\n";
        cout << "1. Add Employee\n";
        cout << "2. View All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Display Total Employees\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
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
            cout << "\nThank you for using the system!\n";
            break;
        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != 5);
    return 0;
}