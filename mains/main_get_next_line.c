/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmarin-o <jmarin-o@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:45:58 by jmarin-o          #+#    #+#             */
/*   Updated: 2024/01/30 18:46:30 by jmarin-o         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // For printf
#include <fcntl.h> // For open and close
#include <time.h>  // For time

// Pon aquí el path de tu librería de get_next_line (con o sin bonus)
#include "/Users/jmarin-o/Cursus/get_next_line/get_next_line_bonus.h"

// Pon aquí el path del directorio de tus textos
#define PATH_TEXTS "/Users/jmarin-o/Cursus/resources/texts"

// Prototipos de las funciones
char	**init_file_names(void);
char	**init_shuffle(char **array, char **temp_array, int size);
void	shuffle(char **array, int size);
char	*ft_strrchr(const char *s, int c);
void	display_line(const char *file_name, int line_number, const char *text);

/*
** Función para inicializar el array de los nombres de ficheros.
**
** El primer elemento no leerá un fichero real, tomará la entrada por teclado.
** De ahí que lo llamemos aquí "stdin".
*/
char	**init_file_names(void)
{
	static char	*file_names[8];

	file_names[0] = "stdin";
	file_names[1] = "01_el_patito_feo.txt";
	file_names[2] = "02_la_caperucita_roja.txt";
	file_names[3] = "03_la_sirenita.txt";
	file_names[4] = "04_los_tres_cerditos.txt";
	file_names[5] = "05_peter_pan.txt";
	file_names[6] = "06_empty.txt";
	file_names[7] = "07_no_existe.txt";
	return (file_names);
}

/*
** Función para incializar el shuffle.
**
** srand() junto a time() se utiliza para crear una semilla única y al utilizar
** rand obtener una secuencia aleatoria de elemntos en cada ejecución, si
** prescidieramos de srand, el programa mostraría la misma secuencia aleatoria en
** todas las ejecuciones.
**
** temp_array se utiliza para guardar los elementos del array original pero a
** partir del segundo elemento. Posteriormente se desordena este array temporal y
** se vuelve a copiar en el array original.
*/
char	**init_shuffle(char **array, char **temp_array, int size)
{
	int		i;
	int		j;
	char	*temp_str;

	srand(time(NULL));
	i = 0;
	while (++i < size)
		temp_array[i - 1] = array[i];
	i = size - 2;
	while (i >= 1)
	{
		j = rand() % (i + 1);
		temp_str = temp_array[i];
		temp_array[i] = temp_array[j];
		temp_array[j] = temp_str;
		--i;
	}
	i = 0;
	while (++i < size)
		array[i] = temp_array[i - 1];
	return (temp_array);
}

/*
** Función para desordenar un array de strings, manteniendo el primer elemento
** en su posición original.
*/
void	shuffle(char **array, int size)
{
	char	**temp_array;

	temp_array = (char **) malloc(sizeof(char *) * size);
	if (temp_array == NULL)
		return ;
	free(init_shuffle(array, temp_array, size));
	temp_array = NULL;
}

/*
** Función que busca la última ocurrencia de un caracter en un string y
** devuelve un puntero a partir del caracter buscado, si no lo encontrará
** devuelve la misma cadena recibida (la función original de libft devuelve
** NULL).
*/
char	*ft_strrchr(const char *s, int c)
{
	char	searched;
	size_t	i;

	searched = (unsigned char) c;
	i = ft_strlen(s);
	while (i > 0)
		if (s[i--] == searched)
			return ((char *) s + i + 1);
	if (s[i] == searched)
		return ((char *) s + i);
	return ((char *) s - 1);
}

/*
** Función para imprimir las línieas de texto.
**
** Se muestra el nombre del fichero, seguido del número de línea y el texto de
** esa línea.
*/
void	display_line(const char *file_name, int line_number, const char *text)
{
	printf("%25s - line [%02d]: %s", file_name, line_number, text);
}

