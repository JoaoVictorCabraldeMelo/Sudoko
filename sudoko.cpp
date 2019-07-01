#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <utility>
#include <string>
#include <functional>
#include <cstdlib>
#include <algorithm>

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
			cout << "-------------------------------------------------------------------------\n";
			for(int i = 0; i < 9; ++i){
			    cout << "|";
				for(int j = 0; j < 9; ++j){
					cout << self[Tabuleiro::MatrizCoordToVectorCoord(i, j)].Valor() << "\t";
					if(j%3 == 2){
						cout << "|";
					}
				}
                cout << "\n";
                if(i%3 == 2){
                    cout << "------------------------------------------------------------------------\n";
                }
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

        int base = (((i - i%3)/9) - ((i - i%3)/9)%3) * 9 + (i - i%3)%9;
        
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                cadaCelula.insert(base + j*9+k);
            }
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

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    vector<int> qtdDisp(81, 0);
    vector<set<int>> valDisp(81, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    vector<map<int, int>> qtdValDisp(81, {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {8, 0}, {9, 0}});

    cout << Matriz[0].size() << endl;
    cout << Matriz[0][11] << endl;
    
    for (int i = 0; i < 81; i++){
        if(tabuleiro[i].Valor() == 0){
            for (int j = 0; j < Matriz[i].size(); j++){
                auto &p = Matriz[i][j];
                qtdValDisp[i][p]++;
                valDisp[i].erase(tabuleiro[p].Valor());
            }
            qtdDisp[i] = valDisp[i].size();
            fila.push({qtdDisp[i], i});
        }
    }

    int z = 0;
    while(!fila.empty()){

        auto topFila = fila.top();
        fila.pop();

        auto disp = topFila.first;
        auto celula = topFila.second;
            if(celula == 5){
                cout << "Ola eu sou goku" << endl;
            }

        if(qtdDisp[celula] == disp && tabuleiro[celula].Pode() == 0 && tabuleiro[celula].Valor() == 0){
            auto valorDisp = *valDisp[celula].begin();
            valDisp[celula].erase(valorDisp);
            tabuleiro[celula].Valor() = valorDisp;
            cerr << celula << " " << valorDisp << endl;
            for(auto &p : Matriz[celula]){
                if(tabuleiro[p].Pode() == 0){
                    valDisp[p].erase(valorDisp);
                    qtdValDisp[celula][p]++;
                    qtdDisp[p] = valDisp[p].size();
                    if(qtdDisp[p] == 0 && tabuleiro[p].Valor() == 0)
                        fila.push({30, p});
                    else if(tabuleiro[p].Valor() == 0)
                        fila.push({qtdDisp[p], p});
                }
            }
            system("cls");
            tabuleiro.printaTaduleiro();
        } 
        else if((disp == 0 || disp == 30) && tabuleiro[celula].Pode() == 0 && tabuleiro[celula].Valor() == 0){
            if(disp == 0){
                fila.push({30, celula});
                continue;
            }
            z++;
            vector<int> cpy(Matriz[celula].begin(), Matriz[celula].end());
            sort(cpy.begin(), cpy.end(), [&qtdDisp](int a, int b){
                return qtdDisp[a] > qtdDisp[b];
            });
            vector<pair<int, int>> vet{{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {0, 8}, {0, 9}};
            int valAlterar = 0, qtdValAlterar = 0;
            for(auto&p : Matriz[celula]){
                if(tabuleiro[p].Valor() != 0 && tabuleiro[p].Pode() == 0){
                    vet[tabuleiro[p].Valor() - 1].first++;
                }
            }
            sort(vet.begin(), vet.end());
            for (auto &p : vet){
                if(p.first != 0){
                    qtdValAlterar = p.first;
                    valAlterar = p.second;
                    break;
                }
            }

            tabuleiro[celula].Valor() = valAlterar;

            if(qtdValAlterar == 1 || true){
                for(auto&p : Matriz[celula]){
                    if(tabuleiro[p].Valor() == valAlterar){
                        tabuleiro[p].Valor() = 0;
                        for(auto&q : Matriz[p]){
                            if(q != celula){
                                qtdValDisp[q][valAlterar]--;
                                if(qtdValDisp[q][valAlterar] <= 0 && tabuleiro[q].Pode() == 0){
                                    qtdValDisp[q][valAlterar] = 0;
                                    valDisp[q].insert(valAlterar);
                                    qtdDisp[q] = valDisp[q].size();
                                    if(tabuleiro[q].Valor() == 0);
                                        fila.push({qtdDisp[q], q});
                                } else if(tabuleiro[q].Pode() == 0 && tabuleiro[q].Valor() == 0){
                                        fila.push({qtdDisp[q], q});
                                }
                            }
                        }
                        for(auto&q : Matriz[celula]){
                            if(q != p){
                                qtdValDisp[p][valAlterar]++;
                                    
                                valDisp[p].erase(valAlterar);
                                qtdDisp[p] = valDisp[p].size();
                                if(qtdDisp[q] == 0 && tabuleiro[q].Valor() == 0 && tabuleiro[q].Pode() == 0)
                                    fila.push({30, q});
                                else if(tabuleiro[q].Valor() == 0 && tabuleiro[q].Pode() == 0)
                                    fila.push({qtdDisp[q], q});
                            }
                        }
                    }
                }
            }
            
            tabuleiro[celula].Valor() = valAlterar;
            system("cls");
            tabuleiro.printaTaduleiro();

            
            // if(qtdDisp[cpy[0]] > 0){
            //     tabuleiro[cpy[0]].Valor() = 0;
            //     auto valorProcura = *valDisp[cpy[0]].begin();
            //     bool flag = true;
                
            //     for(auto &p : Matriz[cpy[0]]){
            //         qtdValDisp[p][valorProcura]--;
            //         if(qtdValDisp[p][valorProcura] <= 0){
            //             qtdValDisp[p][valorProcura] = 0;
            //             valDisp[p].insert(valorProcura);
            //             qtdDisp[p] = valDisp[p].size();
            //             fila.push({qtdDisp[p], p});
            //         }
            //     }

            //     for(auto &p : Matriz[celula]){
            //         if(tabuleiro[p].Valor() == valorProcura){
            //             flag = false;
            //         }
            //     }

            //     if(flag){
            //         tabuleiro[celula].Valor() = valorProcura;
            //         for(auto &p : Matriz[celula]){
            // if(qtdDisp[celula] == disp && disp == 0 && tabuleiro[celula].Pode() == 0 && tabuleiro[celula].Valor() == 0){
            //             if(tabuleiro[p].Pode() == 0){
            //                 valDisp[p].erase(valorProcura);
            //                 qtdValDisp[celula][p]++;
            //                 qtdDisp[p] = valDisp[p].size();
            //                 fila.push({qtdDisp[p], p});
            //             }
            //         }
            //     }



        }
    }
    
            system("cls");
            tabuleiro.printaTaduleiro();

    return 0;
}