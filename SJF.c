#include <stdio.h>


typedef struct {
    char nombre;          // Nombre del proceso (A, B, C, ...)
    int tiempo_llegada;   // Tiempo de llegada
    int rafaga_cpu;       // Ráfaga de CPU
    int tiempo_inicio;    // Tiempo de inicio
    int tiempo_finalizacion; // Tiempo de finalización
    int tiempo_espera;    // Tiempo de espera
    int tiempo_retorno;   // Tiempo de retorno
    int completado;       // Indica si el proceso ha sido completado (1) o no (0)
} Proceso;


int encontrar_proceso_mas_corto(Proceso *procesos, int n, int tiempo_actual) {
    int index = -1;
    int rafaga_minima = 10000; 

    for (int i = 0; i < n; i++) {
        if (procesos[i].tiempo_llegada <= tiempo_actual && !procesos[i].completado) {
            if (procesos[i].rafaga_cpu < rafaga_minima) {
                rafaga_minima = procesos[i].rafaga_cpu;
                index = i;
            }
        }
    }
    return index;
}

int main() {
    int n;
    float tiempo_total_espera = 0, tiempo_total_retorno = 0;

    printf("Ingrese el número de procesos: ");
    scanf("%d", &n);

    Proceso procesos[n];

  
    for (int i = 0; i < n; i++) {
        printf("Ingrese el nombre del proceso %d: ", i + 1);
        scanf(" %c", &procesos[i].nombre);
        printf("Ingrese el tiempo de llegada del proceso %c: ", procesos[i].nombre);
        scanf("%d", &procesos[i].tiempo_llegada);
        printf("Ingrese la ráfaga de CPU del proceso %c: ", procesos[i].nombre);
        scanf("%d", &procesos[i].rafaga_cpu);
        procesos[i].completado = 0; 
    }

    int tiempo_actual = 0;
    int procesos_completados = 0;

 
    while (procesos_completados < n) {
        int index = encontrar_proceso_mas_corto(procesos, n, tiempo_actual);
        if (index != -1) {
          
            procesos[index].tiempo_inicio = tiempo_actual;
            procesos[index].tiempo_finalizacion = procesos[index].tiempo_inicio + procesos[index].rafaga_cpu;
            procesos[index].tiempo_espera = procesos[index].tiempo_inicio - procesos[index].tiempo_llegada;
            procesos[index].tiempo_retorno = procesos[index].tiempo_finalizacion - procesos[index].tiempo_llegada;
         
            tiempo_total_espera += procesos[index].tiempo_espera;
            tiempo_total_retorno += procesos[index].tiempo_retorno;
            
           
            tiempo_actual = procesos[index].tiempo_finalizacion;
            procesos[index].completado = 1;
            procesos_completados++;
        } else {
            tiempo_actual++;
        }
    }


    printf("\n%10s%15s%15s%15s%20s%20s%20s\n", "Proceso", "Llegada", "Ráfaga CPU", "Inicio", "Finalización", "Tiempo Espera", "Tiempo Retorno");
    for (int i = 0; i < n; i++) {
        printf("%10c%15d%15d%15d%20d%20d%20d\n",
            procesos[i].nombre,
            procesos[i].tiempo_llegada,
            procesos[i].rafaga_cpu,
            procesos[i].tiempo_inicio,
            procesos[i].tiempo_finalizacion,
            procesos[i].tiempo_espera,
            procesos[i].tiempo_retorno
        );
    }

    printf("\nTiempo Medio de Espera: %.2f", tiempo_total_espera / n);
    printf("\nTiempo Medio de Retorno: %.2f\n", tiempo_total_retorno / n);

    return 0;
}



