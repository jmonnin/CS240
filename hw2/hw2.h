#ifndef HW2_H
#define HW2_H

/* Constant Definitions */
#define MAX_FILE_LEN (30) /* The maximum file name length */
#define MAX_NAME_LEN (40) /* The maximum person/app name length */

/* Error Codes */
#define OK (0) /* No errors, everything as should be */
#define BAD_RECORD (-1) /* Record is somehow malformed */
#define BAD_DATE (-2)  /* Year must be nonnegative
                          Month is not with the range 1-12
                          Day is not with the range 1-31 */
#define BAD_TIME (-3) /* Hour is not with the range 0-23
                        Minute is not with the range 0-59
                        Second is not with the range 0-59 */
#define FILE_READ_ERR (-4) /* Error reading from a file */
#define FILE_WRITE_ERR (-5) /* Error writing to a file */
#define NO_DATA_POINTS (-6) /* No data points */

/* Function Prototypes */
float avg_time_spent(char *, int, int);
float app_time_percentage(char *, char *);
int daily_phone_usage(char *, int, int, char *);
int min_max_usage(char *, int, int, char *);
int compare_phone_usage(char *, int, int, int, int, char *);

#pragma GCC poison access

#endif // HW2_H
