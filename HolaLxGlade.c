#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *window;
GtkWidget *btnSalir;

int main(int argc, char *argv[])
{
	GtkBuilder *builder;
	///Inicializamos la interface
	gtk_init(&argc, &argv);
	///Inicializamos el apuntador para reservar el espacio de memoria
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder,"HolaLxGlade.glade", NULL);
	
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	window = GTK_WIDGET(gtk_builder_get_object(builder, "btn_salir"));
	
	gtk_builder_connect_signals(builder, NULL);
	
	gtk_widget_show(window);
	gtk_main();
	
	return 0;
}

void on_window_destroy ()
{
	printf("Adios Linux.. \n");
	gtk_main_quit();
}

void on_btn_salir_clicked()
{
	on_window_destroy();
}
