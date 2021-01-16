//чтение данных для обработки из входного потока
//чтение данных для обработки из текстового файла
//случайная генерация данных для обработки

//структура: номер детали, название детали, количество деталей
//сортировать по названиям деталей; найти детали с заданным количеством
//запись текущего состояния обрабатываемых данных в текстовый файл
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ForLab.h"
#define MINSIZE 100

const char *MSGS[] = {"0. Quit", "1. Reading data from console", "2. Reading data from file",
                      "3. Random generation data", "4. Display data on screen", "5. Sort by part name",
											"6. Writing data to a file", "7. Search for a recording by its name", "Enter command number."};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

#define FIRST_COMMAND "\nEnter data in console in format \"number details\",\"calling details\",\"count details\",\n\
                        when you're done enter \"exit\"\n"
#define FIFTH_COMMAND "Enter symbol \"s\" if you want to use seletion sort or symbol \"b\" if you want to use bubble sort,\
 enter and if you want to continue otherwise enter any other character\n"


int main(){
  int size_character[3]={0, 0, 2}, i;
  struct Details *De = NULL;
  char *file_name=NULL, *count_details = NULL, *n = NULL, mode='\0';
  FILE *fp;

	printf("Hello dear and only my user!\n");
	printf("It is a program for accounting details.\n");

	int c = 0;
  do {
  	c = dialog(MSGS, MSGS_SIZE);
  	switch(c) {
  		case 0:
  		    break;
  		case 1:
  		    printf(FIRST_COMMAND);
          if (De != NULL)
            De = FreeStructDetails(De, size_character);
          De = readDetailsInStr2(De, size_character, stdin);
          printf("Data read successfully!\n");

  		    break;
  		case 2:
          printf("Enter the name of the file to which you want to read data:\n");
          file_name = get_str(stdin);
          mode = 'r';
          fp = fopen(file_name, &mode);
          if (fp != NULL){
            if (De != NULL)
              De = FreeStructDetails(De, size_character);
            De = readDetailsInStr2(De, size_character, fp);
            fclose(fp);
            printf("Data read successfully!\n");
          } else {printf("Program cann't open this file!\n");}
          free(file_name);

  		    break;
  		case 3:
          printf("Enter how many records to generate:\n");
          n = get_str(stdin);
          if (atoi(n) > 0){
            De = RandomRecord(atoi(n), size_character);
    		    printf("***\nData has been successfully generated\n***\n");
          } else {
            printf("You has entered an invalid value!\n");
          }
          free(n);

  		    break;
  		case 4:
          if (De != NULL){
    		    printf("***\nRecords about details\n***\n");
            displayDetails(De, size_character[0], stdout);
            printf("end of list\n");
          } else {
            printf("Enter data to display them!\n");
          }

  		    break;
  		case 5:
          if (De != NULL){
            printf(FIFTH_COMMAND);
            scanf("%c", &mode);
            if (mode == 's'){
      		    printf("***\nSort to data\n***\n");
              SelectionSort(De, size_character[0]);
            } else if (mode == 'b'){
              printf("***\nSort to data\n***\n");
              BubbleSort(De, size_character[0]);
            }
          } else {
            printf("Enter data to sort them!\n");
          }
  		    break;
      case 6:
          if (De != NULL){
            printf("Enter the name of the file to which you want to write data.\n");
            file_name = get_str(stdin);
            printf("Enter the parametr for write: \"w\" - if you want to erase the previous content of the file or \"a\" else:\n");
            scanf("%c", &mode);
            fp = fopen(file_name, &mode);
            displayDetails(De, size_character[0], fp);
            fclose(fp);
            free(file_name);
          }
          break;
      case 7:
          if (De != NULL){
            printf("Enter a count details to search\n");
            count_details = get_str(stdin);
            if (count_details != NULL && strlen(count_details) != 0 && isdigit(count_details[0])){
              SearchRecord(atoi(count_details), De, size_character[0]);
            } else {
              printf("You has entered an invalid value!\n");
            }
            free(count_details);
          } else {printf("Enter data to search them!\n");}
          break;
  	}
  } while (c != 0);
  if (De != NULL)
    FreeStructDetails(De, size_character);
	return 0;
}
