#include"Header.h"

int main()
{
	clock_t start = clock();
	// first step you must create memory with random binary number 
	//create_memory(memFileAddr); 

	bool mem[rows][cols] = {};
	read_memory(mem, memFileAddr);

	clock_t end = clock();
	cout << "\nElapsed Time : " << (double)(end-start) / CLOCKS_PER_SEC << " second" << "\n\n" << "finish";
	return 0;
}