![year](https://img.shields.io/badge/Year-2021-lightgrey?style=plastic)
![author](https://img.shields.io/badge/Author-Johnny%20Madigan-yellow?style=plastic)
![C](https://img.shields.io/badge/C%20lang-lightgrey?style=plastic&logo=C)

# Vector

'Vector' is my implementation of an Abstract Data Type in the *C* lang. Resembles Lists like in *C#* and *Python*. Supporting operations such as resizing, push, pop, insert/remove at index, copying, foreach, clearing, and destroying.

Given an API (dbl_vector.h), the challenge is to implement the source code which satisfies all operations mentioned above. These have been implemented as pure functions.

# Run
- Run using a LINUX VM for safety
- Ensure source.c and header.h files are in the same folder
- Compile using: `gcc -Wall -D MOCK_MEMORY=1 -o app dbl_vector.c dbl_vector_driver.c -lm -lpthread -lrt`
- Shorter compile line: `gcc -Wall -o app dbl_vector.c dbl_vector_driver.c`
- Run using: `./app`

# Expected output from the test suit
```
Push 3.35:
3.35

Push 33.00:
3.35,33.00

Push 69.06:
3.35,33.00,69.06

Push 42.25:
3.35,33.00,69.06,42.25

Push 20.63:
3.35,33.00,69.06,42.25,20.63

Push 25.01:
3.35,33.00,69.06,42.25,20.63,25.01

Push 63.66:
3.35,33.00,69.06,42.25,20.63,25.01,63.66

Push 86.36:
3.35,33.00,69.06,42.25,20.63,25.01,63.66,86.36

Push 30.17:
3.35,33.00,69.06,42.25,20.63,25.01,63.66,86.36,30.17

Push 2.49:
3.35,33.00,69.06,42.25,20.63,25.01,63.66,86.36,30.17,2.49

Copy vec1 to vec2:
3.35,33.00,69.06,42.25,20.63,25.01,63.66,86.36,30.17,2.49

Pop from vec1:
3.35,33.00,69.06,42.25,20.63,25.01,63.66,86.36,30.17

Pop from vec1:
3.35,33.00,69.06,42.25,20.63,25.01,63.66,86.36

Pop from vec1:
3.35,33.00,69.06,42.25,20.63,25.01,63.66

vec2 should be unchanged:
3.35,33.00,69.06,42.25,20.63,25.01,63.66,86.36,30.17,2.49

Last element of vec1: 63.66
Last element of vec2: 2.49

Insert 36.50 at 0:
36.50,3.35,33.00,69.06,42.25,20.63,25.01,63.66

Insert 76.54 at 5:
36.50,3.35,33.00,69.06,42.25,76.54,20.63,25.01,63.66

Insert 31.79 at 500:
36.50,3.35,33.00,69.06,42.25,76.54,20.63,25.01,63.66,31.79

Remove element at 0:
3.35,33.00,69.06,42.25,76.54,20.63,25.01,63.66,31.79

Remove element at 5:
3.35,33.00,69.06,42.25,76.54,25.01,63.66,31.79

Remove element at 500:
3.35,33.00,69.06,42.25,76.54,25.01,63.66,31.79

Evaluate a linear function at each point in vec1:
5.50 * 3.35 + 3.00 = 21.41
5.50 * 33.00 + 3.00 = 184.48
5.50 * 69.06 + 3.00 = 382.85
5.50 * 42.25 + 3.00 = 235.37
5.50 * 76.54 + 3.00 = 423.96
5.50 * 25.01 + 3.00 = 140.57
5.50 * 63.66 + 3.00 = 353.11
5.50 * 31.79 + 3.00 = 177.82

Clearing vec1:

Destroying vec1 and vec2!
```
