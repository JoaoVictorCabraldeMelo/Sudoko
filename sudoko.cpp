#include <bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> ListaAdjacencia;
typedef vector<int> Adjacencia;

struct Celula : public pair<int, int>{
	
	Celula() : pair<int, int>(0, 0){} 
	Celula(int valor, int pode) : pair<int, int>(valor, pode){} 
	Celula(Celula &celula) : pair<int, int>(celula){} 

	int& Pode(){
		auto &self = *this;
		return self.second;
	}

	int& Valor(){
		auto &self = *this;
		return self.first;
	}

};

class Tabuleiro : public vector<Celula>{
	private:
	public:
		Tabuleiro(): vector<Celula>(81){}
		
		Tabuleiro(Tabuleiro::iterator begin, Tabuleiro::iterator end): vector<Celula>(begin, end){}
		
		Celula& operator[](Tabuleiro::size_type i){
			auto &self = *this;
			string err;
			if(i >= 81){
				err = "Não pode acessar essa área de memória, indice i(", to_string(i), ") está inválido\n";
				throw range_error(err);
			} else{
				return vector<Celula>::operator[](i);
			}
		}

		static inline Tabuleiro::size_type MatrizCoordToVectorCoord(Tabuleiro::size_type i, Tabuleiro::size_type j){
			string err;
			if(i >= 9 && j >= 9){
				err = "Não pode acessar essa área de memória, indice i(", to_string(i), ") e j(", to_string(j), ") estão inválidos\n";
				throw range_error(err);
			} else if(i >= 9){
				err = "Não pode acessar essa área de memória, indice i(", to_string(i), ") está inválido\n";
				throw range_error(err);
			} else if(j >= 9){
				err = "Não pode acessar essa área de memória, indice j(", to_string(j), ") está inválido\n";
				throw range_error(err);
			} else{
				return i*9+j;
			}
		}

		void printaTaduleiro(){
			auto &self = *this;
			cout << "------------\n" << endl;
			
			for(int i = 0; i < 9; ++i){
				for(int j = 0; j < 9; ++j){
					cout << self[Tabuleiro::MatrizCoordToVectorCoord(i, j)].Valor() << "\t";
					if(i%3 == 2){
						cout << "|";
					}
				}
				cout << "\n------------\n";
			}
		}
};


ListaAdjacencia RetornaListaAdjencia(){
    ListaAdjacencia res(81);
    set <int> cadaCelula;
    for (int i = 0; i < 81; i++){
        cadaCelula.clear();
        for (int j = i % 9; j < 81; j+=9){
            cadaCelula.insert(j);
            
        }
        int l = i - (i%9);
        for (int j = i - (i%9); j < l + 9 ; j++){
            cadaCelula.insert(j);
        }

        l = i - (i%3);

        int moverpracima = l - (l%3 * 9);

        for (int j = 1; j <= 3; j++){
            for (int k = 0; k < 3; k++){
                cadaCelula.insert(moverpracima + k);
            }
            moverpracima = moverpracima + 9;
        }

        cadaCelula.erase(i);
        res[i] = Adjacencia(cadaCelula.begin(), cadaCelula.end());
    }
    
    return res;
}



int main (){

    ListaAdjacencia Matriz = RetornaListaAdjencia();
    Tabuleiro tabuleiro;

    tabuleiro[0] = {8, 1};
    tabuleiro[3] = {1, 1};
    tabuleiro[4] = {5, 1};
    tabuleiro[6] = {6, 1};
    tabuleiro[12] = {3, 1};
    tabuleiro[16] = {4, 1};
    tabuleiro[17] = {1, 1};
    tabuleiro[18] = {5, 1};
    tabuleiro[24] = {7, 1};
    tabuleiro[32] = {9, 1};
    tabuleiro[34] = {6, 1};
    tabuleiro[35] = {2, 1};
    tabuleiro[40] = {3, 1};
    tabuleiro[45] = {1, 1};
    tabuleiro[46] = {4, 1};
    tabuleiro[48] = {8, 1};
    tabuleiro[56] = {8, 1};
    tabuleiro[62] = {9, 1};
    tabuleiro[63] = {2, 1};
    tabuleiro[64] = {9, 1};
    tabuleiro[68] = {1, 1};
    tabuleiro[74] = {5, 1};
    tabuleiro[76] = {9, 1};
    tabuleiro[77] = {7, 1};
    tabuleiro[80] = {6, 1};

    priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> fila;

    cout << Matriz[0].size() << endl;
    
    for (int i = 0; i < 81; i++){
        set <int> aux;
        for (int j = 0; j < Matriz[i].size(); j++){
            auto &p = Matriz[i][j];
            if (tabuleiro[p].Valor() != 0){
                aux.insert(tabuleiro[p].Valor());
            }
            fila.push({aux.size(),i});
        }
        
    }
    

    //tabuleiro.printaTaduleiro();





    return 0;
}