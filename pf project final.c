#include <stdio.h>
#include <string.h>
// Structure to store student details
struct Student {
    int student_roll_no;
    char name[50];
    int age;
    char course[50];
};
// Function to add a student
void add_student(struct Student students[], int *student_count) {
    struct Student new_student;
    // Input student ROLL NO
    printf("Enter student ROLL no: ");
    scanf("%d", &new_student.student_roll_no);
    // Input student name
    printf("Enter student name: ");
    getchar();  // This is necessary for `fgets` to work correctly after `scanf`
    fgets(new_student.name, 50, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0;  // Remove newline from name
    // Input student age
    printf("Enter student age: ");
    scanf("%d", &new_student.age);
    // Input student course
    printf("Enter student course: ");
    getchar();  // Consume the newline left by the previous `scanf`
    fgets(new_student.course, 50, stdin);
    new_student.course[strcspn(new_student.course, "\n")] = 0;  // Remove newline from course
    // Add new student to the list
    students[*student_count] = new_student;
    (*student_count)++;
    printf("Student added successfully!\n");
    // Write updated data to file
    FILE *file = fopen("students.dat", "ab");
    if (file == NULL) {
        printf("Error opening file to save data.\n");
        return;
    }
    fwrite(&new_student, sizeof(struct Student), 1, file);
    fclose(file);
}
// Function to view a student by ROLL NO
void view_student(struct Student students[], int student_count) {
    int student_roll_no, i;
    printf("Enter student roll_no to view: ");
    scanf("%d", &student_roll_no);
    for (i = 0; i < student_count; i++) {
        if (students[i].student_roll_no == student_roll_no) {
            printf("\nStudent roll_no: %d\n", students[i].student_roll_no);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Course: %s\n", students[i].course);
            return;
        }
    }
    printf("Student not found.\n");
}
// Function to update student information
void update_student(struct Student students[], int student_count) {
    int student_roll_no, i,j;
    printf("Enter student ROLL NO to update: ");
    scanf("%d", &student_roll_no);
    for (i = 0; i < student_count; i++) {
        if (students[i].student_roll_no == student_roll_no) {
            printf("Enter new name (current: %s): ", students[i].name);
            getchar();  // This is needed after `scanf` to consume the newline
            fgets(students[i].name, 50, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            printf("Enter new age (current: %d): ", students[i].age);
            scanf("%d", &students[i].age);
            printf("Enter new course (current: %s): ", students[i].course);
            getchar();  // Consume the newline character
            fgets(students[i].course, 50, stdin);
            students[i].course[strcspn(students[i].course, "\n")] = 0;
            printf("Student information updated successfully!\n");
            // Write updated data to file (overwriting)
            FILE *file = fopen("students.dat", "wb");
            if (file == NULL) {
                printf("Error opening file to update data.\n");
                return;
            }
            for (j = 0; j < student_count; j++) {
                fwrite(&students[j], sizeof(struct Student), 1, file);
            }
            fclose(file);
            return;
        }
    }
    printf("Student not found.\n");
}
// Function to delete a student by ROLL NO
void delete_student(struct Student students[], int *student_count) {
    int roll_no, i, j;
    printf("Enter student roll_no to delete: ");
    scanf("%d", &roll_no);
    for (i = 0; i < *student_count; i++) {
        if (students[i].student_roll_no == roll_no) {
            // Shift the remaining students
            for (j = i; j < *student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*student_count)--;
            printf("Student deleted successfully!\n");
            // Write updated data to file (overwriting)
            FILE *file = fopen("students.dat", "wb");
            if (file == NULL) {
                printf("Error opening file to update data.\n");
                return;
            }
            for (j = 0; j < *student_count; j++) {
                fwrite(&students[j], sizeof(struct Student), 1, file);
            }
            fclose(file);
            return;
        }
    }
    printf("Student not found.\n");
}
// Function to list all students
void list_students(struct Student students[], int student_count) {
    if (student_count == 0) {
        printf("No students available.\n");
        return;
    }
    int i;
    for (i = 0; i < student_count; i++) {
        printf("\nStudent Roll no: %d\n", students[i].student_roll_no);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Course: %s\n", students[i].course);
    }
}
// Function to load student data from file
void load_students(struct Student students[], int *student_count) {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No existing data found.\n");
        return;
    }

    while (fread(&students[*student_count], sizeof(struct Student), 1, file)) {
        (*student_count)++;
    }
    fclose(file);
}
int main() {
    struct Student students[100];  // Fixed array for storing students (size 100)
    int student_count = 0;         // Number of students currently stored
    int choice;
    // Load data from file on program start
    load_students(students, &student_count);
    while (1) {
        printf("\nStudent Information System\n");
        printf("1. Add Student\n");
        printf("2. View Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. List All Students\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_student(students, &student_count);
                break;
            case 2:
                view_student(students, student_count);
                break;
            case 3:
                update_student(students, student_count);
                break;
            case 4:
                delete_student(students, &student_count);
                break;
            case 5:
                list_students(students, student_count);
                break;
            case 6:
                printf("Exiting the system...\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    return 0;
}

