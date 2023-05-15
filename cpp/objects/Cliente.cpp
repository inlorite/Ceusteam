/*
 * Cliente.cpp
 *
 *  Created on: 5 may 2023
 *      Author: inigo
 */

#include "Cliente.h"
#include "string.h"

Cliente::Cliente() {
	id = 0;
	nombre = new char[10];
	email = new char[10];
	numTelf = 0;
	contrasena = new char[10];
}

Cliente::~Cliente() {

}

Cliente::Cliente(const Cliente &other) {
	id = other.id;
	nombre = new char[strlen(other.nombre)+1];
	strcpy(nombre, other.nombre);
	email = new char[strlen(other.email)+1];
	strcpy(email, other.email);
	numTelf = 0;
	contrasena = new char[strlen(other.contrasena)+1];
	strcpy(contrasena, other.contrasena);
}

/////////////////// GETTERS ///////////////////////

int Cliente::getId()
{
	return this->id;
}

char* Cliente::getNombre()
{
	return this->nombre;
}
char* Cliente::getEmail()
{
	return this->email;
}

int Cliente::getTelf()
{
	return this->numTelf;
}

char* Cliente::getContrasena()
{
	return this->contrasena;
}
