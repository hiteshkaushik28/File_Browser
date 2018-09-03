# File_Browser
## WHAT IS FILE BROWSER?
File Browser is a `LINUX` based terminal file explorer which is useful for displaying and modifying files and directories.
The project is implemented in `C` and `C++`.
This application is developed and tested on `UBUNTU 14.x`. It is expected that it runs on other versions of `UBUNTU` too.

## COMPILING
The project compiles using `makefile`.

The `COMPILE` and `RUN` commands are :

`user@host:~/application_path$ make`

`user@host:~/application_path$ ./file_browser `
## PACKAGE
The package includes `source`,`headers`,`makefile` and this `README`.
# MODES OF OPERATION
## NORMAL MODE
This mode is used for performing files and directories traversal,open tasks.

- By Default, the application runs in NORMAL MODE.
- Initially, all the files and directories of application root are displayed when the application launches.
- The user can move around the list using `UP` and `DOWN` arrow keys.
- To open a file, user needs to navigate to particular line and then press `ENTER`.
- To open a directory, user needs to navigate to particular line and then press `ENTER`.
- To get back to `PARENT` of a particular directory, the user needs to press `BACKSPACE`. 
- The `LEFT` and `RIGHT` arrow keys are used to move to previous visited location and next visited location respectively.
- If the user presses `H` key, then the application moves to its root directory.
- To switch to `COMMAND MODE` from `NORMAL MODE`, press `SHIFT + ':'`
## COMMAND MODE
This mode is used to enter pre-defined commands to modify files and directories.
- Whenever the user switches to `COMMAND MODE`, he/she get a prompt on the last line to enter his/her command.
### This mode gives the following functionalities:
- Renaming a File in the current directory.
- Copying file/files from current directory to another directory.
- Deleting a file from current directory.
- Jumping to any directory from any directory.
- Creating a new file in the current directory.
- Creating a new directory in the current directory.
- Moving file/files from current directory to another directory.
## COMMAND SYNTAX
### 1. COPY
- While in `NORMAL MODE`,navigate to the directory where the source files are present.
- Change to COMMAND MODE(`SHIFT + ':'`)
- Type: ```copy <file1> <file2> <relative location wrt application root>```
- Hit ENTER
### 2. RENAMING A FILE
- While in `NORMAL MODE`,navigate to the directory where the source files are present.
- Change to COMMAND MODE(`SHIFT + ':'`)
- Type: ```rename <old_filename> <new_filename>``` 
- Hit ENTER
### 3. DELETE A FILE
- While in `NORMAL MODE`,navigate to the directory where the source files are present.
- Change to COMMAND MODE(`SHIFT + ':'`)
- Type: ```deletefile <filename>``` 
- Hit ENTER
### 4. GOTO 
- Change to COMMAND MODE(`SHIFT + ':'`)
- Type: ```goto <relative location wrt application root>```
- Hit ENTER

### 5. MOVE FILES
- While in `NORMAL MODE`,navigate to the directory where the source files are present.
- Change to COMMAND MODE(`SHIFT + ':'`)
- Type: ```movefile <file1> <file2> <file3> <relative location wrt application root> ```
- Hit ENTER

### 6. CREATE A FILE
- While in `NORMAL MODE`,navigate to the directory where the file is to be created.
- Change to COMMAND MODE(`SHIFT + ':'`)
- Type: ```createfile <filename>``` 
- Hit ENTER

### 7. CREATE A DIRECTORY
- While in `NORMAL MODE`,navigate to the directory where the directory is to be created.
- Change to COMMAND MODE(`SHIFT + ':'`)
- Type: ```create_dir <dir_name> ```
- Hit ENTER
## CAUTION
- Do not pass too much or too less parameters to commands.It may trigger undefined behaviour.
- Refrain from entering invalid commands.
## CONTROL FLOW COMMANDS
- ```NORMAL MODE --> COMMAND MODE = SHIFT + ':'```
- ```COMMAND MODE --> NORMAL MODE = ESCAPE```
- ```EXIT THE APPLICATION --> 'Q' or 'q' (WORKS ONLY IN NORMAL MODE)```
## FUTURE PERSPECTIVE
This project will be enhanced by adding more COMMANDS and more of excepting and error handling.

**AUTHOR : HITESH KAUSHIK(2018201057)**

