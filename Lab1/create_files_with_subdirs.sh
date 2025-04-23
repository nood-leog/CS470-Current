#!/bin/bash
#create_files_with_subdirs.sh

#mkdir for creating directories.
#echo and redirection ( >) for writing text to files.
#date for generating the current date and time.

#Creates a main directory with the current date and time as its name.
current_time=$(date +"%Y%m%d_%H%M%S") #creates a timestamp variable for the name of the main directory
mkdir "$current_time" #creates the main directory with the timestamp

#Explain mkdir
#mkdir stands for "Make Directory", and is used to create and name a directory/folder. Example:
#mkdir my_directory

#Explain date
#date is a command that displays or sets the system date and time. In this case, it formats the current date and time to be used as a directory name. Example:
#date  
#output: Weekday Month Day hh:mm:ss timezone year


#Generates ten subdirectories within the main directory, named file101 to file110.
for i in {101..110}; do #iterates from 101 to 110
    subdir="$current_time/file$i" #defines the subdirectory path
    mkdir -p "$subdir" #create the subdirectory within the main directory

    #In each subdirectory, creates a .txt file named tuser501.txt to tuser510.txt.
    #Writes a unique programming language name (e.g. “Python”) into each .txt file
    echo "Fortran" > "$subdir/tuser$(($i - 100)).txt"

    #explain echo
    #echo is a command that outputs the strings it is given. Example:
    #echo "Hello, World!"
    #output: Hello, World!

    #Using a " > ", we redirect the output into a file
    #echo "Hello, World!" > hello.txt
    #output: creates a file named hello.txt with the content "Hello, World!"

done #end of loop
