# CppMySQL

A C++ project file template for developing System that utilizes MySQL Database Connection

This project also includes code sample on executing database queries. (Credit to Iqmal Rizal)

Tested on macOS Catalina

## Notes before use
This project uses CMake as its compiler, with Multi-OS Support

Please refer the Conan Package Manager Documentation page for component installations
https://docs.conan.io/en/latest/getting_started.html

For mac users, please install cmake in your system (using brew is easier)

```shell script
brew install cmake
brew install conan
```

## Installation
to install the packages required for this project, run the command in the project file : 

```shell script
conan install conan -if conan --build missing
```

## Packages included
This project file includes conanfile.txt that includes the required packages for this project

```text
[requires]
libmysqlclient/8.0.17

[generators]
cmake
```

## Usage

In macOS, host must be provided in form of ip address. using localhost does not make the connection to mysql successfull

## Credits
[Adi Iman](https://instagram.com/adimixx)  
[Iqmal Rizal](https://instagram.com/iqmalriz/)

adimixx / 2020
