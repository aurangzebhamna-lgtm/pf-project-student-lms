#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

struct Student {
    char name[100] = "";
    char roll[20] = "";
    char section[10] = "";

    float quizzes[10] = { 0 };
    int quizCount = 0;

    float assignments[10] = { 0 };
    int assignmentCount = 0;
    int assignmentTotalMarks = 0;

    float mid = 0;
    int midTotal = 0;
    float final = 0;

    float percentage = 0;
    char grade = 'F';
};

//setting max limit of students as 100 and inititalising the count to 0
Student students[100];
int studentCount = 0;

void mainMenu();
void studentMenu();
void fileMenu();
void addStudent();
void displayAll();
void searchStudent();
void updateStudent();
void deleteStudent();
void fileSave();
void fileLoad();
void classReport();
void result(int index);
char grade(float percentage);
void sortByPercentage();
bool validRoll(char roll[]);
void subjectStats();

//function to display the main menu which is further broken down into sub-menus
void mainMenu() {
    int choice;
    while (true) {
        cout << "=== Main Menu ===\n1. Student Operations\n2. File Operations\n3. Class Report\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: 
            studentMenu(); 
            break;
        case 2: 
            fileMenu(); 
            break;
        case 3:
            classReport(); 
            break;
        case 0:
            cout << "Exiting..." << endl;
            return;
        default:
            cout << "Invalid choice! Try again." <<endl;
        }
    }
}
//menu for student operations like add, search, update, delete etc.
void studentMenu() {
    int choice;
    while (true) {
        cout << "1. Add Student\n2. Display All\n3. Search by Roll No\n4. Update Student\n5. Delete Student\n0. Back\n";
        cin >> choice;
        switch (choice) {
        case 1: 
            addStudent(); 
            break;
        case 2: 
            displayAll();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    }
}
//menu for file operations.
void fileMenu() {
    int choice;
    while (true) {
        cout << "\n--- File Menu ---\n1. Save to File\n2. Load from File\n0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            fileSave();
            break;
        case 2:
            fileLoad();
            break;
        case 0:
            return;
        default: 
            cout << "Invalid choice! Try again." << endl;
        }
    }
}
//function to check if the roll number format is correct (25X-1234)
bool validRoll(char roll[]) {
    if (strlen(roll) != 8)
        return false;
    if (!isdigit(roll[0]) || !isdigit(roll[1])) 
        return false;
    if (!isalpha(roll[2]) || !isupper(roll[2])) 
        return false;
    if (roll[3] != '-') 
        return false;
    for (int i = 4; i < 8; i++) {
        if (!isdigit(roll[i])) 
            return false;
    }
    return true;
}

