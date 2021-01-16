

typedef struct item {
    int data1;
    int data2;
    struct item *next;
} item;

typedef struct list {
    item *head;
    item *tail;
} list;

//Create new list
list *list_new();

//Delete list
void list_delete(list *list);

//put element at the end of the list
int list_put(list *list, int data1, int data2);

//put element at the beginning of the list
int list_put_head(list *list,int data1,int data2);

//moving snake head
int move_head(list *list, char field[10][15], int data1, int data2);

//moving snake tail
int move_tail(list *list, char field[10][15]);

//displaying the field of play
void display(char field[10][15]);

//food generation
void spawn_food(char field[10][15]);

//setting the initial position of the snake
void snake_create(list* list);

//choice of direction
int direction(list *list, char field[10][15], int i, int j);

//save data on file
int file_save(char field[10][15]);

//game process
int game(list *list, char field[10][15]);

void file_clean();

//game body
void new_game();

void delay(int time);

int watch_game();
