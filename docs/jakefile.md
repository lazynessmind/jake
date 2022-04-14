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
| exclude      | `true`   | `none`         | List of folder or files that are excluded from the final jar.        | `false`     |
| maven        | `true`   | `none`         | List of maven repositories to access throw `libs`                    | `false`     |

## How it works:

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