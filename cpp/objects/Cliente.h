/*
 * Cliente.h
 *
 *  Created on: 5 may 2023
 *      Author: inigo
 */

#ifndef OBJECTS_CLIENTE_H_
#define OBJECTS_CLIENTE_H_

class Cliente {
	private:
		int id;
		char* nombre;
		char* email;
		int numTelf;
		char* contrasena;

	public:
		Cliente();
		virtual ~Cliente();
		Cliente(const Cliente &other);

		int getId();
		char* getNombre();
		char* getEmail();
		int getTelf();
		char* getContrasena();
};

#endif /* OBJECTS_CLIENTE_H_ */
