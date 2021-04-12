#include <iostream>

using namespace std;

enum TokenType {
	Identifier, Keyword, Integer, Float, String,
	Character, Hexadecimal,	Operator, Comment,
	Whitespace, Separator, Eof, Comment_Error,
	String_Error, Char_Error, Hexa_Error,
};
class Token {
	public:
		TokenType tokenType;
		int position;

		Token(TokenType type, int position) {
			tokenType = type;
			this->position = position;
		}

		string tokenRead() {
			string tokenType;
			switch (this->tokenType) {
			case TokenType::Identifier:
				tokenType = "Identificator";
				break;
			case TokenType::Keyword:
				tokenType = "Cuvant cheie";
					break;
			case TokenType::Integer:
				tokenType = "Int";
					break;
			case TokenType::Float:
				tokenType = "Float";
					break;
			case TokenType::String:
				tokenType = "String";
					break;
			case TokenType::Character:
				tokenType = "Caracter";
					break;
			case TokenType::Hexadecimal:
				tokenType = "Hexa";
					break;
			case TokenType::Operator:
				tokenType = "Operator";
					break;
			case TokenType::Comment:
				tokenType = "Comentariu";
					break;
			case TokenType::Separator:
				tokenType = "Separator";
					break;
			case TokenType::Comment_Error:
				tokenType = "Eroare! Comentariu introdus incorect.";
					break;
			case TokenType::String_Error:
				tokenType = "Eroare! String introdus incorect.";
					break;
			case TokenType::Char_Error:
				tokenType = "Eroare! Caracter introdus incorect.";
					break;
			case TokenType::Hexa_Error:
				tokenType = "Eroare! Valoare hexa incorecta.";
					break;
			default:
				tokenType = "Necunoscut";
				break;
			}
		return tokenType;
		}//poate adaugam case whitespace

		bool isError() {
			return (tokenType == TokenType::Comment_Error || tokenType == TokenType::String_Error || tokenType == TokenType::Hexa_Error); // poate mai adaugam eroare
		}
};


