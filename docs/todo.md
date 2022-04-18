# Todo:

- [ ] Include:
  - [x] All in folder.
  - [x] All in single folder.
  - [x] Single file.
  - [ ] File extension filter.
- [ ] Exclude:
  - [x] Single file; 
  - [ ] All in folder.
  - [ ] All in single folder.
  - [ ] File extension filter.
- [ ] Support for external manifest file.
- [ ] Support links to jar on "libs"
- [ ] Maybe my own Java Archive Tool.
- [ ] External repositories
- [ ] Include support for OS dependent jars
    - Maybe `${libsPath}/linux`, `${libsPath}/windows` 

# Done:

- [x] Automatic gather of `.java` files and compilation.
- [x] Build the `.jar` file and include the entry point.
- [x] Make some options `optional`. I.e: `entry_point` isn't always needed.
  - [x] Build and source path.
  - [x] Entry point.  
- [x] Add support for 3rd party libraries.
- [x] Jakefile option: Include folder.
- [x] Change jakefile to json
- [x] Refactor code to use namespaces and classes??