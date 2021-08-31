#ifndef HW1_H
#define HW1_H

#define ARRAY_SIZE (50)
extern char g_msg[ARRAY_SIZE];
extern char g_cip[ARRAY_SIZE];


#define UNEXPECTED_INPUT (-2)
#define OUT_OF_BOUNDS (-1)
#define SUCCESS (0)

int encode(int, int, int);
int checksum(void);

#endif // HW1_H
