# jake - same as make but for java

Simple build system for java.
The idea came from the simple make build system for C and C++. Both Gradle and Maven are useful but requires basic knowledge and has a lot of boilerplate.

### Roadmap:
- [x] Automatic gather of `.java` files and compilation.
- [x] Build the `.jar` file and include the entry point.
- [x] Make some options `optional`. I.e: `entry_point` isn't always needed.
  - [x] Build and source path.
  - [x] Entry point.  
- [ ] Add support for 3rd party libraries.
- [ ] Support for external manifest file.
- [ ] Jakefile option: Include folder.

### jakefile:

- Create a file called `jakefile.properties`
  - **src_path**: Where the `.java` are stored.  
  - **build_path**: Compilation output files.  
  - **entry_point**: The path to the class that contains the `main` method.
  - **jar_name**: The output jar name.  

```toml
src_path=./src
build_path=./build
entry_point=me.test.Main
jar_name=Test
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

- Requires `cmake`.

```bash
$ git clone https://github.com/lazynessmind/jake.git
$ cd jake
$ cmake -b .
```
