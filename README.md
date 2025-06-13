# Simple AI Scripting Engine & IDE

This project is a custom-built scripting language and Integrated Development Environment (IDE) designed for creating, training, and running simple neural networks. The entire system, including the language parser and the IDE, is written from scratch in C++.

## Key Features

-   **Custom Scripting Language:** A simple, high-level language with 16 core functions for neural network and matrix operations.
-   **Integrated Development Environment (IDE):** A basic IDE with essential features for writing and running scripts, including:
    -   **Auto-Completion:** Speeds up coding by automatically completing function names from short prefixes.
    -   **Simple Error Detection:** Highlights basic syntax errors in the code.
    -   **Comment Recognition:** Supports standard and special comment types.
    -   **Code Execution:** Allows running the entire script or individual lines.

## The Language

### Syntax and Execution

-   **Full Script Execution:** A "Run" button in the IDE compiles and executes the entire script.
-   **Comments:** Lines starting with a `#` symbol are treated as comments and are ignored by the compiler.
    ```
    # This is a comment.
    new_model(m, i, o, 5, 1, 1) # This part is also a comment.
    ```
-   **Single-Line Execution:** Lines starting with `\#` are special comments that can be executed individually. This is useful for testing or debugging specific commands without running the whole script.
    ```
    \# predict(model, 1, 2, 3, 4, 5)
    ```

### Auto-Completion

To improve efficiency, every function can be auto-completed by typing its prefix and pressing the `TAB` key.

| Function         | Prefix | Description                                     |
| ---------------- | ------ | ----------------------------------------------- |
| `add_layer`      | `ad`   | Adds a new layer to the model.                  |
| `ai_train`       | `ai`   | Trains the neural network model.                |
| `create_matrix`  | `cr`   | Creates a new matrix with random values.        |
| `erase`          | `er`   | Deletes a specified model or matrix.            |
| `erase_layer`    | `el`   | Removes a layer from the model.                 |
| `load_model`     | `loa`  | Loads a model from a file.                      |
| `loss`           | `los`  | Calculates the loss of the model.               |
| `read_matrix`    | `re`   | Reads matrix data from a file.                  |
| `new_model`      | `ne`   | Creates a new neural network model.             |
| `matrix_reshape` | `ma`   | Reshapes the dimensions of a matrix.            |
| `predict`        | `pr`   | Generates a prediction using the trained model. |
| `save_model`     | `sa`   | Saves a model to a file.                        |
| `set_layer`      | `se`   | Modifies the size of a layer in the model.      |
| `shape`          | `sh`   | Returns the shape (dimensions) of a matrix.     |
| `_size`          | `si`   | Returns the total number of elements in a matrix.|
| `write_matrix`   | `wr`   | Writes matrix data to a file.                   |

---

## Function Reference

#### Model Operations
-   `new_model(model_name, input_matrix, output_matrix, ...)`: Creates a model with specified input and output data.
-   `ai_train(model, activation_function, batch_size)`: Trains the specified model.
-   `predict(model, inputs)`: Predicts an output from the model given a set of inputs.
-   `loss(model)`: Calculates the current loss value for the model.
-   `save_model(model, file_path)`: Saves the model's architecture and weights to a file.
-   `load_model(model_name, file_path)`: Loads a pre-trained model from a file.

#### Layer Operations
-   `add_layer(model, sizes...)`: Adds a new layer to the model with the given neuron counts.
-   `set_layer(model, sizes...)`: Rearranges the model's layer sizes.
-   `erase_layer(model, layer_index)`: Erases a chosen layer from the model.

#### Matrix Operations
-   `create_matrix(matrix_name, rows, cols, min_val, max_val)`: Creates a matrix with random values between `min_val` and `max_val`.
-   `read_matrix(matrix_name, file_path)`: Reads data from a text file and assigns it to `matrix_name`.
-   `write_matrix(matrix_name, file_path)`: Saves a matrix to a text file.
-   `matrix_reshape(matrix, new_sizes...)`: Rearranges the dimensions of a matrix.
-   `shape(matrix)`: Returns the shape of the matrix (e.g., "40x5").
-   `_size(matrix)`: Returns the total number of elements in the matrix.

#### General
-   `erase(object_name)`: Deletes a model or matrix from memory.

---

## Example Usage

The following script demonstrates how to create two matrices, read data into them from files, build a model, train it, and then use it for predictions.
create_matrix(o,40, 1, 0 ,40)
read_matrix(o , C:\Users\Lenovo\Desktop\Ai_Compieler\output.txt)
new_model(model , i ,o , 40 , 10,10 )
load_model(model , C:\Users\Lenovo\Desktop\Ai_Compieler\model.txt)
predict(model , 1,2,3,4,5)
