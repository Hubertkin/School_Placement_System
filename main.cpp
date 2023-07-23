#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <conio.h>
#include <iomanip>
using namespace std;
class Students;

class program
{
    fstream file1, file2;
    list<string> BSchools;
    list<string> GSchools;

public:
    friend class Students;

    program()
    {
        string school;

        file1.open("./fileB.txt", ios::in); // Open the file for reading
        if (!file1.is_open())
        {
            cerr << "Error: Unable to open file 'fileB.txt' for reading\n";
            return;
        }

        while (getline(file1, school))
        {
            BSchools.push_back(school);
        }

        file1.close(); // Close the file after reading

        file2.open("./fileG.txt", ios::in); // Open the file for reading
        if (!file2.is_open())
        {
            cerr << "Error: Unable to open file 'fileG.txt' for reading\n";
            return;
        }

        while (getline(file2, school))
        {
            GSchools.push_back(school);
        }

        file2.close(); // Close the file after reading
    }

    void listSchools(char sex)
    {
        int i = 0;
        if (sex == 'm' || sex == 'M' || sex == 'A' || sex == 'a')
        {
            cout << "Boys and Mixed Schools: " << endl;
            for (string school : BSchools)
            {
                cout << i + 1 << " " << school << endl;
                i++;
            }
        }
        cout << endl;
        i = 0;
        if (sex == 'f' || sex == 'F' || sex == 'A' || sex == 'a')
        {
            cout << "Girls and Mixed Schools: " << endl;
            for (string school : GSchools)
            {
                cout << i + 1 << " " << school << endl;
                i++;
            }
        }
    }

    void addSchools()
    {
        cout << "Which type of school(Mixed(M), Boys(B), Girls(G)): ";
        char ch = _getch();
        if (ch == 'M' || ch == 'm')
        {
            file1.open("./fileB.txt", ios::out | ios::app);
            file2.open("./fileG.txt", ios::out | ios::app); // Open the file for writing (append mode)
            if (!file1.is_open())
            {
                cerr << "Error: Unable to open file 'fileB.txt' for writing\n";
                return;
            }
            if (!file2.is_open())
            {
                cerr << "Error: Unable to open file 'fileG.txt' for writing\n";
                return;
            }

            int num;
            cout << "Number of Schools to add: ";
            cin >> num;
            cin.ignore(2, '\n');

            for (int i = 0; i < num; i++)
            {
                cout << "Please enter the name of school: \n";
                string school;
                getline(cin, school);
                BSchools.push_back(school);
                GSchools.push_back(school);
                file1 << school << '\n'; // Write data to the file
                file2 << school << '\n'; // Write data to the file
            }

            file1.close(); // Close the file after writing
            file2.close(); // Close the file after writing
        }
        else if (ch == 'B' || ch == 'b')
        {
            file1.open("./fileB.txt", ios::out | ios::app); // Open the file for writing (append mode)
            if (!file1.is_open())
            {
                cerr << "Error: Unable to open file 'fileB.txt' for writing\n";
                return;
            }

            int num;
            cout << "Number of Schools to add: ";
            cin >> num;
            cin.ignore(2, '\n');

            for (int i = 0; i < num; i++)
            {
                cout << "Please enter the name of school: \n";
                string school;
                getline(cin, school);
                BSchools.push_back(school);
                file1 << school << '\n'; // Write data to the file
            }

            file1.close(); // Close the file after writing
        }
        else if (ch == 'G' || ch == 'g')
        {
            file2.open("./fileG.txt", ios::out | ios::app); // Open the file for writing (append mode)
            if (!file2.is_open())
            {
                cerr << "Error: Unable to open file 'fileG.txt' for writing\n";
                return;
            }

            int num;
            cout << "Number of Schools to add: ";
            cin >> num;
            cin.ignore(2, '\n');

            for (int i = 0; i < num; i++)
            {
                cout << "Please enter the name of school: \n";
                string school;
                getline(cin, school);
                GSchools.push_back(school);
                file2 << school << '\n'; // Write data to the file
            }
            file2.close(); // Close the file after writing
        }
    }
};

