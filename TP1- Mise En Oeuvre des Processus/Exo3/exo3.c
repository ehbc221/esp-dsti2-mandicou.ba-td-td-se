// Declaration des bibliotheques

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Declaration des valeur minimale et maximale d'un entier

#define int_min -32768
#define int_max  32767

// Declaration et definition de la procedure parler ( )

void parler ( );
void parler ( )
{
  pid_t pid;
  pid = getpid ();
  printf ( "\nFils: Mon pid est : %d et mon PPID est: %d\n" , getpid () , getppid () );
  sleep ( 5 ); // Dormir pendant 5 secondes
  exit ( pid ); // Tuer le processus apres son affichage
}

// Definition de la methode main

int main ( int argc , char *argv[] )
{
  int nbr_arg = argc;

  // Control du nombre d'arguments lors de l'execution

  if ( nbr_arg <= 1 )
  {
    printf ( "Pas assez d'arguments\n" );
    goto sortie;
  }
  if ( nbr_arg > 2 )
  {
    printf ( "Trop d'arguments\n" );
    goto sortie;
  }

   // Control de la valeur de l'argument passe en parametre

  char * fin;
  long M = strtol ( argv [ 1 ] , & fin , 10 );
  if ( fin == argv [1] )
  {
    printf ( "L'argument n'est pas un entier.\n"
              "Donc Echec de creation des processus fils.\n" );
    goto sortie;
  }
  if ( ( M < int_min ) || ( M > int_max ) )
  {
    printf ( "Trop gros pour un entier\n" );
    goto sortie;
  }

  // Declaration des autre variables

  int i = 0 , N = M , test = 0 , status;
  pid_t valeur , pid;


  // S'il est un entier, creation des processus fils

  printf ( "Je suis le pere: %d\n" , getpid() );
  for ( i = 0; i < N ; i++ )
  {
    valeur = fork();
    if ( valeur == -1 ) // La creation ne s'est pas bien passee
    {
      printf ( "Erreur lors de la creation\n" );
      goto sortie;
    }
    if ( valeur == 0 ) // On est dans le processus fils
    {
      parler ( ); // Afficher les informations relatives au fils
      break;
    }
    if ( valeur > 0 ) // On est dans le processus pere
    {
    	if ( wait ( & status ) == -1 )
    	{
	    	printf ( "Error\n" );
	    	goto sortie;
    	}
		if ( WIFEXITED ( status ) )
		{
			printf ( " Terminaison normale du processus fils.\n"
	        " Code de retour : %d.\n" , WEXITSTATUS ( status ) );
    	}
    	if ( WIFSIGNALED ( status ) )
    	{
			printf ( " Terminaison anormale du processus fils.\n"
	        " Tué par le signal : %d.\n" , WTERMSIG (status) );
    	}
    }
  }while ( wait ( 0 ) > 0 );

  sortie: // Etiquette pour quitter le programme directement de n'importe quelle ligne ou partie
  return 0;
}