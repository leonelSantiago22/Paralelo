/*
 * Se compila con: gcc -o Procesos1Glade Procesos1Glade.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
 * */

#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *btnSalir;
GtkLabel *etiqueta;

pid_t id_padre;
pid_t id_proceso; /// Este es el hijo
gchar szPH[64];

int main(int argc, char *argv[])
{
	GtkBuilder *builder;
	id_padre = getppid(); ///Obtenemos el proceso hijo
	id_proceso = getpid(); ///
	
	sprintf(szPH, "\nPID del padre: %d\n PID del proceso: %d \n", id_padre, id_proceso);
	
	///Inicializamos la interface
	gtk_init(&argc, &argv);
	///Inicializamos el apuntador para reservar el espacio de memoria
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder,"Procesos1Glade.glade", NULL);
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	btnSalir = GTK_WIDGET(gtk_builder_get_object(builder, "btnSalir"));
	etiqueta = GTK_LABEL(gtk_builder_get_object(builder, "etiqueta"));
	
	gtk_builder_connect_signals(builder, NULL);
	
	gtk_label_set_text(etiqueta, szPH);
	gtk_widget_show(window);
	gtk_main();
	
	return 0;
}

void on_window_destroy ()
{
	printf("Adios Linux.. \n");
	gtk_main_quit();
}

void on_btnSalir_clicked()
{
	on_window_destroy();
}
