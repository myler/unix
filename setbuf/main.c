#include <stdio.h>
#include <unistd.h>

char outbuf[50];

int
main(void)
{
  /* 将outbuf与stdout输出流相连接 */
  setbuf(stdout,outbuf);
  /* 向stdout中放入一些字符串 */
  puts("This is a test of buffered output.");
  puts("This output will go into outbuf");
  puts("and won't appear until the buffer");
  puts("fills up or we flush the stream.\n");
  /* 以下是outbuf中的内容 */
  //puts(outbuf);
  fflush(stdout);

  puts(outbuf);
  puts(outbuf);
  puts(outbuf);
  sleep(3);
  /*刷新流*/
  fflush(stdout);

  return 0;
}