void addStudent() {
    //checking if more student can be added
    if (studentCount >= 100) {
        cout << "Cannot add more students! Maximum reached." <<endl;
        return;
    }
    cout << "\n--- Add New Student ---\n";
    cin.ignore();

    //roll number validation check
    char roll[20];
    while (true) {
        cout << "Enter Roll No (Format 25X-1234): ";
        cin.getline(roll, 20);
        if (validRoll(roll)) break;
        cout << "Invalid Format! Try again.\n";
    }
   strcpy(students[studentCount].roll, roll);
 
    cout << "Enter Name: ";
    cin.getline(students[studentCount].name,100);
    cout << "Enter Section: ";
    cin.getline(students[studentCount].section, 20);

    //quiz marks are out of 10. user tell how many quizzes were taken and inputs marks for each.
    int qcount = 0;
    cout << "Enter the number of total quizzes: ";
    cin >> qcount;

    for (int i = 0; i < qcount; i++) {
        float mark;
        while (true) {
            cout << "Enter marks for Quiz " << i + 1 << " out of 10: ";
            cin >> mark;
            if (mark >= 0 && mark <= 10) {
                students[studentCount].quizzes[i] = mark;
                break;
            }
            else {
                cout << "Invalid marks! Try again. \n";
            }
        }
    }
    students[studentCount].quizCount = qcount;

    //doing the same for assignments now excep thtere are no fixed marks. user tells the total marks for each assignment
    int acount = 0;
    cout << "Enter the number of total assignments: ";
    cin >> acount;
    int assignmentTotal[10];
    int assignmentSum = 0;
    for (int i = 0; i < acount; i++) {
        cout << "Total marks for Assignment " << i + 1 << " : ";
        cin >> assignmentTotal[i];
        assignmentSum += assignmentTotal[i];

        float mark;
        while (true) {
            cout << "Enter marks for Assignment " << i + 1 << " (0-" << assignmentTotal[i] << "): ";
            cin >> mark;
            if (mark >= 0 && mark <= assignmentTotal[i]) {
                students[studentCount].assignments[i] = mark;
                break;
            }
            else {
                cout << "Invalid marks! Try again.\n";
            }
        }
    }
    students[studentCount].assignmentTotalMarks = assignmentSum;
    students[studentCount].assignmentCount = acount;
    
    //inputting total marks for mids and taking input for obtained marks and storing that
    int midmax;
    cout << "Total Mid Marks: ";
    cin >> midmax;

    while (true) {
        float mark;
        cout << "Enter Midterm marks (0-" << midmax << "): ";
        cin >> mark;
        if (mark >= 0 && mark <= midmax) {
            students[studentCount].mid = mark;
            break;
        }
        else {
            cout << "Invalid marks! Try again.\n";
        }
    }
    students[studentCount].midTotal = midmax;

    //marks for final exams (total is fixed at 100)
    while (true) {
        float mark;
        cout << "Enter Final marks (0-100): ";
        cin >> mark;
        if (mark >= 0 && mark <= 100) {
            students[studentCount].final = mark;
            break;
        }
        else {
            cout << "Invalid marks! Try again.\n";
        }
    }
    result(studentCount);

    //incrementing student count after the student has been successfully added
    studentCount++;
    cout << "Student added successfully!\n\n";
}
//assigning grades based on total percentage.
char grade(float percentage) {
    if (percentage >= 85)
        return 'A';
    else if (percentage >= 75)
        return 'B';
    else if (percentage >= 65)
        return 'C';
    else if (percentage >= 50)
        return 'D';
    else return 'F';
}
//summing up all the marks with the correct weightages to produce the totak percentage
void result(int index) {
    float qsum = 0.0;  
    float asum = 0.0; 

    for (int i = 0; i < students[index].assignmentCount; i++) {
        asum += students[index].assignments[i];
    }
    for (int i = 0; i < students[index].quizCount; i++) {
        qsum += students[index].quizzes[i];
    }
    float qpercent = (qsum / (students[index].quizCount * 10)) * 10; //10% total weightage for quizzes
    float apercent = (asum / students[index].assignmentTotalMarks) * 10; //10 for assignments
    float midpercent = (students[index].mid / students[index].midTotal) * 30; //30 for mid exam
    float finalpercent = (students[index].final / 100) * 50; //50 for final
    students[index].percentage = qpercent + apercent + midpercent + finalpercent;

    students[index].grade = grade(students[index].percentage);

}
void searchStudent() {
    if (studentCount == 0) {
        cout << "No students to search.\n";
        return;
    }
    char roll[20];
    cin.ignore();
    cout << "Enter Roll No to search: ";
    cin.getline(roll, 20);

    //comparing roll number and if its found then student details are displayed
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].roll, roll) == 0) {
            cout << "\nStudent Found:\n";
            cout << "Roll: " << students[i].roll << "\n";
            cout << "Name: " << students[i].name << "\n";
            cout << "Section: " << students[i].section << "\n";
            cout << "Percentage: " << students[i].percentage << "\n";
            cout << "Grade: " << students[i].grade << "\n\n";
            found = true;
            break; //break out of the loop once the student is found
        }
    }
    if (!found) {
        cout << "Student with Roll No " << roll << " not found.\n";
    }
}
void deleteStudent() {
    if (studentCount == 0) {
        cout << "No students to delete.\n";
        return;
    }
    char roll[20];
    cin.ignore();
    cout << "Enter Roll No to delete: ";
    cin.getline(roll, 20);

    // initialised t0 -1 so if the student is not found the -1 serves as a flag as there is no -1 index in an array
    int index = -1;

    //if student is found its index is stored
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].roll, roll) == 0) {
            index = i;
            break;
        }
    }
    //index not being -1 means its >=0 so the roll number was present in the record
    if (index != -1) {
        //shifting all students one index up so there are no empty gaps after the deletion
        for (int i = index; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;  //decrementing total count after the student is deleted
        cout << "Student deleted successfully.\n";
    }
    else {
        cout << "Student with Roll No " << roll << " not found.\n";
    }
}
void updateStudent() {
    if (studentCount == 0) {
        cout << "No data.\n";
        return;
    }
    cin.ignore();
    char roll[20];
    cout << "Enter Roll to update: ";
    cin.getline(roll, 20);

    //taking all inputs again and updating the student record
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].roll, roll) == 0) {
            cout << "New Name: ";
            cin.getline(students[i].name, 100);
            cout << "New Section: ";
            cin.getline(students[i].section, 20);

            int qcount;
            cout << "Quizzes: ";
            cin >> qcount;
            students[i].quizCount = qcount;
            for (int q = 0; q < qcount; q++) {
                float mark;
                while (true) {
                    cout << "Quiz " << q + 1 << " (0-10): ";
                    cin >> mark;
                    if (mark >= 0 && mark <= 10) {
                        students[i].quizzes[q] = mark;
                        break;
                    }
                    cout << "Invalid!\n";
                }
            }
            int acount;
            cout << "Assignments: ";
            cin >> acount;
            students[i].assignmentCount = acount;

            int sum = 0;
            for (int a = 0; a < acount; a++) {
                int maxM;
                cout << "Assignment " << a + 1 << " total: ";
                cin >> maxM;
                sum += maxM;

                float mark;
                while (true) {
                    cout << "Marks (0-" << maxM << "): ";
                    cin >> mark;
                    if (mark >= 0 && mark <= maxM) {
                        students[i].assignments[a] = mark;
                        break;
                    }
                    cout << "Invalid!\n";
                }
            }
            students[i].assignmentTotalMarks = sum;

            int midMax;
            cout << "Mid Total: ";
            cin >> midMax;
            students[i].midTotal = midMax;

            float midMark;
            while (true) {
                cout << "Mid Marks (0-" << midMax << "): ";
                cin >> midMark;
                if (midMark >= 0 && midMark <= midMax) {
                    students[i].mid = midMark;
                    break;
                }
                cout << "Invalid!\n";
            }
            float finalMark;
            while (true) {
                cout << "Final (0-100): ";
                cin >> finalMark;
                if (finalMark >= 0 && finalMark <= 100) {
                    students[i].final = finalMark;
                    break;
                }
                cout << "Invalid!\n";
            }
            result(i);
            cout << "Updated.\n";
            return;
        }
    }
    cout << "Not found.\n";
}

