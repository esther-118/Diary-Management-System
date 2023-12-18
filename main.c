#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIMIT 20

int welcome() { // a welcome msg and ask what they want to do
    printf("    -Hello and welcome to Diary Management System-\n");
    printf("    Here are your options:\n");
    printf("    [1] Create a new entry\n");
    printf("    [2] Search for an existing entry\n");
    printf("    [3] Delete an existing entry\n");
    printf("    [4] Exit\n");

    int userAnswer = 1;
    scanf("%d", &userAnswer);
    if (userAnswer != 1 || userAnswer != 2 || userAnswer != 3 || userAnswer != 4) { // if input is not between 1 and 3:
        while (userAnswer != 1 && userAnswer != 2 && userAnswer != 3 && userAnswer != 4) {
            printf("Please type 1, 2, 3, or 4.\n");
            scanf("%d", &userAnswer);
        }
    }
    return userAnswer;
}

void view(char name[20]) {
    FILE *fp;
    fp = fopen ("gojo", "r");
    if(!fp){
        printf("\n Unable to open : %s ", name);
    }
    char line[500];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line); 
    }
    fclose(fp);
}

int createEntry() {
    printf("    Creating a new entry...\n");
    printf("    Enter the name of the event: \n");
    char name[20];
    scanf("%s", name);
    strcat(name, ".txt");
    
    FILE *fp;
    fp = fopen (name, "w");
    
    printf("    Enter the date of the event(yyyy-mm-dd): \n");
    char date[20];
    scanf("%s", date);
    fprintf(fp, date);
    
    printf("    Enter the location of the event: \n");
    char location[20];
    scanf("%s", location);
    fprintf(fp, "\n");
    fprintf(fp, location);
    
    printf("    Enter the duration of the event: \n");
    char duration[20];
    scanf("%s", duration);
    fprintf(fp, "\n");
    fprintf(fp, duration);
    
    printf("    Entry created...\n");
    char arr[3][20] = {"date", "location", "duration"};
    int i = 0;
    
    fclose(fp);
    FILE *file;
    
    file = fopen (name, "r");
    char line[20];
    while(fgets(line, 100, file)){
        printf("%s %s", arr[i++], line);
    }
    //view(name);
    return 1;
}

int main() {
    int userAnswer = welcome();
    if (userAnswer == 1) createEntry();
    if (userAnswer == 4) exit(0);
    return 0;
}