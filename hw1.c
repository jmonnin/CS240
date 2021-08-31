/* HW1 - Fall 2021
 * Last updated August 28, 2021
 */

/* Add any includes here */

#include "hw1.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

/* Define int encode(int, int, int) here */
int encode(int n, int l, int r) {
    const int ALPHABET_SIZE = 26;

    memcpy(g_cip, g_msg, ARRAY_SIZE);
    
    if (l > ARRAY_SIZE || l < 0 || r > ARRAY_SIZE || r < 0) {
        return OUT_OF_BOUNDS;
    } else if (n < 0 || l > r) {
        return UNEXPECTED_INPUT;
    }

    for (int i = l; i <= r; i++) {
      if (g_cip[i] >= 'A' && g_cip[i] <= 'Z') {
        g_cip[i] = (((g_cip[i] - 'A') + n) % ALPHABET_SIZE) + 'A';
      } else if (g_cip[i] >= 'a' && g_cip[i] <= 'z') {
        g_cip[i] = (((g_cip[i] - 'a') + n) % ALPHABET_SIZE) + 'a'; 
      }
    }

    return SUCCESS;
}

/* Define int checksum() here */

int checksum(void) {
  if (ARRAY_SIZE == 0) {
    return 0;
  }

  int temp = 0;

  for (int i = 0; i < ARRAY_SIZE; i++) {
    temp = temp ^ g_msg[i];
  }

  return temp;
}

/* 0;Remember, you don't need a main function!
 * It is provided by hw1_main.c or  hw1_test.o
*/
