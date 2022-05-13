#include <error.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define BRIDGE 0xC0000000
#define BRIDGE_SPAN 0x2

#define ADDER_SUM 0x0

int main(int argc, char **argv) {
  //  uint64_t a = 0;
  //  uint64_t b = 0;
  uint16_t sum = 0;

  /* uint8_t *a_map = NULL; */
  /* uint8_t *b_map = NULL; */
  uint8_t *sum_map = NULL;

  uint8_t *bridge_map = NULL;

  int fd = 0;
  int result = 0;

  if (argc != 1) {
    perror("There should be no arguments.");
    return -1;
  }

  // a = strtoll(argv[1], NULL, 10);
  // b = strtoll(argv[2], NULL, 10);

  fd = open("/dev/mem", O_RDWR | O_SYNC);

  if (fd < 0) {
    perror("Couldn't open /dev/mem\n");
    return -2;
  }

  bridge_map = (uint8_t *)mmap(NULL, BRIDGE_SPAN, PROT_READ | PROT_WRITE,
                               MAP_SHARED, fd, BRIDGE);

  if (bridge_map == MAP_FAILED) {
    perror("mmap failed.");
    close(fd);
    return -3;
  }

  //a_map = bridge_map + ADDER_A;
  //b_map = bridge_map + ADDER_B;
  sum_map = bridge_map + ADDER_SUM;

  //*((uint64_t *)a_map) = a;
  //*((uint64_t *)b_map) = b;
  sum = *((uint64_t *)sum_map);

  printf("%u\n", (unsigned int)sum);

  result = munmap(bridge_map, BRIDGE_SPAN);

  if (result < 0) {
    perror("Couldn't unmap bridge.");
    close(fd);
    return -4;
  }

  close(fd);
  return 0;
}
