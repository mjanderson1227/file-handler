#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

/* IDEA
 * 1. Create a struct for the course.
 * 2. For read, read in a struct from a file at the id that the user specifies.
 * 3. For create, create a struct and write it to the file at the id that the user specifies.
 * 4. For update, read in a struct from a file at the id that the user specifies, update the struct, and write it back
 * to the file.
 * 5. For delete, read in a struct from a file at the id that the user specifies, set the struct to null, and write it
 * back to the file.
 * */
typedef struct
{
    char course_Name[80];
    char course_Sched[4];
    unsigned course_Hours;
    unsigned course_Size;
    unsigned padding;
} COURSE;

typedef unsigned char byte_t;

off_t getCourseFileSize(int fd)
{
    return lseek(fd, 0, SEEK_END);
}

void printCourse(COURSE course)
{
    printf("%s\n", course.course_Name);
    printf("%s\n", course.course_Sched);
    printf("%u", course.course_Hours);
    printf("%u", course.course_Size);
}

void createCourse(int courseFile)
{
    // Using the buffer created in main.
    char buffer[100];
    int courseNumber;
    char courseName[80];
    char courseSched[4];
    unsigned courseHours;
    unsigned courseSize;
    COURSE course;

    // i. Course number (zero-indexed integer)
    printf("Enter course number: ");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%d", &courseNumber);

    // ii. Course name (string possibly containing whitespace)
    printf("Enter course name: ");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%s", course.course_Name);

    // iii. Course schedule (string ∈ {MWF, TR})
    printf("Enter course schedule: ");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%s", course.course_Sched);
    // iv. Course credit hours (unsigned integer)
    printf("Enter course credit hours: ");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%u", &course.course_Hours);

    // v. Course enrollment (unsigned integer
    printf("Enter course enrollment: ");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%u", &course.course_Size);

    // Add the struct to the file.
    lseek(courseFile, 0, courseNumber * sizeof(COURSE));
    write(courseFile, &course, sizeof(COURSE));
    printf("Course added!\n");
}

void readCourse(int fd_courses)
{
    COURSE course;
    char buffer[100];
    int number;

    printf("Enter a CS course number: \n");
    fgets(buffer, 100, stdin);
    sscanf(buffer, "%d\n", &number);

    printf("Course number: %d\n", number * (int)sizeof(COURSE));
    lseek(fd_courses, 0, number * sizeof(COURSE));
    read(fd_courses, &course, sizeof(COURSE));
    printCourse(course);
}

int printMenu()
{
    printf("Enter one of the following actions or press CTRL-D to exit.\n");
    printf("C - create a new course record.\n");
    printf("U - update an existing course record.\n");
    printf("R - read an existing course record.\n");
    printf("D - delete an existing course record.\n");
    return 1;
}

int main(int argc, char* argv[])
{
    char input;
    char buffer[100];
    int courses = open("assign3/data/courses.dat", O_RDWR);

    if (courses == -1)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    while (printMenu() && fgets(buffer, 5, stdin))
    {
        sscanf(buffer, "%c", &input);

        switch (input)
        {
        case 'C':
            createCourse(courses);
            break;
        case 'R':
            readCourse(courses);
            break;
        case 'U':
            // TODO: Create update.
            break;
        case 'D':
            // TODO: Create delete.
            break;
        default:
            printf("Invalid option.");
        }
    }
    close(courses);
    return 0;
}
