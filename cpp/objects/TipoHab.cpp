/*
 * TipoHab.cpp
 *
 *  Created on: 5 may 2023
 *      Author: inigo
 */

#include "TipoHab.h"
#include "string.h"

TipoHab::TipoHab() {
	id = 0;
	tipo = new char[10];
	precio = 0;
}

TipoHab::~TipoHab() {
	delete [] tipo;
}

TipoHab::TipoHab(const TipoHab &other) {
	id = other.id;
	tipo = new char[strlen(other.tipo)+1];
	strcpy(tipo, other.tipo);
	precio = other.precio;
}

/////////////////// GETTERS ///////////////////////

int TipoHab::getId()
{
	return this->id;
}

char* TipoHab::getTipo()
{
	return this->tipo;
}

float TipoHab::getPrecio()
{
	return this->precio;
}
