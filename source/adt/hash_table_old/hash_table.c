#include "hash_table.h"

#include "arrays.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define AMOUNT_OF_EXP (100)
#define PI 3.1415

void perform_exper(void) {
  uint8_t *array;
  time_t t;
  srand((unsigned)time(&t));
  for (int M = 1; M <= 100; M++) {
    array = malloc(sizeof(uint8_t) * M);
    int randIndex;
    if (array) {
      printf("\n arrai size: %d:", M);
      int cnt = 0;
      uint32_t *firstCollision =
          (uint32_t *)malloc(AMOUNT_OF_EXP * sizeof(uint32_t));
      (void)memset(firstCollision, 0x00,
                   sizeof(firstCollision) * AMOUNT_OF_EXP);
      for (int i = 0; i < AMOUNT_OF_EXP; i++) {
        (void)memset(array, 0x00, M);
        bool loop = true;
        cnt = 0;
        while (loop) {
          randIndex = rand() % M;
          cnt++;
          // printf ("\n rand index: %d:", randIndex);
          if (M < randIndex) {
            printf("\n error ind: %d:", M);
          }
          if (0 == array[randIndex]) {
            array[randIndex] = 1;
          } else {
            firstCollision[i] = cnt;
            // printf (" %d ", cnt);
            loop = false;
            (void)memset(array, 0x00, M);
          }
        }
      }
      float avr = calc_avarage(firstCollision, AMOUNT_OF_EXP);
      printf(" %f %f", avr, sqrt(PI * M / 2.0f));
      free(firstCollision);
      free(array);
    }
  }
}
