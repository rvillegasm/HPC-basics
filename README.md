# Proeycto 4 - HPC

### GDrive con definición del problema: https://drive.google.com/drive/folders/1ZNzmoH6BH2K68mM_ZgBes5wpGWnF9_u0?usp=sharing

El proyecto consiste en la comparacion de rendimiento entre tres formas
diferentes de abordar el problema de transformar una cadena de ADN en una
de ARN: de forma serial, usando paralelizacion de memoria compartida
(OpenMP), y usando paralelizacion basada en paso de mensajes (MPI).

Para ello, se implementaron las tres versiones del algoritmo, las cuales
se ejecutaron en un cluster con un Intel Xeon Phi, tomando los tiempos
de ejecucion para poder contrastarlos entre si.

## Datasets

Cada implementacion se ejecuto con lso siguientes tres datasets:

| Datasets  |      |
|-----------|------|
| Numero    | Size |
| Dataset 1 | 10MB |
| Dataset 2 | 1GB  |
| Dataset 3 | 3GB  |

Cada uno de ellos constaba de una cadena de ADN contenida en una sola 
linea dentro de un archivo.

## Resultados

### Primer Dataset

| Intento           | Serial    | OpenMP-2 Threads | OpenMP-4 Threads | OpenMP-12 Threads | OpenMP-32 Threads | OpenMP-64 Threads | MPI 2 Nodos - 4 Threads  | MPI 4 Nodos - 4 Threads  | MPI 2 Nodos - 16 Threads  | MPI 4 Nodos - 16 Threads  |
|-------------------|-----------|------------------|------------------|-------------------|-------------------|-------------------|--------------------------|--------------------------|---------------------------|---------------------------|
| 1                 | 0,102054  | 0,204978         | 0,140871         | 0,106182          | 0,142689          | 0,194508          | 0,171708                 | 0,193252                 | 0,217608                  | 0,216127                  |
| 2                 | 0,102053  | 0,138683         | 0,122627         | 0,131812          | 0,142483          | 0,134723          | 0,187361                 | 0,191796                 | 0,173308                  | 0,198205                  |
| 3                 | 0,102063  | 0,112893         | 0,114499         | 0,133432          | 0,117703          | 0,203463          | 0,185235                 | 0,189762                 | 0,198995                  | 0,210425                  |
| 4                 | 0,101979  | 0,126505         | 0,137916         | 0,120199          | 0,137851          | 0,138556          | 0,176203                 | 0,202907                 | 0,175903                  | 0,201385                  |
| 5                 | 0,102037  | 0,144951         | 0,113326         | 0,120533          | 0,129583          | 0,126906          | 0,177744                 | 0,218191                 | 0,171689                  | 0,203378                  |
| Promedio (s)      | 0,1020372 | 0,145602         | 0,1258478        | 0,1224316         | 0,1340618         | 0,1596312         | 0,1796502                | 0,1991816                | 0,1875006                 | 0,205904                  |
| Speed Up Relativo | NA        | 0,700795319      | 0,810798441      | 0,83342209        | 0,761120618       | 0,63920587        | 0,567977102              | 0,512282259              | 0,544196659               | 0,495557153               |

En este primer dataset se puede observar que, debido al reducido
tamaño de los datos, el mejor algoritmo para este caso es el **Serial**.
En la tabla se puede evidenciar que ninguna de las variaciones de OpenMP
ni de MPI tienen un speedup positivo cuando se comparan con la version serial.

Esto ocurre porque con tan pocos datos, el programa gasta mucho mas tiempo creando
threads y asignandoles memoria (en el caso de OpenMP) o comunicando los diferentes
nodos (en el caso de MPI) que simplemente procesando todos los datos de forma serial.

### Segundo Dataset

| Intento           | Serial   | OpenMP-2 Threads | OpenMP-4 Threads | OpenMP-12 Threads | OpenMP-32 Threads | OpenMP-64 Threads | MPI 2 Nodos - 4 Threads  | MPI 4 Nodos - 4 Threads  | MPI 2 Nodos - 32 Threads  | MPI 4 Nodos - 32 Threads  |
|-------------------|----------|------------------|------------------|-------------------|-------------------|-------------------|--------------------------|--------------------------|---------------------------|---------------------------|
| 1                 | 10,6290  | 5,61640          | 2,80000          | 0,972762          | 0,403222          | 0,242267          | 6,25000                  | 7,77443                  | 5,06993                   | 7,18970                   |
| 2                 | 10,6251  | 5,52140          | 2,79264          | 0,961628          | 0,402144          | 0,266264          | 6,24520                  | 7,77986                  | 5,04052                   | 7,12061                   |
| 3                 | 10,6264  | 5,51852          | 2,79975          | 0,981088          | 0,415330          | 0,267289          | 6,25530                  | 7,78148                  | 5,04650                   | 7,17455                   |
| 4                 | 10,6302  | 5,52739          | 2,804890         | 0,987690          | 0,490020          | 0,259970          | 6,32523                  | 7,76080                  | 5,03624                   | 7,18447                   |
| 5                 | 10,6285  | 5,54590          | 2,82680          | 0,989413          | 0,441114          | 0,283367          | 6,25919                  | 7,79041                  | 5,05269                   | 7,18834                   |
| Promedio (s)      | 10,62784 | 5,545922         | 2,804816         | 0,9785162         | 0,430366          | 0,2638314         | 6,266984                 | 7,777396                 | 5,049176                  | 7,171534                  |
| Speed Up Relativo | NA       | 1,9163342        | 3,789139822      | 10,86117941       | 24,69488761       | 40,28269569       | 1,69584604               | 1,366503647              | 2,10486622                | 1,481947935               |

