#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

// Rand int from 0 to 15
int rand_package(){
    srand (time (0) * rand());  
    return rand() % 16;
}

// Rand int from -50 to 50
int rand_position(){
    srand (time (0) * rand());  
    return 50 - (rand() % 101);
}

void create_map(){
    int deposit_qnt = 3;
    int client_qnt = 30;
 
    for (int i = 1; i <= deposit_qnt; i++)
        cout << "Deposito" << to_string(i) << ';' << rand_position() << ';' << rand_position() << endl;

    for (int i = 1; i <= client_qnt; i++)
        cout << "Cliente" << to_string(i) << ';' << rand_position() << ';' << rand_position() << ';' << rand_package() << endl;
    
}

int main(){
    for (int i = 1; i <= 5; i++)
    {
        cout << "========================" << endl;
        cout << "MAP #" << i << endl;
        create_map();
        cout << "========================" << endl << endl;

    }
    

}
