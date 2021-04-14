#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// Definim tipiurile de tokeni
enum TokenType {
	Identifier, Keyword, Integer, Float, String,
	Character, Hexadecimal, Operator, Comment,
	Separator, Eof, Comment_Error, String_Error,
	Char_Error, Hexa_Error, Dfa_Error
};

class Token {
public:
	TokenType tokenType;
	int positionValue;

	Token(TokenType type, int positionValue) {
		tokenType = type;
		this->positionValue = positionValue;
	}

	string readToken() {
		string tokenType;
		switch (this->tokenType) {

			// Tipul tokenului este identificator
		case TokenType::Identifier:
			tokenType = "Identificator";
			break;

			// Tipul tokenului este cuvant cheie
		case TokenType::Keyword:
			tokenType = "Cuvant cheie";
			break;

			// Tipul tokenului este literal intreg
		case TokenType::Integer:
			tokenType = "Literal intreg";
			break;

			// Tipul tokenului este literal flotant
		case TokenType::Float:
			tokenType = "Literal flotant";
			break;

			// Tipul tokenului este literal string
		case TokenType::String:
			tokenType = "Literal string";
			break;

			// Tipul tokenului este literal caracter
		case TokenType::Character:
			tokenType = "Caracter";
			break;

			// Tipul tokenului este literal hexadecimal
		case TokenType::Hexadecimal:
			tokenType = "Literal hexadecimal";
			break;

			// Tipul tokenului este operator
		case TokenType::Operator:
			tokenType = "Operator";
			break;

			// Tipul tokenului este comentariu
		case TokenType::Comment:
			tokenType = "Comentariu";
			break;

			// Tipul tokenului este separator
		case TokenType::Separator:
			tokenType = "Separator";
			break;

			// Pentru cazul in care a aparut o eroare la identificarea tokenului
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

		case TokenType::Dfa_Error:
			tokenType = "Eroare!";
			break;

			// Daca ajungem in cazul default inseamna ca nu am identificat
			// niciun token
		default:
			tokenType = "Token necunoscut";
			break;
		}
		return tokenType;
	}

	// Daca intampinam vreo eroare, aceasta trebuie sa se incadreze in una din cele 4 cazuri
	bool isError() {
		return (tokenType == TokenType::Comment_Error || tokenType == TokenType::String_Error || tokenType == TokenType::Hexa_Error || tokenType == TokenType::Dfa_Error);
	}
};

/* Analizorul lexical foloseste un automat finit determinist, cu
   cate o stare finala pentru fiecare tip de token */
class LexicalAnalyzer {
	private:
		// Lista cu cuvintele cheie din C
		vector<string> keyword_List{ "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
									"else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
									"register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
									"switch", "typedef", "union", "unsigned", "void", "volatile", "while", "cin", "cout"};

		// Tabelul unde stocam valorile tokenurilor
		vector<string> value_List;
		ifstream file;
		int current_character = 0;
		int line = 1;
		int character = 0;

	public:
		LexicalAnalyzer(string file_path){
			file.open(file_path, ios::in);
			if (!file.is_open()) {
				cerr << "Error! Check file.";
			}
		}

