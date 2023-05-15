
#ifndef OBJECTS_TIPOHAB_H_
#define OBJECTS_TIPOHAB_H_

class TipoHab {
	private:
		int id;
		char* tipo;
		float precio;

	public:
		TipoHab();
		TipoHab(int id, char* tipo, float precio);
		virtual ~TipoHab();
		TipoHab(const TipoHab &other);

		int getId();
		char* getTipo();
		float getPrecio();
};

#endif /* OBJECTS_TIPOHAB_H_ */
