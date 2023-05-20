
#include "Cliente.h"
#include "string.h"

Cliente::Cliente() {
	id = 0;
	nombre = new char[10];
	email = new char[10];
	numTelf = 0;
	contrasena = new char[10];
}

Cliente::Cliente(int id, char* nombre, char* email, int numTelf, char* contrasena) {
	this->id = id;
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
	this->email = new char[strlen(email)+1];
	strcpy(this->email, email);
	this->numTelf = 0;
	this->contrasena = new char[strlen(contrasena)+1];
	strcpy(this->contrasena, contrasena);
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

void Cliente::setId(int id)
{
	this->id=id;
}

void Cliente::setNombre(char* nombre)
{
	this->nombre = new char[strlen(nombre)+1];
	strcpy(this->nombre, nombre);
}
void Cliente::setEmail(char* email)
{
	this->email = new char[strlen(email)+1];
	strcpy(this->email, email);
}

void Cliente::setTelf(int telf)
{
	this->numTelf = telf;
}

void Cliente::setContrasena(char* contrasena)
{
	this->contrasena = new char[strlen(contrasena)+1];
	strcpy(this->contrasena, contrasena);
}
/////////////////// FUNCIONES ///////////////////////

Cliente* Cliente::encontrarCliente(Cliente* clientes, int numClientes, char* nombre)
{
	for (int i = 0; i < numClientes; i++) {
		if(strcmp(clientes[i].getNombre() ,nombre)==0){
			return &clientes[i];
		}
	}
}
