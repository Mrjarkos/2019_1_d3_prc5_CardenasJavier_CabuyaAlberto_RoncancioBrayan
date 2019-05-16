# 2019_1_d3_prc5_CardenasJavier_CabuyaAlberto_RoncancioBrayan
Escriba un programa en C/C++ que emule las cajas de un banco. Todo el banco se debe ver como un único recurso al que más de un proceso (cliente) puede acceder, es decir, que un único semáforo controlaría el acceso a las cajas.
## Introducción
Ejecutar varios procesos en tiempo real, es una de las mentiras mas grandes; debido a que la estructura del procesador no permite dicha acciòn, sino que en vez de ello se ejecuta por partes cada uno de los procesos generando el efecto que conocemos como ejecución al mismo tiempo. En otras ocaciones, cuando varios procesos ya sean computacionales y/o físicos, intentan acceder a un unico recurso, es imposible que dicho recurso se pueda repartir para todos los procesos que intentan accedere; en el siguiente informe se enseñara la solución que se utilizo para evitar que varios clientes en un banco sean asignados a un mismo cajero en un mismo instante de tiempo. Para la solución de dicho  problema se hizo uso de herramientas de programación como lo son hilos, memoria compartida,semaforos, etc.
## Planteamiento del problema
Un banco llamado Cranks Bank, presenta problema en su cede principal a la hora de atender los clientes; el problema consiste en que debido a que la cantidad de cajeros es menor a la cantidad de clientes que llegan con algun tipo de consulta  dicho lugar, las personas se acercan de a dos o mas a un solo cajero, generando problemas tanto para el banco como para ellos mismos, debido a que pierden tiempo discutiendo sobre quien sera atendido. Para ello, el banco desea implementar un sistema el cual habilite el paso de una unica persona por cajero, asignando turnos por orden de llegada.
## Objetivos
- Comprender y aplicar el uso de semaforos en la sincronización.
- Entender las ventajas de aplicarl sincronización en una solución.
- Comprender importancia del uso de tuberias para la comunicación entre diferentes procesos o programas.
## Procedimiento
En primera instancia, para dar solución al problema pl
