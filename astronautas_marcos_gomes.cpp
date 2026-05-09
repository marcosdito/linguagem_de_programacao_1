#include <iostream>
#include <string>
#include <vector>

using namespace std;
enum Estado {PLANEJADO, EM_CURSO, SUCESSO, EXPLOSAO};

class Astronauta{
    public:
        string cpf;
        string nome;
        int idade;
        bool vivo;
        bool disponibilidade;
        Astronauta(string cpf_individuo, string nome_individuo, int idade_individuo){
            cpf = cpf_individuo;
            nome = nome_individuo;
            idade = idade_individuo;
            vivo = true;
            disponibilidade = true;
        }
};

class Voo{
    public:
        int codigo_voo;
        std::vector<std::string> lista_cpf;
        Estado estado;
        Voo(int codigo) {
            codigo_voo = codigo;
            estado = PLANEJADO;
        }
};

void CADASTRAR_ASTRONAUTA(vector<Astronauta>& astronautas, string cpf, int idade, string nome) {

    // verificar existencia astronauta
    for (int i = 0; i < astronautas.size(); i++) {
        if (astronautas[i].cpf == cpf) {
            cout << "ja foi cadastrado" << endl;
            return;
        }
    }

    // cadastrar se nao tem ninguem igual
    Astronauta a(cpf, nome, idade);
    astronautas.push_back(a);
    cout << "Astronauta " << nome << " foi cadastrado." << endl;
};

void CADASTRAR_VOO(vector<Voo>& voos, int codigo_voo){
    // verificar existencia voo
    for (int i = 0; i<voos.size(); i++){
        if (voos[i].codigo_voo == codigo_voo){
            cout << "voo ja existe" << endl;
            return;
        }
    }
    // cadastrar o voo
    Voo v(codigo_voo);
    voos.push_back(v);
    cout << "Voo" << codigo_voo << " foi cadastrado" << endl;

};

void ADICIONAR_ASTRONAUTA(vector<Astronauta>& astronautas, vector<Voo>& voos, string cpf, int codigo_voo){
    // verificar existencia astronauta
    int indiceAstronauta = -1; //pq a gnt quer que ele esteja vivo
    for (int i = 0; i < astronautas.size(); i++) {
        if (astronautas[i].cpf == cpf) {
            indiceAstronauta = i; // mudar o indice que era negativo pra poder add
        }
    }
    if (indiceAstronauta == -1) {
        cout << "Astronauta nao encontrado." << endl;
        return;
    }

    // verificar existencia do voo
    int indiceVoo = -1;
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].codigo_voo == codigo_voo) {
            indiceVoo = i;
        }
    }
    if (indiceVoo == -1) {
        cout << "Voo nao encontrado." << endl;
        return;
    }
//////////////////////////

    // verificar se voo ta planejado
    if (voos[indiceVoo].estado != PLANEJADO) {
        cout << "Voo nao ta planejado." << endl;
        return;
    }

    // ver se astronauta ta vivo
    if (!astronautas[indiceAstronauta].vivo) {
        cout << "Astronauta ta morto." << endl;
        return;
    }

    // vre se ja tem o mesmo cpf
    for (int i = 0; i < voos[indiceVoo].lista_cpf.size(); i++) {
        if (voos[indiceVoo].lista_cpf[i] == cpf) {
            cout << "Astronauta ja ta no voo." << endl;
            return;
        }
    }

    // adicionar astronauta
    voos[indiceVoo].lista_cpf.push_back(cpf);
    cout << "Astronauta " << astronautas[indiceAstronauta].nome << " adicionado a " << codigo_voo << endl;

};

