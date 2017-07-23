/**
 * Ce programme illustre le fonctionnement de waitpid. Cinq fils sont crees
 * qui se mettent en pause (avec sleep) pendant un temps aleatoire. Le pere
 * attend la fils de chaque fils, dans l'ordre de creation.
 * @author Cyril Rabat
 * @version 17/01/2014
 */

#include <stdio.h>     /* Pour printf */
#include <stdlib.h>    /* Pour exit, EXIT_SUCCESS, EXIT_FAILURE */
#include <unistd.h>    /* Pour fork */
#include <sys/wait.h>  /* Pour wait */
#include <sys/types.h> /* Pour pid_t */

#define NB_FILS 5

void fils(int num) {
  int temps;

  /* Generation d'un nombre aleatoire de secondes */
  srand(getpid());
  temps = (int)(((double)rand() / RAND_MAX) * 5) + 1;

  printf("Je suis dans le fils %d et j'attend %ds\n", num, temps);
  sleep(temps);
  printf("Je suis dans le fils %d et je me termine\n", num);

  exit(num);
}

int main() {
  pid_t pid[NB_FILS];
  int i, statut;

  /* Creation des processus fils */
  for(i = 0; i < NB_FILS; i++) {
    if((pid[i] = fork()) == -1) {
      fprintf(stderr, "Erreur lors de la creation du processus fils %d\n", i);
      perror("Erreur ");
      exit(EXIT_FAILURE);
    }
    if(pid[i] == 0)
      fils(i);
  }

  /* Attente des processus fils */
  printf("Je suis dans le pere et j'attends la fin de mes fils dans l'ordre\n");
  for(i = 0; i < NB_FILS; i++) {
    if(waitpid(pid[i], &statut, 0) == -1) {
      perror("Erreur lors de l'attente du fils ");
      exit(EXIT_FAILURE);
    }
    if(WIFEXITED(statut))
      printf("Le fils %d a termine ; valeur retournee = %d\n", i, WEXITSTATUS(statut));
    else
      printf("Le fils %d s'est termine anormalement\n", i);
  }
  printf("C'est bon, je les ai tous captures.\n");

  return EXIT_SUCCESS;
}
