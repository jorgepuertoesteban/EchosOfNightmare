#include "Director.h"
#include <windows.h>

void HideConsole() {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
}

int main(){
	HideConsole();
	Director director;
	while (director.Update()) {
		director.Render();
	}
}