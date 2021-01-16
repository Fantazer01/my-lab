//#define SWAP(T, A, B) do { T tmp = (A); (A) = (B); (B) = tmp; } while (0)



struct Details {
  int number;
  char *call;
  int count;
};
//it reads string of any length
char *get_str(FILE *fp);

//displays a dialog box for the user
int dialog(const char *msgs[], int n);

//correctFormWriteStruct, return size record in struct,
//else output error -1 (error format) or -2(error memory space)
int corFWS(char *s, struct Details *a);

void ErrorHandler(int error);
//a - array from filling items, count elements in array and step of adding elements
struct Details *readDetailsInStr2(struct Details *A, int a[], FILE *fp);

struct Details *FreeStructDetails(struct Details *A, int *size_character);

void displayDetails(struct Details *A, int items, FILE *fp);

void Swap(struct Details *A, struct Details *B);

void SelectionSort(struct Details *A, int items);

void BubbleSort(struct Details *A, int items);

void SearchRecord(int count, struct Details *A, int items);

struct Details *RandomRecord(int n, int *size_character);

//void readDetails(stract Details *a);
