#!/bin/bash
#create_files_with_subdirs.sh

#mkdir for creating directories.
#echo and redirection ( >) for writing text to files.
#date for generating the current date and time.

#Creates a main directory with the current date and time as its name.
current_time=$(date +"%Y%m%d_%H%M%S") #creates a timestamp variable for the name of the main directory
mkdir "$current_time" #creates the main directory with the timestamp

#Generates ten subdirectories within the main directory, named file101 to file110.
for i in {101..110}; do #iterates from 101 to 110
    subdir="$current_time/file$i" #defines the subdirectory path
    mkdir -p "$subdir" #create the subdirectory within the main directory

    #In each subdirectory, creates a .txt file named tuser501.txt to tuser510.txt.
    #Writes a unique programming language name (e.g. “Python”) into each .txt file
    echo "Fortran" > "$subdir/tuser$(($i - 100)).txt"
done #end of loop
