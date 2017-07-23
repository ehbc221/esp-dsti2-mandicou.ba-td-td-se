#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> 
int main()
{
  int f0=0,f1=1,f2=2,f3=3,f4=4;
  pid_t creation;
  printf ("Je suis le pere :%d\n", getpid());
  creation = fork();
  switch ( creation )
  {
    case  -1 : 
      printf ("Erreur dans la creation du processus");
      break;
    case   0 : 
      printf ("Fils numero %d ,mon pid est: %d \n", f0, getpid());
      break;
    default  :
      creation = fork();
      switch ( creation )
      {
        case  -1 : 
          printf ("Erreur dans la creation du processus");
          break;
        case   0 :
          sleep(1);
          printf ("Fils numero %d ,mon pid est: %d \n", f1, getpid());
          break;
        default  :
          creation = fork();               
          switch ( creation )
          {
            case  -1 : 
              printf ("Erreur dans la creation du processus");
              break;
            case   0 :
              sleep(2);
              printf ("Fils numero %d ,mon pid est: %d \n", f2, getpid());
              break;
            default  :
              creation = fork();               
              switch ( creation )
              {
                case  -1 : 
                  printf ("Erreur dans la creation du processus");
                  break;
                case   0 :
                  sleep(3);
                 printf ("Fils numero %d ,mon pid est: %d \n", f3, getpid());
                 break;
                default  :
                  creation = fork();               
                  switch ( creation )
                  {
                    case  -1 : 
                      printf ("Erreur dans la creation du processus");
                      break;
                    case   0 :
                      sleep(4);
                     printf ("Fils numero %d ,mon pid est: %d \n", f4, getpid());
                     break;
                    default  :
                      sleep(6);
                        printf ("Les 5 processus fils ont ete cree avec succes.\n");
                  }  
              }        
          } 
      }
  }
}