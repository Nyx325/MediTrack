#ifndef MENU_H
#define MENU_H

#include "form_med.h"
#include "form_pac.h"
#include "form_prov.h"
#include "general.h"
#include "listv.h"
#include "listv_bar.h"

#define USUARIO_FARMACIA 0
#define USUARIO_DOCTOR 1
#define USUARIO_ADMIN 2

typedef struct {
  BaseForm baseVentana;
  BtnBase medicamentos;
  BtnBase pacientes;
  BtnBase proveedores;
  GtkWidget *banner;
  GtkWidget *titulos[3];
} WinMenu;

extern Opc tipoUsr;
extern WinMenu menu;

void crear_menu (Opc usuario);

#endif
