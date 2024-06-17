SRC_DIR="src"
BUILD_DIR="build"
INPUT_FILE="../${SRC_DIR}/quine_compressed.c"
COMPRESSED_FILE="${INPUT_FILE}"
OUTPUT_FILE="../${BUILD_DIR}/quine_clock"

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

# Determine input file based on parameters
if [[ "$#" -eq 0 || "$1" == "--one-line" ]]; then
    INPUT_FILE="../${SRC_DIR}/quine_clock.c"
    TEMP_FILE="temp_quine_one_line.c"
    # Transform input file into a single line
    (sed 's/^[ \t]*//;s/[ \t]*$//' $INPUT_FILE | sed ':a;N;$!ba;s/\n//g')  > $TEMP_FILE
    COMPRESSED_FILE="${TEMP_FILE}"
elif [[ "$1" == "--compressed" ]]; then
    INPUT_FILE="../${SRC_DIR}/quine_compressed.c"
else
    echo "Usage: ./build.sh [--one-line | --compressed]"
    exit 1
fi


# Convert the compressed source code into an object file
objcopy --input-target binary --output-target elf64-x86-64 --binary-architecture i386 $COMPRESSED_FILE quine_source.o --rename-section .data=.source_code
cc -include "time.h" -include "stdio.h" -include "unistd.h" -c $INPUT_FILE -o quine_clock.o
gcc quine_source.o quine_clock.o -T ../linker.ld -o quine_clock

