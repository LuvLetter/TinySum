#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5.c"
#include "md5.h"
#include <sys/stat.h>
#include <unistd.h>
#include "sha-1.h"


void print_md5(char input[]) {
  unsigned char digest[16];
  int i;
  MD5_CTX md5;
  MD5Init(&md5);
  MD5Update(&md5, (unsigned char *) input, strlen(input));
  MD5Final(&md5, digest);
  printf("Decryption:\n \
  md5:");
  for(i=0;i<16;i++) printf("%02x", digest[i]);
  printf("\n");
  print_sha_1(input);
}

void filesmd5(char input[])
{
  //printf("%s\n", input);
  FILE *fp;
  if((fp = fopen(input,"r")) == NULL)
  {
      printf("Open file failed.\n");
      exit(1);
  }
  struct stat buf;
  stat(input, &buf);
  printf("%s file size = %ld \n", input, buf.st_size);
  char encrypt[buf.st_size];
  fread(&encrypt, 1, sizeof(encrypt), fp);
  print_md5(encrypt);
  //print_sha_1(encrypt);
  fclose(fp);
}

void showhelp(char input[])
{
  printf("MD5sum calculator:\n \
            -F --file   : Input path of file\n \
            -H --help   : Show help\n \
            -S --string : Input string\n");
}

void comparemd5(char file1[], char file2[])
{
  //filemd5
}

struct command_s {
	char command[20];
	void (*eval)(char *s);
  void (*comparefunc)(char *s1, char *s2);
} commands[]={
	{"-S", print_md5},
  {"--string", print_md5},
  {"-H", showhelp},
  {"--help", showhelp},
  {"-F", filesmd5},
  {"--file", filesmd5},
  //{"-C", comparemd5},
  //{"--compare", comparemd5}
};


int main(int argc, char *argv[])
{
  //showhelp();
  //filesmd5(argv[2]);
  if(argc>2)
  {
      for (int i = 0; i < 7; ++i)
          if (!strcmp(commands[i].command, argv[1])){
            if(i >= 6)  commands[i].comparefunc(argv[2], argv[3]);
            else commands[i].eval(argv[2]);
            }
  }
  else showhelp(argv[2]);
  return 0;
}
