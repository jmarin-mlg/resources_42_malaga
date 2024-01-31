# RECURSOS ÚTILES PARA ESTUDIANTES DE `42 NETWORK`
Desde aquí tendrás acceso a un listado de recursos que pueden serte de mucha
utilidad en tu aventura durante el `Cursus` y el `Common Core`. En este listado
de utilidades encontrarás desde scripts en `Shell` hasta main's que te servirán
para probar y validar tus propios proyectos.

## MAIN's
- [Main para Get Next Line](./mains/main_get_next_line.c)

## SCRIPT's
- [Script shell - Chequea leaks en C](./scripts/checkleaks):

	¡ATENCIÓN! Este script solamente funcionará en los clusters de `42 Network`,
	debido a que utiliza el comando `leaks` que no es nativo. Si quisieras
	estandarizar este script deberías sustituir ese comando por `valgrind` o
	cualquiera otra utilidad para rastrear perdidas de memoria.

	*Ejemplo de uso:*
	```bash
	# Recuerda darle permisos de ejecución a tu script
	chmod +x checkleaks

	# Si el main puede incluir argumentos añadelos en la ejecución de este script
	./checkleaks 01_el_patito_feo.txt 03_la_sirenita.txt 05_peter_pan.txt

	# Si tu main no requiere argumentos o estos pueden ser opcionales
	./checkleaks
	```

	Una vez ejecutado, el script te solicitará los ficheros de C que quieres
	compilar, así como también los flags y constantes que quieras añadir a esta
	compilación.