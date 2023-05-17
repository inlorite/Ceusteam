
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
		Cliente(int id, char* nombre, char* email, int numTelf, char* contrasena);
		virtual ~Cliente();
		Cliente(const Cliente &other);

		int getId();
		char* getNombre();
		char* getEmail();
		int getTelf();
		char* getContrasena();

		Cliente* encontrarCliente(Cliente* clientes, int numClientes, char* nombre);
};

#endif /* OBJECTS_CLIENTE_H_ */
