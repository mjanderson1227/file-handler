#include "assign5.h"

int printMenu();
void printCourse(int, COURSE);

void createCourse(int fd_courses)
{
    char buffer[80];
    int courseNumber;
    COURSE course;

    printf("Enter course number: ");
    fgets(buffer, 6, stdin);
    sscanf(buffer, "%d", &courseNumber);

    // Check if the file already has a name associated with it.
    lseek(fd_courses, courseNumber * sizeof(COURSE), SEEK_SET);
    if (read(fd_courses, &course, sizeof(COURSE)) == sizeof(COURSE) && course.course_Hours)
    {
        printf("ERROR: course already exists\n");
        return;
    }
    lseek(fd_courses, -sizeof(COURSE), SEEK_CUR);

    printf("Enter course name: ");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%[^\n]\n", course.course_Name);

    printf("Enter course schedule: ");
    fgets(buffer, 5, stdin);
    sscanf(buffer, "%s", course.course_Sched);

    printf("Enter course credit hours: ");
    fgets(buffer, 5, stdin);
    sscanf(buffer, "%u", &course.course_Hours);

    printf("Enter course enrollment: ");
    fgets(buffer, 5, stdin);
    sscanf(buffer, "%u", &course.course_Size);

    write(fd_courses, &course, sizeof(COURSE));
    printf("Course added!\n");
}

void updateCourse(int fd_courses)
{
    COURSE existingCourse;
    COURSE newCourse;
    int courseNumber;
    char buffer[80];

    printf("Enter the course number: ");
    fgets(buffer, 6, stdin);
    sscanf(buffer, "%d", &courseNumber);

    // Grab the previous possible course data.
    lseek(fd_courses, courseNumber * sizeof(COURSE), SEEK_SET);
    if (read(fd_courses, &existingCourse, sizeof(COURSE)) < sizeof(COURSE) || !existingCourse.course_Hours)
    {
        printf("ERROR: course not found\n");
        return;
    }
    lseek(fd_courses, -sizeof(COURSE), SEEK_CUR);

    printf("Enter course name: ");
    if (*fgets(buffer, 80, stdin) == '\n')
        strcpy(newCourse.course_Name, existingCourse.course_Name);
    else
        sscanf(buffer, "%[^\n]\n", newCourse.course_Name);

    printf("Enter course schedule: ");
    if (*fgets(buffer, 5, stdin) == '\n')
        strcpy(newCourse.course_Sched, existingCourse.course_Sched);
    else
        sscanf(buffer, "%s\n", newCourse.course_Sched);

    printf("Enter course credit hours: ");
    if (*fgets(buffer, 4, stdin) == '\n')
        newCourse.course_Hours = existingCourse.course_Hours;
    else
        sscanf(buffer, "%u", &newCourse.course_Hours);

    printf("Enter course enrollment: ");
    if (*fgets(buffer, 5, stdin) == '\n')
        newCourse.course_Size = existingCourse.course_Size;
    else
        sscanf(buffer, "%u", &newCourse.course_Size);

    write(fd_courses, &newCourse, sizeof(COURSE));
    printf("Course updated!\n");
}

void readCourse(int fd_courses)
{
    COURSE course;
    char buffer[80];
    int number;

    printf("Enter a CS course number: ");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%d\n", &number);

    lseek(fd_courses, number * sizeof(COURSE), SEEK_SET);
    if (read(fd_courses, &course, sizeof(COURSE)) < sizeof(COURSE) || !course.course_Hours)
    {
        printf("ERROR: Course not found\n");
        return;
    }

    printCourse(number, course);
}

void deleteCourse(int fd_courses)
{
    COURSE deletionObject;
    char buffer[80];
    int courseNumber;

    printf("Enter a course to delete: ");
    fgets(buffer, 80, stdin);
    sscanf(buffer, "%d", &courseNumber);

    // Load existing course data to see if one already exists.
    lseek(fd_courses, courseNumber * sizeof(COURSE), SEEK_SET);
    if (deletionObject.course_Hours == 0 || read(fd_courses, &deletionObject, sizeof(COURSE)) < sizeof(COURSE))
    {
        printf("ERROR: course not found\n");
        return;
    }
    lseek(fd_courses, -sizeof(COURSE), SEEK_CUR);

    // Set every bit in the struct to 0.
    deletionObject = (COURSE){0};

    // Write the zero struct to the class location.
    write(fd_courses, &deletionObject, sizeof(COURSE));
    printf("Course deleted!\n");
}

int main(int argc, char* argv[])
{
    char input;
    char buffer[3];
    int courses = open("assign3/data/courses.dat", O_RDWR | O_CREAT);

    if (courses == -1)
    {
        printf("Error opening file.\n");
        exit(1);
    }

    while (printMenu() && fgets(buffer, 3, stdin))
    {
        sscanf(buffer, "%c", &input);

        switch (input)
        {
        case 'C':
            createCourse(courses);
            break;
        case 'U':
            updateCourse(courses);
            break;
        case 'R':
            readCourse(courses);
            break;
        case 'D':
            deleteCourse(courses);
            break;
        default:
            printf("ERROR: invalid option\n");
        }
    }
    close(courses);
    return 0;
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

void printCourse(int courseNumber, COURSE course)
{
    printf("Course number: %d\n", courseNumber);
    printf("Course name: %s\n", course.course_Name);
    printf("Scheduled days: %s\n", course.course_Sched);
    printf("Credit hours: %u\n", course.course_Hours);
    printf("Enrolled Students: %u\n", course.course_Size);
}
