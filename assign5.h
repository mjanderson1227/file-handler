#ifndef ASSIGN3_H
#define ASSIGN3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

typedef struct
{
    char course_Name[80];
    char course_Sched[4];
    unsigned int course_Hours;
    unsigned int course_Size;
    unsigned int padding;
} COURSE;

/*
 * Prompts the user and writes a new course struct to the file.
 * Parameters:
 * int fd - the file descriptor to write to.
 */
void createCourse(int);

/*
 * Prompts the user and updates an existing course struct in the file.
 * Parameters:
 * int fd - the file descriptor to write to.
 */
void updateCourse(int);

/*
 * Prompts the user and writes a new course struct to the file.
 * Parameters:
 * int fd - the file descriptor to write to.
 */
void readCourse(int);

/*
 * Prompts the user and writes a new course struct to the file.
 * Parameters:
 * int fd - the file descriptor to write to.
 */
void deleteCourse(int);
#endif
