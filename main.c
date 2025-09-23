#include<stdio.h>
#include<string.h>
int readCSV(){
    FILE *fp = fopen("main.csv", "r");
    if (fp == NULL) {
        printf("File not found. Creating a new one...\n");
        fp = fopen("main.csv", "w");
        if (fp == NULL) {
            printf("Error: cannot create main.csv\n");
            return 0;
        }
        fprintf(fp, "Name,Title,Borrow Date,Return Date\n");
    } else {
        printf("File opened successfully!\n");
    }
    fclose(fp);
    return 1;
}

int saveCSV(char *name, char *title, char *B_date, char *R_date){
    FILE *fp = fopen("main.csv", "a");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 0;
    }
    fprintf(fp, "%s,%s,%s,%s\n", name, title, B_date, R_date);
    fclose(fp);
    return 1;
}

int add_new(){
    char name[50];
    char title[50];
    char B_date[20];
    char R_date[20];

    printf("Please enter your name: ");
    scanf(" %[^\n]", name);
    printf("Please enter your Book's title: ");
    scanf(" %[^\n]", title);
    printf("Please enter the borrow date (YYYY-MM-DD): ");
    scanf(" %[^\n]", B_date);
    printf("Please enter the return date (YYYY-MM-DD): ");
    scanf(" %[^\n]", R_date);

    saveCSV(name, title, B_date, R_date);
    printf("Data added successfully!\n");
    return 1;
}
int display_all(){
    FILE *fp = fopen("main.csv", "r");
    if (fp == NULL) {
        printf("Cannot open the file\n");
        return 0;
    }
    char line[200];
    int row = 0;
    printf("\n================ Borrowed Books List ================\n");
    printf("%-20s %-20s %-15s %-15s\n", "Name", "Title", "Borrow Date", "Return Date");
    printf("------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (row == 0) { 
            // ข้าม header เพราะเราเขียนไว้ในไฟล์แล้ว
            row++;
            continue;
        }
        char name[50], title[50], B_date[20], R_date[20];

        // แยกค่าด้วย comma
        sscanf(line, "%49[^,],%49[^,],%19[^,],%19[^\n]", name, title, B_date, R_date);

        printf("%-20s %-20s %-15s %-15s\n", name, title, B_date, R_date);
    }

    fclose(fp);
    return 1;
}

int search_ing(){
    FILE *fp = fopen("main.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    if (fp == NULL || temp == NULL) {
        printf("Cannot open file\n");
        return 0;
    }

    char keyword[50];
    char line[200];
    int found = 0;
    int row = 0;

    printf("Enter keyword (name/title/date): ");
    scanf(" %[^\n]", keyword);

    while (fgets(line, sizeof(line), fp)) {
        if (row == 0) {
            // เขียน header กลับไปใน temp ด้วย
            fprintf(temp, "%s", line);
            row++;
            continue;
        }

        if (strstr(line, keyword)) {
            found = 1;
            printf("\nFound record: %s", line);

            int choice;
            printf("\nWhat do you want to do?\n");
            printf("1. Update this record\n");
            printf("2. Delete this record\n");
            printf("3. Do nothing\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: { // Update
                    char newName[50], newTitle[50], newB[20], newR[20];
                    printf("Enter new name: ");
                    scanf(" %[^\n]", newName);
                    printf("Enter new book title: ");
                    scanf(" %[^\n]", newTitle);
                    printf("Enter new borrow date: ");
                    scanf(" %[^\n]", newB);
                    printf("Enter new return date: ");
                    scanf(" %[^\n]", newR);

                    fprintf(temp, "%s,%s,%s,%s\n", newName, newTitle, newB, newR);
                    printf("Record updated!\n");
                    break;
                }
                case 2: // Delete
                    printf("Record deleted!\n");
                    break;
                case 3: // Do nothing
                    fprintf(temp, "%s", line);
                    break;
                default:
                    printf("Invalid choice! Keeping the record as is.\n");
                    fprintf(temp, "%s", line);
                    break;
            }
        } else {
            // บรรทัดที่ไม่ตรง keyword → เขียนทับไปตามปกติ
            fprintf(temp, "%s", line);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        // แทนที่ main.csv ด้วย temp.csv
        remove("main.csv");
        rename("temp.csv", "main.csv");
    } else {
        printf("No record found with keyword: %s\n", keyword);
        remove("temp.csv"); // ไม่ต้องใช้แล้ว
    }

    return 1;
}
/*
int update(){

}
int del(){

}
*/
int menu(){
    char input[50];
    int fchoose ;
    do{
        printf("\n Hong Samutr Yindih Hai Borikarn Kub \n");
        printf("\n ############# M E N U ############# \n");
        printf("==> 1. Borrow a book\n");
        printf("==> 2. Show all list\n");
        printf("==> 3. Search your borrowed book\n");
        printf("==> 4. nuhh uhhh(Nothing To Do\n");
        printf("choose your own way dragon warrior :");
        scanf(" %49s", input);
        if (sscanf(input, "%d", &fchoose) != 1) {
            printf("Invalid input! Please enter a number 1-4.\n");
            continue; // กลับไปแสดงเมนูใหม่
        }

        switch(fchoose){
            case 1: add_new();break;
            case 2: display_all();break;
            case 3: search_ing();break;
            case 4: printf("\n have a good day \n"); break;
            default: printf("plss press only number 1-4"); break;
        }
    }while (fchoose != 4);

}
int main(){
    readCSV();
    menu();
    return(0);
}