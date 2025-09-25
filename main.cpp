/**
  Ferretería El Martillo de Said
  1.0 Funcionalidades del Menú Principal:
  2.0 Ingresar nuevo producto
  3.0 Modificar productos
  4.0 Ver productos
  5.0 Buscar producto más caro
  6.0 Salir
 */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    
    // Inicialización de los vectores paralelos separados por sus diferentes funciones
    int codigoProducto[100] = {1, 2, 3, 4, 5}; 
    string nombreProducto[100] = {"Tornillo", "Tuerca", "Mazo", "Martillo", "Cerrucho"};
    int cantidadProducto[100] = {10, 12, 14, 6, 1};
    float precioProducto[100] = {2.00, 1.50, 200.00, 250.00, 300.00};
    
    //Inicializamos el archivo.txt
    const string archivoInventario = "inventario.txt";

    // Variable para el bucle while inicializado en false para que no termine el programa
    bool salir = false; 

/*======================================================================================
  1.1 - BUCLE PRINCIPAL DEL MENÚ
======================================================================================*/
    
    // Bucle while que va a repetir el menú principal mientras no se presione el botón de salir
    // El símbolo ! nos dice que mientras salir siga siendo false se seguirá ejecutando, sino terminaría
    while (!salir) {
        
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
  1.2 - OPCIÓN 1: ALMACENAR PRODUCTO NUEVO
======================================================================================*/
        
        if (opc == 1) {
            
            /*------- 2.0 - Asignación de nombre al producto nuevo -------*/
            cout << "\n=== AGREGAR NUEVO PRODUCTO ===" << endl;
            cout << "Ingrese el nombre del producto: ";
            string nombreProductoNuevo;
            cin.ignore();  // Limpiar el buffer para usar getline
            getline(cin, nombreProductoNuevo);  // Permitir que el nombre tenga espacios

            /*------- 2.1 - Asignar código de producto (automático o manual) -------*/
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

            /*------- 2.2 - Asignar cantidad en stock del producto -------*/
            cout << "\nIngrese la cantidad en stock: ";
            int cantidadProductoNuevo;
            cin >> cantidadProductoNuevo;
        
            /*------- 2.3 - Asignar precio unitario del producto con decimales -------*/
            cout << "Ingrese el precio del producto: $";
            float precioProductoNuevo;
            cin >> precioProductoNuevo;

            /*------- 2.4 - Buscar espacio vacío para agregar el producto -------*/
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
  1.3 - OPCIÓN 2: GESTIONAR PRODUCTOS (MODIFICACIÓN O ELIMINACIÓN)
======================================================================================*/
        
        else if (opc == 2) {
            
            /*------- 3.0 - Pedir código del producto para buscarlo y modificarlo -------*/
            cout << "\n=== MODIFICAR PRODUCTO ===" << endl;
            cout << "Ingrese el código del producto a modificar: ";
            int buscarCodigo;
            cin >> buscarCodigo;

            /*------- 3.1 - Buscar en el arreglo el código del producto -------*/
            bool productoEncontrado = false;
            for (int i = 0; i < 100; i++) {
                if (codigoProducto[i] == buscarCodigo) {
                    productoEncontrado = true;
                    cout << "Producto encontrado: " << nombreProducto[i] << endl;

            /*------- 3.2 - Menú de modificación del producto -------*/
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
  1.4 - OPCIÓN 3: VER INVENTARIO DE PRODUCTOS
======================================================================================*/
        
        else if (opc == 3) {
            
            /*------- 4.0 - Opción para ver todo el inventario o buscar producto específico -------*/
            cout << "---------------------------------------" << endl;
            cout << "¿Desea ver todo el inventario o buscar un producto específico?" << endl;
            cout << "1. Ver todo" << endl;
            cout << "2. Buscar" << endl;
            cout << "---------------------------------------\n\n" << endl;
            cin >> opc;
            
            if (opc == 1) {
                /*------- 4.1 - Mostrar todo el inventario -------*/
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
                /*------- 4.2 - Buscar un producto específico -------*/
                cout << "Ingrese el código del producto a buscar: " << endl;
                int buscarCodigo;
                cin >> buscarCodigo;

                /*------- 4.3 - Ciclo for para recorrer todo el array hasta encontrar coincidencia -------*/
                // Variable bool para que mientras no se encuentre el código en el arreglo
                // seguir recorriéndolo hasta encontrar una coincidencia
                bool encontrado = false;
                for (int i = 0; i < 100; i++) {
                    /*------- 4.4 - Si el código buscado es igual a uno dentro del arreglo -------*/
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
  1.5 - OPCIÓN 4: BUSCAR PRODUCTO MÁS CARO DEL INVENTARIO
======================================================================================*/
        
        else if(opc == 4) {
            
            /*------- 5.0 - Algoritmo para encontrar el producto más caro -------*/
            float mayor = -1;      // Inicializamos mayor con un valor muy bajo
            int indexMayor = -1;   // Guardamos el índice del producto más caro
            
            // Ciclo for que recorre todo el arreglo
            for (int i = 0; i < 100; i++) {
                /*------- 5.1 - Comparaciones hasta que se acabe el arreglo de precios -------*/
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
  1.6 - OPCIÓN 5: BUSCAR PRODUCTO MÁS BARATO DEL INVENTARIO
======================================================================================*/
        
        else if(opc == 5) {
            
            /*------- 6.0 - Algoritmo para encontrar el producto más barato -------*/
            float menor = -1;      // Inicializamos mayor con un valor muy bajo
            int indexMenor = -1;   // Guardamos el índice del producto más caro
            
            // Ciclo for que recorre todo el arreglo
            for (int i = 0; i < 100; i++) {
                /*------- 5.1 - Comparaciones hasta que se acabe el arreglo de precios -------*/
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
  1.7 - OPCIÓN 6: GUARDAR CAMBIOS
======================================================================================*/

         else if (opc == 6) {

            /*------- 7.0 - Algoritmo para encontrar el producto más caro -------*/
            cout << "EL inventario ha sido guardado con éxito..." << endl;
            cout << "La verdad verdad, es que no se guardo con éxito, pero vamos a suponer que si..." << endl;
            salir = true;
        }
/*======================================================================================
  1.8 - OPCIÓN 5: SALIR DEL PROGRAMA
======================================================================================*/
        
        else if (opc == 7) {
            
            /*------- 8.0 - Mensaje de salida y cambio de variable salir a true -------*/
            cout << "Saliendo..." << endl;
            // Se transforma la variable salir en true, lo que provoca que el bucle while se rompa
            // terminando el programa
            salir = true;
        } 

/*======================================================================================
  OPCIÓN INVÁLIDA 
======================================================================================*/
        
        else {
            /*------- 9.0 - Mensaje de alerta y vuelta al menú gracias al ciclo while -------*/
            cout << "Opción no valida. Intenta de nuevo" << endl;
        }
        
    } // Fin del bucle while principal
    
    return 0;
}
