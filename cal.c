/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "server.h"

extern char buf[256];

/* HTML source for the start of the page we generate.  */

static char* page_start =
  "<html>\n"
  " <body>\n"
  " <h1>Calendário</h1>\n"
  " <form action='cal' method='get'>Ano:<br><input name='ano'><br>Mês:<br><input name='mes'><br>\n"
  "   <input type='submit' value='Consultar'></form>\n"
  "  <pre>\n";

/* HTML source for the end of the page we generate.  */

static char* page_end =
  "  </pre>\n"
  " </body>\n"
  "</html>\n";

void module_generate (int fd)
{
  pid_t child_pid;
  int rval;
  char *ano = NULL, *mes = NULL;

  /* Write the start of the page.  */
  write (fd, page_start, strlen (page_start));


  /* Fork a child process.  */
  child_pid = fork ();
  if (child_pid == 0) {
    /* This is the child process.  */

    /* Duplicate stdout and stderr to send data to the client socket.  */
    rval = dup2 (fd, STDOUT_FILENO);
    if (rval == -1)
      system_error ("dup2");
    rval = dup2 (fd, STDERR_FILENO);
    if (rval == -1)
      system_error ("dup2");
<<<<<<< HEAD
=======

    /* Parsing the parameters. */
	if(strstr(buf, "ano") != NULL){

		if(strstr(param, "mes") != NULL){
		    //printf("Mes encontrado.\n");
		    aux = strtok(param, "&");
		    ano_aux = aux;
		    while (aux != NULL) {
		        mes_aux = strdup(aux);                
			aux = strtok (NULL, "\0");
		
		    }
		    aux = strtok(mes_aux, "=");
		    while (aux != NULL) {
		        mes = strdup(aux);
		        aux = strtok (NULL, "\0");
		    }
		}
		else{
		    ano_aux = param;
		}
		aux = strtok(ano_aux, "=");
		while (aux != NULL) {
		    ano = strdup(aux);
		    aux = strtok (NULL, "\0");
		}
    }

    /* Run cal to show the calendar.  */
>>>>>>> aedb0a67df8acd1d5c9ddc26941a8fda91d8a686

    /* Parsing the parameters. */
    
    if(strstr(buf, "ano") != NULL){
        if(strstr(buf, "mes") != NULL){
            ano = strtok(buf, "&");
            mes = strtok(NULL, "?");
            strtok(mes, "=");
            mes = strtok(NULL, "=");
        }
        strtok(buf, "=");
        ano = strtok(NULL, "=");
    }

/* Set up an argumnet list for the invocation of cal.  */

    char* argv[] = { "/usr/bin/cal", "-h", mes, ano, NULL };

if(mes==NULL){
	argv[2]="2016";
		if(ano!=NULL){
			argv[2]=ano;
		}
	argv[3]=NULL;
}

if(mes!=NULL && ano==NULL){
	argv[3]="2016";
	argv[2]=mes;
}

    /* Run cal to show the calendar.  */

    execv (argv[0], argv);

    /* A call to execv does not return unless an error occurred.  */
    system_error ("execv");
  }
  else if (child_pid > 0) {
    /* This is the parent process.  Wait for the child process to
       finish.  */
    rval = waitpid (child_pid, NULL, 0);
    if (rval == -1)
      system_error ("waitpid");
  }
  else 
    /* The call to fork failed.  */
    system_error ("fork");
  /* Write the end of the page.  */
  write (fd, page_end, strlen (page_end));
}