class Students
{
    char sex;
    string name, c_school;
    int index_num;
    list<string> schoolChoice;
    int grades[8];
    string course;
    char accepted;
    int aggregate;
    string acceptedSchool;
    string subjects[8] = {"Mathematics", "Integrated Science", "Social Studies", "English", "Visual Arts", "Home Economics", "Pre-Tech"};

public:
    friend class Schools;
    Students()
    {
        // Initialize schoolChoice list here
    }

    Students *insert(program &prog);
    void displayRes();
    void displayDet();
    list<string> retSchoolChoice() { return schoolChoice; }
};

Students *Students::insert(program &prog)
{
    // system("cls");
    cout << "\t\t\t\t Enter Your Name : " << endl;
    cout << "\t\t\t\t ";
    getline(cin, name);
    cout << "\t\t\t\t Enter Your Sex(M/F) : " << endl;
    cout << "\t\t\t\t ";
    cin >> sex;
    cin.ignore(2, '\n');
    cout << "\t\t\t\t Enter Your Current School : " << endl;
    cout << "\t\t\t\t ";
    getline(cin, c_school);
    cout << "\t\t\t\t Enter Your Index Number : " << endl;
    cout << "\t\t\t\t ";
    cin >> index_num;
    cin.ignore(2, '\n');

    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    cout << "\t\t\t\t Enter Your Marks Subject Wise : " << endl;
    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << "\t\t\t\t " << subjects[i] << ": ";
        cin >> grades[i];
        if (i < 4)
            aggregate += grades[i];
        cin.ignore(2, '\n');
    }
    int smallest = 10, secondSmallest = 10;
    for (int i = 4; i < 7; i++)
    {

        if (grades[i] < smallest)
        {
            secondSmallest = smallest;
            smallest = grades[i];
        }
        else if (grades[i] < secondSmallest)
        {
            secondSmallest = grades[i];
        }
    }
    aggregate += (smallest + secondSmallest);
    cout << "Enter your course: ";
    getline(cin, course);

    system("cls");
    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    cout << "\t\t\t\t Select the school from the choices below : " << endl;
    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    prog.listSchools(sex);
    list<string> Bschools = prog.BSchools;
    list<string> Gschools = prog.GSchools;
    for (int i = 0; i < 3; i++)
    {
        cout << "Enter the index of the school: ";
        int indexToSelect;
        cin >> indexToSelect;
        cin.ignore(2, '\n');
        if (sex == 'M' || sex == 'm')
        {
            list<string>::iterator it1 = Bschools.begin();
            advance(it1, indexToSelect - 1);
            if (it1 != Gschools.end())
            {
                string selectedSchool = *it1;
                schoolChoice.push_back(selectedSchool);
                cout << "Selected school at index " << indexToSelect << ": " << selectedSchool << endl;
            }
            else
            {
                cout << "Invalid index!" << endl;
            }
        }
        else if (sex == 'F' || sex == 'f')
        {
            list<string>::iterator it2 = Gschools.begin();

            // Advance the iterator to the desired index
            advance(it2, indexToSelect - 1);

            // Now, 'it' points to the element at the desired index
            if (it2 != Gschools.end())
            {
                string selectedSchool = *it2;
                schoolChoice.push_back(selectedSchool);
                cout << "Selected school at index " << indexToSelect << ": " << selectedSchool << endl;
            }
            else
            {
                cout << "Invalid index!" << endl;
            }
        }
    }
    for (string str : schoolChoice)
    {
        cout << str << endl;
    }

    /*int i = 0;
    if (sex == 'M' || sex == 'm')
    {
        for (string schools : prog.BSchools)
        {
            cout << "\t\t\t\t " << i + 1 << ". " << schools << endl;
            i++;
        }
    }
    else if (sex == 'F' || sex == 'f')
    {
        for (string schools : prog.GSchools)
        {
            cout << "\t\t\t\t " << i + 1 << ". " << schools << endl;
            i++;
        }
    }*/

    // Uncomment the following code when you want to implement schoolChoice selection
    /*
    for (int i = 0; i < 3; i++)
    {
        cout << "\t\t\t\t " << i + 1 << ". Choice: ";
        string school;
        getline(cin, school);
        schoolChoice.push_back(school);
    }
    */
    return this;
}