![OpenMP Tiempo vs Threads](/images/graphs/d2-omp.png)
![MPI Tiempo vs Nodos + Threads](/images/graphs/d2-mpi.png)
![Speedup](/images/graphs/d2-speedup.png)

En este segundo dataset se puede evidenciar que el mejor algoritmo para
este caso es el **paralelizado con memoria compartida**.
Tal como lo muestra la grafica de Tiempo vs Threads de OpenMP, 
se puede observar que mientras mas threads se usen para procesar el dataset
de 1GB, mejores van a ser los resultados. En este caso, la opcion que
mejor rendimiento presenta es la de 64 threads.

Por otro lado, la implementacion con MPI genera mejores resultados que la
serial, pero no tan buenos como las implementaciones con OpenMP. Esto
probablemente se debe a que se gasta mucho tiempo sincronizando la informacion
entre cada uno de los nodos, ya que la informacion que cada uno de estos procese
tiene que entregarse al nodo maestro para reconstruir una sola cadena de ARN,
mientras que en las implementaciones que solamente usan threads,
la informacion no se tiene que mover a ningun lado.

### Tercer Dataset

| Intento           | Serial   | OpenMP-2 Threads | OpenMP-4 Threads | OpenMP-12 Threads | OpenMP-32 Threads | OpenMP-64 Threads | MPI 2 Nodos - 4 Threads  | MPI 4 Nodos - 4 Threads  | MPI 2 Nodos - 32 Threads  | MPI 4 Nodos - 32 Threads  |
|-------------------|----------|------------------|------------------|-------------------|-------------------|-------------------|--------------------------|--------------------------|---------------------------|---------------------------|
| 1                 | 20,3256  | 10,5422          | 5,2928           | 1,7877            | 0,7119            | 0,4030            | 11,9443                  | 14,8454                  | 9,5993                    | 13,8682                   |
| 2                 | 20,3478  | 10,6487          | 5,1425           | 1,6587            | 0,7658            | 0,4159            | 11,8456                  | 14,5987                  | 9,4123                    | 13,5687                   |
| 3                 | 20,1485  | 10,1245          | 5,6548           | 1,7985            | 0,7895            | 0,3987            | 12,0359                  | 14,3698                  | 9,6325                    | 13,6748                   |
| 4                 | 20,3651  | 10,6589          | 5,6548           | 1,5423            | 0,6987            | 0,4258            | 11,3587                  | 14,7645                  | 9,8745                    | 13,8964                   |
| 5                 | 20,9854  | 10,26540         | 5,2745           | 1,9875            | 0,7456            | 0,4025            | 11,1245                  | 14,9875                  | 9,6325                    | 13,3247                   |
| Promedio (s)      | 20,43448 | 10,44794         | 5,40388          | 1,75494           | 0,742296          | 0,4091898         | 11,66179                 | 14,71318                 | 9,63022                   | 13,66656                  |
| Speed Up Relativo | NA       | 1,955838184      | 3,781445924      | 11,64397643       | 27,52874864       | 49,93887922       | 1,752259302              | 1,388855434              | 2,121912064               | 1,495217524               |

![OpenMP Tiempo vs Threads](/images/graphs/d3-omp.png)
![MPI Tiempo vs Nodos + Threads](/images/graphs/d3-mpi.png)
![Speedup](/images/graphs/d3-speedup.png)

En este tercer dataset se puede evidenciar que la mejor implementacion
vuelve a ser la de **paralelizacion con memoria compartida**.
Las graficas muestran que el comportamiento del algoritmo con un dataset
tres veces mas grande que el anterior sigue siendo casi el mismo:
mientras mas threads se usen, mejor es el rendimiento.

La implementacion con MPI vuelve a quedar por detras de la de OpenMP,
seguramente por las mismas razones especuladas en el dataset anterior.

## Conclusiones

Para el problema de transcribir una secuencia ADN a ARN, la mejor estrategia
para implementar un algoritmo para ello parece ser usando paralelizacion
de memoria compartida, y la mayor cantidad de threads posibles
(siendo razonables y teniendo en cuenta las capacidades de la maquina en donde
se ejecutara dicho programa).

Esto aplica para datasets grandes, ya que si los datos a procesar
son extremadamente pequeños (menores a 1GB), es mejor usar solamente
una implementacion serial.

Por otro lado, las implementaciones con MPI no dieron buenos resultados con
ninguno de los dataset, pero puede que con un dataset lo suficientemente
grande, que agote la memoria de una sola maquina o que haga que abordarlo
desde un solo nodo tome demasiado tiempo, se justifique o hasta se recomiende
el uso de esta meotdologia para implementar el algoritmo.

## Distribucion del trabajo

- Implementacion serial: Rafael Villegas.
- Implementacion OpenMP: Felipe Cortes.
- Implementacion MPI: Rafael Villegas.
- Ejecucion en cluster: Felipe Cortes.
- Analisis de resultados: Felipe Cortes y Rafael Villegas.
