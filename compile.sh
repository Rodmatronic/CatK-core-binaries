#!/bin/bash

echo "[remove coreutil bin directory & sbin directory]"
rm -f -r ./bin & rm -f -r ./sbin

echo "[make coreutil bin/sbin directory]"
mkdir ./bin & mkdir ./sbin

# Navigate to the specified corebin
cd "coreutil-bin"

echo "![Compiling bin...]!"
for file in *.c; 
do
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

# Navigate to the specified corebin
cd "../coreutil-sbin"

echo "![Compiling sbin...]!"
# Compile each .c file in sbin
for file in *.c; 
do
  if [ "$file" == "*.c" ]; then
    echo "No .c files to compile."
    exit 0
  fi
  
  # Get the base name of the file (without the .c extension)
  base_name=$(basename "$file" .c)
  
  # Compile the .c file
  gcc "$file" -o "../sbin/$base_name"
  
  # Check if the compilation was successful
  if [ $? -eq 0 ]; then
    echo "[ $file ]"
  else
    echo "[ Failed to compile $base_name. ]"
  fi
done