# CppMySQL

A C++ project file template for developing System that utilizes MySQL Database Connection

This project also includes code sample on executing database queries. (Credit to Iqmal Rizal)

## Notes before use
This project uses CMake as its compiler, with Multi-OS Support

Please refer the Conan Package Manager Documentation page for component installations
https://docs.conan.io/en/latest/getting_started.html

## Installation
to install the packages required for this project, run the command in the project file : 

```shell script
conan install conan -if conan
```

## Packages included
Packages included is generated inside conan/conanfile.txt

```text
[requires]
boost/1.73.0
libmysqlclient/8.0.17

[generators]
cmake
```

## Credits
[Adi Iman](https://github.com/adimixx)  
[Iqmal Rizal](https://www.instagram.com/iqmalriz/)

adimixx / 2020