/*
** Función principal que es capaz de manejar múltiples descriptores al mismo
** tiempo y de manera alterna (genero un shuffle aleatorio), NO respeta la norma.
**
** No quería complicarme más la vida, utilizando estructuras y/o prescidiendo
** de los bucles FOR para conseguir dejarla en 25 líneas.
**
** También veía necesario poner comentarios aclaratorios dentro de esta función
** dada su finalidad pedagógica.
*/
int	main(int argc, char *argv[])
{
	char	full_path[256];
	char	*line;
	int		num_files;
	int		nil_files;
	int		line_number;
	int		*fd;
	char	**file_names;

	/*
	** En el caso de que el programa reciba argumentos, cuento el número de
	** ficheros introducidos y guardo en el puntero `file_names` estos ficheros
	** reservando siempre el primer elemento para stdin.
	**
	** Por lo contrario, si el programa no recibe argumentos fijo a 8 el número
	** de ficheros e inicializo el puntero `file_names` mediante la función
	** asignada a tal efecto.
	*/
	if (argc > 1) {
		num_files = argc;
		file_names = (char **) malloc(sizeof(char *) * num_files);
		file_names[0] = "stdin";
		for (int i = 1; i < num_files; i++) {
			file_names[i] = argv[i];
		}
	} else {
		num_files = 8;
		file_names = init_file_names();
	}

	// Reservo memoria para todos los descriptores
	fd = (int *) malloc(sizeof(int) * num_files);

	/*
	** Limpio la pantalla (código de escape "\033[H\033[J") y solicito
	** introducir texto por el teclado.
	*/
	printf("\033[H\033[J\nEnter lines of text (Press Ctrl+D to finish):\n\n");

	// Primer descriptor guardará la entrada por teclado (stdin)
	fd[0] = STDIN_FILENO;

	// Mezclo aleatoriamente el array de nombres de ficheros
	shuffle(file_names, num_files);

	/*
	** Guardo el contenido de los ficheros de texto en cada descriptor,
	** excluyendo el primer descriptor que está reservado para stdin
	*/
	for (int i = 1; i < num_files; i++)
	{
		if (argc > 1)
			fd[i] = open(file_names[i], O_RDONLY);
		else
		{
			snprintf(
				full_path, sizeof(full_path),
				"%s/%s",
				PATH_TEXTS,
				file_names[i]);
			fd[i] = open(full_path, O_RDONLY);
		}
		if (fd[i] == -1)
			close(fd[i]);
	}

	/*
	** Inicio un bucle infinito, únicamente saldrá de él cuando todos los
	** descriptores devuelvan NULL.
	**
	** Es decir, si los ficheros de texto se quedan sin líneas que leer pero
	** continuo introduciendo líneas de texto por teclado el programa continuará.
	**
	** El programa concluirá cuando tras pulsar Ctrl+D, todos los descriptores
	** devuelvan NULL.
	*/
	line_number = 1;
	while (1)
	{
		nil_files = 0;
		for (int i = 0; i < num_files; i++)
		{
			line = get_next_line(fd[i]);

			/*
			** Si el programa se ejecuta con argumentos busco la última
			** ocurrencia del carcacter '/' para eliminar el path e imprimo el
			** puntero resultante a partir de la segunda posición para evitar
			** mostrar el primer caracter '/'.
			*/
			if (argc > 1)
				display_line(
					ft_strrchr(file_names[i], '/') + 1, line_number, line);
			else
				display_line(file_names[i], line_number, line);

			/*
			** Si la línea devuelve NULL significa que no hay nada más que leer
			** en ese descriptor.
			**
			** Por lo tanto, lo contabilizamos nulo y cerramos el descriptor
			** siempre y cuando no sea stdin que no es necesario cerrarlo.
			**
			** El descriptor de entrada estándar no se cierra explicítamente, se
			** encargará de cerrarlo el sistema operativo cuando acabe con él.
			*/
			if (!line)
			{
				printf("\n");
				++nil_files;
				if (i != 0)
					close(fd[i]);
			}

			free(line);
			line = NULL;
		}

		printf("\n");
		++line_number;

		if (nil_files == num_files)
		{
			printf("\nThere are no more lines to read. Exiting...\n\n");
			break ;
		}
	}

	/*
	** Por último, libero la memoria utilizada para el puntero de los
	** descriptores y también para el puntero de los nombres de ficheros.
	**
	** Este último puntero solamente se libera en el caso de hayan llegado al
	** programa argumentos que es cuando se le asigna memoria dinámicamente,
	** en el caso de no llegar argumentos no se asigna memoria dinamicamente a
	** `file_names` y si utilizaramos free nos daría un leak de memoria.
	*/
	free(fd);
	fd = NULL;
	if (argc > 1)
	{
		free(file_names);
		file_names = NULL;
	}
	return (0);
}
