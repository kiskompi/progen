# Progen Project Structure Generator
This app will be a simple project structure generator. It is under development and in alpha state. Right now it only works as a folder structure generator, but later more features will be added. Created only to practice the language by making something potentially useful thing.

## Features to implement
- [x] Folder structure generation
- [ ] Extend the previous with permission handling.
- [ ] Project and Folder generation modes
- [ ] Makefile generation for standard project buildups

## How to use it
Build the source with build.sh. The following flags are to use:
1. --help
2. --path 'path_to__project' sets the path to the project to be created. If not an absolute path, then the place of the binary will be the starting point.
3. --file 'filename.str' is the file from which the software reads the structure of the project.
4. --cmake ***bool*** to be implemented

## The .str file
Progen reads the project structure from a given file with a .str file extension. This file is as follows:

name1#333
|--name2#456
|--|--name3#765
|--|--name5
|-----|--name6
|--name4
name7

Where the folders tabbed with more '|--' strings than the previous line are the children of that, and #xxx are the permissions on the folder in chmod form:
> 4 stands for "read",
> 2 stands for "write",
> 1 stands for "execute", and
> 0 stands for "no permission."