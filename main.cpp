#include <iostream>
#include <Windows.h>

#include "Field.h"

int main(){
	Field fld(23,70,6);

	fld.generate();

	while (true){
		system("cls");
		fld.draw();
		fld.make_step();
		Sleep(400);
	}

	return 0;
}