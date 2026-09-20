# PrograProyecto — Centro Deportivo "Zona Activa"

Proyecto académico (curso de Programación) en **C++20**, aplicación de **consola** para gestionar un centro deportivo: canchas, clientes y reservas. Todo el código, identificadores, comentarios y mensajes al usuario están en **español (sin tildes en el código y las cadenas)**. Responder al usuario en español.

## Build / entorno
- Visual Studio, solución `PrograProyecto.slnx` / `PrograProyecto.vcxproj`, toolset `v145`, `stdcpp20`, x64, `CharacterSet=Unicode`.
- No hay tests, CMake ni Makefile. Compilar: abrir en VS (Ctrl+F5) o `msbuild PrograProyecto.vcxproj /p:Configuration=Debug /p:Platform=x64`.
- Los archivos nuevos deben agregarse a `PrograProyecto.vcxproj` (`ClCompile`/`ClInclude`) y a `.vcxproj.filters`.
- La UI usa `system("cls")` y `system("pause")` (solo Windows).
- Ramas: `master`, `ModuloCancha`, `ModuloCliente(V2)`, `ModuloListaEspera` (actual). Un módulo por rama, integrados por PR/merge.

## Arquitectura (sin STL de contenedores, sin plantillas)
Regla del curso evidente en el código: **arreglos crudos y punteros manuales, no `std::vector`/`std::map`**. Cada entidad tiene una clase "Gestión/Colección" que posee los punteros (`new` en registrar, `delete` en destructor).

```
main (PrograProyecto.cpp) -> Menu (Menu.h, header-only)
Menu posee: GestionClientes*, ColeccionCanchas*, GestionReservas*, GestionEspera*, Reportes*   (new en inicializadores de miembro, delete en ~Menu)
```

Capa de UI (`Menu`) → capa de gestión → capa de entidad. Las entidades y gestores **no leen de `cin`** (excepto lo indicado abajo); `Menu` hace toda la E/S.

### Cliente (`Cliente.h/.cpp`)
Entidad. Atributos: `identificacion`, `nombreCompleto`, `telefono`. Constructor por defecto y con parámetros (usa `this->`). Getters `const`; setters solo de nombre y teléfono (la identificación es inmutable). `mostrar() const` → string de una línea `ID: .. | Nombre: .. | Telefono: ..`.

### GestionClientes (`GestionClientes.h/.cpp`)
Arreglo dinámico fijo `Cliente**` de `MAX_CLIENTES = 100` (miembro `const int`). Métodos: `registrarCliente(id, nombre, tel)` (valida capacidad, campos vacíos y duplicado; **imprime mensajes con `cout`**, devuelve bool), `mostrarListado() const`, `buscarCliente(id) const` → `Cliente*`/`nullptr`, `existeCliente`, `buscarIndice` (−1 si no), `getCantidad`, `getClientePorIndice`. Declara `class Reserva;` adelantada (sin uso actual).

### Cancha (`Cancha.h/.cpp`)
Entidad. Atributos: `codigo`, `tipoDeporte`, `precioHora`, `char estado[12]` (12 franjas horarias, índice 0 = 8:00 … 11 = 19:00). Estados: `'L'` libre, `'O'` ocupada, `'M'` mantenimiento; `'X'` = posición inválida al consultar.
- `getConsultaEstado(pos)`, `setEstado(pos, c)` (false si pos inválida o si se intenta `'M'` sobre `'O'`), `verificarDisponibilidad(idx)` (true solo si `'L'`), `mostrarDisponibilidad()` (todas las franjas), `mostrarLibre()` (solo las libres, numeradas 1..12), `setPrecio`, getters (no `const`).

### ColeccionCanchas (`ColeccionCanchas.h/.cpp`)
`Cancha**` con `capacidad = 10` fija. Métodos: `existeCodigo`, `registrarCancha(codigo, tipo, precio)` (false si duplicado o lleno), `buscarPorCodigo` → `Cancha*`/`nullptr`, `modificarPrecio`, `getCantidad`, `mostrarCanchas()` (**imprime directo con `cout`**, void). Único módulo que se llama "Coleccion" en vez de "Gestion".