		Token getToken() {
				// Verificam finalul fisierului
			if (file.eof()) {
				return Token(TokenType::Eof, current_character);
			}

			// Variabila pentru acumularea valorilor
			// Dorim sa identificam de fiecare data cel mai lung token
			string value_assembled = "";

			// Variabila pentru setare tipului de token
			TokenType tokenType = TokenType::Eof;

			// Variabila pentru memorarea starii
			int state = 0;

			// Variabila pentru marcarea erorilor
			bool error = false;

			while (true) {
				char c = file.get();
				value_assembled = value_assembled + c;
				current_character = current_character + 1;

				// Daca am ajuns la finalul fisierului inseamna ca am analizat tot
				if (file.eof())
					break;

				if (c == '\n') {
					character = 0;
					line++;
				}
				else character++;

				// Stare initiala
				if (state == 0) {
					// Verificam daca am intalnit un spatiu in fisier
					if (isWhitespace(c)) {
						// Analizorul lexical va ignora spatiile albe din fisierul sursa
						value_assembled = "";
						continue;
					}

					// Literal string
					if (c == '"') {
						state = 1;
						continue;
					}

					// Literal caracter
					if (c == '\'') {
						tokenType = TokenType::Character;
						state = 14;
						continue;
					}

					// Inceput constanta intreaga/flotanta
					if (isDigit(c) && c != '0') {
						state = 3;
						continue;
					}

					// Inceput cifra 0
					if (c == '0') {
						state = 11;
						continue;
					}

					// Separator
					if (isSeparator(c)) {
						tokenType = TokenType::Separator;
						break;
					}

					// Operator
					if (c == '!' || c == '~') {
						// Operatori care au decat lungime 1
						tokenType = TokenType::Operator;
						break;
					}

					if (isOperator(c)) {
						state = 5;
						continue;
					}

					// Identificatori
					if (isLetter(c) || c == '_') {
						tokenType = TokenType::Identifier;
						state = 7;
						continue;
					}
				}

#pragma region String

				if (state == 1) {
					tokenType = TokenType::String;
					// Verificam aparitia "
					if (c == '"') {
						// Ne oprim pentru ca starea urmatoare nu are tranzitii
						break;
					}

					// Verificam aparitia  '\'
					if (c == '\\') {
						state = 2;
						continue;
					}

					// Verificare caracterele
					if (isCharacter(c) || isWhitespace(c) || isDigit(c) || c == '\t') { continue; }

					// Daca nu este niciuna din variantele de mai sus inseamna ca am intalnit o eroare
					error = true;
					tokenType = TokenType::String_Error;
					break;
				}

				if (state == 2) {
					// Verificam caracterele
					if (isCharacter(c) || isWhitespace(c) || isDigit(c) || c == '\t') {
						state = 1;
						continue;
					}

					// Daca nu este niciuna din variantele de mai sus inseamna ca am intalnit o eroare
					error = true;
					tokenType = TokenType::String_Error;
					break;
				}
#pragma endregion

#pragma region Integer

				if (state == 3) {
					tokenType = TokenType::Integer;
					// Verificam daca avem .
					if (c == '.') {
						// Inseamna ca avem de a face cu un numar real
						// Mergem in starea pentru literal flotant
						state = 4;
						continue;
					}
					if (c == 'e') {
						state = 8;
						continue;
					}
					if (isDigit(c)) { continue; }

					// Blocaj
					/*Daca automatul s-a blocat intr-o stare nefinala si pe traseul parcurs de la starea initiala
					pana acolo s-a intalnit macar o stare finala, se intoarce pe traseu
					pana la ultima stare finala intalnita*/
					file.unget();
					current_character--;
					value_assembled = value_assembled.substr(0, value_assembled.size() - 1);
					break;
				}
#pragma endregion

#pragma region Float

				if (state == 4) {
					tokenType = TokenType::Float;
					if (isDigit(c)) { continue; }
					if (c == 'e') {
						state = 8;
						continue;
					}

					// Am atins finalul
					if (c != 'f') {
						file.unget();
						current_character--;
						value_assembled = value_assembled.substr(0, value_assembled.size() - 1);
					}
					break;
				}
				if (state == 8) {
					// Verificam daca avem dupa caracterul 'e' o cifra sau '-' pentru a fi literal flotant
					if (c == '-' || (isDigit(c) && c != '0')) {
						state = 4;
						continue;
					}

					// S-a terminat literal-ul flotant
					file.unget();
					current_character--;
					value_assembled = value_assembled.substr(0, value_assembled.size() - 1);
					break;
				}
#pragma endregion

#pragma region Operator

				if (state == 5) {
					// Verificam daca avem de-a face cu un comentariu
					if (c == '*' && value_assembled[0] == '/') {
						// Mergem in starea corespunzatoare comentariului
						state = 9;
						continue;
					}

					tokenType = TokenType::Operator;
					// Verificam operatorii de lungime 2 formati din dublare <<, >>, &&, ||, ++, --, ==
					if ((c == '<' || c == '>' || c == '&' || c == '|' || c == '+' || c == '-' || c == '=') && c == value_assembled[0]) {
						// Verificam << sau >> din nou care pot merge si la lungimea 3
						if (c == '<' || c == '>') {
							state = 6;
							continue;
						}
						// Gata
						break;
					}
					// Pentru operatorul ->
					if (c == '>' && value_assembled[0] == '-') { break; }

					if (c == '=') {
						// Gata
						break;
					}

					// Blocaj
					value_assembled = value_assembled.substr(0, value_assembled.size() - 1);
					file.unget();
					current_character--;
					break;
				}

				if (state == 6) {
					if (c == '=') {
						break;
					}
					// Blocaj
					value_assembled = value_assembled.substr(0, value_assembled.size() - 1);
					file.unget();
					current_character--;
					break;
				}
#pragma endregion

#pragma region Identifier

				if (state == 7) {
					if (isLetter(c) || isDigit(c) || c == '_') { continue; }

					// Blocaj
					value_assembled = value_assembled.substr(0, value_assembled.size() - 1);
					file.unget();
					current_character--;
					break;
				}
#pragma endregion

#pragma region Comment

				if (state == 9) {
					tokenType = TokenType::Comment;
					// In cazul in care intalnim steluta pentru incheierea comentariului pe mai multe linii
					if (c == '*') {
						state = 10;
						continue;
					}

					// Caz caracter eronat
					if (!(isCharacter(c) || isWhitespace(c))) {
						error = true;
						tokenType = TokenType::Comment_Error;
						break;
					}
				}

				if (state == 10) {
					// Daca avem '/' s-a terminat comentariul pe mai multe linii, altfel inapoi
					if (c == '/') {
						// Putem opri fortat parcurgerea pentru ca starea urmatoare nu are tranzitii

						// Analizorul lexical ignora spatiile albe din fisierul sursa si comentariile
						value_assembled = "";
						state = 0;
						continue;
					}
					// Daca avem * ramanem in aceeasi stare
					if (c == '*') { continue; }

					if (isCharacter(c) || isWhitespace(c)) {
						state = 9;
						continue;
					}
					// Eroare
					error = true;
					tokenType = TokenType::Comment_Error;
					break;
				}
#pragma endregion

#pragma region Hexa

				if (state == 11) {
					if (c == 'x' || c == 'X') {
						tokenType = TokenType::Hexadecimal;
						state = 12;
						continue;
					}

					//Blocaj, am gasit 0 const int
					tokenType = TokenType::Integer;
					value_assembled = value_assembled.substr(0, value_assembled.size() - 1);
					file.unget();
					current_character--;
					break;
				}

				if (state == 12) {
					string hexa_CharFirst = "123456789abcdefABCDEF";
					if (hexa_CharFirst.find(c) != string::npos) {
						state = 13;
						continue;
					}

					// Eroare
					error = true;
					tokenType = TokenType::Hexa_Error;
					break;
				}
				if (state == 13) {
					string hexa_Char = "0123456789abcdefABCDEF";
					if (hexa_Char.find(c) != string::npos) { continue; }

					// Blocaj
					tokenType = TokenType::Hexadecimal;
					value_assembled = value_assembled.substr(0, value_assembled.size() - 1);
					file.unget();
					current_character--;
					break;
				}
#pragma endregion

#pragma region Character

				if (state == 14) {
					if (isCharacter(c) || c == ' ') {
						state = 15;
						continue;
					}

					//Eroare
					error = true;
					tokenType = TokenType::Char_Error;
					break;
				}

				if (state == 15) {
					if (c == '\'') { break; } // Final literal caracter
					//Eroare
					error = true;
					tokenType = TokenType::Char_Error;
					break;
				}
			#pragma endregion

			}
			if (file.eof()) {
				if (state == 0) {
					return Token(TokenType::Eof, 0);
				}

				if (state == 1 || state == 2 || state == 8 || state == 9 || state == 10 || state == 14) {
					tokenType = TokenType::Dfa_Error;
					error = true;
				}
			}
			if (error) {
				return Token(tokenType, current_character);
			}
			int position = 0;
			vector<string>::iterator it;

			/*Daca automatul se blocheaza in starea finala asociata tipului de token "Identifier",
			atunci va cauta sirul consumat in tabelul cu cuvinte cheie si: daca-l gaseste,
			va genera tokenul cu tipul "Keyword"*/
			if (tokenType == TokenType::Identifier) {
				it = find(keyword_List.begin(), keyword_List.end(), value_assembled);
				if (it != keyword_List.end()) {
					// Avem de-a face cu un cuvant cheie
					tokenType = TokenType::Keyword;
					position = distance(keyword_List.begin(), it);
					return Token(tokenType, position);
				}
			}

			// Cautam valoarea acumulata in tabela de stringuri
			it = find(value_List.begin(), value_List.end(), value_assembled);
			if (it != value_List.end()) {
				position = distance(value_List.begin(), it);
			}
			else {
				// Adaugam la finalul listei
				value_List.push_back(value_assembled);
				position = value_List.size() - 1;
			}
			return Token(tokenType, position);
		}

