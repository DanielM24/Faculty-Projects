#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
class LLk {
	private:
		ifstream file;
	public:
		LLk(string file_path) {
			file.open(file_path, ios::in);
			if (!file.is_open()) {
				cerr << "Error! Check grammar file.";
			}
		}
};

class Parser {

};

int main()
{
	string input_grammar = "grammar.txt", input_words = "words.txt";
	LLk grammar (input_grammar);

	Parser word = grammar.verifyLLK();
	cout << "Gramatica LL(" << word.get_k() << ")";




}