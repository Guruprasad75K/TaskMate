#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

struct todo {
    int id;
    char title[40];
    int deadLine[3];  
    bool isDone;     
};

int daysRemaining(int deadline[3]) {
    time_t now = time(NULL);
    struct tm *today = localtime(&now);

    struct tm deadlineDate = {0};
    deadlineDate.tm_mday = deadline[0];    
    deadlineDate.tm_mon = deadline[1] - 1; 
    deadlineDate.tm_year = deadline[2] - 1900; 

    time_t deadlineTime = mktime(&deadlineDate);
    time_t todayTime = mktime(today);

    double diff = difftime(deadlineTime, todayTime);
    int days = diff / (60 * 60 * 24);

    return days;
}

int main() {
    struct todo list[100];
    int select, n = 0, i, toDelete, extend, markDone;
    char temp[40];

    while (true) {
        printf("1. Add ToDo 2. Mark ToDo as Done 3. Delete ToDo 4. Extend Deadline 5. Exit\n");
        printf("Select Operation: ");
        scanf("%d", &select);

        if (select == 1) {
            list[n].id = n + 1;
            printf("Enter title: ");
            scanf("%s", temp);
            strcpy(list[n].title, temp);
            printf("Enter deadline in DD MM YYYY format: ");
            scanf("%d %d %d", &list[n].deadLine[0], &list[n].deadLine[1], &list[n].deadLine[2]);
            list[n].isDone = false; 
            n++;
        } 
        else if (select == 2) {
            printf("Enter the ID of the Task to mark as done: ");
            scanf("%d", &markDone);
            if (markDone > 0 && markDone <= n) {
                list[markDone - 1].isDone = true; 
            } else {
                printf("Invalid Task ID\n");
            }
        } 
        else if (select == 3) {
            printf("Enter the ID of the Task to be deleted: ");
            scanf("%d", &toDelete);
            if (toDelete > 0 && toDelete <= n) {
                n -= 1;
                for (i = toDelete - 1; i < n; i++) {
                    list[i] = list[i + 1];
                }
            } else {
                printf("Invalid Input\n");
            }
        } 
        else if (select == 4) {
            printf("Enter the ID of the task to extend: ");
            scanf("%d", &extend);
            if (extend > 0 && extend <= n) {
                printf("Enter new deadline in DD MM YYYY format: ");
                scanf("%d %d %d", &list[extend - 1].deadLine[0], &list[extend - 1].deadLine[1], &list[extend - 1].deadLine[2]);
            } else {
                printf("Invalid Task ID\n");
            }
        } 
        else if (select == 5) {
            break;
        } 
        else {
            printf("Invalid Input\n");
        }

        for (i = 0; i < n; i++) {
            int daysLeft = daysRemaining(list[i].deadLine);
            printf("%d. %s - Days remaining: %d", list[i].id, list[i].title, daysLeft);
            if (list[i].isDone) {
                printf(" ->Completed");
            }
            printf("\n");
        }
    }
    return 0;
}