void Students::displayRes()
{
    cout << "\n\t------------------------------------------------------------";
    cout << "\n\t|  Subject Name           |   Marks Obtained  |";
    cout << "\n\t-------------------------------------------------------------";
    for (int i = 0; i < 7; i++)
    {
        // Use setw() and left to align the output nicely
        cout << "\n\t| " << setw(23) << left << subjects[i] << "| " << setw(17) << left << grades[i] << " |";
    }
    cout << "\n\t-------------------------------------------------------------\n";
}

void Students::displayDet()
{
    cout << "Name: " << name << endl;
    cout << "Sex: " << sex << endl;
    cout << "Current school: " << c_school << endl;
    cout << "Index number: " << index_num << endl;
    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    cout << "\t\t\t\t Preferred School Choices : " << endl;
    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    int i = 0;
    if (!schoolChoice.empty())
    {
        for (string choice : schoolChoice)
        {
            cout << "\t\t\t\t " << i + 1 << ". " << choice << endl;
            i++;
        }
    }
}

class Schools
{

protected:
    list<string> courses;
    int cutOff;
    list<string> students;
    list<string> studCourseSelected;
    int numOfStudents;

public:
    string name;
    void addDetail(string nam)
    {
        name = nam;
        int num;
        cout << "What is the number of courses offered by the school: ";
        cin >> num;
        cin.ignore(2, '\n');
        for (int i = 0; i < num; i++)
        {
            cout << "Pls enter course " << i + 1 << " offered by the school: ";
            string crs;
            getline(cin, crs);
            courses.push_back(crs);
        }
        cout << "Pls add cut-Off point: ";
        cin >> cutOff;
        cin.ignore(1, '\n');
        cout << "Pls add number of students to be accepted: ";
        cin >> numOfStudents;
        cin.ignore(2, '\n');
    }
    char acceptStudent(Students stud)
    {
        if (stud.aggregate <= cutOff && numOfStudents != 0)
        {
            students.push_back(stud.name);
            studCourseSelected.push_back(stud.course);
            --numOfStudents;
            stud.accepted = 'y';
            stud.acceptedSchool = name;
            return 'y';
        }
        else

            return 'n';
    }
    void schoolDetails()
    {
        cout << "School Name: " << name << endl;
        cout << "Courses offered: " << endl;
        for (string course : courses)
            cout << course << endl;
        cout << "Cut-Off Point: " << cutOff << endl;
        cout << "Number of students to be accepted: " << numOfStudents << endl;
    }
    void printStudents()
    {
        int i = 0;
        for (string student : students)
        {
            cout << i + 1 << " " << student << endl;

            for (string course : studCourseSelected)
                cout << "Course: " << course << endl;
        }
        i++;
    }
};

int main()
{
    fstream file;
    int n = 100000;
    int totalSchools = 0;
    Schools prog;
    Schools *trial[n];
    Students stud;
    list<string> schoolchoice;
    char ch;

    //stud.insert(prog);
    //stud.displayDet();
    //stud.displayRes();

    file.open("SCHGROUP.DAT", ios::app | ios::out | ios::in | ios::binary);
    do
    {
        trial[totalSchools] = new Schools;
        cout << "\nEnter Schools name: ";
        getline(cin, trial[totalSchools]->name);

        // write to file
        trial[totalSchools]->addDetail(trial[totalSchools]->name);
        file.write(reinterpret_cast<char *>(trial[totalSchools]), sizeof(Schools));
        cout << "Enter another person (y/n)? ";
        cin >> ch;
        cin.ignore(); // Ignore the newline character left by cin
        ++totalSchools;
    } while (ch != 'n'); // quit on 'n'

    file.seekg(0); // reset to start of file

    for (int i = 0; i < totalSchools; i++)
    {
        file.read(reinterpret_cast<char *>(trial[i]), sizeof(Schools));
        trial[i]->schoolDetails();
    }

    file.close();

    // Deallocate dynamically allocated memory
    for (int i = 0; i < totalSchools; i++)
    {
        delete trial[i];
    }

    return 0;
}