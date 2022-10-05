# Params Parser

## Task description

Need to write an implementation of the `ParseParams` function, located in the file `params_parser/params_parser.cpp`.
The function takes a string with parameters in the form "/param value" and returns a `std::map` that maps parameter names to values.
Parameter values containing spaces must be enclosed in quotes or escaped with a backslash. At the same time, quotes themselves, forward and back slashes can also be escaped.
In case of incorrect input data, the function throws an exception.

When performing a task, only the standard library should be used. The code should be expressive so that readers of the program don't have to guess how it works or what the author meant.
  
The implementation must satisfy the provided unit-tests:  
`parser_tests/basic_suite.cpp` - basic test suite
`parser_tests/errors_suite.cpp` - test suite for invalid input data
`parser_tests/extra_suite.cpp` - an additional set of tests, mostly about escaping
  
You are welcome to add your own unit-tests to `parser_tests/extra_suite.cpp` or to a new file.

## Before start

1. Download submodules (`git submodule init` + `git submodule update`)
2. Generate a project for your IDE using cmake
3. Compile, run the `ParserTests` project and make sure the tests fail
4. Complete the task and make sure that all tests pass