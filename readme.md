# jake - same as make but for java

**Warning:** This is a WIP and my knowledge of C++ isn't the best of all time. Feel free to improve everthing!

Simple build system for java.
The idea came from the simple make build system for C and C++. Both Gradle and Maven are useful but requires basic knowledge and has a lot of boilerplate.

**Note:** Only tested on Linux Ubuntu 21

### Jakefile:

Check the full explanation in [docs/jakefile.md](docs/jakefile.md).

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
