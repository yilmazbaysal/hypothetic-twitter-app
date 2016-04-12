#include "Main.h"
#include "Manager.h"

int main() {
	Manager* manager = new Manager();
	manager->operateInputs();
	
	delete manager;
	
	std::cin.get(); // Hold the console open
	
	return 0;
}
