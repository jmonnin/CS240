#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hw2.h"

/*  This function is used to clear the input buffer. Upon completion,
 *  the function returns one.
 */

int clean_stdin()
{
  while (getchar() != '\n') {
  }
  return (1);
} /* clean_stdin() */

/*  This function prints out all of the characters in the file named
 *  filename. It returns FILE_READ_ERR if it cannot read the specified
 *  file. Otherwise, it returns OK to indicate that the funciton was
 *  successful.
 */

int print_out(char *filename) {
  FILE *file_ptr = NULL;
  file_ptr = fopen(filename, "r");
  if (file_ptr == NULL) {
    return (FILE_READ_ERR);
  }

  int character = '\0';
  while ((character = fgetc(file_ptr)) != EOF) {
    putchar(character);
  }

  fclose(file_ptr);
  file_ptr = NULL;
  return (OK);
} /* print_out() */

/*  This function is used to run the functions implemented in hw2.c.
 *  User input is used to determine which function to run what input
 *  is passed to it. Upon completion, the function returns zero.
 */

int main(int argc, char **argv) {
  while (1) {
    printf("\n");
    printf("Test Menu\n");
    printf("1. Get Average Time Spent\n");
    printf("2. Get App Time Usage Percentage\n");
    printf("3. Get Daily Phone Usage\n");
    printf("4. Get Min Max Usage\n");
    printf("5. Compare Phone Usage\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");

    int response = 0;
    scanf("%d", &response);
    getchar();

    int month = 0;
    int year = 0;
    int month1 = 0;
    int year1 = 0;
    int month2 = 0;
    int year2 = 0;
    float value = 0;
    char in_file[MAX_FILE_LEN] = "";
    char out_file[MAX_FILE_LEN] = "";
    char app_name[MAX_NAME_LEN] = "";

    switch (response) {
      case 1:
        printf("Enter input file name: ");
        scanf("%s", in_file);
        printf("Enter month as a number (ex. January -> 1): ");
        scanf("%d", &month);
        printf("Enter year: ");
        scanf("%d", &year);

        value = avg_time_spent(in_file, month, year);
        if (value >= 0) {
          printf("Average time spent in %s for month %d "
                  "and year %d is %f\n", in_file, month, year, value);
        } else {
          printf("Error! (code %d)\n", (int)value);
        }
        break;

      case 2:
        printf("Enter input file name: ");
        scanf("%s", in_file);
        clean_stdin();
        printf("Enter the app name: ");
        fgets(app_name, MAX_NAME_LEN, stdin);
        int is_good_string = 0;
        for (int i = 0; i < MAX_NAME_LEN; i++) {
          if (app_name[i] == '\n') {
            app_name[i] = '\0';
            is_good_string = 1;
          }
        }
        if (!is_good_string) {
          printf("Length of app name should be less "
                    "than %d\n", MAX_NAME_LEN);
          break;
        }

        value = app_time_percentage(in_file, app_name);
        if (value >= 0) {
          printf("Total percentage time spent in %s for %s is %f %%\n",
                 in_file, app_name, value);
        } else {
          printf("Error! (code %d)\n", (int)value);
        }
        break;

      case 3:
        printf("Enter input file name: ");
        scanf("%s", in_file);
        printf("Enter output file name: ");
        scanf("%s", out_file);
        printf("Enter month as a number (ex. January -> 1): ");
        scanf("%d", &month);
        printf("Enter year: ");
        scanf("%d", &year);
        value = daily_phone_usage(in_file, year, month, out_file);
        if (value >= 0) {
          printf("Daily Phone usage log of %s created in %s\n",
              in_file, out_file);
        } else {
          printf("Error! (code %d)\n", (int)value);
        }
        break;

      case 4:
        printf("Enter 1st input file name: ");
        scanf("%s", in_file);
        printf("Enter output file name: ");
        scanf("%s", out_file);
        printf("Enter month as a number (ex. January -> 1): ");
        scanf("%d", &month);
        printf("Enter year: ");
        scanf("%d", &year);

        value = min_max_usage(in_file, month, year, out_file);
        if (value >= 0) {
          printf("Min Max usage activity log of %s for month %d and "
              "year %d created in %s\n", in_file, month, year, out_file);
        } else {
          printf("Error! (code %d)\n", (int)value);
        }
        break;

      case 5:
        printf("Enter input file name: ");
        scanf("%s", in_file);
        printf("Enter output file name: ");
        scanf("%s", out_file);
        printf("Enter first month as number (ex. January -> 1): ");
        scanf("%d", &month1);
        printf("Enter first year: ");
        scanf("%d", &year1);
        printf("Enter second month as number (ex. January -> 1): ");
        scanf("%d", &month2);
        printf("Enter second year: ");
        scanf("%d", &year2);
        value = compare_phone_usage(in_file, month1, year1,
                                    month2, year2, out_file);
        if (value >= 0) {
          printf("Compare phone usage %s for month %d and year %d with "
              "month %d and year %d created in %s\n",
              in_file, month1, year1, month2, year2, out_file);
        } else {
          printf("Error! (code %d)\n", (int)value);
        }
        break;

      case 6:
        printf("\nGood Bye :^) \n\n");
        return (0);

      default:
        printf("\nInvalid choice!\n");
        break;
    }
  }
  return (0);
} /* main() */
