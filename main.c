#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIMIT 20

char data[20] = "data.txt";

int welcome() { // a welcome msg and ask what they want to do
    printf("    -Hello and welcome to Diary Management System-\n");
    printf("    Here are your options:\n");
    printf("    [1] Create a new entry\n");
    printf("    [2] Search for an existing entry\n");
    printf("    [3] Delete an existing entry\n");
    printf("    [4] Exit\n\n");

    int userAnswer = 1;
    scanf("    %d", &userAnswer);
    if (userAnswer != 1 || userAnswer != 2 || userAnswer != 3 || userAnswer != 4) { // if input is not between 1 and 3:
        while (userAnswer != 1 && userAnswer != 2 && userAnswer != 3 && userAnswer != 4) {
            printf("    WARNING: Please type 1, 2, 3, or 4.\n\n");
            scanf("%d", &userAnswer);
        }
    }
    return userAnswer;
}

void view() {
    FILE *fp;
    fp = fopen (data, "r");
    if(!fp){
        printf("\n Unable to open : %s ", data);
    }
    char line[20];
    char arr[4][20] = {"Name: ", " Date: ", " Location: ", " Duration: "};
    int i = 0;
    fgets(line, 100, fp);
    while(fgets(line, 100, fp)){
        char *ptr = line;
        int i = 0;
        printf(arr[i++]);
        while (*ptr != '\0') {
            if (*ptr == '/') {
                printf(arr[i++]);
            }
            else {
                printf("%c", *ptr);
            }
            ptr++;
        }
    }
    //while(fgets(line, 100, fp)){
        //printf("%*s %s", 20, arr[i++], line);
    //}
    fclose(fp);
}

void delete() {
    FILE *fileptr1, *fileptr2;
    char filename[20] = "data.txt";
    char ch;
    int delete_line, temp = 1;

    printf("Enter file name: ");
    //open file in read mode
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
   while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    //rewind
    rewind(fileptr1);
    printf(" \n Enter line number of the line to be deleted:");
    scanf("%d", &delete_line);
    //open new file in write mode
    fileptr2 = fopen("replica.c", "w");
    ch = 'A';
    while (ch != EOF)
    {
        ch = getc(fileptr1);
        //except the line to be deleted
        if (temp != delete_line)
        {
            //copy all lines in file replica.c
            putc(ch, fileptr2);
        }
        if (ch == '\n')
        {
            temp++;
        }
    }
    fclose(fileptr1);
    fclose(fileptr2);
    remove(filename);
    //rename the file replica.c to original name
    rename("replica.c", filename);
    printf("\n The contents of file after being modified are as follows:\n");
    fileptr1 = fopen(filename, "r");
    ch = getc(fileptr1);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fileptr1);
    }
    fclose(fileptr1);
}

int createEntry() {
    printf("    Creating a new entry...\n\n");
    printf("    Enter the name of the event: \n\n");
    char name[20];
    scanf("%s", name);
    //strcat(name, ".txt");
    
    FILE *fp;
    fp = fopen (data, "a");
    
    fprintf(fp, name);
    fprintf(fp, "/");

    printf("    Enter the date of the event(yyyy-mm-dd): \n\n");
    char date[20];
    scanf("%s", date);
    fprintf(fp, date);
    
    printf("    Enter the location of the event: \n\n");
    char location[20];
    scanf("%s", location);
    fprintf(fp, "/");
    fprintf(fp, location);
    
    printf("    Enter the duration of the event: \n\n");
    char duration[20];
    scanf("%s", duration);
    fprintf(fp, "/");
    fprintf(fp, duration);
    fprintf(fp, "\n");
    
    printf("    Entry created...\n\n");
    fclose(fp);

    view(data);
    return 1;
}

int main() {
    int userAnswer = welcome();
    if (userAnswer == 1) createEntry();
    if (userAnswer == 2) {
        view(data);
    }
    if (userAnswer == 3) delete();
    if (userAnswer == 4) exit(0);
    return 0;
}