# Genetic Traveling Salesman
## Description
This is a university project for the 'advanced algorithms' course. Uses SFML for visualization, and the parameters are easy to change.
To step a generation, hit space.
## Prerequisites
- CMake (Version >= 3.16)
- C++ Compiler supporting C++11 standard or later
## Getting Started
1. Clone this repository to your local machine:
```bash
git clone --recursive https://github.com/infopek/genetic-traveling-salesman.git
```
2. Navigate to the cloned directory:
```bash
cd ./genetic-traveling-salesman/
```
3. Generate build files:
```bash
cmake --preset=x64-debug
```
4. Build the project:
```bash
cd ./build-x64-debug/
cmake --build .
```
5. Run unit tests (there are none; genetic algorithm is mostly random):
```bash
# In the project root directory
ctest --preset=windows-default
```
## License
This project is licensed under the MIT License - see the LICENSE file for details.