### Reserva (`Reserva.h/.cpp`)
Entidad. `static int contadorConsecutivo` (empieza en 0) → `consecutivo` autoincremental. Guarda `Cliente*`, `Cancha*` (no propietarios), `char franjasReservadas[12]` (`'O'` = franja reservada, `'L'` = no), `int montoTotal`, `bool estadoReserva` (true = activa, false = cancelada). **El constructor marca `'O'` en la cancha solo para las franjas `'O'` de la reserva.** Getters, `setEstadoReserva`. El arreglo `franjasReservadas` se conserva aunque la reserva se cancele.

### GestionReservas (`GestionReservas.h/.cpp`)
`Reserva**` que **crece de uno en uno** (crea arreglo nuevo de `tamano+1`, copia, `delete[]` el viejo). Métodos: `registrarReserva(cliente, cancha, franjas[12], monto, estado)` → `Reserva*`, `obtenerListado() const` (string), `buscarPorConsecutivo`, `buscarPorCancha` (primera reserva; ya no lo usa `Menu`), `cancelarReserva(consecutivo)` → `bool` (false si no existe o ya estaba cancelada; libera con `'L'` las franjas `'O'` de la reserva), `listarReserva(Reserva*) const` (string de una reserva), `getCantidad`, `getReservaPorIndice(i)`. El destructor libera las reservas.

### Espera (`Espera.h/.cpp`)
Registro del listado de espera. `static int contadorConsecutivo` (empieza en **1**), `Cliente*`, `Cancha*`, `int posicionFranja` (0–11), `std::string estado` (`"Esperando"` al crear, luego `"Asignado"` o `"Cancelado"`). Getters, `setEstado`, `mostrar() const` (string multilínea con `->`).

### GestionEspera (`GestionEspera.h/.cpp`)
Arreglo fijo `Espera**` de `MAX_ESPERA = 10` (spec: arreglo unidimensional de 10, no lista enlazada; los registros Asignado/Cancelado siguen ocupando espacio). Métodos: `estaLlena`, `existeEnEspera(cliente, cancha, pos)` (mismo cliente+cancha+franja en estado Esperando), `registrarEspera(...)` → `Espera*`/`nullptr` si llena, `mostrarListado() const`, `buscarPorConsecutivo`, `cambiarEstado(consecutivo, nuevo)` (solo desde `"Esperando"`), `contarEsperando(cancha, pos)`, `listarEsperando(cancha, pos)`, `getCantidad`. No imprime; las reglas de negocio con mensajes (franja debe estar `'O'`, no `'M'`) viven en `Menu::registrarEnEspera`.

### Reportes (`Reportes.h/.cpp`)
Recibe punteros a `ColeccionCanchas`, `GestionClientes`, `GestionReservas` (no los posee). Todos los métodos devuelven `std::string` con detalle: `canchaMasReservada`, `clienteMasReservas` (ambos muestran todos los empatados), `ingresoTotal`, `ocupacionCanchas` (% = franjas `'O'` / 12), `horasMayorYMenor` (+ helper privado `detalleHora`). Solo cuentan reservas con `getEstadoReserva() == true`.

### Menu (`Menu.h`, header-only, ~680 líneas)
Clase con toda la lógica de UI, métodos definidos inline en el header. Agrupados por módulo con comentarios `// --- Funciones del modulo de X ---` y `// --- Menu de X ---`:
- Lectura: `leerEntero()`, `leerDecimal()` (repiten hasta que `cin` lea un número; **usar siempre estos en vez de `cin >> int`**).
- Clientes: `ingresarCliente`, `mostrarClientes`, `buscarClientePorId`, `menuClientes` (opciones 1–4).
- Canchas: `ingresarCancha`, `mostrarDisponibilidad`, `buscarCancha`, `mostrarCanchas`, `modificarPrecio`, `mantenimiento` (no toca franjas `'O'`), `menuGestionCanchas` (1–7).
- Espera: `registrarEnEspera(cliente, cancha, pos)` (valida `'O'`, duplicado y lleno; también se llama desde `registrarReserva`), `ingresarEspera`, `mostrarEspera`, `cambiarEstadoEspera`, `menuGestionEspera` (1–4).
- Reservas: `registrarReserva` (elige franjas 1–12, 0 termina; franja `'O'` ofrece lista de espera, `'M'` se rechaza), `avisarEspera(reserva)` (se llama al cancelar), `cancelarReserva`, `listarReservas`, `listarPorConsecutivo`, `listarPorCancha` (todas las de la cancha), `menuGestionReservas` (1–6).
- Reportes: `menuReportes` (1–6).
- `menuPrincipal`: 1 Canchas, 2 Clientes, 3 Reservas, 4 Lista de espera, 5 Reportes, 6 Salir.

