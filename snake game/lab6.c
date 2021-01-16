/*6.15
Реализовать игру в «Змейку» («Snake»), в которой
программа самостоятельно будет играть за игрока
(без интерактивности), используя генератор слу-
чайных чисел для определения его действий. Иг-
ровое поле должны отображаться в терминале
постоянно обновляться. Препятствия и тело
змейки должны описываться в виде списков. Файл
должен использоваться для записи хода игры.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gameLib.h"

int main(){
 int f = 1, c;
 char *s;
 srand(time(NULL));
 while (f != 3) {
   if (f == 1)
    new_game();
   else if (f == 2)
    watch_game();
   printf("\n1. New game\n2. Watch the previous game\n3. Exit\n");
   scanf("%s", s);
   c = getchar();
   if (c == '1')
     f = 1;
   else if (c == '2')
    f = 2;
   else
    f = 3;
  }
 return 0;
}
