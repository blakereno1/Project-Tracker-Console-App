// Full Name: Blake Reno
// Class: ITCS 2530 – C++ Programming
// GitHub Repo URL: https://github.com/your-username/cosplay-tracker
// One-Sentence Summary: Console app for tracking cosplay/costume build projects.
// Your posted hobby or interest: Costume and cosplay building, electronics tinkering, and 3D printing
// AI Tool(s) Used: ChatGPT (OpenAI, GPT-4)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// Struct to hold cosplay project details
struct Project {
    string name;
    string dueDate;
    string status;
    int hoursAllocated;
};

// Class to handle simple reminders
class Reminder {
private:
    string message;
public:
    Reminder(string msg) {
        message = msg;
    }
    void show() {
        cout << "\n[Reminder] " << message << endl;
    }
};

// Function prototypes
void addProject(Project projects[], int& count);
void listProjects(const Project projects[], int count);
void updateStatus(Project projects[], int count);
void saveToFile(const Project projects[], int count);
void loadFromFile(Project projects[], int& count);

const int MAX_PROJECTS = 50;

int main() {
    Project projects[MAX_PROJECTS];
    int projectCount = 0;
    int choice;

    do {
        cout << "\n--- Cosplay Project Tracker ---\n";
        cout << "1. Add New Project\n";
        cout << "2. View All Projects\n";
        cout << "3. Update Project Status\n";
        cout << "4. Save Projects to File\n";
        cout << "5. Load Projects from File\n";
        cout << "6. Exit\n";
        cout << "Enter choice (1-6): ";
        cin >> choice;

        switch (choice) {
        case 1:
            addProject(projects, projectCount);
            break;
        case 2:
            listProjects(projects, projectCount);
            break;
        case 3:
            updateStatus(projects, projectCount);
            break;
        case 4:
            saveToFile(projects, projectCount);
            break;
        case 5:
            loadFromFile(projects, projectCount);
            break;
        case 6:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

// Add a new project
void addProject(Project projects[], int& count) {
    if (count >= MAX_PROJECTS) {
        cout << "Project limit reached.\n";
        return;
    }

    cin.ignore(); // clear newline
    cout << "Enter project name: ";
    getline(cin, projects[count].name);
    cout << "Enter estimated completion date (MM/DD/YYYY): ";
    getline(cin, projects[count].dueDate);
    cout << "Enter hours allocated: ";
    cin >> projects[count].hoursAllocated;
    projects[count].status = "Not Started";

    Reminder r("Project \"" + projects[count].name + "\" added to schedule.");
    r.show();

    count++;
}

// List all projects
void listProjects(const Project projects[], int count) {
    if (count == 0) {
        cout << "No projects to show.\n";
        return;
    }

    cout << left << setw(20) << "Project Name" << setw(15) << "Due Date"
        << setw(10) << "Hours" << setw(15) << "Status" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(20) << projects[i].name
            << setw(15) << projects[i].dueDate
            << setw(10) << projects[i].hoursAllocated
            << setw(15) << projects[i].status << endl;
    }
}

// Update status of a project
void updateStatus(Project projects[], int count) {
    if (count == 0) {
        cout << "No projects available.\n";
        return;
    }

    cout << "Enter project number (1 to " << count << "): ";
    int index;
    cin >> index;
    if (index < 1 || index > count) {
        cout << "Invalid project number.\n";
        return;
    }

    cin.ignore(); // clear newline
    cout << "Enter new status (e.g., In Progress, Completed): ";
    getline(cin, projects[index - 1].status);

    Reminder r("Status updated for \"" + projects[index - 1].name + "\".");
    r.show();
}

// Save projects to file
void saveToFile(const Project projects[], int count) {
    ofstream outFile("projects.txt");
    for (int i = 0; i < count; i++) {
        outFile << projects[i].name << endl
            << projects[i].dueDate << endl
            << projects[i].status << endl
            << projects[i].hoursAllocated << endl;
    }
    outFile.close();
    cout << "Projects saved to projects.txt\n";
}

// Load projects from file
void loadFromFile(Project projects[], int& count) {
    ifstream inFile("projects.txt");
    if (!inFile) {
        cout << "No saved file found.\n";
        return;
    }

    count = 0;
    while (getline(inFile, projects[count].name)) {
        getline(inFile, projects[count].dueDate);
        getline(inFile, projects[count].status);
        inFile >> projects[count].hoursAllocated;
        inFile.ignore(); // skip newline after int
        count++;
    }
    inFile.close();
    cout << "Projects loaded from projects.txt\n";
}
