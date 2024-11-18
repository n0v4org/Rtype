#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define the directories to search for .hpp and .cpp files
# Use '.' to start searching from the current directory
DIRECTORIES=('.')

# Define the clang-format version or binary to use
CLANG_FORMAT="clang-format"

# Optional: Format options
FORMAT_STYLE="file" # Uses the .clang-format file if present

# Iterate over all .hpp and .cpp files in the specified directories
echo "Running clang-format on all .hpp and .cpp files..."
find "${DIRECTORIES[@]}" \( -name "*.hpp" -o -name "*.cpp" \) | while read -r FILE; do
    echo "Formatting $FILE"
    $CLANG_FORMAT -i -style="$FORMAT_STYLE" "$FILE"
done

echo "Formatting OK"