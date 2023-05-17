#include <iostream>
#include "string.h"
#include "Reserva.h"
#include "stdio.h"

using namespace std;
Reserva::Reserva() {
	cliente = NULL;
	hotel = NULL;
	numHabitacion = 0;
}

Reserva::Reserva(Cliente* cliente, Hotel* hotel, int numHabitacion) {
	this->cliente = cliente;
	this->hotel = hotel;
	this->numHabitacion = numHabitacion;
}

Reserva::~Reserva() {

}

Reserva::Reserva(const Reserva &other) {
	cliente = other.cliente;
	hotel = other.hotel;
	numHabitacion = other.numHabitacion;
}

/////////////////// GETTERS ///////////////////////

Cliente* Reserva::getCliente()
{
	return this->cliente;
}

Hotel* Reserva::getHotel()
{
	return this->hotel;
}

int Reserva::getNumHabitacion()
{
	return this->numHabitacion;
}

void Reserva::imprimirReserva(){
	cout<< "\nReserva: Hotel "<< this->getHotel()->getNombre()<<" habitacion numero "<<this->getNumHabitacion()<<" a nombre de "<<this->getCliente()->getNombre()<<endl;
}
