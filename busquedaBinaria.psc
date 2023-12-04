Función encontrado <- busquedaBinaria (arregloCadenas,TAMANOARREGLO,buscar)
	izquierda <- 1
	derecha <- TAMANOARREGLO
	encontrado <- Falso
	// Búsqueda binaria
	Mientras izquierda<=derecha Y  NO encontrado Hacer
		medio <- trunc(izquierda+(derecha-izquierda)/2)
		Si arregloCadenas[medio]=buscar Entonces
			encontrado <- Verdadero
		SiNo
			Si arregloCadenas[medio]<buscar Entonces
				izquierda <- medio+1
			SiNo
				derecha <- medio-1
			FinSi
		FinSi
	FinMientras
FinFunción

Función bsort (arregloCadenas,TAMANOARREGLO)
	// Ordenamiento de Burbuja
	Para i<-1 Hasta TAMANOARREGLO-1 Hacer
		Para j<-1 Hasta TAMANOARREGLO-i Hacer
			Si arregloCadenas[j]>arregloCadenas[j+1] Entonces
				temp <- arregloCadenas[j]
				arregloCadenas[j] <- arregloCadenas[j+1]
				arregloCadenas[j+1]<-temp
			FinSi
		FinPara
	FinPara
FinFunción

Algoritmo OrdenarArregloCadenas
	// Declaración de variables
	Definir arregloCadenas, temp, busqueda Como Cadena
	Definir i, j Como Entero
	Definir encontrado Como Lógico
	Definir TAMANOARREGLO Como Entero
	TAMANOARREGLO <- 5
	Escribir "Ingrese la cadena a buscar:"
	Leer busqueda
	Dimensionar arregloCadenas(TAMANOARREGLO)
	// Asignación de valores al arreglo
	arregloCadenas[1] <- 'zebra'
	arregloCadenas[2] <- 'gato'
	arregloCadenas[3] <- 'manzana'
	arregloCadenas[4] <- 'banana'
	arregloCadenas[5] <- 'elefante'
	// Ordenar Arreglo
	bsort(arregloCadenas,TAMANOARREGLO)
	// Mostrar el arreglo ordenado
	Escribir 'Arreglo de cadenas ordenado:'
	Para i<-1 Hasta TAMANOARREGLO Hacer
		Escribir arregloCadenas[i]
	FinPara
	// Buscar en el arreglo mediante Busqueda Binaria
	encontrado <- busquedaBinaria(arregloCadenas,TAMANOARREGLO,busqueda)
	Escribir ''
	Si encontrado Entonces
		Escribir 'El elemento ', busqueda, ' se encuentra en el arreglo.'
	SiNo
		Escribir 'El elemento ', busqueda, ' no se encuentra en el arreglo.'
	FinSi
FinAlgoritmo
