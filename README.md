# Quine Clock in C

This project is a unique implementation of a quine (a program that prints its own source code) that also displays a digital clock within the printed source code. The clock is displayed by marking some of the characters with different colors to form the shape of the clock. **Main idea** is to store the source code into `.source_code` section of the generated executable binary(I'm not sure if this is considered as cheating or not :) )

https://github.com/agulamkadirov/quine_clock_c/assets/59074816/d96ee101-3744-4709-8543-21dd57bab7e1

## Project Structure

- **src/**: Contains the source code files.
  - `quine_clock.c`: The readable, uncompressed version of the source code.
  - `quine_compressed.c`: The compressed version of the source code with extra spaces removed and shortened variable names.
- **build.bash**: The build script to compile the project.

## Build Requirements

To build this project, you need the following tools:
- `objdump`
- `sed`
- `cc`
- `gcc`

## Build Instructions

1. **Default Build (using `quine_clock.c`):**
   - Run the following command:
     ```sh
     ./build.bash
     ```
   - This will:
     - Minimize `quine_clock.c` by removing extra spaces and save it as `temp_quine_one_line.c`.
     - Generate `quine_source.o` from `temp_quine_one_line.c`. In the object file, there will be a section with name `.source_code`.
     - Generate `quine.o` from `quine_clock.c`.
     - Build the main executable binary linking `quine_source.o` and `quine.o`

2. **Compressed Build (using `quine_compressed.c`):**
   - Run the following command:
     ```sh
     ./build.bash --compressed
     ```
   - This will:
     - Use `quine_compressed.c` to generate both `quine_source.o` and `quine.o`.
     - Build the main executable binary using `quine_source.o` and `quine.o`

## Running the Executable

After building, you can run the executable located in the `build` directory:

```sh
./build/quine_clock
```
## Notes

If you build the project as described in the first instruction, the generated binary is not considered a true quine. This is because it first creates a minimized version of the original code by removing extra spaces and stores it in the `.source_code` section to print later. However, it does not use the minimized version to generate the `quine.o` file, so it cannot be considered as using its own source code to print. This version is intended for testing purposes.

After ensuring your code is working correctly, you can compress it and build it with the `--compressed` argument to create a true quine.
