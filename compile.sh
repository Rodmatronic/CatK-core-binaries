#!/bin/bash

echo "remove coreutil bin directory"
rm -f -r ./bin

echo "make coreutil bin directory"
mkdir ./bin

# Navigate to the specified corebin
cd "corebin"

echo "Compiling..."
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
  gcc "$file" -o "../bin/$base_name"
  
  # Check if the compilation was successful
  if [ $? -eq 0 ]; then
    echo "[ $file ]"
  else
    echo "[ Failed to compile $base_name. ]"
  fi
done
