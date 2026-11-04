
#include <iostream>
#include <string>

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

    // Friend function

    friend void displayEmployeeDetails(const Employee &e)
    {
        cout << "\nEmployee ID   : " << e.employeeId;
        cout << "\nEmployee Name : " << e.name;
        cout << "\nShift         : " << e.shift;
        cout << "\nFloor         : " << e.floor;
        cout << "\n";
    }
};
int Employee::totalEmployees=0;
// Shift Allocator Class

class ShiftAllocator
{
private:
    Employee employees[100];

    int count = 0;

    Employee *currentEmployee = nullptr;

public:
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

        count++;

        Employee::increaseCount();

        cout << "\nEmployee added successfully!\n";
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
        bool found = false;

        for (int i = 0; i < count; i++)
        {
            if (employees[i].getEmployeeId() == id)
            {
                currentEmployee = &employees[i];

                cout << "\nEmployee Found!\n";

                currentEmployee->display();

                found = true;

                break;
            }
        }

        if (found == false)
        {
            cout << "\nEmployee not found!\n";
        }
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
        cout << "\n====================================\n";
        cout << " HOTEL HOUSEKEEPING SHIFT ALLOCATOR\n";
        cout << "====================================\n";

        cout << "1. Add Employee\n";
        cout << "2. View All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Display Total Employees\n";
        cout << "5. Exit\n";

        cout << "====================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            allocator.addEmployee();
            break;

        case 2:
            allocator.viewEmployees();
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
