#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

/*======================================================================================
FUNCIONES DE VALIDACIÓN - IMPLEMENTADAS PARA HACER EL PROGRAMA MÁS ROBUSTO
======================================================================================*/

// Validar entrada de números enteros
// Esta función evita que el programa se rompa cuando el usuario ingresa texto donde se esperan números
// Utiliza cin.clear() para limpiar flags de error y cin.ignore() para vaciar el buffer
int validarEntero(const string& mensaje) {
    int numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer después de leer número exitosamente
            return numero;
        } else {
            cout << "Error: Debe ingresar un número entero válido." << endl;
            cin.clear(); // Limpiar el flag de error de cin cuando falla la lectura
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar todos los caracteres hasta nueva línea
        }
    }
}

// Validar entrada de números decimales positivos
// Garantiza que solo se ingresen precios válidos (mayores a 0) y maneja errores de entrada
float validarFloat(const string& mensaje) {
    float numero;
    while (true) {
        cout << mensaje;
        if (cin >> numero && numero > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        } else {
            cout << "Error: Debe ingresar un número decimal válido mayor a 0." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Validar opciones del menú
// Asegura que el usuario solo pueda seleccionar opciones válidas del menú
int validarOpcionMenu(int min, int max) {
    int opcion;
    while (true) {
        opcion = validarEntero("Seleccione una opción: ");
        if (opcion >= min && opcion <= max) {
            return opcion;
        } else {
            cout << "Error: Opción no válida. Ingrese un número entre " 
                 << min << " y " << max << "." << endl;
        }
    }
}

// Validar strings no vacíos
// Evita que se ingresen nombres de productos vacíos o que contengan solo espacios
string validarStringNoVacio(const string& mensaje) {
    string texto;
    while (true) {
        cout << mensaje;
        getline(cin, texto);
        
        // Eliminar espacios al inicio y final - técnica de trim
        size_t inicio = texto.find_first_not_of(" \t");
        size_t fin = texto.find_last_not_of(" \t");
        
        if (inicio != string::npos && fin != string::npos) {
            texto = texto.substr(inicio, fin - inicio + 1);
            if (!texto.empty()) {
                return texto;
            }
        }
        
        cout << "Error: El texto no puede estar vacío." << endl;
    }
}

// Validar cantidad (debe ser 0 o positiva)
// Función especializada para validar cantidades en stock
int validarCantidad() {
    int cantidad;
    while (true) {
        cantidad = validarEntero("Ingrese la cantidad en stock: ");
        if (cantidad >= 0) {
            return cantidad;
        } else {
            cout << "Error: La cantidad debe ser mayor o igual a 0." << endl;
        }
    }
}

// Función para cargar el inventario desde el archivo .txt a los vectores paralelos
void cargarInventario(const string& nombreArchivo, int codigoProducto[], string nombreProducto[], int cantidadProducto[], float precioProducto[], string ubicacionProducto[], int& numProductos) {
    ifstream inventario(nombreArchivo);
    numProductos = 0;
    
    if (inventario.is_open()) {
        string linea;
        
        // Saltar la primera línea (encabezados)
        getline(inventario, linea);
        
        while (getline(inventario, linea) && numProductos < 100) {
            stringstream ss(linea);
            string item;
            
            try {
                // Leer código del producto
                if (getline(ss, item, ',')) {
                    codigoProducto[numProductos] = stoi(item);
                }
                
                // Leer nombre del producto
                if (getline(ss, item, ',')) {
                    nombreProducto[numProductos] = item;
                }
                
                // Leer cantidad del producto
                if (getline(ss, item, ',')) {
                    cantidadProducto[numProductos] = stoi(item);
                }
                
                // Leer precio del producto
                if (getline(ss, item, ',')) {
                    precioProducto[numProductos] = stof(item);
                }
                
                // Leer ubicación del producto
                if (getline(ss, item, ',')) {
                    ubicacionProducto[numProductos] = item;
                }
                
                numProductos++;
            } catch (const exception& e) {
                // Manejo de errores robusto - si una línea tiene formato incorrecto, se ignora
                cout << "Línea con formato incorrecto ignorada." << endl;
                continue;
            }
        }
        inventario.close();
        cout << "Inventario cargado exitosamente. Productos encontrados: " << numProductos << endl;
    } else {
        cout << "Archivo no encontrado. Creando nuevo archivo..." << endl;
        ofstream nuevoArchivo(nombreArchivo);
        if (nuevoArchivo.is_open()) {
            nuevoArchivo << "Codigo,Nombre,Cantidad,Precio,Ubicacion\n";
            nuevoArchivo.close();
            cout << "Archivo creado exitosamente." << endl;
        }
    }
}

// Función para guardar los cambios en el archivo .txt
void botonGuardar(const string& nombreArchivo, int codigoProducto[], string nombreProducto[], int cantidadProducto[], float precioProducto[], string ubicacionProducto[], int numProductos) {
    // Abrir el archivo en modo de escritura (sobrescribir contenido anterior)
    ofstream inventario(nombreArchivo);

    if (inventario.is_open()) {
        // Escribir encabezados del archivo.txt
        inventario << "Código,Nombre,Cantidad,Precio,Ubicación\n";
        
        // Escribir todos los productos válidos
        for (int i = 0; i < 100; i++) { // Recorrer todo el arreglo completo
            if (codigoProducto[i] != 0) { // Solo escribir productos válidos (código != 0)
                // Formato CSV separado por comas
                inventario << codigoProducto[i] << ","
                           << nombreProducto[i] << ","
                           << cantidadProducto[i] << ","
                           << precioProducto[i] << ","
                           << ubicacionProducto[i] << "\n";
            }
        }
        inventario.close();
        cout << "Inventario guardado exitosamente." << endl;
    } else {
        cout << "No se pueden guardar los cambios en el archivo." << endl;
    }
}

int main() {
    // Inicialización de los vectores paralelos para el inventario
    int codigoProducto[100] = {}; 
    string nombreProducto[100] = {""};
    int cantidadProducto[100] = {};
    float precioProducto[100] = {};
    string ubicacionProducto[100] = {""};
    
    // Variable para contar productos cargados
    int numProductos = 0;
    
    // Cargar inventario existente desde el archivo
    cargarInventario("inventario.txt", codigoProducto, nombreProducto, cantidadProducto, precioProducto, ubicacionProducto, numProductos);
    
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
        
        int opc = validarOpcionMenu(1, 7); // Validación automática de opciones del menú

        // Opción 1: Agregar un nuevo producto
        if (opc == 1) {
            /*------- Asignación de nombre al producto nuevo -------*/
            cout << "\n=== AGREGAR NUEVO PRODUCTO ===" << endl;
            string nombreProductoNuevo = validarStringNoVacio("Ingrese el nombre del producto: "); // Validación de strings vacíos

            // Validación de nombre repetido
            bool nombreRepetido = false;
            for (int i = 0; i < 100; i++) {
                if (nombreProducto[i] == nombreProductoNuevo) {
                    nombreRepetido = true;
                    break;
                }
            }
            if (nombreRepetido) {
                cout << "El nombre del producto ya existe. Por favor ingrese un nombre diferente." << endl;
                continue; // Si el nombre ya existe, volvemos al menú
            }

            /*------- Asignación automática de código de producto -------*/
            int codigoProductoNuevo = 0;
            // Asignación automática de código
            int maxCodigo = 0;
            for (int i = 0; i < 100; i++) {
                if (codigoProducto[i] > maxCodigo) {
                    maxCodigo = codigoProducto[i];
                }
            }
            codigoProductoNuevo = maxCodigo + 1;
            cout << "\nCódigo asignado automáticamente: " << codigoProductoNuevo << endl;

            /*------- Asignar cantidad en stock del producto -------*/
            int cantidadProductoNuevo = validarCantidad(); // Validación de cantidades no negativas

            /*------- Asignar precio unitario del producto con decimales -------*/
            float precioProductoNuevo = validarFloat("Ingrese el precio del producto: $"); // Validación de precios positivos

            /*------- Asignar ubicación del producto en almacén -------*/
            string ubicacionProductoNuevo = validarStringNoVacio("Ingrese la ubicación del producto (A-00)"); // Campo ubicación agregado

            /*------- Buscar espacio vacío para agregar el producto -------*/
            bool agregado = false;
            for (int i = 0; i < 100; i++) {
                if (codigoProducto[i] == 0) {  // Si el código es 0, es un espacio vacío
                    nombreProducto[i] = nombreProductoNuevo;
                    codigoProducto[i] = codigoProductoNuevo;
                    cantidadProducto[i] = cantidadProductoNuevo;
                    precioProducto[i] = precioProductoNuevo;
                    ubicacionProducto[i] = ubicacionProductoNuevo; // Agregar ubicación al producto
                    cout << "\nProducto agregado: " << nombreProductoNuevo << " (Código: " << codigoProductoNuevo << ")" << endl;
                    numProductos++; // Incrementar contador de productos
                    agregado = true;
                    break;
                }
            }

            if (!agregado) {
                cout << "No hay espacio disponible para agregar más productos" << endl;
            }
        }

        /*======================================================================================
        Opción 2: Modificar producto
        =====================================================================================*/
        else if (opc == 2) {
            /*------- Pedir código del producto para buscarlo y modificarlo -------*/
            cout << "\n=== MODIFICAR PRODUCTO ===" << endl;
            int buscarCodigo = validarEntero("Ingrese el código del producto a modificar: "); // Validación de entrada numérica

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
                    cout << "4. Ubicación" << endl;
                    cout << "5. Eliminar producto" << endl;
                    cout << "Opción: ";
                    cin >> opc;

                    if(opc == 1) {
                        // Modificar NOMBRE del producto
                        cout << "Ingrese el nuevo nombre del producto: ";
                        cin.ignore();  // Limpiar buffer antes de getline para evitar problemas con entrada previa
                        string nuevoNombre;
                        getline(cin, nuevoNombre); // getline permite espacios en el nombre
                        nombreProducto[i] = nuevoNombre;
                        cout << "Nombre actualizado a: " << nombreProducto[i] << endl;
                    } 
                    else if (opc == 2) {
                        // Modificar CANTIDAD del producto
                        cout << "Ingrese la nueva cantidad del producto: ";
                        int nuevaCantidad;
                        cin >> nuevaCantidad;
                        cantidadProducto[i] = nuevaCantidad;
                        cout << "Cantidad actualizada a: " << cantidadProducto[i] << endl;
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
                        // Modificar UBICACIÓN del producto
                        cout << "Ingrese la nueva ubicación del producto (ej: A-01): ";
                        cin.ignore();  // Limpiar buffer antes de getline
                        string nuevaUbicacion;
                        getline(cin, nuevaUbicacion);
                        ubicacionProducto[i] = nuevaUbicacion;
                        cout << "Ubicación actualizada a: " << ubicacionProducto[i] << endl;
                    } 
                    else if (opc == 5) {
                        // Eliminar producto - Se resetean todos los valores para liberar el espacio
                        nombreProducto[i] = "";         // Vaciar nombre
                        codigoProducto[i] = 0;          // Código 0 indica espacio libre
                        cantidadProducto[i] = 0;        // Resetear cantidad
                        precioProducto[i] = 0.0;        // Resetear precio
                        ubicacionProducto[i] = "";      // Vaciar ubicación
                        numProductos--; // Decrementar contador total de productos
                        cout << "Producto eliminado del inventario" << endl;
                    } 
                    else {
                        cout << "Opción no válida" << endl;
                    }

                    break;
                }
            }
            
            // Si no se encontró el producto
            if (!productoEncontrado) {
                cout << "Producto no encontrado" << endl;
            }
        }

        /*======================================================================================
        Opción 3: Ver inventario
        =====================================================================================*/
        else if (opc == 3) {
            cout << "---------------------------------------" << endl;
            cout << "¿Desea ver todo el inventario o buscar un producto específico?" << endl;
            cout << "1. Ver todo" << endl;
            cout << "2. Buscar" << endl;
            cout << "---------------------------------------\n\n" << endl;
            cin >> opc; // Sin validación aquí para simplificar el sub-menú
            
            if (opc == 1) {
                // Mostrar todo el inventario
                cout << "Inventario: " << endl;
                for (int i = 0; i < 100; i++) {
                    if (codigoProducto[i] != 0) { // Solo mostrar productos válidos (código != 0)
                        cout << "Producto " << codigoProducto[i] << " - " << nombreProducto[i] 
                             << " - Cantidad: " << cantidadProducto[i] 
                             << " - Precio: $" << precioProducto[i] 
                             << " - Ubicación: " << ubicacionProducto[i] << endl; // Mostrar ubicación
                    }
                }
            } 
            else if (opc == 2) {
                cout << "Ingrese el código del producto a buscar: " << endl;
                int buscarCodigo;
                cin >> buscarCodigo;

                bool encontrado = false;
                for (int i = 0; i < 100; i++) {
                    if (codigoProducto[i] == buscarCodigo) {
                        cout << "Producto encontrado: " << endl;
                        cout << "Nombre: " << nombreProducto[i] << endl;
                        cout << "Código: " << codigoProducto[i] << endl;
                        cout << "Cantidad: " << cantidadProducto[i] << endl;
                        cout << "Precio: $" << precioProducto[i] << endl;
                        cout << "Ubicación: " << ubicacionProducto[i] << endl; // Mostrar ubicación en búsqueda
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
        Opción 4: Buscar producto más caro
        =====================================================================================*/
        else if(opc == 4) {
            // Algoritmo de búsqueda lineal para encontrar el máximo precio
            float mayor = -1;      // Inicializar en -1 porque todos los precios son positivos
            int indexMayor = -1;   // Guardará la posición del producto más caro
            for (int i = 0; i < 100; i++) {
                if (precioProducto[i] > mayor) { // Comparar cada precio con el máximo actual
                    mayor = precioProducto[i];   // Actualizar precio máximo
                    indexMayor = i;              // Guardar posición del producto más caro
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
        Opción 5: Buscar producto más barato
        =====================================================================================*/
        else if(opc == 5) {
            // Corrección del algoritmo - ahora inicia con valor alto y verifica productos válidos
            float menor = 999999999;  // Valor inicial muy alto
            int indexMenor = -1;
            for (int i = 0; i < 100; i++) {
                if (codigoProducto[i] != 0 && precioProducto[i] < menor) {
                    menor = precioProducto[i];
                    indexMenor = i;
                }
            }

            if (indexMenor != -1) {
                cout << "El producto más barato es: " << nombreProducto[indexMenor] 
                     << " con un precio de: $" << menor << endl;
            } else {
                cout << "No hay productos registrados" << endl;
            }
        }

        /*======================================================================================
        Opción 6: Guardar cambios
        =====================================================================================*/
        else if (opc == 6) {
            cout << "Guardando cambios en el inventario..." << endl;
            botonGuardar("inventario.txt", codigoProducto, nombreProducto, cantidadProducto, precioProducto, ubicacionProducto, numProductos);
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
