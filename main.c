#include<stdio.h>
#include<string.h>
int readCSV(){
    FILE *fp = fopen("main.csv","r");
    if (fp == NULL)
    {
        printf("File: %p\n",fp);
        printf("Cannot open the file\n");
    }
    else
    {
        printf("File: %p\n",fp);
        printf("File opened successfully\n");
    }
    fclose (fp);
    return 0;
}

int saveCSV(char *name, char *title, char *B_date, char *R_date){

    FILE *fp;
    fp = fopen("main.csv","a");
    if (fp==NULL)
    {
        printf("Cannot open file\n");
        return 0;
    }
    fprintf(fp,"()\nBorrower name: %s\nBook's title: %s\nBorrow date: %s\nReturn date: %s\n", name, title, B_date, R_date);

    fclose (fp);
    
    return 0;
}


int add_new(){
    FILE *fp;
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

    saveCSV(name,title,B_date,R_date);
    printf("Data added successfully!\n");

    return 0 ;
}
int display_all(){
    FILE *fp = fopen("main.csv","r");
    if (fp == NULL)
    {
    printf("File: %p\n",fp);
    printf("Cannot open the file\n");
    return 0;
    }
    char line[100];
    while(fgets(line,sizeof(line),fp)!=NULL){
        printf("%s",line);
    }
    fclose(fp);
    return 1;
}
int search_ing(){

}
int update(){

}
int del(){

}
int menu(){
    int fchoose ;
    do{
        printf("\n Hong Samutr Yindih Hai Borikarn Kub \n");
        printf("\n ############# M E N U ############# \n");
        printf("==> 1. Borrow a book\n");
        printf("==> 2. Show all list\n");
        printf("==> 3. Search your borrowed book\n");
        printf("==> 4. nuhh uhhh(Nothing To Do\n");
        printf("choose your own way dragon warrior :");
        scanf("%d", &fchoose);

        switch(fchoose){
            case 1: add_new();
            case 2: display_all();
            case 3: search_ing();
            case 4: printf("\n have a good day \n"); break;
            default: printf("plss press only number 1-4");
        }
    }while (fchoose != 4);

}
int main(){
    readCSV();
    menu();
    return(0);
}