## Convenciones y patrones
- **Nombres**: clases `PascalCase`; métodos/variables `camelCase` en español (`registrarCancha`, `buscarPorCodigo`, `montoTotal`). Verbos habituales: `registrar…`, `buscar…`, `existe…`, `mostrar…`, `listar…`, `modificar…`, `cancelar…`, `get…`/`set…`. Constantes en `MAYUSCULAS` (`MAX_CLIENTES`). Parámetros que chocan con atributos: sufijo `_` (Reserva) o `this->` (Cliente) o sufijo `Nuevo`.
- **Búsqueda**: siempre lineal; devuelve puntero o `nullptr`, o índice/−1. Patrón de "existe" = `buscar… != nullptr/-1`.
- **Retorno**: `bool` para éxito/fracaso de registrar/modificar; `std::string` para "mostrar" (el que llama imprime), aunque algunos métodos aún imprimen directo (`mostrarCanchas`, mensajes de `registrarCliente`, `mostrarListado` vacío).
- **Memoria**: `new`/`delete` manual, destructor libera elementos y luego el arreglo. `#pragma once` en todos los headers. Strings pasados por valor (no `const&`).
- **UI**: bucle `do { … } while (opc != N)` con `switch`; opción "volver" es el último número. Validación con `do/while` repetido. Los `std::cin >> x` se usan sin validar fallo del stream; nombres con espacios usan `cin.ignore()` + `getline`.
- **Estilo de formato**: mezcla de tabs (Cancha, Reserva, GestionReservas, ColeccionCanchas) y 4 espacios (Cliente, GestionClientes, Menu). Al editar un archivo, **respetar la indentación que ya tiene ese archivo**. Comentarios cortos en español al lado de la línea explicando el porqué.
- **Simplicidad**: el código es deliberadamente básico (nivel curso de programación): sin templates, sin `const&`, sin excepciones, sin smart pointers, sin STL de contenedores. Mantener ese nivel; no introducir abstracciones avanzadas salvo que se pida.

## Deudas conocidas que quedan
1. `GestionClientes.h` tiene `class Reserva;` sin uso. `GestionClientes::mostrarListado` imprime con `cout` el caso vacío. El teléfono se lee con `cin >>` (no admite espacios).
2. `Reserva::contadorConsecutivo` inicia en 0 (los de `Espera` inician en 1). `montoTotal` es `int` (se trunca `precio * franjas`); `cout` muestra doubles grandes en notación científica (no hay `<iomanip>`).
3. `Cancha::mostrarLibre` ya no se usa (`Menu` usa `mostrarDisponibilidad`, que ahora numera las franjas 1–12).
4. Marcar una espera como "Asignado" no crea la reserva ni valida que la franja esté libre; es solo un cambio de estado.
5. Al llenarse los 10 registros de espera no se reutilizan los Asignado/Cancelado.
6. Comprobación de compilación: no hay msbuild en PATH; se puede compilar con `cl /std:c++20 /EHsc` tras `vcvars64.bat` (VS 18 Community) sobre todos los `.cpp`. Para probar el flujo por consola con entrada redirigida hay que quitar los `system("pause"/"cls")` en una copia temporal.

## Al implementar cambios
1. Seguir el patrón entidad → gestor → `Menu` (E/S solo en `Menu`, gestores devuelven `bool`/puntero/`string`).
2. Mantener nombres en español, camelCase, sin tildes.
3. Agregar nuevos `.h/.cpp` a los archivos de proyecto de VS.
4. No hay tests; validar compilando y probando el flujo por consola.
