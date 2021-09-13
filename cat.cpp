#include <iostream>
#include <string.h>
#define MAX 256
using namespace std;

int main(int argc, char *args[])
{
  FILE *f;
  char filename[MAX], ch;
  if(argc <= 1)
  {
    cout<<"Usage mycat <FILENAME>\n";
    return 1;
  }

  strncpy(filename, args[1], MAX);
  f = fopen(filename, "r");

  if(f == NULL)
  {
    cout<<args[1]<<": No such File Exists\n";
    return 1;
  }

  ch = fgetc(f);
  if(ch == EOF)
  {
    cout<<filename<<": Cannot Read file\n";
    return 1;
  }
  while(ch != EOF)
  {
    putchar(ch);
    ch = fgetc(f);
  }

  cout<<"\n";
  fclose(f);
  return 1;
}
