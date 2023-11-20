#ifndef MENU_H
#define MENU_H

#include "form_med.h"
#include "form_pac.h"
#include "form_prov.h"
#include "general.h"
#include "listv.h"
#include "listv_bar.h"

typedef struct {
  BaseForm baseVentana;
  BtnBase medicamentos;
  BtnBase pacientes;
  BtnBase proveedores;
  GtkWidget *banner;
  GtkWidget *titulos[3];
} WinMenu;


void crear_menu (void);

#endif