		string valueStringTable(Token t){
				if (t.tokenType == TokenType::Keyword)
					return keyword_List[t.positionValue];
				return value_List[t.positionValue];
		}

		int getLine() { return line; }

		int getChar() {	return character; }

		private:
			// Functii ajutatoare pentru identificarea caracterelor
			bool isLetter(char c) {
				string letters = "abcdefghijqlmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

				return letters.find(c) != string::npos;
			}

			bool isDigit(char c) {
				string digits = "0123456789";

				return digits.find(c) != string::npos;
			}

			bool isCharacter(char c)
			{
				string characters = "abcdefghijkqlmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#%&'()*+,-./:;<=>?[\\]^_{|}~0123456789";

				return characters.find(c) != string::npos;
			}

			bool isWhitespace(char c)
			{
				return isspace(c);
			}

			bool isSeparator(char c)
			{
				string separators = "{},[]();";

				return separators.find(c) != string::npos;
			}

			bool isOperator(char c)
			{
				string operators = "+-*/%=&|^<>!";

				return operators.find(c) != string::npos;
			}
};

int main()
{
	// Luam parametrii pentru fisierul de input si fisierul de output
	string inputPath = "test.txt", outputPath = "result.txt";

	// Construim analizatorul lexical
	LexicalAnalyzer analyzer(inputPath);

	// Deschidem fisierul de output pentru scriere
	ofstream output(outputPath);

	Token token = analyzer.getToken();
	while (token.tokenType != TokenType::Eof)
	{
		if (token.isError())
		{
			cerr << "A aparut o eroare.";
			output << "Eroare lexicala de tipul: " << token.readToken() << ", la pozitia absoluta: " << token.positionValue <<
				" ,linia: " << analyzer.getLine() << " ,caracterul: " << analyzer.getChar() << endl;
			return 0;
		}
		output << "( " << token.readToken() << ", " << analyzer.valueStringTable(token) << " )" << endl;
		token = analyzer.getToken();
	}
	return 0;
}