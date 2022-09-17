#include "Log.h"
#include <iostream>
#include <d3d9.h>

int main(){
	const char* Name = "Hello";
	printf("%s \n",Name);
	LOG_INFO("Hello World! %s \n", Name);
	while(true){};
	return 0;
}