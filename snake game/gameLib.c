#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gameLib.h"

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

list *list_new() {
    return (list *) calloc(1, sizeof(list));
}

void list_delete(list *list) {
  item *ptr = list->head, *ptr_prev;
  while (ptr)
   {
    ptr_prev = ptr;
    ptr = ptr->next;
    free(ptr_prev);
   }
  free(list);
}

int list_put(list *list, int data1, int data2) {
  item *new = (item *) calloc(1, sizeof(item));
  if (!new)
    return -1;

  new->data1 = data1;
  new->data2 = data2;
  new->next = NULL;
  if (!list->head) {
    list->head = new;
    list->tail = new;
  } else {
    list->tail->next = new;
    list->tail = new;
  }
  return 0;
}

int list_put_head(list *list,int data1,int data2) {
  item *new = (item *) calloc(1, sizeof(item));
  if (!new)
    return -1;

  new->data1 = data1;
  new->data2 = data2;
  new->next = list->head;
  list->head = new;
  return 0;
}

int move_head(list *list, char field[10][15], int data1, int data2) {
 list_put_head(list, data1, data2);
 field [list->head->data1][list->head->data2] = '@';
 field [list->head->next->data1][list->head->next->data2] = '&';
 return 0;
}

int move_tail(list *list, char field[10][15]) {
 int i, j;
 item *tmp = list->head;
 while (tmp->next != list->tail)
   tmp = tmp->next;

 i = tmp->next->data1;
 j = tmp->next->data2;
 field[i][j] = ' ';
 list->tail = tmp;
 tmp = tmp->next;
 free(tmp);
 list->tail->next = NULL;
 return 0;
}

void display(char field[10][15]) {
 printf("\n");
 for(int i = 0; i < 10; i++) {
   for(int j = 0; j < 15; j++)
    printf("%c", field[i][j]);
   printf("\n");
  }
}

void spawn_food(char field[10][15]) {
 int i, j, k = 0;
 while (k == 0) {
   i = rand()%10;
   j = rand()%15;
   if (field[i][j] == ' ') {
     field[i][j] = '*';
     k = 1;
    }
  }
}

void snake_create(list* list) {
 list_put(list, 3, 3);
 list_put(list, 3, 2);
 list_put(list, 3, 1);
}

int direction(list *list, char field[10][15], int i, int j)//выбор направления
{
 int r, x, y;
 y = list->head->next->data1;
 x = list->head->next->data2;
 while (1) {
   r = rand()%4;
   if (r == 0 && !((y == i)&&(x == j-1))) //влево
       return 0;
   else if (r == 1 && !((y == i-1)&&(x == j))) //вверх
       return 1;
   else if (r == 2 && !((y == i)&&(x == j+1))) //вправо
       return 2;
   else if (r == 3 && !((y == i+1)&&(x == j))) //вниз
       return 3;
 }
}

int file_save(char field[10][15]) {
  FILE *fp;
  char c = '\n';
  fp = fopen("GameRecorder.dat", "a+b");
  if(fp == NULL) {
    printf("\nФайл не найден");
    return -1;
  }
  for (int i=0; i<10; i++) {
    for (int j=0; j<15; j++)
     fwrite(field[i]+j, sizeof(char), 1, fp);
    fwrite(&c, sizeof(char), 1, fp);
  }
  fclose(fp);
  return 0;
}

void delay(int delays){
  time_t start, end;
  time(&start);
  time(&end);
  while (delays > 1000 * difftime(end, start))
    time(&end);
}

int game(list *list, char field[10][15]){
 int next, a, i = 3, j = 4, end = 0;
 display(field);
 file_save(field);
 delay(1000);
 do {
    if (field[i][j] != '*') {
      move_head(list, field, i, j);
      move_tail(list, field);
    } else {
      move_head(list, field, i, j);
      spawn_food(field);
    }
    a = direction(list, field, i, j);
    if(a == 0)//left
      j--;
    else if(a == 1)//up
      i--;
    else if(a == 2)//right
      j++;
    else if(a == 3)//down
      i++;
    delay(1000);
    display(field);
    file_save(field);
    if ((field[i][j]=='#')||(field[i][j]=='&'))
      end = 1;
 } while (end != 1);
 printf("\nGame over!\n");
 return 0;
}

void file_clean() {
 FILE *fp;
 fp = fopen("GameRecorder.dat", "w+b");
 if (fp != NULL)
  fclose(fp);
}

void new_game() {
 list* list = list_new();
 char field[10][15] ={{"###############"},
                      {"#        ##   #"},
                      {"#             #"},
                      {"#&&@*         #"},
                      {"#       ###   #"},
                      {"#        #    #"},
                      {"#  #          #"},
                      {"#  ##         #"},
                      {"#        ###  #"},
                      {"###############"}};
 file_clean();
 snake_create(list);
 game(list, field);
 list_delete(list);
}

int watch_game(){
  FILE *fp;
  char c = '\n';
  char *s;
  fp = fopen("GameRecorder.dat", "r+b");
  if(fp == NULL) {
    printf("\nFile not found!");
    return -1;
  }

  s = get_str(fp);
  while (s) {
    printf("%s\n", s);
    free(s);
    s = get_str(fp);
  }
  free(s);
  fclose(fp);
  return 0;
}