void REMOVER_ASTRONAUTA(vector<Astronauta>& astronautas, vector<Voo>& voos, string cpf, int codigo_voo){
    // verificar existencia astronauta
    int indiceAstronauta = -1; //pq a gnt quer que ele esteja vivo
    for (int i = 0; i < astronautas.size(); i++) {
        if (astronautas[i].cpf == cpf) {
            indiceAstronauta = i; // mudar o indice que era negativo pra poder add
        }
    }
    if (indiceAstronauta == -1) {
        cout << "Astronauta nao encontrado." << endl;
        return;
    }

    // verificar existencia do voo
    int indiceVoo = -1;
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].codigo_voo == codigo_voo) {
            indiceVoo = i;
        }
    }
    if (indiceVoo == -1) {
        cout << "Voo nao foi encontrado." << endl;
        return;
    }

    // verificar se voo ta planejado
    if (voos[indiceVoo].estado != PLANEJADO) {
        cout << "Voo nao ta planejado." << endl;
        return;
    }

    // ver se astronauta está no voo
    int indiceCpf = -1;
    for (int i = 0; i < voos[indiceVoo].lista_cpf.size(); i++) {
        if (voos[indiceVoo].lista_cpf[i] == cpf) {
            indiceCpf = i;
        }
    }
    if (indiceCpf == -1) {
        cout << "Astronauta nao esta no voo." << endl;
        return;
    }

    // remover astronauta
    voos[indiceVoo].lista_cpf.erase(voos[indiceVoo].lista_cpf.begin()+ indiceCpf);
    cout << "Astronauta " << astronautas[indiceAstronauta].nome << " removido de " << codigo_voo << endl;

};

void LANCAR_VOO(vector<Astronauta>& astronautas, vector<Voo>& voos, int codigo_voo){
    // encontrar voo
    int indiceVoo = -1;
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].codigo_voo == codigo_voo) {
            indiceVoo = i;
        }
    }
    if (indiceVoo == -1) {
        cout << "Voo nao foi encontrado." << endl;
        return;
    }

    // verificar se está planejado
    if (voos[indiceVoo].estado != PLANEJADO) {
        cout << "Voo nao ta planejado." << endl;
        return;
    }

    // verificar se tem pelo menos um astronauta
    if (voos[indiceVoo].lista_cpf.size() == 0) {
        cout << "Voo nao tem astronautas." << endl;
        return;
    }

    // verificar se todos estão vivos e disponíveis
    for (int i = 0; i < voos[indiceVoo].lista_cpf.size(); i++) {
        string cpf = voos[indiceVoo].lista_cpf[i];
        for (int j = 0; j < astronautas.size(); j++) {
            if (astronautas[j].cpf == cpf) {
                if (!astronautas[j].vivo) {
                    cout << "Astronauta " << astronautas[j].nome << " esta morto." << endl;
                    return;
                }
                if (!astronautas[j].disponibilidade) {
                    cout << "Astronauta " << astronautas[j].nome << " esta indisponivel." << endl;
                    return;
                }
            }
        }
    }

    // lançar o voo
    voos[indiceVoo].estado = EM_CURSO;

    // marcar todos como indisponíveis
    for (int i = 0; i < voos[indiceVoo].lista_cpf.size(); i++) {
        string cpf = voos[indiceVoo].lista_cpf[i];
        for (int j = 0; j < astronautas.size(); j++) {
            if (astronautas[j].cpf == cpf) {
                astronautas[j].disponibilidade = false;
            }
        }
    }

    cout << "Voo " << codigo_voo << " lancado." << endl;
}

void EXPLODIR_VOO(vector<Astronauta>& astronautas, vector<Voo>& voos, int codigo_voo){
    // encontrar voo
    int indiceVoo = -1;
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].codigo_voo == codigo_voo) {
            indiceVoo = i;
        }
    }
    if (indiceVoo == -1) {
        cout << "Voo nao foi encontrado." << endl;
        return;
    }

    // verificar se está em curso
    if (voos[indiceVoo].estado != EM_CURSO) {
        cout << "Voo nao ta em curso." << endl;
        return;
    }

    // matar todos os astronautas
    for (int i = 0; i < voos[indiceVoo].lista_cpf.size(); i++) {
        string cpf = voos[indiceVoo].lista_cpf[i];
        for (int j = 0; j < astronautas.size(); j++) {
            if (astronautas[j].cpf == cpf) {
                astronautas[j].vivo = false;
                astronautas[j].disponibilidade = false;
            }
        }
    }

    voos[indiceVoo].estado = EXPLOSAO;
    cout << "Voo " << codigo_voo << " explodiu." << endl;
}

