#include <stdio.h>


typedef struct {
    char nombre;           // Nombre del proceso (A, B, C, ...)
    int tiempo_llegada;    // Tiempo de llegada
    int rafaga_cpu;        // Ráfaga de CPU (tiempo total requerido)
    int tiempo_restante;   // Tiempo restante por ejecutar (inicialmente igual a rafaga_cpu)
    int tiempo_espera;     // Tiempo de espera
    int tiempo_retorno;    // Tiempo de retorno
    int completado;        // Si el proceso ha completado (1) o no (0)
} Proceso;

int main() {
    int n, quantum, tiempo_total = 0, procesos_completados = 0;
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
        procesos[i].tiempo_restante = procesos[i].rafaga_cpu; 
        procesos[i].completado = 0; 
    }

    printf("Ingrese el valor del quantum: ");
    scanf("%d", &quantum);

    int tiempo_actual = 0;

  
    while (procesos_completados < n) {
        int hecho = 0;  

      
        for (int i = 0; i < n; i++) {
            if (procesos[i].tiempo_llegada <= tiempo_actual && procesos[i].tiempo_restante > 0) {
                hecho = 1;  

               
                if (procesos[i].tiempo_restante <= quantum) {
                    tiempo_actual += procesos[i].tiempo_restante;
                    procesos[i].tiempo_restante = 0;
                    procesos[i].completado = 1;
                    procesos_completados++;

                    procesos[i].tiempo_retorno = tiempo_actual - procesos[i].tiempo_llegada;
                    procesos[i].tiempo_espera = procesos[i].tiempo_retorno - procesos[i].rafaga_cpu;

                    
                    tiempo_total_espera += procesos[i].tiempo_espera;
                    tiempo_total_retorno += procesos[i].tiempo_retorno;
                }
                
                else {
                    tiempo_actual += quantum;
                    procesos[i].tiempo_restante -= quantum;
                }
            }
        }

    
        if (!hecho) {
            tiempo_actual++;
        }
    }


    printf("\n%10s%15s%15s%15s%15s%15s\n", "Proceso", "Llegada", "Ráfaga CPU", "Espera", "Retorno", "Completado");
    for (int i = 0; i < n; i++) {
        printf("%10c%15d%15d%15d%15d%15d\n",
            procesos[i].nombre,
            procesos[i].tiempo_llegada,
            procesos[i].rafaga_cpu,
            procesos[i].tiempo_espera,
            procesos[i].tiempo_retorno,
            procesos[i].completado
        );
    }


    printf("\nTiempo Medio de Espera: %.2f", tiempo_total_espera / n);
    printf("\nTiempo Medio de Retorno: %.2f\n", tiempo_total_retorno / n);

    return 0;
}



