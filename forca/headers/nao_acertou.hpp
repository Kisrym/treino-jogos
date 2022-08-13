#pragma once
#include <string.h>
#include <map>
namespace Forca{
	bool nao_acertou(std::string PALAVRA_SECRETA, const std::map <char, bool>& chutou);
}