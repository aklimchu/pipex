# pipex: Implementation of pipes
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://opensource.org/licenses/GPL-3.0)
Try piping various commands and also here_doc (user input from the command line)!

## 🚀 Installation!

Clone the repository and navigate to the project directory:
```bash
git clone https://github.com/aklimchu/pipex.git
cd pipex
```
## 🛠️ Build the Program!

### Use `make` command to create the program:
```bash
make
```
### Or - use `make bonus` command to create the bonus program:
```bash
make bonus
```

## 🎮 Running the Program

* #### Pipex:
```bash
./pipex file1 cmd1 cmd2 file2
```
* #### Pipex-bonus(multiple pipes):
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
* #### Pipex-bonus(user input):
```bash
./pipex here_doc LIMITER cmd cmd1 file
```
*(you can choose any combination of symbols as LIMITER, 
the program will stop collecting the input if LIMITER is typed)*

## 🧹 Cleaning Up

To remove object files and libraries:
```bash
make fclean
```
## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE - see the LICENSE.md file for details
