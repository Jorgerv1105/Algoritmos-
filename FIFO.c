#include <stdio.h>
#include <stdlib.h>


typedef struct {
    char nombre;          // Nombre del proceso (A, B, C, ...)
    int tiempo_llegada;   // Tiempo de llegada
    int rafaga_cpu;       // Ráfaga de CPU
    int tiempo_inicio;    // Tiempo de inicio
    int tiempo_finalizacion; // Tiempo de finalización
    int tiempo_espera;    // Tiempo de espera
    int tiempo_retorno;   // Tiempo de retorno
} Proceso;


void ordenar_por_llegada(Proceso *procesos, int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(procesos[i].tiempo_llegada > procesos[j].tiempo_llegada) {
                Proceso temp = procesos[i];
                procesos[i] = procesos[j];
                procesos[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    float tiempo_total_espera = 0, tiempo_total_retorno = 0;

    printf("Ingrese el número de procesos: ");
    scanf("%d", &n);

    Proceso procesos[n];


    for(int i = 0; i < n; i++) {
        printf("Ingrese el nombre del proceso %d: ", i+1);
        scanf(" %c", &procesos[i].nombre);
        printf("Ingrese el tiempo de llegada del proceso %c: ", procesos[i].nombre);
        scanf("%d", &procesos[i].tiempo_llegada);
        printf("Ingrese la ráfaga de CPU del proceso %c: ", procesos[i].nombre);
        scanf("%d", &procesos[i].rafaga_cpu);
    }


    ordenar_por_llegada(procesos, n);


    for(int i = 0; i < n; i++) {
        if(i == 0) {

            procesos[i].tiempo_inicio = procesos[i].tiempo_llegada;
        } else {

            if(procesos[i].tiempo_llegada > procesos[i-1].tiempo_finalizacion) {
                procesos[i].tiempo_inicio = procesos[i].tiempo_llegada;
            } else {
                procesos[i].tiempo_inicio = procesos[i-1].tiempo_finalizacion;
            }
        }

        procesos[i].tiempo_finalizacion = procesos[i].tiempo_inicio + procesos[i].rafaga_cpu;

        procesos[i].tiempo_espera = procesos[i].tiempo_inicio - procesos[i].tiempo_llegada;

        procesos[i].tiempo_retorno = procesos[i].tiempo_finalizacion - procesos[i].tiempo_llegada;

 
        tiempo_total_espera += procesos[i].tiempo_espera;
        tiempo_total_retorno += procesos[i].tiempo_retorno;
    }

printf("\n%10s%15s%15s%15s%20s%20s%20s\n", "Proceso", "Llegada", "Ráfaga CPU", "Inicio", "Finalización", "Tiempo Espera", "Tiempo Retorno");
for(int i = 0; i < n; i++) {
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