void fileSave() {
    //open file for writing
    ofstream outFile("students.txt");
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    //loop thru all the students stored
    for (int i = 0; i < studentCount; i++) {
        //writing stident details in the file
        outFile << students[i].roll << endl;
        outFile << students[i].name << endl;
        outFile << students[i].section << endl;

        //writing quiz details
        outFile << students[i].quizCount << endl;
        for (int j = 0; j < students[i].quizCount; j++) {
            outFile << students[i].quizzes[j] << " ";
        }
        outFile << endl;

        //assignment details
        outFile << students[i].assignmentCount << endl;
        outFile << students[i].assignmentTotalMarks << endl;
        for (int j = 0; j < students[i].assignmentCount; j++) {
            outFile << students[i].assignments[j] << " ";
        }
        outFile << endl;

        outFile << students[i].mid << endl;
        outFile << students[i].midTotal << endl;
        outFile << students[i].final << endl;
        outFile << students[i].percentage << endl;
        outFile << students[i].grade << endl;
    }
    outFile.close();
    cout << "All student records saved to file successfully." << endl;
}
void fileLoad() {
    //opening file for reading
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "File not found! No data loaded." << endl;
        return;
    }
    studentCount = 0;

    //loop till end of file
    while (!inFile.eof()) {
        inFile.getline(students[studentCount].roll, 20);
        if (strlen(students[studentCount].roll) == 0) break; 
        //roll number field being empty means no further records so breaking the loop

        inFile.getline(students[studentCount].name, 100);
        inFile.getline(students[studentCount].section, 20);
        inFile >> students[studentCount].quizCount;
        for (int j = 0; j < students[studentCount].quizCount; j++) {
            inFile >> students[studentCount].quizzes[j];
        }
        inFile >> students[studentCount].assignmentCount;
        inFile >> students[studentCount].assignmentTotalMarks;
        for (int j = 0; j < students[studentCount].assignmentCount; j++) {
            inFile >> students[studentCount].assignments[j];
        }
        inFile >> students[studentCount].mid;
        inFile >> students[studentCount].midTotal;
        inFile >> students[studentCount].final;
        inFile >> students[studentCount].percentage;
        inFile >> students[studentCount].grade;
        inFile.ignore();

        studentCount++;
    }
    inFile.close();
    cout << "All student records loaded from file successfully." << endl;
}
//function to sort students in descending order
void sortByPercentage() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].percentage < students[j + 1].percentage) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}
   void classReport() {
        if (studentCount == 0) {
            cout << "No students in the class." << endl;
            return;
        }
        sortByPercentage(); 

        float totalpercent = 0;
        float highest = students[0].percentage;
        float lowest = students[0].percentage;

        for (int i = 0; i < studentCount; i++) {
            totalpercent += students[i].percentage;
            if (students[i].percentage > highest) highest = students[i].percentage;
            if (students[i].percentage < lowest) lowest = students[i].percentage;
        }
        float classAverage = totalpercent / studentCount;

        cout << fixed << setprecision(2);
        cout << "\n=== Class Report ===" << endl;
        cout << "Class Average Percentage: " << classAverage << "%" << endl;
        cout << "Highest Percentage: " << highest << "%" << endl;
        cout << "Student(s) with Highest Percentage: ";
        for (int i = 0; i < studentCount; i++) {
            if (students[i].percentage == highest)
                cout << students[i].name << " ";
        }
        cout << endl;

        cout << "Lowest Percentage: " << lowest << "%" << endl;
        cout << "Student(s) with Lowest Percentage: ";
        for (int i = 0; i < studentCount; i++) {
            if (students[i].percentage == lowest)
                cout << students[i].name << " ";
        }
        cout << endl;
        subjectStats();
    }
  void displayAll() {
        if (studentCount == 0) {
            cout << "No students to display." << endl;
            return;
        }
        sortByPercentage();

        cout << fixed << setprecision(2);
        cout << setw(5) << "No"
            << setw(15) << "Roll"
            << setw(25) << "Name"
            << setw(10) << "Section"
            << setw(12) << "Percentage"
            << setw(8) << "Grade" << endl;
        cout << string(75, '-') << endl;

        for (int i = 0; i < studentCount; i++) {
            cout << setw(5) << (i + 1)
                << setw(15) << students[i].roll
                << setw(25) << students[i].name
                << setw(10) << students[i].section
                << setw(12) << students[i].percentage
                << setw(8) << students[i].grade
                << endl;
        }
   }
  void subjectStats() {
      if (studentCount == 0) {
          cout << "No students available.\n";
          return;
      }
      float totalQuiz = 0, totalAssign = 0, totalMid = 0, totalFinal = 0;
      int quizCount = 0, assignPossible = 0, midPossible = 0;

      for (int i = 0; i < studentCount; i++) {
          for (int q = 0; q < students[i].quizCount; q++) {
              totalQuiz += students[i].quizzes[q];
              quizCount++;
          }
          for (int a = 0; a < students[i].assignmentCount; a++) {
              totalAssign += students[i].assignments[a];
          }
          assignPossible += students[i].assignmentTotalMarks;

          totalMid += students[i].mid;
          midPossible += students[i].midTotal;
          totalFinal += students[i].final;
      }
      cout << fixed << setprecision(2);
      cout << "\n=== Subject-Wise Statistics ===\n";
      cout << "Average Quiz Score:       " << (totalQuiz / quizCount) << "/10\n";
      cout << "Average Assignment Score: " << (totalAssign / studentCount) << "\n";
      cout << "Average Midterm Marks:    " << (totalMid / studentCount) << "\n";
      cout << "Average Final Marks:      " << (totalFinal / studentCount) << "\n";
  }

  int main() {
      fileLoad();
      mainMenu();
      fileSave();

      return 0;
  }