#include <iostream>
#include <list>
#include <fstream>
#include <conio.h>
#include <iomanip>
using namespace std;

// Function to get a password from the user without displaying characters
string passwordFunc()
{
    string password;
    char ch;
    while ((ch = _getch()) != 13)// 13 is the ASCII value for 'Enter'
    { 
        if (ch == 8)
        { // 8 is the ASCII value for 'Backspace'
            if (!password.empty())
            {
                password.pop_back(); // Remove the last character
                cout << "\b \b";     // Move the cursor back, print a space, and move the cursor back again
            }
        }
        else
        {
            password.push_back(ch);
            cout << '*'; // Display asterisks instead of the actual characters
        }
    }
    return password;
}

// Forward declaration of classes
class Schools;
class program
{
    fstream file1, file2;
    list<string> BSchools;
    list<string> GSchools;

public:
    friend class Students;
    friend class Schools;

    // Constructor for the 'program' class
    program()
    {
        // Read schools from fileB.txt and store them in the 'BSchools' list
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

        // Read schools from fileG.txt and store them in the 'GSchools' list
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

    // Function to list schools based on sex (M: male, F: female, A: all)
    void listSchools(char sex)
    {
        int i = 0;
        if (sex == 'm' || sex == 'M' || sex == 'A' || sex == 'a')
        {
            cout << "Boys and Mixed Schools: " << endl;
            // Loop through 'BSchools' list and display schools
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
            // Loop through 'GSchools' list and display schools
            for (string school : GSchools)
            {
                cout << i + 1 << " " << school << endl;
                i++;
            }
        }
    }

    // Function to add schools to the files based on type (M: mixed, B: boys, G: girls)
    void addSchools(string school)
    {
        cout << "Which type of school(Mixed(M), Boys(B), Girls(G)): ";
        char ch = _getch();
        if (ch == 'M' || ch == 'm')
        {
            // Open both files for writing (append mode)
            file1.open("./fileB.txt", ios::out | ios::app);
            file2.open("./fileG.txt", ios::out | ios::app);
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

            // Add the school to both 'BSchools' and 'GSchools' lists and write to files
            BSchools.push_back(school);
            GSchools.push_back(school);
            file1 << school << '\n'; // Write data to the file
            file2 << school << '\n'; // Write data to the file

            file1.close(); // Close the file after writing
            file2.close(); // Close the file after writing
        }
        else if (ch == 'B' || ch == 'b')
        {
            // Open the file for writing (append mode)
            file1.open("./fileB.txt", ios::out | ios::app);
            if (!file1.is_open())
            {
                cerr << "Error: Unable to open file 'fileB.txt' for writing\n";
                return;
            }

            // Add the school to 'BSchools' list and write to the file
            BSchools.push_back(school);
            file1 << school << '\n'; // Write data to the file

            file1.close(); // Close the file after writing
        }
        else if (ch == 'G' || ch == 'g')
        {
            // Open the file for writing (append mode)
            file2.open("./fileG.txt", ios::out | ios::app);
            if (!file2.is_open())
            {
                cerr << "Error: Unable to open file 'fileG.txt' for writing\n";
                return;
            }

            // Add the school to 'GSchools' list and write to the file
            file2 << school << '\n'; // Write data to the file

            file2.close(); // Close the file after writing
        }
    }
};


// Define a class Students to store information about students and their choices
class Students
{
private:
    // Private member variables to store student data
    char sex; // Student's gender (M/F)
    string c_school; // Student's current school
    list<string> schoolChoice; // List of preferred school choices
    int grades[8]; // Array to store student's marks in 8 subjects
    string course; // Student's preferred course
    char accepted; // Flag to indicate if the student is accepted to any school ('y' or 'n')
    int aggregate; // Aggregate of marks in selected subjects
    string acceptedSchool; // Name of the school where the student is accepted
    string subjects[8] = {"Mathematics", "Integrated Science", "Social Studies", "English", "Visual Arts", "Home Economics", "Pre-Tech"}; // Array of subject names

public:
    // Public member variables
    string name; // Student's name
    long index_num; // Student's index number

    // Allow the Schools class to access private members of this class
    friend class Schools;

    // Function to insert student data
    void insert(program &prog, int dumNum);

    // Function to display student's subject-wise marks
    void displayRes();

    // Function to display student's details
    void displayDet(int k);

