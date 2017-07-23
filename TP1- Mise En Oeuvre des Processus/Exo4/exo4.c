// Declaration des bibliotheques

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Declaration et definition de la procedure qui va gerer le temps aleatoirement

void creerFils ( int pid_fils );
void creerFils ( int pid_fils )
{
  int temps;
 
  // Generation d'un nombre aleatoire de secondes
  printf("\n");
  srand ( getpid ( ) );
  temps = (int) ( ( ( double ) rand ( ) / RAND_MAX ) * 5 ) + 1;
  printf ( " Pere: Je suis dans le fils (PID=) %d et j'attend %d seconde(s)\n" , pid_fils , temps );
  sleep ( temps );
  printf("\n");
  printf ( " Pere: Je suis dans le fils (PID=) %d et je me termine\n", pid_fils );
  exit ( pid_fils );
}
 
// Definition de la methode main

int main ( )
{
  pid_t pid [ 5 ];
  int i , statut;
 
  // Creation des processus fils

  for ( i = 0; i < 5; i++ )
  {
    if ( ( pid [ i ] = fork ( ) ) == -1 )
    {
      printf( "Erreur lors de la creation du processus fils numero %d\n", i );
      goto sortie;
    }
    if ( pid [ i ] == 0 )
      creerFils ( i );
  }
 
  // Attente des processus fils et gestion des eventuelles erreurs

  printf ( "\nEn attente de la fin des processus fils dans l'ordre\n" );
  for ( i = 0 ; i < 5 ; i++ )
  {
    if ( waitpid ( pid [ i ] , &statut , 0 ) == -1 )
    {
      printf ( "Erreur lors de l'attente du fils numero %d\n" , i );
      goto sortie;
    }
    if (WIFEXITED ( statut ) )
      printf ( "\n Le fils numero %d a termine.\n La valeur retournee est %d\n", i , WEXITSTATUS ( statut ) );
    else
      printf ( "\nLe fils numero %d s'est termine anormalement\n", i );
  }
  printf ( "\nAttente terminee avec succes.\n");
 
  sortie:
  return 0;
}