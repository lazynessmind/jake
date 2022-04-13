# jake - same as make but for java

**Warning:** This is a WIP and my knowledge of C++ isn't the best of all time. Feel free to improve everthing!

Simple build system for java.
The idea came from the simple make build system for C and C++. Both Gradle and Maven are useful but requires basic knowledge and has a lot of boilerplate.

**Note:** Only tested on Linux Ubuntu 21

### Roadmap:
- [x] Automatic gather of `.java` files and compilation.
- [x] Build the `.jar` file and include the entry point.
- [x] Make some options `optional`. I.e: `entry_point` isn't always needed.
  - [x] Build and source path.
  - [x] Entry point.  
- [x] Add support for 3rd party libraries.
- [ ] Support for external manifest file.
- [ ] Support links to jar on "libs"
- [x] Jakefile option: Include folder.
- [x] Change jakefile to json
- [ ] Maybe my own Java Archive Tool.
- [ ] External repositories
- [ ] Refactor code to use namespaces and classes??

### jakefile:

Create a file called `jakefile.json`.<br>
Note: `[?]` means the field is optional. <br>
Every fields only accepts strings.

- **src_path[?]**: Where the source code is present. Defaults to `./src`.  
- **build_path[?]**: Compilation output files. Defaults to `./build`.  
- **entry_point[?]**: The path to the class that contains the `main` method.
- **project_name**: The project name.
- **version**: The project version.
- **libs**: Array of paths of .jar files to include on classpath.
- **include**: Array of paths to include in the jar.
- **fat_jar[?]**: If set to false, jake doesn't include the libs when creating the jar. Defaults to `"true"`.

```json
{
    "project_name": "Test",
    "version": "1.0.0",
    "src_path": "./example/src",
    "build_path": "./example/build",
    "entry_point": "lazy.test.Main",
    "fat_jar": "true",
    "libs": [
        "./example/libs/math.jar"
    ],
    "include": [
      "./example/include.txt",
      "./examples/assets/"
    ]
}
```

#### Command line:

- **-b**: Build all the sources and creates the `.jar` file.
- **-v**: Prints the current `jake` version.

Basic usage: `./jake [options][path to jakefile]`

```bash
$ ./jake -b .
```

In the above command the `jakefile.properties` is in the root file.

### Build jake:

- Requires:
  - **cmake**

```bash
$ git clone https://github.com/lazynessmind/jake.git
$ cd jake
$ cmake --build .
```
### Third Party Software

- `nlohmann::json` https://github.com/nlohmann/json/releases
