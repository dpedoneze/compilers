/**@<main.c>::**/
#include <stdlib.h>
#include <stdio.h>
#include <parser.h>

FILE * target;

int main(int argc, char *argv[])
{
  if(argc > 1) target = fopen(argv[1],"r");
  else target = stdin;
  
  start();
  
  return 0;
}
