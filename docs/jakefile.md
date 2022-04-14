# Jakefile

### Available properties:
| Name         | Optional | Default        | Description                                                          | Implemented |
| ------------ | -------- | -------------- | -------------------------------------------------------------------- | ----------- |
| project_name | `false`  | `none`         | Defines the name of the output jar.                                  | `true`      |
| version      | `false`  | `none`         | Included in the name of the output jar.                              | `true`      |
| src_path     | `true`   | `${pwd}/src`   | Where there the java sources are present.                            | `true`      |
| build_path   | `true`   | `${pwd}/build` | Where all the build outputs will be placed.                          | `true`      |
| entry_point  | `true`   | `none`         | The package to the Java file where the `main` method is implemented. | `true`      |
| include      | `true`   | `none`         | List of folder or files that are copied to the final jar.            | `true`      |
| exclude      | `true`   | `none`         | List of folder or files that are excluded from the final jar.        | `false`     |
| libs         | `true`   | `none`         | List of .jar files or links to .jar files.                           | `partial`   |
| maven        | `true`   | `none`         | List of maven repositories to access throw `libs`                    | `false`     |

## How it works:

### `libs`

You can include a file in your local machine or give a link to a remote `.jar` file, in both situations the file is extracted and placed in the build folder.

```json
{
    "libs": [
        "./libs/math.jar",
        "https://repo1.maven.org/maven2/com/badlogicgames/gdx/gdx/1.10.0/gdx-1.10.0.jar"
    ]
}
```

### `include`

You can include a folder or a single file. If you specify a folder, all the contents inside are copied to the final jar.

```json
{
    "include": [
        "./assets/",
        "./secret.txt"
    ]
}
```