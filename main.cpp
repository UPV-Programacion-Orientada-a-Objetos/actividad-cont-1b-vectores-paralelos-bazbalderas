#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Función para poder guardar los cambios en el botón de la opción 6 del menú principal, ante cualquier cambio o adición que hagamos
void botonGuardar(const string& nombreArchivo, int codigoProducto[], string nombreProducto[], int cantidadProducto[], float precioProducto[], string ubicacionProducto[], int numProductos) {
    ofstream inventario(nombreArchivo, ios::app);

    if (inventario.is_open()) {
        // Escribimos la primera línea del archivo (encabezado)
        inventario << "Código,Nombre,Cantidad,Precio,Ubicación\n";

        // Escribimos todos los productos
        for (int i = 0; i < numProductos; i++) { // Ciclo para recorrer el inventario
            if (codigoProducto[i] != 0) { // Solo escribir productos válidos
                // Se van ingresando los productos separando por comas
                inventario << codigoProducto[i] << ","
                           << nombreProducto[i] << ","
                           << cantidadProducto[i] << ","
                           << precioProducto[i] << ","
                           << ubicacionProducto[i] << "\n";
            }
        }
        inventario.close();
    } else {
        cout << "No se pueden guardar los cambios, llama a tu experto (no a Baz)" << endl;
    }
}

int main() {
    // Inicialización de los vectores paralelos para el inventario
    int codigoProducto[100] = {}; 
    string nombreProducto[100] = {""};
    int cantidadProducto[100] = {};
    float precioProducto[100] = {};
    string ubicacionProducto[100] = {""};
    
    bool salir = false; // Variable para controlar el bucle del menú

    // Bucle principal del menú
    while (!salir) {
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

        // Opción 1: Agregar un nuevo producto
        if (opc == 1) {
            /*------- Asignación de nombre al producto nuevo -------*/
            cout << "\n=== AGREGAR NUEVO PRODUCTO ===" << endl;
            cout << "Ingrese el nombre del producto: ";
            string nombreProductoNuevo;
            cin.ignore();  // Limpiar el buffer para usar getline
            getline(cin, nombreProductoNuevo);  // Permitir que el nombre tenga espacios

            // Validación de nombre repetido
            bool nombreRepetido = false;
            for (int i = 0; i < 100; i++) {
                if (nombreProducto[i] == nombreProductoNuevo) {
                    nombreRepetido = true;
                    break;
                }
            }
            if (nombreRepetido) {
                cout << "El nombre del producto ya existe. Por favor, ingrese un nombre diferente." << endl;
                continue; // Si el nombre ya existe, volvemos al menú
            }

            /*------- Asignar código de producto (automático o manual) -------*/
            int codigoProductoNuevo = 0;
            cout << "\n--- ASIGNACIÓN DE CÓDIGO ---" << endl;
            cout << "¿Prefieres que se asigne un código automático o prefieres asignarlo tú?" << endl;
            cout << "1. Automático" << endl;
            cout << "2. Manual" << endl;
            cout << "Opción: ";
            cin >> opc;

            if (opc == 1) {
                // Asignación automática de código
                int maxCodigo = 0;
                for (int i = 0; i < 100; i++) {
                    if (codigoProducto[i] > maxCodigo) {
                        maxCodigo = codigoProducto[i];
                    }
                }
                codigoProductoNuevo = maxCodigo + 1;
                cout << "\nCódigo asignado automáticamente: " << codigoProductoNuevo << endl;
            } else {
                // Asignación manual de código (asegurar que sea mayor que 100)
                bool codigoValido = false;
                do {
                    cout << "\nIngrese el código del producto (debe ser mayor que 100): ";
                    cin >> codigoProductoNuevo;
                    if (codigoProductoNuevo <= 100) {
                        cout << "El código debe ser mayor que 100." << endl;
                    } else {
                        codigoValido = true;
                    }
                } while (!codigoValido);
                
                // Verificar que no haya un código repetido dentro del arreglo
                bool codigoRepetido = false;
                for (int i = 0; i < 100; i++) {
                    if (codigoProducto[i] == codigoProductoNuevo) {
                        cout << "Este código ya existe. Intenta con otro." << endl;
                        codigoRepetido = true;
                        break;
                    }
                }
                if (codigoRepetido) {
                    continue; // Si el código es repetido, volvemos al menú
                }
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
            bool agregado = false;
            for (int i = 0; i < 100; i++) {
                if (codigoProducto[i] == 0) {  // Si el código es 0, es un espacio vacío
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
            if (!agregado) {
                cout << "No hay espacio disponible para agregar más productos" << endl;
            }
        }

        /*======================================================================================
        Opción 6: Guardar cambios
        =====================================================================================*/
        else if (opc == 6) {
            cout << "Guardando cambios en el inventario..." << endl;
            botonGuardar("inventario.txt", codigoProducto, nombreProducto, cantidadProducto, precioProducto, ubicacionProducto, 100);
            cout << "Los cambios han sido guardados con éxito." << endl;
        }

        /*======================================================================================
        Salir del programa
        =====================================================================================*/
        else if (opc == 7) {
            cout << "Saliendo..." << endl;
            salir = true;
        }

        /*======================================================================================
        Opción no válida
        =====================================================================================*/
        else {
            cout << "Opción no válida. Intenta de nuevo." << endl;
        }
    }

    return 0;
}
