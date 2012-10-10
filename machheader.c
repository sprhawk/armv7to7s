#include <stdio.h>
#include <mach-o/loader.h>

int main(int argc, char * argv[]) {
  if (argc < 1) {
    printf("usage: %s a.out", argv[0]);
    return 1;
  }

  struct mach_header header = {};
  FILE * file = fopen(argv[1], "rb");
  if (NULL == file) {
    printf("failed to open file: %s\n", argv[1]);
    return 1;
  }
  size_t sz = fread(&header, sizeof(header), 1, file);
  fclose(file);
  file = NULL;
  if (1 == sz) {
    printf("magic:%x\n", header.magic);
    printf("cputype:%d  cpusubtype:%d\n", header.cputype, header.cpusubtype);
  }
  else {
    printf("read file failed:%s\n", argv[1]);
    return 1;
  }
  return 0;
}