void FINALIZAR_VOO(vector<Astronauta>& astronautas, vector<Voo>& voos, int codigo_voo){
    // encontrar voo
    int indiceVoo = -1;
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].codigo_voo == codigo_voo) {
            indiceVoo = i;
        }
    }
    if (indiceVoo == -1) {
        cout << "Voo nao foi encontrado." << endl;
        return;
    }

    // verificar se está em curso
    if (voos[indiceVoo].estado != EM_CURSO) {
        cout << "Voo nao ta em curso" << endl;
        return;
    }

    // liberar todos os astronautas
    for (int i = 0; i < voos[indiceVoo].lista_cpf.size(); i++) {
        string cpf = voos[indiceVoo].lista_cpf[i];
        for (int j = 0; j < astronautas.size(); j++) {
            if (astronautas[j].cpf == cpf) {
                astronautas[j].disponibilidade = true;
            }
        }
    }

    voos[indiceVoo].estado = SUCESSO;
    cout << "Voo " << codigo_voo << " finalizado" << endl;
}

void LISTAR_VOOS(vector<Astronauta>& astronautas, vector<Voo>& voos){
    string estados[] = {"PLANEJADO", "EM CURSO", "SUCESSO", "EXPLOSAO"};
    Estado ordem[] = {PLANEJADO, EM_CURSO, SUCESSO, EXPLOSAO};

    for (int e = 0; e < 4; e++) {
        cout << " - " << estados[e] << " - " << endl;
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].estado == ordem[e]) {
                cout << "Voo " << voos[i].codigo_voo << endl;
                for (int j = 0; j < voos[i].lista_cpf.size(); j++) {
                    string cpf = voos[i].lista_cpf[j];
                    for (int k = 0; k < astronautas.size(); k++) {
                        if (astronautas[k].cpf == cpf) {
                            cout << "  " << cpf << " " << astronautas[k].nome << endl;
                        }
                    }
                }
            }
        }
    }
}

void LISTAR_MORTOS(vector<Astronauta>& astronautas, vector<Voo>& voos){
    for (int i = 0; i < astronautas.size(); i++) {
        if (!astronautas[i].vivo) {
            cout << astronautas[i].cpf << " - " << astronautas[i].nome << endl;
            // listar voos em que participou
            for (int j = 0; j < voos.size(); j++) {
                if (voos[j].estado == EM_CURSO || voos[j].estado == SUCESSO || voos[j].estado == EXPLOSAO) {
                    for (int k = 0; k < voos[j].lista_cpf.size(); k++) {
                        if (voos[j].lista_cpf[k] == astronautas[i].cpf) {
                            cout << "  Voo " << voos[j].codigo_voo << endl;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    string comando;
    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        }
        if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);     // lê o resto da linha como nome
            CADASTRAR_ASTRONAUTA(astronautas, cpf, idade, nome);
        }
        if (comando == "CADASTRAR_VOO") {
            int codigo_voo;
            cin >> codigo_voo;
            CADASTRAR_VOO(voos, codigo_voo);

        }
        if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo_voo;
            cin >> cpf >> codigo_voo;
            ADICIONAR_ASTRONAUTA(astronautas, voos, cpf, codigo_voo);
        }
        if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo_voo;
            cin >> cpf >> codigo_voo;
            REMOVER_ASTRONAUTA(astronautas, voos, cpf, codigo_voo);
        }
        if (comando == "LANCAR_VOO") {
            int codigo_voo;
            cin >> codigo_voo;
            LANCAR_VOO(astronautas, voos, codigo_voo);
        }
        if (comando == "EXPLODIR_VOO") {
            int codigo_voo;
            cin >> codigo_voo;
            EXPLODIR_VOO(astronautas, voos, codigo_voo);
        }
        if (comando == "FINALIZAR_VOO") {
            int codigo_voo;
            cin >> codigo_voo;
            FINALIZAR_VOO(astronautas, voos, codigo_voo);
        }
        if (comando == "LISTAR_VOOS") {
            LISTAR_VOOS(astronautas, voos);
        }
        if (comando == "LISTAR_MORTOS") {
            LISTAR_MORTOS(astronautas, voos);
        }
        
    }
    return 0;
}