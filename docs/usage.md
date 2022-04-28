# Usage:

### Available commands:

  - `-v` prints version.
  - `-b` builds jakefile project.
  - `-r` runs the jar program.
  - `-br` builds and runs the jar program.

### `./jake` or `./jake + unknown arg`

Prints usage.

### `./jake -v`

Prints the current version.

### `./jake -b`

Builds the jakefile project.
This command tries to find the `jakefile` in the current directory.

### `./jake -r`

Runs the jar program.
This commands uses the jakefile `projectName` and `version` property to find the jar file with the following name scheme: `[projectName]-[version].jar`.

### `./jake -br`

Does the `./jake -b` and `./jake -r` one after another.