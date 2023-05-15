/*
 * TipoHab.h
 *
 *  Created on: 5 may 2023
 *      Author: inigo
 */

#ifndef OBJECTS_TIPOHAB_H_
#define OBJECTS_TIPOHAB_H_

class TipoHab {
	private:
		int id;
		char* tipo;
		float precio;

	public:
		TipoHab();
		virtual ~TipoHab();
		TipoHab(const TipoHab &other);

		int getId();
		char* getTipo();
		float getPrecio();
};

#endif /* OBJECTS_TIPOHAB_H_ */
