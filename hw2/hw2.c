/* John Monnin, hw2.c, CS 240, Fall 2021
 * Last updated Sep 15, 2021
 */

/* Includes here */

#include "hw2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define LINE_LENGTH (255)

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/*
 *  Define hms_to_hours here
 *  This function converts hours to min
 *  and seconds to min
 */
float hms_to_hours(int hour, int min, int seconds)
{
  float converted_min = min / 60.0f;
  float converted_sec = seconds / 3600.0f;
  return converted_min + converted_sec + hour;
} /* hms_to_hours() */

typedef struct
{
  int month;
  int day;
  int year;
  int hour;
  int min;
  int seconds;
  char app_name[10];
} parsed_line;

/*
 *  Define parse_line here
 *  This function compares
 *  the segments of the string
 *  in the file and parses
 *  the line
 */
parsed_line parse_line(FILE *in_file)
{
  parsed_line result = {0};

  fscanf(in_file, "%d", &result.month);
  fscanf(in_file, "/");
  fscanf(in_file, "%d", &result.day);
  fscanf(in_file, "/");
  fscanf(in_file, "%d", &result.year);
  fscanf(in_file, "|");

  memset(result.app_name, 0, sizeof result.app_name);
  char ch = '0';
  do {
    ch = fgetc(in_file);
    if (ch == '|') {
      continue;
    }
    strncat(result.app_name, &ch, 1);
  } while (ch != '|');

  fscanf(in_file, "%d", &result.hour);
  fscanf(in_file, ":");
  fscanf(in_file, "%d", &result.min);
  fscanf(in_file, ":");
  fscanf(in_file, "%d", &result.seconds);

  return result;
} /* parse_line() */

/* 
 *  Define avg_time_spent here
 *  This function compares
 *  the average time spent
 *  in a month
 */

float avg_time_spent(char *file_name, int given_month, int given_year)
{
  FILE *in_file = fopen(file_name, "r");
  if (in_file == NULL) {
    return FILE_READ_ERR;
  }

  char line[LINE_LENGTH];
  bool counted_days[31];
  float time_spent = 0;
  int matching_days = 0;
  while (fgets(line, LINE_LENGTH, in_file) != NULL) {
    parsed_line result = parse_line(in_file);

    if ((result.month != given_month) || (result.year != given_year)) {
      continue;
    }

    float time = hms_to_hours(result.hour, result.min, result.seconds);

    time_spent += time;

    if (counted_days[result.day] != true) {
      matching_days++;
      counted_days[result.day] = true;
    }
  }

  fclose(in_file);

  return time_spent / matching_days;
} /* avg_time_spent() */

/* 
 *  Define app_time_percentage here
 *  This function compares
 *  the phone usage between different
 *  months in a year
 */
float app_time_percentage(char *file_name, char *given_app_name) {
  FILE *in_file = fopen(file_name, "r");
  if (in_file == NULL) {
    return FILE_READ_ERR;
  }

  char line[LINE_LENGTH];
  float time_spent = 0;
  float app_time_spent = 0;
  while (fgets(line, LINE_LENGTH, in_file) != NULL) {
    parsed_line result = parse_line(in_file);

    float time = hms_to_hours(result.hour, result.min, result.seconds);

    time_spent += time;

    if (strcmp(result.app_name, given_app_name) == 0) {
      app_time_spent += time;
    }
  }

  fclose(in_file);

  return (app_time_spent / time_spent) * 100;
} /* app_time_percentage() */

/* 
 *  Define daily_phone_usage here
 *  This function compares
 *  the phone usage between different
 *  months in a year
 */
int daily_phone_usage(char *in_file_name, int given_year, int given_month,
 char *out_file_name) {
  FILE *in_file = fopen(in_file_name, "r");
  if (in_file == NULL) {
    return FILE_READ_ERR;
  }
  FILE *out_file = fopen(out_file_name, "w");
  if (out_file == NULL) {
    return FILE_WRITE_ERR;
  }

  char line[LINE_LENGTH];
  float time_by_days[31] = {0};

  char name[LINE_LENGTH];
  fgets(name, LINE_LENGTH, in_file);
  name[strcspn(name, "\n")] = 0; // remove trailing '\n'

  do {
    parsed_line result = parse_line(in_file);

    if ((result.month != given_month) || (result.year != given_year)) {
      continue;
    }

    float time = hms_to_hours(result.hour, result.min, result.seconds);

    time_by_days[result.day] += time;
  } while (fgets(line, LINE_LENGTH, in_file) != NULL);

  fprintf(out_file, "Name: %s, Month: %d, Year: %d\n", name, given_month,
   given_year);
  float epsilon = 1.084202e-19;
  for (int i = 0; i < 31; i++) {
    float time = time_by_days[i];
    if (time > epsilon) {
      fprintf(out_file, "Day %d: %.2f hrs\n", i, time);
    }
  }

  fclose(in_file);
  fclose(out_file);

  return OK;
} /* daily_phone_usage() */

