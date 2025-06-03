//Boyce_testFC.c

//to run:
//make Boyce_testFC
//./Boyce_testFC

#include "Boyce_libFC.h"
#include <ctype.h>  // For tolower()

// Function to display the menu
void displayMenu() 
{
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    printf("4. Read from a file\n");
    printf("5. Close a file\n");
    printf("6. Delete a file\n");
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() 
{
    printf("\nPress Enter to continue...");
    getchar();  // Wait for Enter key
    getchar();  // Clear the newline character from the buffer
}

int main() 
{
    char filename[MAX_FILENAME];
    char introduction[] = "Hello, my name is Alex Boyce.\n\n"
                          "I am currently pursuing two bachelor's degrees in both computer science and psychology. "
                          "I am passionate about using code as a medium for creativity, and also systems programming.\n"
                          "I also really like to program arduino boards and other microcontrollers like the RP2040.\n"
                          "On the side I have been teaching myself Flutter and Dart and building out a personal website.\n\n"                        

                          "In the time I am not in front of a computer, I enjoy dirt biking, hiking, and spending time with my cats.\n"
                          "I also remotely work full time as a security operations analyst for a startup based in Salt Lake City.\n\n"
                          
                          "This project involves creating a file system library in C.\n"
                          "The library allows for basic file operations such as creating, opening, writing, reading, closing, and deleting files.\n";

    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];

    while (1) {
        displayMenu();
        scanf("%d", &choice);  // Get user choice
        getchar();  // Clear the newline character from the buffer

        switch (choice) 
        {
            case 1:  // Create a file
                printf("Enter the filename to create: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) 
                {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Open a file
                printf("Enter the filename to open: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                file_index = fileOpen(filename);
                if (file_index == -1) 
                {
                    printf("Error opening file.\n");
                }
                waitForUser();
                break;

            case 3:  // Write to a file
                if (file_index == -1) 
                {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Writing introduction to file '%s'...\n", filename);
                    if (fileWrite(file_index, introduction) != 0) 
                    {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            case 4:  // Read from a file 
                if (file_index == -1) 
                {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    int bytes_read = fileRead(file_index, buffer, sizeof(buffer));
                    if (bytes_read < 0) 
                    {
                        printf("Error reading from file.\n");
                    } else {
                        printf("Data read from file '%s':\n%s\n", filename, buffer);
                    }
                }
                waitForUser();
                break;

            case 5:  // Close a file
                if (file_index == -1) 
                {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    if (fileClose(file_index) != 0) 
                    {
                        printf("Error closing file.\n");
                    } else {
                        file_index = -1;  // Reset file index
                    }
                }
                waitForUser();
                break;

            case 6:  // Delete a file
                printf("Enter the filename to delete: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileDelete(filename) != 0) 
                {
                    printf("Error deleting file.\n");
                }
                waitForUser();
                break;


            case 7:  // Exit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }

    return 0;
}