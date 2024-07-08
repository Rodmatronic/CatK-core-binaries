#!/bin/bash

# Navigate to the specified corebin
cd "corebin"

# Compile each .c file in the corebin
for file in *.c; 
do
  # Check if there are any .c files in corebin
  if [ "$file" == "*.c" ]; then
    echo "No .c files to compile."
    exit 0
  fi
  
  # Get the base name of the file (without the .c extension)
  base_name=$(basename "$file" .c)
  
  # Compile the .c file
  gcc -m32 -c "$file" -o "$base_name" -ffreestanding -nostdlib
  
  # Check if the compilation was successful
  if [ $? -eq 0 ]; then
    echo "Compiled $file successfully."
  else
    echo "Failed to compile $file."
  fi
done
