#pragma once
#include <string.h>
namespace Forca{
	using namespace std; // Nesse caso, pode usar o "using namespace" em um header, porque ele não irá vazar para o código todo.
	bool letra_existe(const char& letra, std::string PALAVRA_SECRETA);
}