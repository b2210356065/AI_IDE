#include "window.h"
#include <QApplication>
#include "ai_model.h"
#include "matrix.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Window w;
    w.show();
    return QApplication::exec();
}
//create_matrix(i,40, 5, 0 ,40)
//read_matrix(i ,C:\Users\Lenovo\Desktop\Ai_Compieler\input.txt)
//create_matrix(o,40, 1, 0 ,40)
//read_matrix(o , C:\Users\Lenovo\Desktop\Ai_Compieler\output.txt)
//new_model(model , i ,o , 40 , 10,10 )
//add_layer(model, 8 , 50,10)
//ai_train(model, tanh , 8)
//
//predict(model , 1,2,3,4,5)



//create_matrix(i,40, 5, 0 ,40)
//read_matrix(i ,C:\Users\Lenovo\Desktop\Ai_Compieler\input.txt)
//create_matrix(o,40, 1, 0 ,40)
//read_matrix(o , C:\Users\Lenovo\Desktop\Ai_Compieler\output.txt)
//new_model(model , i ,o , 40 , 10,10 )
//load_model(model , C:\Users\Lenovo\Desktop\Ai_Compieler\model.txt)
//predict(model , 1,2,3,4,5)