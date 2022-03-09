#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

struct Estudiante{
	int codigo;
	char nombre[20];
	char apellido[20];
	char curso[15];	
	float nota1,nota2,nota3,nota4,promedio;
}; Estudiante estudiante;

void crear(){
	FILE * archivo=fopen("Estudiantes.dat","ab");
	string nombre, apellido, curso;
	
	cout<<"Ingresa el Codigo: "; cin>>estudiante.codigo;
	cin.ignore();
	cout<<"Ingresa el Nombre: "; getline(cin, nombre);
	strcpy(estudiante.nombre, nombre.c_str());	
	cout<<"Ingrese el Apellido: "; getline(cin, apellido);
	strcpy(estudiante.apellido, apellido.c_str());
	cout<<"Ingresa el Curso: "; getline(cin, curso);
	strcpy(estudiante.curso, curso.c_str());
	cout<<"Ingresa la Primera Nota: "; cin>>estudiante.nota1;
	cin.ignore();
	cout<<"Ingresa la Segunda Nota: "; cin>>estudiante.nota2;
	cin.ignore();
	cout<<"Ingresa la Tercera Nota: "; cin>>estudiante.nota3;
	cin.ignore();
	cout<<"Ingresa la Cuarta Nota: "; cin>>estudiante.nota4;
	cin.ignore();
	
	estudiante.promedio = (estudiante.nota1+estudiante.nota2+estudiante.nota3+estudiante.nota4)/4;
		if (estudiante.promedio>=60){
			cout<<"\nEl Estudiante aprueba con un promedio de: "<<estudiante.promedio<<endl;
		}else{
			cout<<"\nEl Estudiante reprueba con un promedio de: "<<estudiante.promedio<<endl;
		}
	
	fwrite(&estudiante,sizeof(Estudiante),1,archivo);
	fclose(archivo);
}

void leer(){
	FILE * archivo=fopen("Estudiantes.dat","rb");
	if (!archivo){
		cout<<"No se encontró el archivo"<<endl;
		exit;
	}
	int id = 0;
	double promedio;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	cout<<"id	Codigo	Nombre	Apellido Curso	Nota 1	Nota 2	Nota 3	Nota 4	Promedio"<<endl;
	do{
		cout<<"_________________________________________________________________________________________________"<<endl;
		cout<<id<<"	| "<<estudiante.codigo<<"	|"<<estudiante.nombre<<"	| "<<estudiante.apellido<<"	| "<<estudiante.curso
			<<"	| "<<estudiante.nota1<<"	| "<<estudiante.nota2<<"	| "<<estudiante.nota3<<"	| "<<estudiante.nota4<<"	| "<<estudiante.promedio<<endl;
		fread(&estudiante,sizeof(Estudiante),1,archivo);
		id+=1;
	} while (feof(archivo) ==0);
	cout<<endl;
	fclose(archivo);
}

void buscar(){
	FILE * archivo=fopen("Estudiantes.dat","rb");
	int codigo;
	double promedio;
	cout<<"Busca por el codigo del estudiante: "; cin>>codigo;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	do
	{
		if(codigo==estudiante.codigo)
		{
			fseek(archivo,codigo* sizeof(Estudiante),SEEK_SET);
			fread(&estudiante,sizeof(Estudiante),1,archivo);
			cout<<"\n_________________ Codigo "<<codigo<<" _________________"<<endl;
			cout<<"Codigo:		"<<estudiante.codigo<<endl;
			cout<<"Nombre:		"<<estudiante.nombre<<endl;
			cout<<"Apellido:	"<<estudiante.apellido<<endl;
			cout<<"Curso:		"<<estudiante.curso<<endl;
			cout<<"Primera Nota:	"<<estudiante.nota1<<endl;
			cout<<"Segunda Nota:	"<<estudiante.nota2<<endl;
			cout<<"Tercera Nota:	"<<estudiante.nota3<<endl;
			cout<<"Cuarta Nota:	"<<estudiante.nota4<<endl;
			cout<<"Promedio:	"<<estudiante.promedio;
			if (estudiante.promedio>=60){
			cout<<"\nEstudiante Aprobado: "<<estudiante.promedio<<endl;
				}else{
				cout<<"\nEstudiante Reporbado D:"<<estudiante.promedio<<endl;
			}
		}
		fread(&estudiante,sizeof(Estudiante),1,archivo);
	}while(feof(archivo)==0);
	fclose(archivo);
}

