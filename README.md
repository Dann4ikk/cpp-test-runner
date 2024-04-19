# Test Runner

The Test Runner is a command-line tool that runs a C++ program against a set of test cases and compares the program's output with the expected output for each test case. It compiles the program, runs it with the input from each test case, and reports whether the test passed or failed.

## Directory Structure

The Test Runner expects the following directory structure:  
(parent_directory)  
|-- main.cpp  
|-- input.txt  
|-- output.txt  
|-- tests  
‎ ‎ ‎ ‎ |-- input.01  
‎ ‎ ‎ ‎ |-- output.01  
‎ ‎ ‎ ‎ |-- input.02  
‎ ‎ ‎ ‎ |-- output.02  
‎ ‎ ‎ ‎‎ |-- ...  

- `main.cpp`: The C++ source file that contains the program to be tested.
- `input.txt`: A temporary file used by the Test Runner to provide input to the program.
- `output.txt`: A temporary file used by the Test Runner to capture the program's output.
- `tests/`: A directory containing the test cases. Each test case consists of an `input.n` file (containing the input for the test) and a corresponding `output.n` file (containing the expected output for the test).

## Usage
First of all, compile the program:


To run the Test Runner, use the following command:
```bash
./test_runner <parent_directory> [-s|--show-input]
```
- `<parent_directory>`: The path to the directory containing the `main.cpp`, `input.txt`, `output.txt`, and `tests/` directory.
- `-s` or `--show-input` (optional): If this flag is provided, the Test Runner will display the input for each test case along with the actual and expected outputs.
## Example Output
===== Test 01 =====

Input:
1 2

Actual Output:
3.000000

Expected Output:
3.000000

Time Taken: 12 ms

Test 01 passed.

===== Test 02 =====

Actual Output:
1.414214 3.141593

Expected Output:
1.414213 3.141593

Time Taken: 8 ms

Test 02 failed.

===== Summary =====
1/2 tests passed.

### The Test Runner outputs the following information for each test case:

- Test number
- Input (if the `-s` or `--show-input` flag is provided)
- Actual output from the program
- Expected output
- Time taken to run the test case
- Whether the test passed or failed

After running all test cases, a summary is displayed showing the number of tests passed out of the total number of tests.

Note: The Test Runner assumes that the `main.cpp` file is compiled correctly using a `make` command. If your build process is different, you might need to modify the line `system(("make -C " + parentDir).c_str());` in the code accordingly.
