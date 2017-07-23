// Declaration des bibliotheques

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Definition de la methode main

int main ( )
{
  // Declaration des autre variables

  int i;
  pid_t valeur;
  printf ( "Je suis le pere: %d\n" , getpid ( ) );

  // Creation des processus fils et affichage de leurs informations
  
  for ( i = 0 ; i < 5 ; i++ )
  {
    valeur = fork ( );
    if ( valeur == 0 )
    {
      printf ( "Fils numero %d ,mon pid est: %d \n" , i , getpid ( ) );
      break;
    }
  }
  while ( wait ( 0 ) > 0 );

  return 0;
}