void actualizar(){
	FILE* archivo = fopen("Estudiantes.dat","r+b");
	string nombre, apellido, curso;
	int codigo, id=0;
	cout<<"\nBusca por el ID del estudiante: "; cin>>id;
	fseek(archivo,id* sizeof(Estudiante), SEEK_SET);
	cout<<"_____________________________________________________________";
	cout<<"\nIngresa el nuevo codigo: ";cin>>estudiante.codigo;
	cin.ignore();
	cout<<"Ingresa el nuevo nombre: "; getline(cin,nombre);
	strcpy(estudiante.nombre,nombre.c_str());
	cout<<"Ingresa el nuevo apellido: "; getline(cin,apellido);
	strcpy(estudiante.apellido, apellido.c_str());
	cout<<"Ingresa el nuevo curso: "; getline(cin,curso);
	strcpy(estudiante.curso, curso.c_str());
	cout<<"Ingresa la nueva nota 1: "; cin>>estudiante.nota1;
	cin.ignore();
	cout<<"Ingresa la nueva nota 2: "; cin>>estudiante.nota2;
	cin.ignore();
	cout<<"Ingresa la nueva nota 3: "; cin>>estudiante.nota3;
	cin.ignore();
	cout<<"Ingresa la nueva nota 4: "; cin>>estudiante.nota4;
	cin.ignore();
	estudiante.promedio = (estudiante.nota1+estudiante.nota2+estudiante.nota3+estudiante.nota4)/4;
	cout<<"El nuevo promedio es de: "<<estudiante.promedio<<endl;
	if (estudiante.promedio>=60){
			cout<<"\nAprobado"<<estudiante.promedio<<endl;
				}else{
				cout<<"\nReporbado"<<estudiante.promedio<<endl;
			}
	fwrite(&estudiante,sizeof(Estudiante),1,archivo);
	fclose(archivo);
}

void expulsar(){
	int id;
	double promedio;
	FILE * archivo=fopen("Estudiantes.dat","rb");
	FILE * auxiliar=fopen("auxiliar.dat","wb");
	cout<<"Busca el codigo del estudiante que deseas expulsar: ";cin>>id;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	while(!feof(archivo))
	{
		fwrite(&estudiante,sizeof(Estudiante),1,auxiliar);
		if(estudiante.codigo==id)
		{
			int pos=ftell(auxiliar)-sizeof(Estudiante);
			fseek(auxiliar,pos,SEEK_SET);
		}
		fread(&estudiante,sizeof(Estudiante),1,archivo);
	}
	cout<<"Registro eliminado"<<endl;
	fclose(archivo);
	fclose(auxiliar);
	remove("Estudiantes.dat");
	rename("auxiliar.dat","Estudiantes.dat");
}

void menu()
{
	int opt;
	string opcion;
	cout<<"_________________________Menu de Registro_________________________"<<endl;
	cout<<"1. Agregar registros"<<endl;
	cout<<"2. Leer registros"<<endl;
	cout<<"3. Busqueda por codigo"<<endl;
	cout<<"4. Actualizar registros"<<endl;
	cout<<"5. Eliminar registros"<<endl;
	cout<<"\nElige una opcion: "; cin>>opt;
	switch(opt)
	{
		case 1:
			system("cls");
			crear();
		break;
		case 2:
			system("cls");
			leer();
		break;
		case 3:
			system("cls");
			leer();
			buscar();
		break;
		case 4:
			system("cls");
			leer();
			actualizar();
			cout<<"\n_________________________________Cambios Realizados_________________________________"<<endl;
			leer();
		break;
		case 5:
			system("cls");
			leer();
			expulsar();
			cout<<"\n_________________________________Cambios Realizados_________________________________"<<endl;
			leer();
		break;
		default:
			cout<<"Esa opcion no existe"<<endl;
		break;
	}
	cout<<"\nDeseas probar otra opcion (s/n): "; cin>>opcion;
	if(opcion=="S"||opcion=="s")
	{
		system("cls");
		menu();
	}
	else
	{
		cout<<"Fin del proceso"<<endl;
	}
}

main()
{
	menu();
}
