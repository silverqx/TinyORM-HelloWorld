<h1><img src="https://github.com/silverqx/TinyORM/blob/main/resources/icons/logo-optim.svg" width="34" height="34" alt="TinyORM Logo" align="center">&nbsp;Hello world example for TinyORM</h1>

[![www.tinyorm.org][docs-badge]][docs]
[![Building: Hello world - TinyORM - www.tinyorm.org][helloworld-docs-badge]][helloworld-docs]
[![License MIT][license-badge]][license]

This Hello world example application does several things, it prepares the `qmake` or `CMake` build systems using dynamic linkage and does two simple queries against the `SQLite` database. The first query uses the `QueryBuilder` and the second one uses the `ORM` (`Post` model).

The `HelloWorld.sqlite3` database contains one `posts` table with two records. Copy this database into the build folder, one folder up, or wherever you want, and set the correct path to it in the [`main.cpp`](https://github.com/silverqx/TinyORM-HelloWorld/blob/main/main.cpp#L37-L38) file.

Copy the [`.qmake.conf.example`](https://github.com/silverqx/TinyORM-HelloWorld/blob/main/.qmake.conf.example) to `.qmake.conf`, open it, and set the following `qmake` variable so the `HelloWorld` project can find the [`qmake/TinyOrm.pri`](https://github.com/silverqx/TinyORM/blob/main/qmake/TinyOrm.pri) file:

 - `TINY_MAIN_DIR` - Path to the folder that contains the `TinyORM/` folder, it's not a path to the `TinyORM` source folder itself! Look at the expected [Folders structure](https://www.tinyorm.org/building/tinyorm#folders-structure).

Copy the `.env.(win32|unix|mingw).example` file to `.env.(win32|unix|mingw)` and set the following `qmake` variables so the `HelloWorld` project can find the shared library in the TinyORM's __build folder__:

 - `TINYORM_BUILD_TREE` - Path to the TinyORM build folder.
 - `TINY_VCPKG_ROOT`    - Path to the vcpkg installation folder. If not defined, then it tries to use the `VCPKG_ROOT` environment variable.
 - `TINY_VCPKG_TRIPLET` - The vcpkg triplet to use (vcpkg/installed/$$TINY_VCPKG_TRIPLET/). If not defined, then it tries to guess the vcpkg triplet based on the current compiler and OS (based on the `QMAKESPEC`), and as the last thing, it tries to use the `VCPKG_DEFAULT_TRIPLET` environment variable.

The `qmake/TinyOrm.pri` auto-configures the `TinyORM` library.

I will not explain all details here as everything is already described in the [Building - Hello world with qmake](https://www.tinyorm.org/building/hello-world#hello-world-with-qmake) or [Building - Hello world with CMake](https://www.tinyorm.org/building/hello-world#hello-world-with-cmake) documentation.

[docs-badge]: https://img.shields.io/badge/Docs-www.tinyorm.org-blue
[docs]: https://www.tinyorm.org
[helloworld-docs-badge]: https://img.shields.io/badge/Docs-HelloWorld-blue
[helloworld-docs]: https://www.tinyorm.org/building/hello-world
[license-badge]: https://img.shields.io/github/license/silverqx/TinyORM
[license]: https://github.com/silverqx/TinyORM/blob/main/LICENSE
