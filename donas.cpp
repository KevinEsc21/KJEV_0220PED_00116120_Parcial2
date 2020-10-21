#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct producto{
    string nombre;
    float precio_unitario;
};

struct pedido{
    string apellido;
    vector<producto> lista_comida;
};

//Definiendo nuestras colas;
queue<pedido>colaDonas;
queue<pedido>colaComida;

//TODO: Prototipos de funciones
void atenderPedido();
void menuDonas(pedido);
void menuComida(pedido);
pedido llenarPedido();
float montoporpedido(pedido);
void calculoGananciaDonas();
void calculoGananciaComida();

int main(){
    
    bool status=true;
    while(status){
        int opcion;

        cout << endl << "****BIENVENIDO A DONUT MISTER****" << endl;
        cout << "Escoja una de las siguientes opciones" << endl;
        cout << "1) Atender pedidos de clientes" << endl;
        cout << "2) Calcular ganancias por venta de donas" << endl;
        cout << "3) Calcular ganancias por venta de platos fuertes" << endl;
        cout << "4) Salir" << endl;
        cout << "Ingrese una opcion: "; 
        cin >> opcion; cin.ignore();

        switch (opcion){
        case 1:
            atenderPedido();
            break;
        case 2:
            calculoGananciaDonas();
            break;
        case 3:
            calculoGananciaComida();
            break;
        case 4:
            status=false;
            cout << endl << "Finalizando programa...";
            break;
        default:
            cout << endl << "Ingrese una opcion valida" << endl;
            break;
        }

    }

    
    return 0;
}


void atenderPedido(){
    
    pedido Pedido;

    cout << endl << "Ingrese el apellido del cliente: ";
    getline(cin,Pedido.apellido);
    bool status=true;
    
    while(status){
    int opcion;
    cout << "Escoja lo que se desea ordenar: " << endl;
    cout << "1) Donas" << endl;
    cout << "2) Platos fuertes" << endl;
    cout << "ingrese una opcion: ";
    cin >> opcion; cin.ignore();

        switch (opcion){
            case 1:
                menuDonas(Pedido);
                status=false;
                break;  
                
            case 2:
                menuComida(Pedido);
                status=false;
                break;
            default:
                cout << endl << "Ingrese una opcion valida" << endl << endl;
                break;
        }
    } 
    

}

void menuDonas(pedido Pedido){
    float monto;
    producto Producto;

    bool status=true;
    
    while(status){
        int opcion;
        cout << endl << "Escoja el tipo de donas que desea" << endl;
        cout << "1) Donas sencillas, $1.00" << endl;
        cout << "2) Donas rellenas, $1.25" << endl;
        cout << "3) Sabores especiales (moca), $1.50" << endl;
        cout << "4) Sabores especiales (caramelo), $1.50" << endl;
        cout << "5) Finalizar pedido" << endl;
        cout << "Ingrese la opcion: ";
        cin >> opcion; cin.ignore();
        while(opcion==5 && Pedido.lista_comida.empty()){
            cout << "Debes comprar algo" << endl;
            cout << "Ingrese la opcion: ";
            cin >> opcion; cin.ignore();
        }

        switch (opcion){
            case 1:
                Producto.nombre="Dona sencilla";
                Producto.precio_unitario = 1.00;
                Pedido.lista_comida.push_back(Producto);
                break;
            case 2:
                Producto.nombre="Dona rellena";
                Producto.precio_unitario = 1.25;
                Pedido.lista_comida.push_back(Producto);
                break;
            case 3:
                Producto.nombre="Dona Moca";
                Producto.precio_unitario = 1.50;
                Pedido.lista_comida.push_back(Producto);
                break;
            case 4:
                Producto.nombre="Dona Caramelo";
                Producto.precio_unitario = 1.50;
                Pedido.lista_comida.push_back(Producto);
                break;
            case 5:
                monto=montoporpedido(Pedido);
                cout << endl << "Gracias cliente " << Pedido.apellido << " por su compra de $" << monto << endl;
                colaDonas.push(Pedido);
                status=false;
                break;    
            default:
                cout << "Ingrese una opcion valida" << endl;
                break;
        }
    }
}

void menuComida(pedido Pedido){
    float monto;
    producto Producto;

    bool status=true;
    
    while(status){
        int opcion;
        cout << endl << "Escoja el tipo de plato fuerte que desea" << endl;
        cout << "1) Desayuno, $2.50" << endl;
        cout << "2) Almuerzo, $5.00" << endl;
        cout << "3) Cena, $3.50" << endl;
        cout << "4) Finalizar pedido" << endl;
        cout << "Ingrese la opcion: ";
        cin >> opcion; cin.ignore();
        while(opcion==4 && Pedido.lista_comida.empty()){
            cout << "Debes comprar algo" << endl;
            cout << "Ingrese la opcion: ";
            cin >> opcion; cin.ignore();
        }

        switch (opcion){
            case 1:
                Producto.nombre="Desayuno";
                Producto.precio_unitario = 2.50;
                Pedido.lista_comida.push_back(Producto);
                break;
            case 2:
                Producto.nombre="Almuerzo";
                Producto.precio_unitario = 5.00;
                Pedido.lista_comida.push_back(Producto);
                break;
            case 3:
                Producto.nombre="Cena";
                Producto.precio_unitario = 3.50;
                Pedido.lista_comida.push_back(Producto);
                break; 
            case 4:
                monto=montoporpedido(Pedido);
                cout << endl << "Gracias cliente " << Pedido.apellido << " por su compra de $" << monto << endl;
                colaComida.push(Pedido);
                status=false;
                break;     
            default:
                cout << "Ingrese una opcion valida." << endl;
                break;
        }
    }
}

float montoporpedido(pedido Pedido){
    float monto=0;

    for(int i=0; i<Pedido.lista_comida.size(); i++){
        monto+=Pedido.lista_comida[i].precio_unitario;
    }
    return monto;
}

void calculoGananciaDonas(){
    float ganancia=0;
    queue<pedido>Copy=colaDonas;

    while(!Copy.empty()){
        pedido Pedido=Copy.front();
        ganancia+=montoporpedido(Pedido);
        Copy.pop();
    }
    cout << endl << "La ganancia total de donas vendidas es: $" << ganancia << endl; 
}

void calculoGananciaComida(){
    float ganancia=0;
    queue<pedido>Copy=colaComida;

    while(!Copy.empty()){
        pedido Pedido=Copy.front();
        ganancia+=montoporpedido(Pedido);
        Copy.pop();
    }
    cout << endl << "La ganancia total de comida vendidas es: $" << ganancia << endl; 
}