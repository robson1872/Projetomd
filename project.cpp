#include<bits/stdc++.h>//biblioteca 
#define ll long long // trataremos com numeros muito grandes da ordem de 10^100
using namespace std;//nao precisar usar std::
int escolha;//escolha do usario
ll p,q,e,n,chaven,chavee,fi;//inteiros primos p e q e o expoente e primo em relacao a (p-1)*(q-1) e o n que forma a chave publica junto com o e
string mensagem,mensageme,mensagemd;
ll inv(ll a, ll b, ll & x, ll & y) {//encontra o inverso
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = inv(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
long long mod(long long a, long long b, long long m) {// calcula o inverso do modulo em uma exponencial de forma (log n) 
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)    //impar  (& operador bitwise and)
            res = res * a % m;  //o mesmo que (res % m) * (a % m)
        a = a * a % m;
        b >>= 1;   // /2 ( >> operador bitwise shift)
    }
    return res;
}
void encriptar(){//encripta a mensagem
    for(auto a: mensagem){
        if(a==' '){
            ll b = 28;
            b = mod(b,chavee,chaven);
            mensageme += (char)(b+63);
        }else{
            ll b = (ll)(a) - 63;
            b = mod(b,chavee,chaven);
            mensageme += (char)(b+63);
        }
    }
    return;
}
void desencriptar(){//desencripta a mensagem
    fi = (p-1)*(q-1);
    ll x,y;
    inv(e,fi,x,y);
    ll d = x;// d para chave privada que eh o inverso mult de e mod fi
    for(auto k : mensageme){
        ll b = (ll)(k) - 63;
        b = mod(b,d,n);
        if(b==28){
            mensagemd += ' ';
        }else{
            mensagemd += (char)(b+63);
        }
    }
    return;
}
int main(){//funcao principal
    while(true){
        cout<<"Digite a escolha:";
        cin>>escolha;//escolha do usuario
        if(escolha == 1){//gerar chave publica
            cout<<"Digite um Primo:";
            cin>>p;
            cout<<"Digite outro Primo:";
            cin>>q;
            cout<<"Digite o expoente>";
            cin>>e;
            n = p*q;
            ofstream out("chavep.txt");
            out<<"Chave: ("<<n<<","<<e<<")";
            out.close();
            cout<<"Gerada chave publica, verifique em chavep.txt"<<endl;
        }else if(escolha == 2){//encriptar
            cout<<"Digite a mensagem a encriptar: ";
            cin.ignore();
            getline(cin,mensagem);
            cout<<"Digite a chave publica, dada anteriormente(os dois valores): ";
            cin>>chaven>>chavee;
            encriptar();
            ofstream out("msgencriptada.txt");
            out<<"Mensagem Encriptada: "<<mensageme;
            out.close();
            cout<<"Gerada a mensagem encriptada, verifique em msgencripatada.txt"<<endl;
        }else if(escolha == 3){ //desencriptar
            cout<<"Digite um Primo:";
            cin>>p;
            cout<<"Digite outro Primo:";
            cin>>q;
            cout<<"Digite o expoente>";
            cin>>e;
            desencriptar();
            ofstream out("msgdesencriptada.txt");
            out<<"Mensagem Desencriptada: "<<mensagemd;
            out.close();
            cout<<"Gerada a mensagem desencriptada, verifique em msgdesencripatada.txt"<<endl;
            cout<<"goodbye!";
            return 0;
        }else{ 
            cout<<"Digite um valor entre 1 e 3\n";
        }
    }
    return 0;
}
