#include <stdio.h>
#include <mach-o/loader.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  if (argc < 2) {
    printf("usage: %s armv7lib armv7slib\n", argv[0]);
    return 1;
  }

  FILE * file = fopen(argv[1], "rb");
  if(NULL == file) {
    printf("failed to open file to read: %s\n", argv[1]);
    return 1;
  }
  fseek(file, 0, SEEK_END);
  size_t end = ftell(file);
  void * buf = malloc(sizeof(char) * end);
  if(NULL == buf) {
    printf("no enough memory\n");
    fclose(file);
    return 1;
  }
  fseek(file, 0, SEEK_SET);
  size_t sz = fread(buf, end ,1, file);
  fclose(file);
  file = NULL;
  if (1 == sz) {
    struct mach_header * header = (struct mach_header*)buf;
    if(MH_MAGIC == header->magic && CPU_TYPE_ARM == header->cputype && CPU_SUBTYPE_ARM_V7 == header->cpusubtype) {
      header->cpusubtype = 11; //CPU_SUBTYPE_ARM_V7S; to the machine.h from Xcode 4.5
    }
    else {
      printf("%s seems not be a valid armv7 mach-o file\n", argv[1]);
      return 1;
    }
  }
  else {
    printf("read mach header failed\n");
    return 1;
  }
  file = fopen(argv[2], "wb");
  if(NULL == file) {
    printf ("failed to open file to write: %s\n", argv[2]);
    return 1;
  }
  fseek(file, 0L, SEEK_SET);
  sz = fwrite(buf, end, 1,  file);
  free(buf);
  buf = NULL;
  fclose(file);
  file = NULL;
  if(1 != sz) {
    printf("write file failed\n");
    return 1;
  }
  return 0;
}
