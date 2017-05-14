#include "Director.h"

int main(){
	Director director;
	while (director.Update()) {
		director.Render();
	}
}