#include <iostream>
#include <vector>


int main(int argc, char *argv[])
{
   int i = 10;
   int* j = &i;
   printf("This is %p", j);
   return 0;
}
