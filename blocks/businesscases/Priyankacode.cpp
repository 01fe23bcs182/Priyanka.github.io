//JOB VACANCY DATABASE MANAGEMENT USING QUICK SORT

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure to hold job details
struct Job {
    string industry;
    double salary;
    string requiredSkill;
};

// Function to partition the array
int partition(vector<Job>& jobs, int low, int high) {
    double pivot = jobs[high].salary;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (jobs[j].salary <= pivot) {
            i++;
            swap(jobs[i], jobs[j]);
        }
    }
    swap(jobs[i + 1], jobs[high]);
    return i + 1;
}

// Quick Sort implementation
void quickSort(vector<Job>& jobs, int low, int high) {
    if (low < high) {
        int pi = partition(jobs, low, high);
        quickSort(jobs, low, pi - 1);
        quickSort(jobs, pi + 1, high);
    }
}

// Function to display the jobs
void displayJobs(const vector<Job>& jobs) {
    for (const auto& job : jobs) {
        cout << "Industry: " << job.industry
             << ", Salary: " << job.salary
             << ", Required Skill: " << job.requiredSkill << endl;
    }
}

int main() {
    vector<Job> jobs = {
        {"IT", 70000, "C++"},
        {"Healthcare", 50000, "Nursing"},
        {"Education", 40000, "Teaching"},
        {"Finance", 60000, "Accounting"},
        {"Retail", 30000, "Sales"}
    };

    cout << "Before Sorting:" << endl;
    displayJobs(jobs);

    quickSort(jobs, 0, jobs.size() - 1);

    cout << "\nAfter Sorting by Salary:" << endl;
    displayJobs(jobs);

    return 0;
}

//JOB VACANCY DATABASE MANAGEMENT USING MERGE SORT
#include <iostream>
#include <vector>
using namespace std;

struct Job {
    int id;
    string industry;
    int salary;
    string requiredSkills;
};

void merge(vector<Job> &jobs, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Job> leftArr(n1), rightArr(n2);
    for (int i = 0; i < n1; i++) leftArr[i] = jobs[left + i];
    for (int i = 0; i < n2; i++) rightArr[i] = jobs[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].salary <= rightArr[j].salary) {
            jobs[k++] = leftArr[i++];
        } else {
            jobs[k++] = rightArr[j++];
        }
    }
    while (i < n1) jobs[k++] = leftArr[i++];
    while (j < n2) jobs[k++] = rightArr[j++];
}

void mergeSort(vector<Job> &jobs, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(jobs, left, mid);
        mergeSort(jobs, mid + 1, right);
        merge(jobs, left, mid, right);
    }
}

void displayJobs(const vector<Job> &jobs) {
    for (const auto &job : jobs) {
        cout << "ID: " << job.id << ", Industry: " << job.industry
             << ", Salary: " << job.salary
             << ", Skills: " << job.requiredSkills << endl;
    }
}

int main() {
    vector<Job> jobs;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        Job job;
        cin >> job.id >> job.industry >> job.salary >> job.requiredSkills;
        jobs.push_back(job);
    }

    mergeSort(jobs, 0, jobs.size() - 1);
    displayJobs(jobs);

    return 0;}





//ECONOMIC INEQUALITY REPORTING USING WARSHALL'S
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define INF 1000000  // Representing no direct connection

// Warshall's Algorithm for finding the transitive closure
void warshallAlgorithm(int** graph, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][k] != INF && graph[k][j] != INF) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }
}

// BFS for exploring economic connections (e.g., job availability)
void bfs(int** graph, int n, int start) {
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal (Job Availability from Region " << start << "): ";
    while (!q.empty()) {
        int region = q.front();
        q.pop();
        cout << region << " ";

        for (int i = 0; i < n; i++) {
            if (!visited[i] && graph[region][i] != INF) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of regions: ";
    cin >> n;

    // Dynamically allocate the graph
    int** graph = new int*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
    }

    cout << "Enter the adjacency matrix (use " << INF << " for no direct connection):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    // Apply Warshall's Algorithm
    warshallAlgorithm(graph, n);

    cout << "\nTransitive Closure (Economic Connections Matrix):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INF) cout << "INF ";
            else cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    // BFS Traversal from a specific region
    int startRegion;
    cout << "Enter the starting region for BFS: ";
    cin >> startRegion;
    bfs(graph, n, startRegion);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}
