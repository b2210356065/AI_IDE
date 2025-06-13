There is a string support for perceive simple errors, Comment lines , Run Lines
Comment lines can initialize with "#" symbol
If there is a "\" symbol after "#" this means that line runs only.
For compile all code there is a run button.

There are 19 funtions in my basic language. Every functions can completed automaticlly. You can examine my below list
            {"ad", "add_layer"},
            {"ai", "ai_train"},
            {"cr", "create_matrix"},
            {"er", "erase"},
            {"el", "erase_layer"},
            {"loa","load_model"},
            {"los","loss"},
            {"re", "read_matrix"},
            {"ne", "new_model"},
            {"ma", "matrix_reshape"},
            {"pr", "predict"},
            {"sa", "save_model"},
            {"se", "set_layer"},
            {"sh", "shape"},
            {"si", "_size"},
            {"wr", "write_matrix"},


In this map there is a essential prefix string for each function. If you write this prefix strings then click "TAB" your string will completed automaticlly. You can see
every functions mission below.

predict(model , inputs) : This function predicts a output from your model.
set_layer(model,  sizes) : rearranges your models layers size.
erase_layer(model,  sizes) : erases a layer you choosed.
add_layer(model,  sizes) : adds a layer for your model.
loss(model) : calculate loss of your model.
ai_train(model, "tanh" , batch_size): its trains your model with corresponding values.
reshape_matrix(matrix , sizes) : rearranges sizes of a matrix.
_size(matrix) : gives matrix total size.
shape(matrix) : gives shape of matrix.
create_matrix(matrix_name , sizes , random_no1 , random_no2) : creates a matrix with random values thats between random_no1 and random_no2.
read_matrix(matrix_name , file_path) : reads your matrix and assign it to matrix_name.
write_matrix(matrix_name , file_path) : saves your matrix to a file
save_model(model , file_path) : reads your model and assign it to model_name.
load_model(model_name , file_path) : saves your model to a file
erase(object_name) : erases a model or matrix.
new_model(model,input_matrix , output_matrix , input_size ,embed_sizes, embed_sizes) : creates a model with input and outputs.

Here an example for usage:

create_matrix(i,40, 5, 0 ,40)
read_matrix(i ,C:\Users\Lenovo\Desktop\Ai_Compieler\input.txt) # My file path for input.txt you can reach this or others txt in that project file
create_matrix(o,40, 1, 0 ,40)
read_matrix(o , C:\Users\Lenovo\Desktop\Ai_Compieler\output.txt)
new_model(model , i ,o , 40 , 1 ,1)
add_layer(model, 8 , 5,1)
ai_train(model, tanh , 8)
predict(model, 1, 2, 3, 4, 5)
predict(model, 6, 7, 8, 9, 10)
predict(model, 11, 12, 13, 14, 15)
predict(model, 16, 17, 18, 19, 20)
predict(model, 21, 22, 23, 24, 25)
predict(model, 26, 27, 28, 29, 30)
predict(model, 31, 32, 33, 34, 35)
predict(model, 36, 37, 38, 39, 1)
predict(model, 2, 3, 4, 5, 6)
predict(model, 7, 8, 9, 10, 11)
predict(model, 12, 13, 14, 15, 16)
predict(model, 17, 18, 19, 20, 21)
predict(model, 22, 23, 24, 25, 26)
predict(model, 27, 28, 29, 30, 31)
predict(model, 32, 33, 34, 35, 36)
predict(model, 37, 38, 39, 1, 2)
predict(model, 3, 4, 5, 6, 7)
predict(model, 8, 9, 10, 11, 12)
predict(model, 13, 14, 15, 16, 17)
predict(model, 18, 19, 20, 21, 22)
---------------------------------
create_matrix(i,40, 5, 0 ,40)
read_matrix(i ,C:\Users\Lenovo\Desktop\Ai_Compieler\input.txt)
create_matrix(o,40, 1, 0 ,40)
read_matrix(o , C:\Users\Lenovo\Desktop\Ai_Compieler\output.txt)
new_model(model , i ,o , 40 , 10,10 )
load_model(model , C:\Users\Lenovo\Desktop\Ai_Compieler\model.txt)
predict(model , 1,2,3,4,5)