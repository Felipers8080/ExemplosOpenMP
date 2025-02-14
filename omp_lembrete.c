/* Arquivo:  
 *    omp_lembrete.c
 *
 * Propósito:
 *    Demonstrar uma solução para os efeitos do
 *    Race Condition usando OpenMP.    
 *
 * Compile:  gcc -g -Wall -fopenmp -o omp_lembrete omp_lembrete.c
 * Usage:    ./omp_lembrete.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

struct Medicacao{
   char nome[50];
   int intervalo;
   int total;
}; 

void Lembrete(void* medicacao);

int main(int argc, char* argv[]) {
   
   struct Medicacao *m1, *m2, *m3, *m4;
   
   // Medicação 1
   m1 = malloc(sizeof(struct Medicacao));
   strcpy(m1->nome, "Paracetamol");
   m1->intervalo = 8;
   m1->total =  10;

   // Medicação 2
   m2 = malloc(sizeof(struct Medicacao));
   strcpy(m2->nome, "Dorflex");
   m2->intervalo = 6;
   m2->total = 12;

   // Medicação 3
   m3 = malloc(sizeof(struct Medicacao));
   strcpy(m3->nome, "Cataflan");
   m3->intervalo = 12;
   m3->total = 8;
   
   m4 = malloc(sizeof(struct Medicacao));
   strcpy(m4->nome, "B12");
   m4->intervalo = 24;
   m4->total = 7;
   
   printf("Gerenciador de lembretes iniciado!!\n");
   printf("====================================\n");
   
   omp_set_num_threads(4);
   # pragma omp parallel sections
   {
       #pragma omp section
        Lembrete(m1);
        
       #pragma omp section
        Lembrete(m2);
        
       #pragma omp section
        Lembrete(m3);
       
       #pragma omp section
        Lembrete(m4);
       
   }
   
   free(m1);
   free(m2);
   free(m3);
   free(m4);
   
   return 0; 
}

void Lembrete(void* medicacao) {
   struct Medicacao *med = (struct Medicacao*) medicacao; 
    
   int i;
   time_t t;   
   
   for  (i = 1; i <= med->total; i++){
      time(&t);
      printf("Tomar %s %d/%d ## %s", med->nome, i, med->total, ctime(&t));
      sleep(med->intervalo);
   }
   printf("FIM: %s\n", med->nome);
} 