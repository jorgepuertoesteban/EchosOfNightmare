#include "Director.h"

int main(){
	Director *director = new Director();
	while (director->Update()) {
		director->Render();
	}
}