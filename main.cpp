/*VALDACIONES QUE SE ME OCURREN AL TOQUE:
Que solo acepte txt, y si no hay crea uno desde 0, esto para que no truene el programa
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    
    // Inicialización de los vectores paralelos separados por sus diferentes funciones
     int codigoProducto[100] = {}; 
    string nombreProducto[100] = {""};
    int cantidadProducto[100] = {};
    float precioProducto[100] = {};
    string ubicacionProducto[100] = {""};
    
    /*
    string linea;//Inicializamos evariable linea para el manejo de archivos
    string texto; //Variable para guardar un valor
    */

    // Variable para el bucle while inicializado en false para que no termine el programa
    bool salir = false; 

/*======================================================================================
BUCLE PRINCIPAL DEL MENÚ
======================================================================================*/
    
    // Bucle while que va a repetir el menú principal mientras no se presione el botón de salir
    // El símbolo ! nos dice que mientras salir siga siendo false se seguirá ejecutando, sino terminaría
    while (!salir) {
        
        //Ejemplo de este video: https://www.youtube.com/watch?v=RBZidsPGkfs
        /*
        //llamamos al inventario en forma de variable
        ifstream inventario("inventario.txt");

        while(getline(inventario, linea)){ //Si queremos obtener todo el inventario leido hasta que se acabe se necesita un bucle while
        //getline(inventario, linea); //EN cambio si solo queremos obtener del inventario la primera linea porque fue la unica que pedimos
            texto = texto + linea + "\n"; //imprimir todos el documento respetando los saltos de linea
    }
        inventario.close(); //Buena práctica para cerrar el archivo y que no este comiendo memoria
        cout << texto << endl; //Imprime todo el archivo
        //cout << linea << endl; //Impresion de primera linea del inventario.txt

        //Para ingresar valores dentro del inventario
        ofstream inventario2("inventario.txt");
        inventario2 << texto << "Nuevo producto gg\n"; //Para agregar un nuevo texto al texto que ya esta en el inventario, si no ponemos la variable texto, se eliminara todo lo demás
        inventario2.close();*/

        //Abrimos el archivo del inventario para lectura, esto para cargar todo lo que hay dentro
        ifstream inventario("inventario.txt");

        string linea;
        while(getline(inventario, linea)){
            int i = 0;
            
            //Lo que vamos a hacer va a ser separar las columnas mediante las comas, esto quiere decir que cada coma va a ser donde termine una columna y empieza la siguiente
            stringstream ss(linea);
            string campo; //Para ir almacenando cada campo temporal hasta que terminemos

            //Leemos el txt mientras vamos ingresando los valores a los vectores
            getline(ss, campo, '/');
            codigoProducto[i] = stoi(campo); //Lo que hace stoi es trasnformar el texto en entero

                        getline(ss, campo, '/');
            nombreProducto[i] = campo;

                        getline(ss, campo, '/');
            cantidadProducto[i] = stoi(campo); 

                        getline(ss, campo, '/');
            precioProducto[i] = stof(campo); //Lo que hace stof es trasnformar el texto en un flotante

                        getline(ss, campo, '/');
            ubicacionProducto[i] = campo;

            i++; //Para ir recorriendo todos los campos xd
               }
        // Mostrar menú de opciones
        cout << "\n=========================================" << endl;
        cout << "    FERRETERIA EL MARTILLO DE SAID     " << endl;
        cout << "=========================================" << endl;
        cout << "1. Ingresar nuevo producto" << endl;
        cout << "2. Modificar productos" << endl;
        cout << "3. Ver productos" << endl;
        cout << "4. Buscar producto más caro" << endl;
        cout << "5. Encontrar el producto más barato" << endl;
        cout << "===========================================" << endl;
        cout << "6. Guardar cambios en el sistema" << endl;
        cout << "7. Salir" << endl;
        cout << "=========================================\n" << endl;
        cout << "Seleccione una opción: ";
        
        int opc;
        cin >> opc;

/*======================================================================================
OPCIÓN 1: ALMACENAR PRODUCTO NUEVO
======================================================================================*/
        
        if (opc == 1) {
            
            /*------- Asignación de nombre al producto nuevo -------*/
            cout << "\n=== AGREGAR NUEVO PRODUCTO ===" << endl;
            cout << "Ingrese el nombre del producto: ";
            string nombreProductoNuevo;
            cin.ignore();  // Limpiar el buffer para usar getline
            getline(cin, nombreProductoNuevo);  // Permitir que el nombre tenga espacios

            /*------- Asignar código de producto (automático o manual) -------*/
            int codigoProductoNuevo = 0;
            cout << "\n--- ASIGNACIÓN DE CÓDIGO ---" << endl;
            cout << "¿Prefieres que se asigne un código automático o prefieres asignarlo tú?" << endl;
            cout << "1. Automático" << endl;
            cout << "2. Manual" << endl;
            cout << "Opción: ";
            cin >> opc;

            if (opc == 1) {
                // Asignación AUTOMÁTICA de código
                // Variable para almacenar el código más alto encontrado en el inventario
                int maxCodigo = 0;

                for (int i = 0; i < 100; i++) { // Ciclo for que recorre todo el arreglo de códigos de productos
                    if (codigoProducto[i] > maxCodigo) {    // Si el código en la posición actual es mayor al máximo encontrado hasta ahora
                        maxCodigo = codigoProducto[i];  // Actualizar el código más alto encontrado
        }
    }
                codigoProductoNuevo = maxCodigo + 1;  // Asignar el siguiente código porque sino se va a asignar al mismo lugar
                cout << "\nCódigo asignado automáticamente: " << codigoProductoNuevo << endl;
            } 
            else {
                // Asignación MANUAL de código
                bool codigoRepetido = false;
                do {
                    // Asignar el código del producto nuevo MANUALMENTE
                    cout << "\nIngrese el código del producto: ";
                    cin >> codigoProductoNuevo;
                    
                    // Verificar que no haya un código repetido dentro del arreglo
                    codigoRepetido = false;
                    for (int i = 0; i < 100; i++) {
                        if (codigoProducto[i] == codigoProductoNuevo) { //Si hay repetido entonces mostrar mensaje de error y pedir otro
                            cout << "Este código ya existe. Intenta con otro." << endl;
                            codigoRepetido = true;
                            break;
                        }
                    }
                } while (codigoRepetido);  // Mientras el código sea repetido, seguirá pidiendo uno nuevo
            }

            /*------- Asignar cantidad en stock del producto -------*/
            cout << "\nIngrese la cantidad en stock: ";
            int cantidadProductoNuevo;
            cin >> cantidadProductoNuevo;
        
            /*------- Asignar precio unitario del producto con decimales -------*/
            cout << "Ingrese el precio del producto: $";
            float precioProductoNuevo;
            cin >> precioProductoNuevo;

            /*------- Buscar espacio vacío para agregar el producto -------*/
            // Se crea una variable bool que será falsa hasta que se encuentre un espacio vacío
            // Cuando lo haga se transformará en verdadera para no dar más vueltas en el ciclo for
            bool agregado = false;
            for (int i = 0; i < 100; i++) {
                if (codigoProducto[i] == 0) {  // Si el código es 0, es un espacio vacío
                    // Esto hará que todos los valores se ingresen en la dirección que está vacía
                    nombreProducto[i] = nombreProductoNuevo;
                    codigoProducto[i] = codigoProductoNuevo;
                    cantidadProducto[i] = cantidadProductoNuevo;
                    precioProducto[i] = precioProductoNuevo;
                    cout << "\nProducto agregado: " << nombreProductoNuevo << " (Código: " << codigoProductoNuevo << ")" << endl;
                    agregado = true;
                    break;
                }
            }
            
            // Si la variable agregado bool verifica que todos los espacios están llenos
            // Se transforma en verdadera y nos dice que no hay espacio
            if (!agregado) {
                cout << "---------------------------------------" << endl;
                cout << "No hay espacio disponible para agregar más productos" << endl;
                cout << "---------------------------------------\n\n" << endl;
            }
        }

/*======================================================================================
OPCIÓN 2: GESTIONAR PRODUCTOS (MODIFICACIÓN O ELIMINACIÓN)
======================================================================================*/
        
        else if (opc == 2) {
            
            /*------- Pedir código del producto para buscarlo y modificarlo -------*/
            cout << "\n=== MODIFICAR PRODUCTO ===" << endl;
            cout << "Ingrese el código del producto a modificar: ";
            int buscarCodigo;
            cin >> buscarCodigo;

            /*------- Buscar en el arreglo el código del producto -------*/
            bool productoEncontrado = false;
            for (int i = 0; i < 100; i++) {
                if (codigoProducto[i] == buscarCodigo) {
                    productoEncontrado = true;
                    cout << "Producto encontrado: " << nombreProducto[i] << endl;

            /*------- Menú de modificación del producto -------*/
                    cout << "\n¿Qué desea modificar del producto?" << endl;
                    cout << "1. Nombre" << endl;
                    cout << "2. Cantidad" << endl;
                    cout << "3. Precio" << endl;
                    cout << "4. Eliminar producto" << endl;
                    cout << "Opción: ";
                    cin >> opc;

                    if(opc == 1) {
                        // Modificar NOMBRE del producto
                        cout << "Ingrese el nuevo nombre del producto: ";
                        cin.ignore();  // Limpiar el buffer para usar getline
                        string nuevoNombre;
                        getline(cin, nuevoNombre);
                        nombreProducto[i] = nuevoNombre;
                        cout << "Nombre actualizado a: " << nombreProducto[i] << endl;
                    } 
                    else if (opc == 2) {
                        // Modificar CANTIDAD del producto
                        cout << "Ingrese la nueva cantidad del producto: ";
                        int nuevaCantidad;
                        cin >> nuevaCantidad;
                        cantidadProducto[i] = nuevaCantidad;
                        cout << "antidad actualizada a: " << cantidadProducto[i] << endl;
                    } 
                    else if (opc == 3) {
                        // Modificar PRECIO del producto
                        cout << "Ingrese el nuevo precio del producto: $";
                        float nuevoPrecio;
                        cin >> nuevoPrecio;
                        precioProducto[i] = nuevoPrecio;
                        cout << "Precio actualizado a: $" << precioProducto[i] << endl;
                    } 
                    else if (opc == 4) {
                        // Eliminar producto ,aquí lo que hacemos es poner todos los valores a 0 para que se encuentren disponibles si se quiere agregar un nuevo producto
                        nombreProducto[i] = "";
                        codigoProducto[i] = 0;
                        cantidadProducto[i] = 0;
                        precioProducto[i] = 0.0;
                        cout << "Producto eliminado del inventario" << endl;
                    } 
                    else {
                        cout << "Opción no válida" << endl;
                    }

                    break;
                }
            }
            
            // Utilizamos !productoEncontrado, que se transforma en true si no encuentra el código
            // Si recorre todo el arreglo y no encuentra el producto, entonces no existe
            if (!productoEncontrado) {
                cout << "Producto no encontrado" << endl;
            }
        }

/*======================================================================================
OPCIÓN 3: VER INVENTARIO DE PRODUCTOS
======================================================================================*/
        
        else if (opc == 3) {
            
            /*------- Opción para ver todo el inventario o buscar producto específico -------*/
            cout << "---------------------------------------" << endl;
            cout << "¿Desea ver todo el inventario o buscar un producto específico?" << endl;
            cout << "1. Ver todo" << endl;
            cout << "2. Buscar" << endl;
            cout << "---------------------------------------\n\n" << endl;
            cin >> opc;
            
            if (opc == 1) {
                /*------- Mostrar todo el inventario -------*/
                cout << "Inventario: " << endl;
                // Mediante un ciclo for se imprimen todos los productos hasta que se termine el arreglo
                for (int i = 0; i < 100; i++) {
                    if (codigoProducto[i] != 0) {  // Con este if decimos que si no detectamos valores en codigoProducto, cortamos los recorridos ya que significa que ahí no hay valores existentes
                        cout << "Producto " << codigoProducto[i] << " - " << nombreProducto[i] 
                             << " - Cantidad: " << cantidadProducto[i] 
                             << " - Precio: $" << precioProducto[i] << endl;
                             cout << "Lugar (índice que ocupa dentro del vector): " << i << endl; //ACTUALIZACIÓN: LUGAR EN EL QUE SE ENCUENTRA EL PRODUCTO DEPENDIENDO SU POSICIÓN EN EL INDICE

                    }
                }
            } 
            else if (opc == 2) {
                /*------- Buscar un producto específico -------*/
                cout << "Ingrese el código del producto a buscar: " << endl;
                int buscarCodigo;
                cin >> buscarCodigo;

                /*------- Ciclo for para recorrer todo el array hasta encontrar coincidencia -------*/
                // Variable bool para que mientras no se encuentre el código en el arreglo
                // seguir recorriéndolo hasta encontrar una coincidencia
                bool encontrado = false;
                for (int i = 0; i < 100; i++) {
                    /*------- Si el código buscado es igual a uno dentro del arreglo -------*/
                    if (codigoProducto[i] == buscarCodigo) {
                        cout << "Producto encontrado: " << endl;
                        cout << "Nombre: " << nombreProducto[i] << endl;
                        cout << "Código: " << codigoProducto[i] << endl;
                        cout << "Cantidad: " << cantidadProducto[i] << endl;
                        cout << "Precio: $" << precioProducto[i] << endl;
                        cout << "Lugar (índice que ocupa dentro del vector): " << i << endl; //ACTUALIZACIÓN: LUGAR EN EL QUE SE ENCUENTRA EL PRODUCTO DEPENDIENDO SU POSICIÓN EN EL INDICE
                        // Cuando se imprima el valor, la variable encontrado pasa a ser true
                        // lo que termina el ciclo for
                        encontrado = true;
                        break;
                    }
                }
                
                if (!encontrado) {
                    cout << "Producto no encontrado" << endl;
                }
            }
        }

/*======================================================================================
OPCIÓN 4: BUSCAR PRODUCTO MÁS CARO DEL INVENTARIO
======================================================================================*/
        
        else if(opc == 4) {
            
            /*------- Algoritmo para encontrar el producto más caro -------*/
            float mayor = -1;      // Inicializamos mayor con un valor muy bajo
            int indexMayor = -1;   // Guardamos el índice del producto más caro
            
            // Ciclo for que recorre todo el arreglo
            for (int i = 0; i < 100; i++) {
                /*------- Comparaciones hasta que se acabe el arreglo de precios -------*/
                // Cuando se termine, la variable mayor mostrará el precio más alto
                if (precioProducto[i] > mayor) {
                    mayor = precioProducto[i];
                    indexMayor = i;
                }
            }

            if (indexMayor != -1) {
                cout << "El producto más caro es: " << nombreProducto[indexMayor] 
                     << " con un precio de: $" << mayor << endl;
            } else {
                cout << "No hay productos registrados" << endl;
            }
        }

/*======================================================================================
OPCIÓN 5: BUSCAR PRODUCTO MÁS BARATO DEL INVENTARIO
======================================================================================*/
        
        else if(opc == 5) {
            
            /*------- Algoritmo para encontrar el producto más barato -------*/
            float menor = -1;      // Inicializamos mayor con un valor muy bajo
            int indexMenor = -1;   // Guardamos el índice del producto más caro
            
            // Ciclo for que recorre todo el arreglo
            for (int i = 0; i < 100; i++) {
                /*------- Comparaciones hasta que se acabe el arreglo de precios -------*/
                // Cuando se termine, la variable mayor mostrará el precio más alto
                if (precioProducto[i] < menor) {
                    menor = precioProducto[i];
                    indexMenor = i;
                }
            }

            if (indexMenor != -1) {
                cout << "El producto más caro es: " << nombreProducto[indexMenor] 
                     << " con un precio de: $" << menor << endl;
            } else {
                cout << "No hay productos registrados" << endl;
            }
        }

/*======================================================================================
OPCIÓN 6: GUARDAR CAMBIOS
======================================================================================*/

         else if (opc == 6) {

            /*------- Guardar inventario en archivo -------*/
            cout << "EL inventario ha sido guardado con éxito..." << endl;
            cout << "La verdad verdad, es que no se guardo con éxito, pero vamos a suponer que si..." << endl;
            salir = true;
        }
/*======================================================================================
OPCIÓN 7: SALIR DEL PROGRAMA
======================================================================================*/
        
        else if (opc == 7) {
            
            /*------- Mensaje de salida y cambio de variable salir a true -------*/
            cout << "Saliendo..." << endl;

            //Cerramos el archivo del inventario
            inventario.close();

            // Se transforma la variable salir en true, lo que provoca que el bucle while se rompa terminando el programa
            salir = true;
        } 

/*======================================================================================
  OPCIÓN INVÁLIDA 
======================================================================================*/
        
        else {
            /*------- Mensaje de alerta y vuelta al menú gracias al ciclo while -------*/
            cout << "Opción no valida. Intenta de nuevo" << endl;
        }
        
    } // Fin del bucle while principal
    
    return 0;
}
