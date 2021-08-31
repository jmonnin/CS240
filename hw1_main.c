#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "hw1.h"

char g_msg[ARRAY_SIZE];
char g_cip[ARRAY_SIZE];

/*  This function is used to clear the input buffer. Upon completion,
 *  the function returns one.
 */

int clean_stdin()
{
  while (getchar() != '\n') {
  }
  return (1);
} /* clean_stdin() */

/*  This function is used to run the encode() and checksum()
 *  functions implemented in file hw1.c.
 *  User input is used to determine which function to run and what input
 *  is passed to it. Upon completion, the function returns zero.
 */

int main() {
  int n = 0;
  int l = 0;
  int r = 0;
  int choice = 0;
  int res = 0;
  int good_string = 0;
  int input_given = 0;

  while (choice != 5) {
    printf("Select an option:\n"
      "   1) Input string to g_msg\n"
      "   2) encode()\n"
      "   3) checksum()\n"
      "   4) Print g_msg and g_cip\n"
      "   5) Exit\n"
      "Your choice? ");

    fscanf(stdin, "%d", &choice);
    clean_stdin();


    char* in_str = (char*) malloc(ARRAY_SIZE + 2);

    switch (choice) {
      case 1:
        printf("Please enter the string to be stored in g_msg: ");
        fgets(in_str, ARRAY_SIZE + 2, stdin);

        good_string = 0;
        for (int i = 0; i < ARRAY_SIZE + 2; i++) {
          if ((in_str[i] == '\n') || good_string) {
            in_str[i] = g_msg[i];
            good_string = 1;
          }
          if (in_str[i] == '\0') {
            in_str[i] = g_msg[i];
          }
        }
        if (!good_string) {
          printf("The length of the string should be less than %d!\n",
              ARRAY_SIZE);
          break;
        }
        input_given = 1;
        memcpy(g_msg, in_str, ARRAY_SIZE);
        break;
      case 2:
        if (input_given == 0) {
          printf("You should first give an input for g_msg!\n");
          break;
        }

        printf("Enter the value of n: ");

        fscanf(stdin, "%d", &n);
        clean_stdin();
        printf("Enter value of l: ");
        fscanf(stdin, "%d", &l);
        clean_stdin();
        if (l < 0) {
          printf("You should choose a value bigger than 0!\n");
        } else {
          printf("Enter value of r: ");
          fscanf(stdin, "%d", &r);
          clean_stdin();
          if (r > ARRAY_SIZE) {
            printf("You should choose a value less than %d!\n",
              ARRAY_SIZE + 1);
          } else {
            res = encode(n, l, r);
            printf("The encode returned %d\n", res);
          }
        }
        break;
      case 3:
        if (input_given == 0) {
          printf("You should first give an input for g_msg!\n");
          break;
        }
        res = checksum();
        printf("The checksum() outputs %2d \n", res);
        break;

      case 4:
        printf("g_msg: ");
        for (int i = 0; i < ARRAY_SIZE; i++) {
          printf("%c", g_msg[i]);
        }
        printf("\ng_cip: ");
        for (int i = 0; i < ARRAY_SIZE; i++) {
          printf("%c", g_cip[i]);
        }
        printf("\n");
        break;
      case 5:
        printf("Goodbye!\n");
        free(in_str);
        break;

      default:
        printf("Select one of the given options...!\n");
        break;
    }
  }

  return 0;
} /* main() */
