#!/bin/bash

mkdir -p source470
mkdir -p dest470

for i in {1..100}; do
    echo "100 files" > "source470/file_$i.txt"
done

#copy files
cp source470/* dest470/
