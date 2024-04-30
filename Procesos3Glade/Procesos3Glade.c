/*Compilar:
* gcc -o Procesos2Glade Procesos2Glade.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
* */

#include <gtk/gtk.h>
#include <stdio.h>

GtkWidget *window;
GtkLabel  *etiqueta;
GtkWidget *btnSalir;

pid_t id_padre;
pid_t id_proceso;
gchar szPH[128];

int main(int argc, char *argv[])
{
	GtkBuilder *builder;
	pid_t pid;
	char szWho[64];

	int i, n =3;
	for (i = 0; i<n; i++)
	{
		pid = fork();
		if(pid == -1)
		{
			sprintf(szWho,"Error al crear el hijo");
			break;
		}else if(pid == 0)
		{
			sprintf(szWho,"Proceso Hijo %d",i);
			break;
		}else {
			sprintf(szWho,"Proceso Padre %d",i);
	
		}
		
	}

	/*pid = fork();
	switch(pid)
	{
		case -1:
			sprintf(szWho,"Error al crear el hijo");
		break;
		case 0:
			sprintf(szWho,"Proceso Hijo");
		break;
		default:
			sprintf(szWho,"Proceso Padre");
		break;
	}
*/
	id_padre = getppid();
	id_proceso = getpid();
	
	sprintf(szPH,"\n%s\nPID del padre:%d\nPID del proceso: %d\n",szWho, id_padre, id_proceso);
	
	gtk_init(&argc, &argv);
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "Procesos3Glade.glade", NULL);
	
	window   = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	etiqueta = GTK_LABEL(gtk_builder_get_object(builder, "etiqueta"));
	btnSalir = GTK_WIDGET(gtk_builder_get_object(builder, "btnSalir"));
	
	gtk_builder_connect_signals(builder, NULL);
	
	gtk_label_set_text(etiqueta, szPH);
	
	gtk_widget_show(window);
	gtk_main();

	return 0;
}

void on_window_destroy()
{
	printf("Adios, hasta la próxima...\n");
	//system("./Procesos3Glade&");
	gtk_main_quit();
}

void on_btnSalir_clicked()
{
	on_window_destroy();
}