    // Function to return the list of selected school choices
    list<string> retSchoolChoice() { return schoolChoice; }

    // Serialization method to write object data to a file
    void serialize(fstream &file)
    {
        // Write student data to the file in a specific format
        file << sex << '\n';
        file << name << '\n';
        file << c_school << '\n';
        file << index_num << '\n';
        for (int i = 0; i < 8; i++)
            file << grades[i] << '\n';
        file << course << '\n';
        file << accepted << '\n';
        file << aggregate << '\n';
        file << acceptedSchool << '\n';

        // Write the number of selected schools and each selected school
        file << schoolChoice.size() << '\n';
        for (const string &school : schoolChoice)
            file << school << '\n';
    }

    // Deserialization method to read object data from the file
    void deserialize(fstream &file)
    {
        // Read student data from the file and assign it to the class members 
        file >> sex;
        file.ignore(1, '\n');
        getline(file, name);
        getline(file, c_school);
        file >> index_num;
        file.ignore(10, '\n');
        for (int i = 0; i < 8; i++)
        {
            file >> grades[i];
            file.ignore(1, '\n');
        }
        getline(file, course);
        file >> accepted;
        file.ignore(1, '\n');
        file >> aggregate;
        file.ignore(2, '\n');
        getline(file, acceptedSchool);

        // Read the number of selected schools and each selected school
        int numSelectedSchools;
        file >> numSelectedSchools;
        file.ignore(1, '\n');
        for (int i = 0; i < numSelectedSchools; i++)
        {
            string school;
            getline(file, school);
            schoolChoice.push_back(school);
        }
    }
};

// Function to insert student data into the Students class
void Students::insert(program &prog, int dumNum)
{
    // Clear the screen
    system("cls");

    // Prompt the user to enter the student's name
    cout << "\t\t\t\t Enter Name : " << endl;
    cout << "\t\t\t\t ";
    getline(cin, name);

    // Prompt the user to enter the student's gender
    cout << "\t\t\t\t Enter Sex(M/F) : " << endl;
    cout << "\t\t\t\t ";
    cin >> sex;
    cin.ignore(2, '\n');

    // Prompt the user to enter the student's current school
    cout << "\t\t\t\t Enter Current School : " << endl;
    cout << "\t\t\t\t ";
    getline(cin, c_school);

    // Prompt the user to enter the student's index number
    cout << "\t\t\t\t Enter Index Number : " << endl;
    cout << "\t\t\t\t ";
    cin >> index_num;

    cin.ignore();
if( dumNum == 1) //To prevent from updating the marks and the school choice
{
    // Prompt the user to enter marks subject-wise
    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    cout << "\t\t\t\t Enter Marks Subject Wise : " << endl;
    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    for (int i = 0; i < 7; i++)
    {
        // Prompt the user to enter marks for each subject
        cout << "\t\t\t\t " << subjects[i] << ": ";
        cin >> grades[i];

        // Calculate the aggregate marks for the first four subjects
        if (i < 4)
            aggregate += grades[i];

        cin.ignore(2, '\n');
    }

    // Find the two lowest marks from the remaining three subjects
    int smallest = 20, secondSmallest = 20;
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

    // Add the two lowest marks to the aggregate
    aggregate += (smallest + secondSmallest);

    // Prompt the user to enter the student's preferred course
    cout << "Enter your course: ";
    getline(cin, course);

    // Clear the screen
    system("cls");

    // Display a list of schools based on the student's gender and let the student choose three schools
    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    cout << "\t\t\t\t Select the school from the choices below : " << endl;
    cout << "\t\t\t\t ------------------------------------------------------" << endl;
    prog.listSchools(sex);
    list<string> Bschools = prog.BSchools;
    list<string> Gschools = prog.GSchools;
    for (int i = 0; i < 3; i++)
    {
        // Prompt the user to enter the index of the chosen school
        cout << "Enter the index of the school: ";
        int indexToSelect;
        cin >> indexToSelect;
        cin.ignore(2, '\n');

        // Based on the student's gender, select the school from the appropriate list
        if (sex == 'M' || sex == 'm')
        {
            list<string>::iterator it1 = Bschools.begin();
            advance(it1, indexToSelect - 1);
            if (it1 != Bschools.end())
            {
                // Add the selected school to the list of school choices
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
                // Add the selected school to the list of school choices
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

    // Display the list of selected school choices
    for (string str : schoolChoice)
    {
        cout << str << endl;
    }
}

}

// Function to display student's subject-wise marks
void Students::displayRes()
{
    // Display the student's subject-wise marks
    // with appropriate formatting
    // system("cls");
    cout << "\n\t\t\t\t\t\t--------------------------------------------------";
    cout << "\n\t\t\t\t\t\t|  Subject Name           |   Marks Obtained  |";
    cout << "\n\t\t\t\t\t\t--------------------------------------------------";
    for (int i = 0; i < 7; i++)
    {
        // Use setw() and left to align the output nicely
        cout << "\n\t\t\t\t\t\t| " << setw(23) << left << subjects[i] << "| " << setw(17) << left << grades[i] << " |";
    }
    cout << "\n\t\t\t\t\t\t-------------------------------------------------\n";
}

// Function to display student's details
void Students::displayDet(int k)
{
    // Display student's name, sex, current school, index number, and preferred school choices
    cout << "\t\t\t\t\t\tName: " << name << endl;
    cout << "\t\t\t\t\t\tSex: " << sex << endl;
    cout << "\t\t\t\t\t\tCurrent school: " << c_school << endl;
    cout << "\t\t\t\t\t\tIndex number: " << index_num << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t ------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t Preferred School Choices : " << endl;
    cout << "\t\t\t\t\t\t------------------------------------------------------" << endl;
    int i = 0;
    if (!schoolChoice.empty())
    {
        // Display the list of preferred school choices
        for (string choice : schoolChoice)
        {
            cout << "\t\t\t\t\t\t " << i + 1 << ". " << choice << endl;
            i++;
        }
    }
    cout << endl;
    if (accepted == 'y' && k == 1)
    {
        // If the student is accepted to a school, display the accepted status and school name
        cout << "\t\t\t\t\t\tAccepted: Yes" << endl;
        
    
        // ... (header art code)
        cout << "\033[32;1m ";
        stringstream art;
        art 
            << R"(

   ______                             __      
  / ____/___  ____  ____ __________ _/ /______
 / /   / __ \/ __ \/ __ `/ ___/ __ `/ __/ ___/
/ /___/ /_/ / / / / /_/ / /  / /_/ / /_(__  ) 
\____/\____/_/ /_/\__, /_/   \__,_/\__/____/  
                 /____/                       
)"
            ;

        int terminalWidth = 135; // Change this value according to your terminal width

        string line;
        while (getline(art, line))
        {
            int spaces = (terminalWidth - line.length()) / 2;
            cout << setw(spaces + line.length()) << line << endl;
        }
    
    
        cout << "\n\t\t\t\t\t\tYou been accepted into:  " << acceptedSchool << endl;
        cout << "\n\t\t\t\t\t\tYour course is:  " << course << endl;
        cout << "\t\t\t\t\t\tYour aggregate is:  " << aggregate << endl;
        cout << "\033[1;36m";
        cout << endl;
    }
    else if (accepted == 'n' && k == 1)
    {
        // If the student is not accepted to any school, display the rejected status
        cout << "Accepted: No" << endl;
    }
}

class Schools
{
private:
    // Data members
    list<string> courses;           // List of courses offered by the school
    int cutOff;                     // Cut-off point for student acceptance
    list<string> students;          // List of accepted student names
    list<string> studCourseSelected; // List of courses selected by each student
    int numOfStudents;              // Number of students to be accepted
    //fstream fileupdate;             // File stream for updating the data file (not currently used)

public:
    string name; // School name

    // Method to add school details
    void addDetail(program &prog)
    {
        // Get school name from the user
        cout << "Pls enter school name: ";
        getline(cin, name);
        prog.addSchools(name); // Assuming 'prog' is an object of the 'program' class.

        // Get the number of courses offered by the school
        int num;
        cout << "What is the number of courses offered by the school: ";
        cin >> num;
        cin.ignore(2, '\n');

        // Get the names of each course offered by the school
        for (int i = 0; i < num; i++)
        {
            cout << "Pls enter course " << i + 1 << " offered by the school: ";
            string crs;
            getline(cin, crs);
            courses.push_back(crs);
        }

        // Get cut-off point and number of students to be accepted
        cout << "Pls add cut-Off point: ";
        cin >> cutOff;
        cin.ignore(1, '\n');
        cout << "Pls add number of students to be accepted: ";
        cin >> numOfStudents;
        cin.ignore(2, '\n');
    }

    // Method to accept a student to the school
    char acceptStudent(Students &stud)
    {
        // Check if the student's aggregate score is below the cut-off and there are still available slots for students
        if (stud.aggregate <= cutOff && numOfStudents != 0)
        {
            // Add the student to the accepted students list
            students.push_back(stud.name);

            // Add the selected course to the list of courses selected by the student
            studCourseSelected.push_back(stud.course);

            // Reduce the number of available slots for students
            --numOfStudents;

            // Update the student's acceptance status and accepted school
            stud.accepted = 'y';
            stud.acceptedSchool = name;

            return 'y'; // Return 'y' to indicate that the student was accepted
        }
        else
        {
            // If the student doesn't meet the criteria or no available slots, mark the student as not accepted
            stud.accepted = 'n';
            return 'n'; // Return 'n' to indicate that the student was not accepted
        }
    }

    // Method to display school details
    void schoolDetails()
    {
        cout << "School Name: " << name << endl;
        cout << "Courses offered: " << endl;
        for (string course : courses)
            cout << course << endl;
        cout << "Cut-Off Point: " << cutOff << endl;
        cout << "Number of students to be accepted: " << numOfStudents << endl;
        cout << "Students accepted: " << endl;
        list<string>::iterator studIter = students.begin();
        list<string>::iterator courseIter = studCourseSelected.begin();

        for (; studIter != students.end() && courseIter != studCourseSelected.end(); ++studIter, ++courseIter)
        {
            cout << "Student: " << *studIter << ",  course: " << *courseIter << endl;
        }
    }

    // Method to print the list of accepted students and their selected courses
    void printStudents()
    {
        int i = 0;
        for (string student : students)
        {
            cout << i + 1 << " " << student << endl;

            // Print each student's selected course
            for (string course : studCourseSelected)
                cout << "Course: " << course << endl;
        }
        i++;
    }

    // Serialization method to write object data to the file
    void serialize(fstream &file)
    {
        // Write the school name
        file << name << '\n';

        // Write the number of courses and each course
        file << courses.size() << '\n';
        for (const string &course : courses)
            file << course << '\n';

        // Write the cut-off point and number of students
        file << cutOff << '\n';
        file << numOfStudents << '\n';
        file << students.size() << '\n';
        for (const string &student : students)
            file << student << '\n';

        file << studCourseSelected.size() << '\n';
        for (const string &course : studCourseSelected)
            file << course << '\n';
    }

    // Deserialization method to read object data from the file
    void deserialize(fstream &file)
    {
        // Read the school name
        getline(file, name);

        // Read the number of courses and each course
        int numCourses;
        file >> numCourses;
        file.ignore(1, '\n');
        for (int i = 0; i < numCourses; i++)
        {
            string crs;
            getline(file, crs);
            courses.push_back(crs);
        }

        // Read the cut-off point and number of students
        file >> cutOff;
        file.ignore(1, '\n');
        file >> numOfStudents;
        file.ignore(1, '\n');

        int numStudents;
        file >> numStudents;
        file.ignore(1, '\n');
        for (int i = 0; i < numStudents; i++)
        {
            string student;
            getline(file, student);
            students.push_back(student);
        }
        int numCoursesSelected;
        file >> numCoursesSelected;
        file.ignore(1, '\n');
        for (int i = 0; i < numCoursesSelected; i++)
        {
            string course;
            getline(file, course);
            studCourseSelected.push_back(course);
        }
        // fileupdate.close(); // Note: 'fileupdate' is not used in this code
    }
};



// SHSPlacementSystem class for managing the placement system
class SHSPlacementSystem {
private:
    fstream file, fileStud;
    int n = 100000;
    int totalSchools, totalStuds;
    program prog;
    Schools *trial[100000];
    Students *stud[100000];
    string password;
    int choice;
    bool status;
    list<string> schoolchoice;

public:
    // Function to display a header art on the console
    void generateGES() {
        // ... (header art code)
        stringstream art;
        art << "\033[1;36m"
            << R"(
 $$$$$$\  $$$$$$$$\  $$$$$$\  
$$  __$$\ $$  _____|$$  __$$\ 
$$ /  \__|$$ |      $$ /  \__|
$$ |$$$$\ $$$$$\    \$$$$$$\  
$$ |\_$$ |$$  __|    \____$$\ 
$$ |  $$ |$$ |      $$\   $$ |
\$$$$$$  |$$$$$$$$\ \$$$$$$  |
 \______/ \________| \______/ 
                           
)"
            << "\033[0m";

        int terminalWidth = 156; // Change this value according to your terminal width

        string line;
        while (getline(art, line))
        {
            int spaces = (terminalWidth - line.length()) / 2;
            cout << setw(spaces + line.length()) << line << endl;
        }
    
    }

    // Function to read program details from 'program.txt' file
    void readProgramFile() {
        fstream programfile;
        programfile.open("./program.txt", ios::in); // Open the file for reading
        if (!programfile.is_open()) {
            cerr << "Error: Unable to open file 'program.txt' for reading\n";
            exit(1);
        } else {
            programfile >> totalSchools;
            programfile >> password;
            programfile >> totalStuds;
        }
        programfile.close();
    }

    // Function to read school details from 'SCHGROUP.DAT' file
    void readSchoolsFile() {
        file.open("./SCHGROUP.DAT", ios::app | ios::out | ios::in | ios::binary);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file 'SCHGROUP.DAT'\n";
            exit(1);
        }
        file.seekg(0);

        for (int i = 0; i < totalSchools; i++) {
            trial[i] = new Schools;
            trial[i]->deserialize(file);
            //trial[i]->schoolDetails();
        }
        file.close();
    }

    // Function to read student details from 'STUD.DAT' file
    void readStudentsFile() {
        fileStud.open("./STUD.DAT", ios::app | ios::out | ios::in | ios::binary);
        if (!fileStud.is_open()) {
            cerr << "Error: Unable to open file 'STUD.DAT'\n";
            exit(1);
        }
        fileStud.seekg(0);

        for (int j = 0; j < totalStuds; j++) {
            stud[j] = new Students;
            stud[j]->deserialize(fileStud);
           //. stud[j]->displayDet();
        }
        fileStud.close();
    }

    // Function to save school details to 'SCHGROUP.DAT' file
    void saveSchoolsToFile() {
        file.open("SCHGROUP.DAT", ios::out | ios::binary);
        if (!file.is_open()) {
            cerr << "Error: Unable to open file 'SCHGROUP.DAT'\n";
            exit(1);
        }
        file.seekg(0);
        for (int i = 0; i < totalSchools; i++) {
            trial[i]->serialize(file);
        }
        file.close();
    }

    // Function to save student details to 'STUD.DAT' file
    void saveStudentsToFile() {
        fileStud.open("STUD.DAT", ios::out | ios::binary);
        if (!fileStud.is_open()) {
            cerr << "Error: Unable to open file 'STUD.DAT'\n";
            exit(1);
        }
        fileStud.seekg(0);
        for (int i = 0; i < totalStuds; i++) {
            stud[i]->serialize(fileStud);
        }
        fileStud.close();
    }

    // Function for administrator menu and actions
    void adminMenu() {
        // ... (administrator menu and actions)
        cout << "\t\t\t\t\t\t\t\tEnter Password: ";
        string pass;

        
        pass = passwordFunc();
        cout << endl;
        // cout << pass << endl;

        if (pass == password)
        {
            char ch;
            do
            {
                system("cls");

                cout << "\t\t\t\t\t\t\t\t ------------------------------------------" << endl;
                cout << "\t\t\t\t\t\t\t\t |1. Enter a new School                   |" << endl;
                cout << "\t\t\t\t\t\t\t\t |2. Add a Student                        |" << endl;
                cout << "\t\t\t\t\t\t\t\t |3. Navigate Students profiles           |" << endl;
                cout << "\t\t\t\t\t\t\t\t |4. Navigate School profiles             |" << endl;
                cout << "\t\t\t\t\t\t\t\t |5. Change password                      |" << endl;
                cout << "\t\t\t\t\t\t\t\t |6. Exit                                 |" << endl;
                cout << "\t\t\t\t\t\t\t\t |Choose Option: [1 / 2 / 3 / 4 / 5 / 6 ] |" << endl;
                cout << "\t\t\t\t\t\t\t\t ------------------------------------------" << endl;
                cout << "\t\t\t\t\t\t\t\t Please Enter Your Choice :";
                int ind = 0;
                cin >> choice;
                string prevPass;
                cin.ignore();

                switch (choice)
                {
                case 1:
                    do
                    {
                        trial[totalSchools] = new Schools;
                        trial[totalSchools]->addDetail(prog);
                        trial[totalSchools]->serialize(file);
                        cout << "Enter another school (y/n)? ";
                        cin >> ch;
                        cin.ignore();
                        ++totalSchools;
                    } while (ch != 'n');

                    file.close();

                    break;
                case 2:
                    do
                    {
                        stud[totalStuds] = new Students;
                        // Write to file
                        stud[totalStuds]->insert(prog, 1);
                        // cout << studentsNames[totalStuds] << endl;
                        stud[totalStuds]->serialize(fileStud);
                        schoolchoice = stud[totalStuds]->retSchoolChoice();
                        char c = 'n';

                        for (string str : schoolchoice)
                        {
                            for (int i = 0; i < totalSchools; i++)
                            {
                                if (str == trial[i]->name)
                                {
                                    cout << str << endl;
                                    if (trial[i]->acceptStudent(*stud[totalStuds]) == 'y')
                                    {
                                        cout << "Student accepted" << endl;
                                        c = 'y';
                                        // studentAccepted = true; // Set the flag to true if any student is accepted
                                        break;
                                    }
                                    else
                                    {
                                        cout << "Student not accepted" << endl;
                                    }
                                }
                            }
                            if (c == 'y')
                            {
                                //cout << "yeah" << endl;
                                break;
                            }
                        }
                        stud[totalStuds]->serialize(fileStud);
                        ++totalStuds;
                        cout << "Enter another person (y/n)? ";
                        cin >> ch;    // Update the value of 'ch' based on user input
                        cin.ignore(); // Ignore the newline character left by cin

                    } while (ch == 'y'); // Continue the loop until 'n' is entered
                    fileStud.close();

                    break;
                case 3:
                    cout << "Listing all students: " << endl;
                    for (int i = 0; i < totalStuds; i++)
                    {
                        cout << i + 1 << " - " << stud[i]->name << endl;
                    }
                    cout << "Select student by Index: " << endl;

                    cin >> ind;
                    cin.ignore();
                    if (ind - 1 < totalStuds)
                    {
                        stud[ind - 1]->displayDet(2);
                        stud[ind - 1]->displayRes();
                        cout << "Would you like to change the detail(y/n): ";

                        cin >> ch;
                        cin.ignore();
                        if (ch == 'y' || ch == 'Y')
                        {
                            stud[ind - 1]->insert(prog, 2);
                            // stud[i]->serialize(fileStud);
                            cout << "Edit completed!" << endl;
                        }
                    }

                    break;

                case 4:
                    cout << "Listing all schools: " << endl;
                    for (int i = 0; i < totalSchools; i++)
                    {
                        cout << i + 1 << " - "<< trial[i]->name << endl;
                    }
                    cout << "Select school by Index: " << endl;

                    cin >> ind;
                    cin.ignore();
                    if (ind - 1 < totalSchools)
                    {
                        trial[ind - 1]->schoolDetails();
                        //trial[ind - 1]->printStudents();
                        cout << "Would you like to change the detail: ";

                        cin >> ch;
                        cin.ignore();
                        if (ch == 'y' || ch == 'Y')
                        {
                            trial[ind - 1]->addDetail(prog);
                            // trial[i]->serialize(file);
                            cout << "Edit completed!" << endl;
                        }
                    }
                    status = false;
                    break;
                case 5:
                    cout << "Enter previous password: ";

                    prevPass = passwordFunc();
                    // cout << prevPass << endl;
                    if (prevPass == password)
                    {
                        cout << "Enter new password: ";
                        password = passwordFunc();
                        // cout << password << endl;
                        cout << "Password changed successfully!" << endl;
                    }
                    else
                    {
                        cout << "Wrong password!" << endl;
                    }
                    break;
                case 6:
                    cout << "Exiting..." << endl;
                    status = false;
                    break;

                default:
                    cout << "Invalid Choice! Please Try Again" << endl;
                }

            } while (choice != 6  && status);
            cout << "Would you like to do anything else(y/n): ";
            cin >> ch;
            cin.ignore();
            if (ch == 'n' || ch == 'N')
            {
                status = false;
            }
            else if(ch == 'y' || ch == 'Y')
            {
                status = true;
            }
            else
            {
                cout << "Invalid input" << endl;
            }
        }

        else
        {
            cout << "Wrong Password!" << endl;
        }
    }

    // Function for student menu and actions
    void studentMenu() {
        // ... (student menu and actions)
         char ch;
        cout << "Enter your index number: ";
        long index;
        cin >> index;
        do
        {
            system("cls");

            //cin.ignore();
            cout << "\t\t\t\t\t\t\t\t ----------------------------------------" << endl;
            cout << "\t\t\t\t\t\t\t\t |1. Check details and Placement        |" << endl;
            cout << "\t\t\t\t\t\t\t\t |2. Check Results                      |" << endl;
            cout << "\t\t\t\t\t\t\t\t |3. Exit                               |" << endl;
            cout << "\t\t\t\t\t\t\t\t |Choose Option: [1 / 2 / 3 ]           |" << endl;
            cout << "\t\t\t\t\t\t\t\t ----------------------------------------" << endl;
            cout << "\t\t\t\t\t\t\t\t Please Enter Your Choice :";
            int ind = 0;
            cin >> choice;
            cin.ignore();

            switch (choice)
            {

            case 1:
                for (int i = 0; i < totalStuds; i++)
                {
                    if (index == stud[i]->index_num)
                    {
                        stud[i]->displayDet(1);
                        break;
                    }
                    else if (i == totalStuds - 1)
                    {
                        cout << "Index is not in Our SystemB" << endl;
                    }
                }
                cout << "Would you like to do anything else(y/n): ";
                cin >> ch;
                cin.ignore(1, '\n');
                if (ch == 'n' || ch == 'N')
                {
                    status = false;
                    choice = 3;
                }
                
                break;
            case 2:
                for (int i = 0; i < totalStuds; i++)
                {
                    if (index == stud[i]->index_num)
                    {
                        stud[i]->displayRes();
                        break;
                    }
                    else if(i == totalStuds - 1)
                    {
                        cout << "Index is not in Our SystemA" << endl;
                    }
                }
                cout << "Would you like to do anything else(y/n): ";
                cin >> ch;
                cin.ignore(1, '\n');
                if (ch == 'n' || ch == 'N')
                {
                    status = false;
                    choice = 3;
                }
                
                break;
            case 3:
                cout << "Exiting..." << endl;
                status = false;
                break;
            default:
                cout << "Invalid Choice! Please Try Again" << endl;
            }
        } while (choice != 3 && status);
        if (status != false)
        {
            cout << "Would you like to do anything else(y/n): ";
            cin >> ch;
            cin.ignore(1, '\n');
        }
        if (ch == 'n' || ch == 'N')
        {
            status = false;
        }
    }
    

    // Function to run the placement system
    void run() {
        // ... (read data, display header, show menus, save data, clean up)
         status = true;
        readProgramFile();
        readSchoolsFile();
        readStudentsFile();
        system("cls");
        generateGES();

        char x;
        cout << "\033[1;36m";
        cout << "\n\t\t\t\t\t\t\t\t-------------------------" << endl;
        cout << "\t\t\t\t\t\t\t\t SHS PLACEMENT SYSTEM " << endl;
        cout << "\t\t\t\t\t\t\t\t-------------------------" << endl;

        do
        {
            cout << "\t\t\t\t \t\t\t\tAre you an Administrator or a Student? (A/S): ";
            cin >> x;
            cin.ignore(2, '\n');
            if (x == 'A' || x == 'a')
            {
                adminMenu();
            }
            else if (x == 'S' || x == 's')
            {
                studentMenu();
            }
            else
            {
                cout << "Invalid Entry" << endl;
            }
            
        } while (status);

        saveSchoolsToFile();
        saveStudentsToFile();
        for (int i = 0; i < totalSchools; i++)
        {
            delete trial[i];
        }
        for (int i = 0; i < totalStuds; i++)
        {
            delete stud[i];
        }

        fstream programfile;
        programfile.open("./program.txt", ios::out); // Open the file for writing
        if (!programfile.is_open())
        {
            cerr << "Error: Unable to open file 'program.txt' for writing\n";
            exit(1);
        }
        else
        {
            programfile << totalSchools << '\n';
            programfile << password << '\n';
            programfile << totalStuds << '\n';
        }
        programfile.close(); // Close the file after writing
        cout << "\033[0m";
    }
    
};

// Main function
int main() {
    // Create an instance of the SHSPlacementSystem class
    SHSPlacementSystem system;

    // Run the placement system
    system.run();

    // Return 0 to indicate successful execution
    return 0;
}