//Boyce_libFC.c

#include "Boyce_libFC.h"

// Global variables
FileEntry file_table[MAX_FILES];  // File table to track files
int file_count = 0;               // Number of files in the system

// Create a new file
int fileCreate(const char *filename) 
{

    // Check if file already exists
    for (int i = 0; i < file_count; i++) 
    {
        if (strcmp(file_table[i].filename, filename) == 0) 
        {
            printf("Error: File '%s' already exists.\n", filename);
            return -1;
        }
    }

    // Create the file on the local disk
    FILE *file = fopen(filename, "w");
    if (!file) 
    {
        printf("Error: Unable to create file '%s'.\n", filename);
        return -1;
    }
    fclose(file);

    // Add file to the file table
    strcpy(file_table[file_count].filename, filename);
    file_table[file_count].size = 0;
    file_table[file_count].is_open = 0;  // File is closed
    file_count++;

    printf("File '%s' created successfully.\n", filename);
    return 0;
}

// Open a file
int fileOpen(const char *filename) 
{
    for (int i = 0; i < file_count; i++) 
    {
        if (strcmp(file_table[i].filename, filename) == 0) 
        {
            if (file_table[i].is_open) 
            {
                printf("Error: File '%s' is already open.\n", filename);
                return -1;
            }
            file_table[i].is_open = 1;  // Mark file as open
            printf("File '%s' opened successfully.\n", filename);
            return i;  // Return file index
        }
    }

    printf("Error: File '%s' not found.\n", filename);
    return -1;
}

// Write data to a file
int fileWrite(int file_index, const char *data) 
{

    if (!file_table[file_index].is_open) 
    {
        printf("Error: File '%s' is not open.\n", file_table[file_index].filename);
        return -1;
    }

    int data_size = strlen(data);

    // Write data to the local file
    FILE *file = fopen(file_table[file_index].filename, "w");
    if (!file) {
        printf("Error: Unable to open file '%s' for writing.\n", file_table[file_index].filename);
        return -1;
    }
    fwrite(data, 1, data_size, file);
    fclose(file);

    file_table[file_index].size = data_size;
    printf("Data written to file '%s' successfully.\n", file_table[file_index].filename);
    return 0;
}

// Read data from a file
int fileRead(int file_index, char *buffer, int buffer_size) 
{
    if (!file_table[file_index].is_open) 
    {
        printf("Error: File '%s' is not open.\n", file_table[file_index].filename);
        return -1;
    }

    // Read data from the local file
    FILE *file = fopen(file_table[file_index].filename, "r");
    if (!file) {
        printf("Error: Unable to open file '%s' for reading.\n", file_table[file_index].filename);
        return -1;
    }
    
    size_t bytes_read = fread(buffer, 1, buffer_size - 1, file);
    buffer[bytes_read] = '\0';  // Null-terminate the buffer
    fclose(file);

    printf("Data read from file '%s' successfully.\n", file_table[file_index].filename);
    return bytes_read;  // Return number of bytes read
}



// Close a file
int fileClose(int file_index) 
{
    if (file_index < 0 || file_index >= file_count) 
    {
        printf("Error: Invalid file index %d.\n", file_index);
        return -1;
    }

    if (!file_table[file_index].is_open) 
    {
        printf("Error: File '%s' is not open.\n", file_table[file_index].filename);
        return -1;
    }

    file_table[file_index].is_open = 0;  // Mark file as closed
    printf("File '%s' closed successfully.\n", file_table[file_index].filename);
    return 0;
}



// Delete a file
int fileDelete(const char *filename) 
{
    for (int i = 0; i < file_count; i++)
     {
        if (strcmp(file_table[i].filename, filename) == 0) 
        {
            if (file_table[i].is_open) 
            {
                printf("Error: File '%s' is open. Please close it before deleting.\n", filename);
                return -1;
            }

            // Remove the file from the local disk
            if (remove(filename) != 0) 
            {
                printf("Error: Unable to delete file '%s'.\n", filename);
                return -1;
            }

            // Shift remaining files in the table
            for (int j = i; j < file_count - 1; j++) 
            {
                file_table[j] = file_table[j + 1];
            }
            file_count--;

            printf("File '%s' deleted successfully.\n", filename);
            return 0;
        }
    }

    printf("Error: File '%s' not found.\n", filename);
    return -1;
}