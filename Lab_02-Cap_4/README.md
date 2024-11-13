# EJERCICIOS CAPÍTULO 4️⃣​

## Lista de Ejercicios

#### ["Ejercicio 4.1"](/Lab_02-Cap_4/Ejer_01.cpp)

![Histograma_2.7](/src/Histograma.png)

En esta sección se implementará un programa de histograma utilizando Pthreads.

#### ["Ejercicio 4.2"](/Lab_02-Cap_4/Ejer_02.cpp)

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

#### ["Ejercicio 4.6"](/Lab_02-Cap_4/Ejer_06.cpp)

Escribe un programa en Pthreads que utilice dos variables de condición y un mutex para implementar un candado de lectura-escritura. Descarga el programa de lista enlazada en línea que utiliza los candados de lectura-escritura de Pthreads y modifícalo para usar tus propios candados de lectura-escritura. Luego, compara el rendimiento del programa cuando se da preferencia a los lectores con el programa cuando se da preferencia a los escritores. ¿Puedes hacer alguna generalización?
