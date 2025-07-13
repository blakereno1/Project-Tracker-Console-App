// Full Name: Blake Reno
// Class: ITCS 2530 – C++ Programming
// GitHub Repo URL: https://github.com/blakereno1/Project-Tracker-Console-App
// One-Sentence Summary: Console app for tracking cosplay/costume build projects.
// Your posted hobby or interest: Costume and cosplay building, electronics tinkering, and 3D printing
// AI Tool(s) Used: ChatGPT (OpenAI, GPT-4)

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

const int MAX_PROJECTS = 50;

struct Project {
    string name;
    string startDate;
    string dueDate;
    string status;
    int hoursAllocated;
    int hoursCompleted;
    string priority;
    string notes;
};

class Reminder {
private:
    string message;
public:
    Reminder(string msg) : message(msg) {}
    void show() {
        cout << "\n[Reminder] " << message << endl;
    }
};

class ProjectManager {
private:
    Project projects[MAX_PROJECTS];
    int projectCount;

    Project getProjectInput();
    void printProjectList() const;

public:
    ProjectManager() : projectCount(0) {}

    void displayMenu();
    void addProject();
    void listProjects() const;
    void updateStatus();
    void saveToFile() const;
    void loadFromFile();
};

void ProjectManager::displayMenu() {
    int choice;
    do {
        cout << "\n===========================================\n";
        cout << "         COSPLAY PROJECT TRACKER           \n";
        cout << "===========================================\n";
        cout << "[1]  Add New Project\n";
        cout << "[2]  View All Projects\n";
        cout << "[3]  Edit a Project\n";
        cout << "[4]  Delete a Project\n";
        cout << "[5]  Update Project Status\n";
        cout << "[6]  Archive Completed Projects\n";
        cout << "[7]  Export Projects to CSV (Excel)\n";
        cout << "[8]  Save Projects to File\n";
        cout << "[9]  Load Projects from File\n";
        cout << "[0]  Exit\n";
        cout << "===========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addProject(); break;
        case 2:
            listProjects(); break;
        case 5:
            updateStatus(); break;
        case 8:
            saveToFile(); break;
        case 9:
            loadFromFile(); break;
        case 0:
            cout << "Exiting program...\n"; break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

Project ProjectManager::getProjectInput() {
    Project p;
    cin.ignore();
    cout << "Enter project name: ";
    getline(cin, p.name);
    cout << "Enter start date (MM/DD/YYYY): ";
    getline(cin, p.startDate);
    cout << "Enter due date (MM/DD/YYYY): ";
    getline(cin, p.dueDate);
    cout << "Enter hours allocated: ";
    cin >> p.hoursAllocated;
    cout << "Enter hours completed: ";
    cin >> p.hoursCompleted;
    cin.ignore();
    cout << "Enter priority (Low/Medium/High): ";
    getline(cin, p.priority);
    cout << "Enter notes/tags: ";
    getline(cin, p.notes);
    p.status = "Not Started";
    return p;
}

void ProjectManager::addProject() {
    if (projectCount >= MAX_PROJECTS) {
        cout << "Project limit reached.\n";
        return;
    }
    projects[projectCount] = getProjectInput();
    Reminder r("Project \"" + projects[projectCount].name + "\" added to schedule.");
    r.show();
    projectCount++;
}

void ProjectManager::printProjectList() const {
    for (int i = 0; i < projectCount; ++i) {
        cout << "\nProject #" << (i + 1) << ":\n";
        cout << "Name: " << projects[i].name << endl;
        cout << "Start Date: " << projects[i].startDate << endl;
        cout << "Due Date: " << projects[i].dueDate << endl;
        cout << "Status: " << projects[i].status << endl;
        cout << "Hours: " << projects[i].hoursCompleted << "/" << projects[i].hoursAllocated << endl;
        cout << "Priority: " << projects[i].priority << endl;
        cout << "Notes: " << projects[i].notes << endl;
    }
}

void ProjectManager::listProjects() const {
    if (projectCount == 0) {
        cout << "No projects to show.\n";
        return;
    }
    printProjectList();
}

void ProjectManager::updateStatus() {
    if (projectCount == 0) {
        cout << "No projects available.\n";
        return;
    }
    int index;
    cout << "Enter project number (1 to " << projectCount << "): ";
    cin >> index;
    if (index < 1 || index > projectCount) {
        cout << "Invalid project number.\n";
        return;
    }
    cin.ignore();
    cout << "Enter new status (e.g., In Progress, Completed): ";
    getline(cin, projects[index - 1].status);
    Reminder r("Status updated for \"" + projects[index - 1].name + "\".");
    r.show();
}

void ProjectManager::saveToFile() const {
    ofstream outFile("projects.txt");
    for (int i = 0; i < projectCount; ++i) {
        outFile << projects[i].name << endl
            << projects[i].startDate << endl
            << projects[i].dueDate << endl
            << projects[i].status << endl
            << projects[i].hoursAllocated << endl
            << projects[i].hoursCompleted << endl
            << projects[i].priority << endl
            << projects[i].notes << endl;
    }
    outFile.close();
    cout << "Projects saved to projects.txt\n";
}

void ProjectManager::loadFromFile() {
    ifstream inFile("projects.txt");
    if (!inFile) {
        cout << "No saved file found.\n";
        return;
    }
    projectCount = 0;
    while (getline(inFile, projects[projectCount].name)) {
        getline(inFile, projects[projectCount].startDate);
        getline(inFile, projects[projectCount].dueDate);
        getline(inFile, projects[projectCount].status);
        inFile >> projects[projectCount].hoursAllocated;
        inFile >> projects[projectCount].hoursCompleted;
        inFile.ignore();
        getline(inFile, projects[projectCount].priority);
        getline(inFile, projects[projectCount].notes);
        projectCount++;
    }
    inFile.close();
    cout << "Projects loaded from projects.txt\n";
}

int main() {
    ProjectManager manager;
    manager.displayMenu();
    return 0;
}
