# jake - same as make but for java

**Warning:** This is a WIP and my knowledge of C++ isn't the best of all time. Feel free to improve everthing!

Simple build system for java.
The idea came from the simple make build system for C and C++. Both Gradle and Maven are useful but requires basic knowledge and has a lot of boilerplate.

**Note:** Only tested on Linux Ubuntu 21

### Documentation:

Jakefile: [docs/jakefile.md](docs/jakefile.md).<br>
TODO: [docs/todo.md](docs/todo.md).<br>
Usage: [docs/usage.md](docs/usage.md).<br>

### Build jake:

- Requires:
  - **cmake**

```bash
git clone https://github.com/lazynessmind/jake.git
cd jake
cmake .
make
```
### Third Party Software

- `nlohmann::json` https://github.com/nlohmann/json/releases
