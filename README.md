# Blake Rainbow Tables

![GitHub top language](https://img.shields.io/github/languages/top/dean-dalianis/blake-rainbow-tables?style=flat-square&color=5D6D7E)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/dean-dalianis/blake-rainbow-tables?style=flat-square&color=5D6D7E)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

The project is a collection of code files that allow for the generation and cracking of rainbow tables, which are used
for password hashing and retrieval. It includes a password generator, hash functions, reduction functions, and chain
generators. The purpose of the project is to provide a tool for generating rainbow tables that can be used for password
cracking and recovery, offering a faster and more efficient method than traditional brute force techniques.

## Table of Contents

- ⚙ [Features](#⚙-Features)
  - ⚙ [Architecture](#⚙-Architecture)
  - 🔗 [Dependencies](#🔗-Dependencies)
  - ⚡ [Performance](#⚡-Performance)
- 📂 [Project Structure](#📂-Project-Structure)
- 🧩 [Modules](#🧩-Modules)
- 📄 [License](#📄-License)

## ⚙ Features

### ⚙ Architecture

The system follows a modular architecture, with separate components for generating rainbow tables and cracking
passwords. It uses multithreading to improve performance and speed. The codebase is written in C++ and designed to
efficiently generate rainbow tables and crack passwords using the Blake256 hash algorithm and reduction functions. The
system also utilizes POSIX realtime extensions for scheduling and synchronization in multithreaded environments.

### 🔗 Dependencies

The system does not rely on external libraries but uses POSIX headers and functions for multithreading, scheduling, and
semaphore management. These dependencies are built-in within the operating system and do not require additional
installations.

### ⚡ Performance

The system's performance relies on the efficient usage of multithreading to parallelize the generation of rainbow
tables. By dividing the workload among multiple threads, the system can take advantage of modern multi-core processors
to speed up the table generation process.

## 📂 Project Structure

The project structure is as follows:

```plaintext
blake-rainbow-tables
├── rainbow_table_cracker
│   ├── cracker.cpp
│   ├── hash
│   │   ├── blake_ref.cpp
│   │   ├── blake_ref.h
│   │   ├── hash.cpp
│   │   └── hash.h
│   ├── info.h
│   └── reduce
│       ├── reduction_function.cpp
│       └── reduction_function.h
├── rainbow_table_generator
│   ├── chainGenerator
│   │   ├── chain_generator.h
│   │   └── chains_generator.cpp
│   ├── hash
│   │   ├── blake_ref.cpp
│   │   ├── blake_ref.h
│   │   ├── hash.cpp
│   │   └── hash.h
│   ├── info.h
│   ├── passwordGenerator
│   │   ├── password_generator.cpp
│   │   └── password_generator.h
│   ├── pThreads
│   │   ├── pthread.h
│   │   ├── sched.h
│   │   └── semaphore.h
│   ├── rbt_generator.cpp
│   └── reduce
│       ├── reduction_function.cpp
│       └── reduction_function.h
├── README.md
└── rt_3k_2k_tmp

9 directories, 25 files
```

## 🧩 Modules

### Root
| File                             | Summary                                     |
|----------------------------------|---------------------------------------------|
| [**rt_3k_2k_tmp**](rt_3k_2k_tmp) | Passwords and hashes for the rainbow table. |

### rainbow_table_generator

| File                                                               | Summary                                                                                                                                                                                                                                                                                                      |
|--------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [**info.h**](rainbow_table_generator/info.h)                       | Contains preprocessor directives that define various constants used in the program, such as the number of threads, character set length, maximum password length, chain count, chain length, output path, and file name. These constants define key parameters for generating rainbow tables in the program. |
| [**rbt_generator.cpp**](rainbow_table_generator/rbt_generator.cpp) | Initializes threads to generate unique passwords and create a rainbow table by merging the results. It uses mutex locks to ensure thread safety and measures the elapsed time of the process.                                                                                                                |

#### passwordGenerator

| File                                                                                           | Summary                                                                                                                                                                                                                                                                                                                                                                                        |
|------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [**password_generator.h**](rainbow_table_generator/passwordGenerator/password_generator.h)     | Defines a class called PasswordGen. It has a member variable "passwords" which is an unordered set of strings. The class also has a default constructor and a destructor. It provides a method called "password_generator" that takes a string as input and generates a password. The class also has a method called "get_password" which returns the generated password as a character array. |
| [**password_generator.cpp**](rainbow_table_generator/passwordGenerator/password_generator.cpp) | Implementation of a password generator. It generates unique passwords of length 6 using a predefined character set. It uses recursion to generate all possible combinations of characters and stores them in a set to ensure uniqueness. The generated passwords can be retrieved using the get_password() function.                                                                           |

#### hash

| File                                                            | Summary                                                                                                                                                                                                                                                                                                                                                                                    |
|-----------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [**hash.h**](rainbow_table_generator/hash/hash.h)               | Provides a function hash_blake256 that calculates the BLAKE-256 hash value for a given input data. It includes the necessary dependencies, such as blake_ref.h, which contains the required definitions and structures for implementing the BLAKE hash function.                                                                                                                           |
| [**hash.cpp**](rainbow_table_generator/hash/hash.cpp)           | Responsible for calculating the BLAKE-256 hash value for a given input data. It dynamically allocates memory for the hash value, invokes the Hash function with the specified parameters, and returns the resulting hash.                                                                                                                                                                  |
| [**blake_ref.h**](rainbow_table_generator/hash/blake_ref.h)     | Provides the necessary definitions, functions, and constants for implementing the BLAKE hash function in C. It includes data types, structures for the hash state, and functions for initialization, data update, and finalization. This header file is essential for incorporating the BLAKE hash function into a C program.                                                              |
| [**blake_ref.cpp**](rainbow_table_generator/hash/blake_ref.cpp) | an implementation of the BLAKE hash function. It includes functions for hash initialization, salt addition, data compression, and finalization. The code supports both 32-bit and 64-bit versions of BLAKE, depending on the desired hash output length. It processes the input data in blocks and applies various bitwise operations and transformations to produce the final hash value. |

#### pThreads

| File                                                            | Summary                                                                                              |
|-----------------------------------------------------------------|------------------------------------------------------------------------------------------------------|
| [**pthread.h**](rainbow_table_generator/pThreads/pthread.h)     | This is an implementation of the threads API of POSIX 1003.1-2001.                                   |
| [**sched.h**](rainbow_table_generator/pThreads/sched.h)         | Provides an implementation of POSIX realtime extensions as defined in POSIX 1003.1b-1993 (POSIX.1b). |
| [**semaphore.h**](rainbow_table_generator/pThreads/semaphore.h) | Provides Semaphores implementation as defined in POSIX 1003.1b-1993  (POSIX.1b).                     |

#### reduce

| File                                                                                | Summary                                                                                             |
|-------------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------|
| [**reduction_function.h**](rainbow_table_generator/reduce/reduction_function.h)     | Declares the reduction function.                                                                    |
| [**reduction_function.cpp**](rainbow_table_generator/reduce/reduction_function.cpp) | Implements the reduction function to generate a character array from a hash array and a step value. |

#### chainGenerator

| File                                                                                   | Summary                                                                                                                                                                                               |
|----------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [**chain_generator.h**](rainbow_table_generator/chainGenerator/chain_generator.h)      | Declares the Chain class and the function to generate a chain.                                                                                                                                        |
| [**chains_generator.cpp**](rainbow_table_generator/chainGenerator/chain_generator.cpp) | Implements the function to generate a chain by creating a Chain object, processing the password through hashing and reduction functions, and storing the resulting head and tail in the Chain object. |

### rainbow_table_cracker

| File        | Summary                                                                                                                                                                                                                                                                                        |
|-------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| info.h      | Defines constants related to the creation of rainbow tables, including the number of threads, character set length, maximum password length, chain length, output path, and file name. This information can be used to control and configure the generation and storage of rainbow tables.     |
| cracker.cpp | Loads a rainbow table from a file and allows the user to input a hash value. If the hash is found in the table, the corresponding password is displayed. If not, the code performs reduce and hash operations to search for a matching chain in the table, and displays the password if found. |

#### hash

These files are the same as those in the rainbow_table_generator module.

#### reduce

These files are the same as those in the rainbow_table_generator module.

## 📄 License

This project is licensed under the `MIT` License. See the [LICENSE](LICENSE) file for additional info.
