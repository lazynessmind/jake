# Jakefile

### Available properties:
| Name         | Optional | Default        | Description                                                          | Implemented |
| ------------ | -------- | -------------- | -------------------------------------------------------------------- | ----------- |
| projectName | `false`  | `none`         | Defines the name of the output jar.                                  | `true`      |
| version      | `false`  | `none`         | Included in the name of the output jar.                              | `true`      |
| srcPath     | `true`   | `${pwd}/src`   | Where there the java sources are present.                            | `true`      |
| buildPath   | `true`   | `${pwd}/build` | Where all the build outputs will be placed.                          | `true`      |
| libsPath   | `true`   | `${pwd}/libs` | All the local `.jar` files that are included in the final jar.                          | `true`      |
| entryPoint  | `true`   | `none`         | The package to the Java file where the `main` method is implemented. | `true`      |
| include      | `true`   | `none`         | List of folder or files that are copied to the final jar.            | `true`      |
| exclude      | `true`   | `none`         | List of folder or files that are excluded from the final jar.        | `partial`     |
| maven        | `true`   | `none`         | List of maven repositories to access throw `libs`                    | `false`     |

## How it works:

### `include`

Currently you can include files in three forms:
- Using `*` to include everything in the folder.
- Specify the path to a single file.
- Specify the path to a folder. In this case all the files inside are included if not present in the `exclude` list.

```json
{
    "include": [
        "./assets/",
        "./secret.txt",
        "./assets/*"
    ]
}
```

### `exclude`

Currently only supports single file paths.

```json
{
    "exclude": [
        "./assets/dont.md"
        "./assets/other/dont2.js"
    ]
}
```