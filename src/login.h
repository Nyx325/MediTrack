#ifndef LOGIN_H
#define LOGIN_H

#include "general.h"
#include "menu.h"


typedef struct {
  Opc tipo;
  char nombreUsr[31];
  char contrasenia[31];
} Usuario;

typedef struct {
  BaseForm baseLog;
  GtkWidget *usuario;
  GtkWidget *contrasenia;
  GtkWidget *banner;
  GtkWidget *warning;
  GtkWidget *aceptBtn;
} LoginWindow;


void gen_login (void);

#endif
