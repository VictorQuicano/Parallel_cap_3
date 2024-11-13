# EJERCICIOS CAPÍTULO 3️⃣

> How to excute the code
> `mpic++ 'file_name'.cpp -o 'executable_file'`
> `mpirin -np 'num' ./'executable_file'`

## Lista de Ejercicios

#### ["Ejercicio 3.1"](/Lab_01-Cap_3/Ejer_01.cpp)

![Histograma_2.7](/src/Histograma.png)

En esta sección se implementará un programa de histograma utilizando MPI. El proceso 0 leerá los datos de entrada y los distribuirá entre los procesos. Además, el proceso 0 imprimirá el histograma generado.

#### ["Ejercicio 3.2"](/Lab_01-Cap_3/Ejer_02.cpp)

Supongamos que lanzamos dardos aleatorios en una diana cuadrada, cuyo centro está en el origen, y cuyos lados tienen una longitud de 2 pies. Además, hay un círculo inscrito en la diana, cuyo radio es de 1 pie y su área es π pies cuadrados. Si los puntos donde caen los dardos están distribuidos de manera uniforme (y siempre caen sobre el cuadrado), entonces el número de dardos que caen dentro del círculo debería cumplir aproximadamente con la siguiente ecuación:

\[
\frac{\text{número en el círculo}}{\text{número total de lanzamientos}} = \frac{\pi}{4}
\]

Esto se debe a que la relación entre el área del círculo y el área del cuadrado es \(\frac{\pi}{4}\). Usando esta fórmula, podemos estimar el valor de π con un generador de números aleatorios:

```c
número en el círculo = 0;
para (lanzamiento = 0; lanzamiento < número de lanzamientos; lanzamiento++) {
    x = número aleatorio entre -1 y 1;
    y = número aleatorio entre -1 y 1;
    distancia al cuadrado = x*x + y*y;
    si (distancia al cuadrado <= 1) número en el círculo++;
}
estimación de π = 4 * número en el círculo / ((double) número de lanzamientos);
```

Este método se conoce como "Método de Monte Carlo", ya que utiliza aleatoriedad (los lanzamientos de dardos) para realizar la estimación.

Crea un programa MPI que utilice el método de Monte Carlo para estimar π:

1. El proceso 0 debe leer el número total de lanzamientos y enviarlo a todos los demás procesos usando **MPI Broadcast**.
2. Usar **MPI Reduce** para encontrar la suma global de la variable local `número en el círculo` y hacer que el proceso 0 imprima el resultado.
3. Utilizar enteros de tipo `long long` para almacenar el número de aciertos dentro del círculo y el número total de lanzamientos, ya que ambos valores pueden ser muy grandes para obtener una estimación razonable de π.

Este enfoque garantiza que, a medida que aumente el número de lanzamientos, la estimación de π sea más precisa.

#### ["Ejercicio 3.3"](/Lab_01-Cap_3/Ejer_03.cpp)

Escribe un programa en MPI que calcule una suma global estructurada en árbol. Primero escribe tu programa para el caso especial en el que `comm_sz` es una potencia de dos. Luego, después de que hayas logrado que esta versión funcione, modifica tu programa para que pueda manejar cualquier valor de `comm_sz`.

#### ["Ejecicio 3.6"](/Lab_01-Cap_3/Ejer_06.cpp)

Implementa la multiplicación de matrices y vectores utilizando una distribución de submatrices por bloques de la matriz. Supón que los vectores están distribuidos entre los procesos de la diagonal. Nuevamente, puedes hacer que el proceso 0 lea la matriz y agregue las submatrices antes de enviarlas a los procesos. Supón que `comm_sz` es un cuadrado perfecto y que √`comm_sz` divide de manera uniforme el orden de la matriz.

#### ["Ejecicio 3.8"](/Lab_01-Cap_3/Ejer_08.cpp)

El ordenamiento paralelo por mezcla comienza con `n/comm_sz` claves asignadas a cada proceso. Termina con todas las claves almacenadas en el proceso 0 en orden ascendente. Para lograr esto, utiliza la misma comunicación estructurada en árbol que utilizamos para implementar una suma global. Sin embargo, cuando un proceso recibe las claves de otro proceso, fusiona las nuevas claves con su lista de claves ya ordenada. Escribe un programa que implemente el ordenamiento paralelo por mezcla. El proceso 0 debe leer n y enviarlo a los demás procesos mediante broadcast. Cada proceso debe usar un generador de números aleatorios para crear una lista local de `n/comm_sz enteros`. Luego, cada proceso debe ordenar su lista local e imprimir el resultado.
