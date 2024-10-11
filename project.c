//Workplace Clearance System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declare named expressions
#define MAX_STAFF 150
#define NAME_LENGTH 50
#define CLEARANCE_LEVELS 15
#define MAX_REQUESTS 50

//Create new name for existing data types
typedef struct {
    int id;
    char name[NAME_LENGTH];
    int clearanceLevel;
} Staff;

//Create new name for existing data types
typedef struct {
    int staffId;
    int clearanceLevel;
    char status[10]; 
    // "pending", "approved", or "rejected"
} ClearanceRequest;

void addStaff(Staff staff[], int *count) {
    if (*count >= MAX_STAFF) {
        printf("Maximum staff limit reached.\n");
        return;
    }

    Staff newStaff;
    newStaff.id = *count + 1;

    printf("Enter name: ");
    scanf("%s", newStaff.name);

    printf("Enter clearance level (1-%d): ", CLEARANCE_LEVELS);
    scanf("%d", &newStaff.clearanceLevel);

    staff[*count] = newStaff;
    (*count)++;
    printf("Staff added successfully!\n");
}

void removeStaff(Staff staffs[], int *count, int id) {
    int found = 0;

    for (int i = 0; i < *count; i++) {
        if (staffs[i].id == id) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                staffs[j] = staffs[j + 1];
            }
            (*count)--;
            printf("Staff removed successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Staff not found.\n");
    }
}

void viewStaffs(Staff staff[], int count) {
    if (count == 0) {
        printf("No staffs to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Clearance Level: %d\n", staff[i].id, staff[i].name, staff[i].clearanceLevel);
    }
}

void requestClearance(ClearanceRequest requests[], int *count, Staff staff[], int staffId, int clearanceLevel) {
    if (*count >= MAX_REQUESTS) {
        printf("Maximum clearance requests reached.\n");
        return;
    }

    ClearanceRequest newRequest;
    newRequest.staffId = staffId;
    newRequest.clearanceLevel = clearanceLevel;
    strcpy(newRequest.status, "pending");

    requests[*count] = newRequest;
    (*count)++;
    printf("Clearance request submitted successfully!\n");
}

void viewRequests(ClearanceRequest requests[], int count) {
    if (count == 0) {
        printf("No clearance requests to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("STAFF ID: %d, Clearance Level: %d, Status: %s\n", requests[i].staffId, requests[i].clearanceLevel, requests[i].status);
    }
}

void processRequest(ClearanceRequest requests[], int *count, int requestId, char *status) {
    if (requestId < 0 || requestId >= *count) {
        printf("Clearance request not found.\n");
        return;
    }

    strcpy(requests[requestId].status, status);
    printf("Clearance request %d updated to %s.\n", requestId, status);
}

void menu() {
    Staff staffs[MAX_STAFF];
    int staffCount = 0;
    ClearanceRequest requests[MAX_REQUESTS];
    int requestCount = 0;
    int choice, id, clearanceLevel, requestId;
    char status[10];

    while (1) {
        printf("\n  *--------------------------------------------------------------------------* \n");
        printf("\n  *---------------------- WELCOME TO MAMBO LEO COMPANY ----------------------* \n");
        printf("\n  *--------------------------------------------------------------------------* \n");
        printf("\n   |********************** Menu: ************************|\n");
        printf("         1. Add Staff\n");
        printf("         2. Remove Staff\n");
        printf("         3. View Staffs\n");
        printf("         4. Request Clearance\n");
        printf("         5. View Clearance Requests\n");
        printf("         6. Process Clearance Request\n");
        printf("         7. Exit\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        //Switch Statement
        switch (choice) {        
            case 1:
                addStaff(staffs, &staffCount);
                break;
            case 2:
                printf("Enter staff ID to remove: ");
                scanf("%d", &id);
                removeStaff(staffs, &staffCount, id);
                break;
            case 3:
                viewStaffs(staffs, staffCount);
                break;
            case 4:
                printf("Enter staff ID: ");
                scanf("%d", &id);
                printf("Enter clearance level (1-%d): ", CLEARANCE_LEVELS);
                scanf("%d", &clearanceLevel);
                requestClearance(requests, &requestCount, staffs, id, clearanceLevel);
                break;
            case 5:
                viewRequests(requests, requestCount);
                break;
            case 6:
                printf("Enter request ID to process: ");
                scanf("%d", &requestId);
                printf("Enter new status (approved/rejected): ");
                scanf("%s", status);
                processRequest(requests, &requestCount, requestId, status);
                break;
            case 7:
                exit(0);
            default:
                printf("Please select a valid option and attempt again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
