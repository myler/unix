#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

void test_longjmp(void)
{
  printf("test_longjmp() \n");
  longjmp(buf, 1);
  printf("end test_longjmp()\n");
}

int
main(void)
{
  if(setjmp(buf))
    printf("back test_longjmp\n");
  else
  {
    printf("first time to setjmp\n");
    test_longjmp();
  }
  return 0;
}