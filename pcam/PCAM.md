# Diseño de algoritmo paralelo del problema

## Algoritmo paralelo para memoria compartida

Teniendo en cuenta la versión más de C++ implementada para la traducción de cadenas se busca optimizar el algoritmo teniendo en cuenta los múltiples recursos como núcleos y nodos para la optimización de este, de eta forma se buscan las siguientes características:

### Particionado

El programa recibe como entrada un archivo .txt con una longitud fija, compuesto principalmente de los siguientes caracteres: {A, T, C, G}, representando Adenina, Timina, Citosina y Guanina. La traducción de cada complemento es independiente, de tal manera que se calculan de manera aislada con el proposito de generar la cadena ARN correspondiente. La posición del complemento corresponde respectivamente a la misma posición del complemento traducido en la cadena ARN, de esta manera se puede implementar una partición de la cadena inicial para procesar de manera paralela cada subcadena generada.

### Comunicación

El algoritmo en cuestión busca encontrar el complemento de una base especifica. Para esta tarea no es necesario conocer el estado o la informacion de otro elemento en la cadena original de ADN. De esta manera cada unidad de procesamiento o también llamado hilos no necesiten comunicarse entre ellos porque cada uno contiene la informacioón necesaria para lograr su propia tarea.

El hecho de que cada hilo tenga como tarea unas posiciones especificas en la cadena asegura que no haya una carrera para leer o escribir la variable que se comparte entre los hilos (cadena de ADN), de tal manera que se evitan problemas de concurrencia y comunicacion en los hilos que van a ejecutar el programa.

### Aglomeración

Según lo enunciado anteriormente, es posible distribuir los datos en partes iguales o similares y que cada una de estas partes sea procesada por un núcleo independiente. Lo ideal es que la cantidad de partes sea igual o muy cercana a la cantidad de núcleos ya que, de ser menos se desperdicia poder computacional, y de ser más cada una de las partes tendría una disputa de recursos, haciendo más lento el procesamiento.

De esta manera se ha decidido divirir el problema en potencia de dos para los hilos de esta manera, con un analisis se decidira cual es el número óptimo de procesos. 

### Mapeo

Para este proyecto se cuenta con un nodo [Intel® Xeon Phi™ Processor 7210](https://ark.intel.com/content/www/us/en/ark/products/94033/intel-xeon-phi-processor-7210-16gb-1-30-ghz-64-core.html) el cual cuenta con 68 núcleos, la potencia de 2 más cercana el 64, el cual debería ser la cantidad óptima de hilos. De esta manera, cada una de las tareas para el archivo de 100 millones de registros tomaría 1'562.500 registros aproximadamente.

![Speedup](../images/graphs/Multiple Threads Single Data.png.png)

## Algoritmo paralelo para procesos múltiples

Teniendo en cuenta la versión más de C++ implementada para la traducción de cadenas se busca optimizar el algoritmo teniendo en cuenta los múltiples recursos como núcleos y nodos para la optimización de este, de eta forma se buscan las siguientes características:

### Particionado

El programa recibe como entrada un archivo .txt con una longitud fija, compuesto principalmente de los siguientes caracteres: {A, T, C, G}, representando Adenina, Timina, Citosina y Guanina. La traducción de cada complemento es independiente, de tal manera que se calculan de manera aislada con el proposito de generar la cadena ARN correspondiente.

Se debe recalcar que cada uno de los procesos posee una memoria independiente, sería un contraeficiente si cada uno creara una cadena completa para su traduccion individual cuando solo llenará caracteres específicos, por esto la longitud de la cadena será dividida por el numero de procesos en cuestión. Ya que este tamaño será mucho menor a la longitud de la cadena original, lo cual permitira que cada proceso no consuma mas espacio de lo necesario y en si mejorar la velocidad de procesamiento en general. La particion es la siguiente:

````
const int stepsPerProcess = double(secuence.length()) / double(nRanks);
````

Donde stepsPerProcess son los caracteres por proceso que va a traducir. Secuence es la cadena original de ADN y nRanks es el numero de procesos en total.

### Comunicación

El algoritmo en cuestión busca encontrar el complemento de una base especifica. Para esta tarea no es necesario conocer el estado o la informacion de otro elemento en la cadena original de ADN. De esta manera cada unidad de procesamiento o también llamado hilos no necesiten comunicarse entre ellos porque cada uno contiene la informacioón necesaria para lograr su propia tarea.

En este caso hay que considerar que cada proceso cuenta con una memoria independiente en la que guarda el resultado del cálculo realizado, es necesario que los demás procesos integren de manera ordenada sus resultados ya que al ser una cadena reversa el resultado de la primera base debe ir al final y así sucesivamente. Esto se logra implementando la función Gather de MPI, la cual busca juntar el resultado de todos los procesos en uno solo. Donde en ests caso todas las subcadenas creadas son guardadas en un espacio de memoria creada por el proceso líder (proceso con rango 0).

En la implementación se puede observar lo enunciado anteriormente en los siguientes pedazos:

````
char *rna = NULL;

    if (rank == 0) {
        rna = (char *) malloc(sizeof(char) * secuence.length());
    }

    MPI_Gather(secuence.c_str() + iStart, iEnd - iStart, MPI_CHAR, rna, stepsPerProcess, MPI_CHAR, 0, MPI_COMM_WORLD);

    return rna;
````

Finalmente, de esta manera se juntan las cadenas y se asegura que el resultado sea toda la cadena en orden pero con su respectiva traducción.

### Aglomeración

Debido a las propiedades anteriormente mencionadas, es posible distribuir los datos en partes iguales o similares y que cada una de estas partes sea procesada por un nodo independiente. Lo ideal es que la cantidad de partes sea igual o muy cercana a la cantidad de nodos ya que, de ser menos se desperdicia poder computacional, y de ser más cada una de las partes tendría que disputar los recursos, haciendo más lento el procesamiento.

Por lo tanto, se ha decidido que la cantidad de partes en la que se dividirá la cadena debe estar relacionada con el número de nodos disponibles. En este caso se observó que la cantidad de nodos disponibles en el clúster era 4. Por lo cual se pueden utilizar hasta 4 nodos con múltiples hilos. Todos los datos fueron registrados en el análisis final del documento en cuestión.

### Mapeo

Para este proyecto se cuenta con máximo 4 nodos [Intel® Xeon Phi™ Processor 7210](https://ark.intel.com/content/www/us/en/ark/products/94033/intel-xeon-phi-processor-7210-16gb-1-30-ghz-64-core.html) los cuales cuentan con 68 núcleos, que es la disponibilidad del clúster de Intel puesto a disposición en este caso.
Se espera que según el tamaño del programa a ejecutar y los recursos (hilos y nodos) se evidencien los resultados de tal manera que a medida que el programa se vuelva mas complejo, sea necesario una implementación paralelizada. Sin embargo, dado el caso contrario, sea mas útil una implementación secuencial. Lo cual es el objetivo principal del proyecto en cuestión.
