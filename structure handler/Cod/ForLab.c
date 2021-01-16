#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ForLab.h"

//#define SWAP(T, A, B) do { (T) tmp = (A); (A) = (B); (B) = tmp; } while (0)


int dialog(const char *msgs[], int n) {
   char *error = "";
   int choice;
   do {
	    puts(error);
   		error = "You're wrong. Try again!";
 		  for (int i = 0; i < n; ++i) {
 		    puts(msgs[i]);
 		  }
 		   puts("Make your choice: ");
 		   choice = getchar() - '0';
 		   while (getchar() != '\n') {}
} while (choice < 0 || choice >= n);
     return choice;
}
 // && getchar() != EOF???

char *get_str(FILE *fp) {
   char buf[81] = {0};
   char *res = NULL;
   int len = 0;
   int n = 0;
   do {
       n = fscanf(fp, "%80[^\n]", buf);
       if (n < 0) {
           if (!res) {
               return NULL;
           }
       } else if (n > 0) {
           int chunk_len = strlen(buf);
           int str_len = len + chunk_len;
           res = realloc(res, str_len + 1);
           memcpy(res + len, buf, chunk_len);
           len = str_len;
       } else {
           fscanf(fp, "%*c");
       }
   } while (n > 0);

   if (len > 0) {
       res[len] = '\0';
   } else {
       res = calloc(1, sizeof(char));
   }

   return res;
}

void ErrorHandler(int error){
  if (error == -1)
    printf("***\nRecord format error\n***\n");
  else
    printf("***\nNot enough memory space!\n***\n");
}

int corFWS(char *s, struct Details *a){
  int countN = 0, countCa = 0, countCo = 0;

  for (;isdigit(*s);s++)
    countN++;
  if(countN == 0 || *s != ',')
    return -1;

  for (s++;isalnum(*s);s++)
    countCa++;
  if(countCa == 0 || *s != ',')
    return -1;

  for (s++;isdigit(*s);s++)
    countCo++;
  if(countCo == 0 || (!(isspace(*s) || *s == '\0')))
    return -1;

  s-=2+countN+countCa+countCo;

  char strN[countN+1], strCa[countCa+1], strCo[countCo+1];
  strncpy(strN, s, countN);
  strN[countN]='\0';

  s+=countN+1;
  strncpy(strCa, s, countCa);
  strCa[countCa]='\0';

  s+=countCa+1;
  strncpy(strCo, s, countCo);
  strCo[countCo]='\0';

  char *test = (char *)malloc((countCa+1)*sizeof(char));
  if (test == NULL)
    return -2;
  a->number = atoi(strN);
  a->call = test;
  strcpy(a->call, strCa);
  a->count = atoi(strCo);

  return countN+countCa+countCo+1;
}

struct Details *readDetailsInStr2(struct Details *A, int size_character[], FILE *fp){
  char *s = NULL;
  int correct = 0, size, i;

  while ((s = get_str(fp)) && strcmp(s,"exit")){
    for (size = strlen(s); *s; s++){
      if (!(isspace(*s))){
        if (size_character[0] == size_character[1]){
          size_character[1] += size_character[2];
          A = realloc(A, size_character[1] * sizeof(struct Details));
        }
        correct = corFWS(s, A+size_character[0]);
        if (correct < 0){
          ErrorHandler(correct);
          while (!(isspace(*(s+1))) && *(s+1) != '\0' ){
            s++;
          }
        } else {
          s += correct;
          size_character[0]++;
        }
      }
    }
    free(s-size);
  }
  return A;
}

struct Details *FreeStructDetails(struct Details *A, int *a){
  int i;
  for(i = 0; i < a[0];i++)
    if ((A+i)->call != NULL)
      free((A+i)->call);
  free(A);
  a[0] = 0;
  a[1] = 0;
  return NULL;
}

void displayDetails(struct Details *A, int items, FILE *fp){
  int i;
  for(i = 0; i < items;i++)
    fprintf(fp, "%d,%s,%d\n", (A+i)->number, (A+i)->call, (A+i)->count);
}

void Swap(struct Details *A, struct Details *B){
  struct Details tmp = *A;
  *A = *B;
  *B = tmp;
}

void SelectionSort(struct Details *A, int a){
  int i, j;
  struct Details *min = NULL;
  for(i=0; i < a; i++){
    min = A+i;
    for(j=i+1;j < a; j++)
      if (strcmp(min->call,(A+j)->call) > 0)
        min = A+j;
    Swap(A+i, min);
  }
}

void BubbleSort(struct Details *A, int a){
  int i, j;
  for(i=0; i < a; i++)
    for(j=i;j < a; j++)
      if (strcmp((A+i)->call,(A+j)->call) > 0)
        Swap(A+i, A+j);
}

void SearchRecord(int a, struct Details *A, int items){
  int i, j = 0;
  for(i=0;i<items;i++){
    if ((A+i)->count == a){
      printf("%d,%s,%d\n", (A+i)->number, (A+i)->call, (A+i)->count);
      j = 1;
    }
  }
  if (j == 0)
    printf("Nothing found!\n");
}

struct Details *RandomRecord(int n, int *size_character){
  int i, j, a;
  char *s;
  struct Details *A=(struct Details *)malloc(n*sizeof(struct Details));

  for(i=0;i<n;i++){
    (A+i)->number = rand()%10000;
    (A+i)->count = rand()%10000;

    a = (rand()%35)+2;
    s = (char *)malloc(a*sizeof(char));
    for (j=0;j<a-1;j++)
      s[j] = ((rand()%26)+65+32*(rand()%2));
    s[j]='\0';
    (A+i)->call = s;
    s = NULL;
  }
  size_character[0] = n;
  size_character[1] = n;
  return A;
}