/* 
 *  Define min_max_usage here
 *  This function compares
 *  the phone usage between different
 *  months in a year
 */
int min_max_usage(char *in_file_name, int given_month, int given_year,
 char *out_file_name)
{
  FILE *in_file = fopen(in_file_name, "r");
  if (in_file == NULL) {
    return FILE_READ_ERR;
  }
  FILE *out_file = fopen(out_file_name, "w");
  if (out_file == NULL) {
    return FILE_WRITE_ERR;
  }

  char line[LINE_LENGTH];
  float time_by_days[31] = {0};

  char name[LINE_LENGTH];
  fgets(name, LINE_LENGTH, in_file);
  name[strcspn(name, "\n")] = 0; // remove trailing '\n'

  do {
    parsed_line result = parse_line(in_file);

    if ((result.month != given_month) || (result.year != given_year)) {
      continue;
    }

    float time = hms_to_hours(result.hour, result.min, result.seconds);

    time_by_days[result.day] += time;
  } while (fgets(line, LINE_LENGTH, in_file) != NULL);

  fprintf(out_file, "Name: %s, Month: %d, Year: %d\n",
   name, given_month, given_year);
  float epsilon = 1.084202e-19;

  int min_day = 0;
  float min = INT_MAX;
  int max_day = 0;
  float max = INT_MIN;

  for (int i = 0; i < 31; i++) {
    float time = time_by_days[i];
    if (time > epsilon) {
      if (time < min) {
        min_day = i;
        min = time;
      }
      if (time > max) {
        max_day = i;
        max = time;
      }
    }
  }

  fprintf(out_file, "Minimum usage happened on Day %d for %.2f hrs\n",
   min_day, min);
  fprintf(out_file, "Maximum usage happened on Day %d for %.2f hrs\n",
   max_day, max);

  fclose(in_file);
  fclose(out_file);

  return OK;
} /* min_max_usage() */

/*
 *  Define compare_phone_usage here
 *  This function compares
 *  the phone usage between different
 *  months in a year
 */
int compare_phone_usage(char *in_file_name, int month1, int year1, int month2,
 int year2, char *out_file_name)
{
  FILE *in_file = fopen(in_file_name, "r");
  if (in_file == NULL) {
    return FILE_READ_ERR;
  }
  FILE *out_file = fopen(out_file_name, "w");
  if (out_file == NULL) {
    return FILE_WRITE_ERR;
  }

  char line[LINE_LENGTH];
  float time_by_days1[31] = {0};
  float time_by_days2[31] = {0};

  char name[LINE_LENGTH];
  fgets(name, LINE_LENGTH, in_file);
  name[strcspn(name, "\n")] = 0; // remove trailing '\n'

  do {
    parsed_line result = parse_line(in_file);

    float time = hms_to_hours(result.hour, result.min, result.seconds);

    if ((result.month == month1) && (result.year == year1)) {
      time_by_days1[result.day] += time;
    }
    else if ((result.month == month2) && (result.year == year2)) {
      time_by_days2[result.day] += time;
    }
  } while (fgets(line, LINE_LENGTH, in_file) != NULL);

  fprintf(out_file, "Name: %s\n", name);
  fprintf(out_file, "Month 1: %d, Year 1: %d\n", month1, year1);
  fprintf(out_file, "Month 2: %d, Year 2: %d\n", month2, year2);
  float epsilon = 1.084202e-19;

  for (int i = 0; i < 31; i++) {
    float time1 = time_by_days1[i];
    float time2 = time_by_days2[i];

    float lower_time = MIN(time1, time2);
    float higher_time = MAX(time1, time2);
    float diff = higher_time - lower_time;

    if ((time1 > epsilon) || (time2 > epsilon)) {
      if (diff <= epsilon) {
        fprintf(out_file, "Day %d: Used phone is equal in %d/%d and %d/%d\n",
         i, month1, year1, month2, year2);
      }
      else
      {
        fprintf(out_file,
        "Day %d: Used phone for %.2f hrs more in %d/%d than %d/%d\n",
         i, diff, month1, year1, month2, year2);
      }
    }
  }

  fclose(in_file);
  fclose(out_file);

  return OK;
} /* compare_phone_usage() */