//Converts an infix expression to a postfix expression.

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

template <class typ>

class Stos
{
    typ *elementy; //miejsce na znaki i elementy
    int ile; //do zapamiętania ile jest tych elementów
    
    public: Stos()
    {
        elementy = NULL;
        ile = 0;
    }
    
    Stos(int a)
    {
        elementy = new typ[ile];
        ile = a;
    }
    
    ~Stos()
    {
        delete [] elementy;
        cout << "zwalniam obiekt" << endl;
    }
    
    void put(char a) //funkcja dodajaca element i zwrocenie go ze szczytu stosu
    {
        typ *ntab = new typ[ile + 1];
        for (int i = 0; i<ile; i++)
        {
            ntab[i]=elementy[i]; //przepisanie elementow ze starej do nowej tablicy
        };
        ntab[ile] = a;//wstawimy nasz nowy element na pozycje ile
        ile = ile + 1; //zwiekszamy rozmiar bo dotychczas tylko wydluzylismy stos
        //brakuje nam jeszcze przepisania, ze stara tablica ma teraz wskazywac na nowa dluzsza tablice i stara tablice usunac
        delete [] elementy; //najpierw musimy wyczyszczic pamiec zaalokowana na elementy a potem na 
        elementy = ntab;
    }
    
    char get()//funkcja zwracajca element ze stosu
    {
        //zdejmuje ze stosu i zmniejsza rozmiar
        typ wynik = elementy[ile-1]; //ostatni znak z obecnej tablicy pobieramy i go potem zwrócimy
        typ *ntab = new typ[ile - 1]; //stworzenie tablicy o jeden mniejszej niz stos
        for (int i = 0; i<ile-1; i++) //przepisujemy elementy do elementu przedostatniego
        {
            ntab[i]=elementy[i];
        };
        
        ile=ile - 1;
        delete [] elementy;
        elementy = ntab;
        return wynik; //zwrócenie wyniku
    }
    
    char top() //funkcja zwaracająca wierzchołek stosu
    {
        return elementy[ile-1];
    }
    
    bool empty()
    {
        if (ile == 0) {return true;}
        else
        {
            return false;
        }
    }
    
    int size()
    {
        return ile;
    }
    
    void show()
    {
        cout<<"#";
        for(int i=0;i<ile;i++)
        {
            cout<<" "<< elementy[i]<<",";
        }
        cout<<endl;
    }
};

//Function to return precedence of operators
int prec(char c) {
    if(c == '^')
        return 3;
    else if(c == '/' || c=='*')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

int czyliczba(char a)
{
    if (a == '0'||a=='1'||a=='2'||a=='3'||a=='4'||a=='5'||a=='6'||a=='7'||a=='8'||a=='9')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string infixToPostfix(string intext)
{
    Stos<char> *wskStos = new Stos<char>(0);
    string outtext = "";
    for (int i = 0; i < intext.length(); i++)
    {
        char c = intext[i];
        if (c != ' ')
        {
            if(czyliczba(c) == 1 && czyliczba(intext[i+1]) == 0)
            {
                outtext = outtext + c;
            }
            if (czyliczba(c) == 1 && czyliczba(intext[i+1]) == 1 && czyliczba(intext[i+2]) == 0)
            {
                outtext = outtext + c + intext[i+1];
                i = i + 2;
            }
            if (czyliczba(c) == 1 && czyliczba(intext[i+1]) == 1 && czyliczba(intext[i+2]) == 1)
            {
                outtext = outtext + c + intext[i+1] + intext[i+2];
                i = i + 3;
            }
            if(c == '(')
            {
                wskStos -> put(c);
            }
            if(c == ')') 
            {
			    while(wskStos -> top() != '(')
			    {
			    	outtext += wskStos -> top();
		    		wskStos -> get();
		    	}
		    	wskStos -> get();
	    	}
	    	if (c =='+'||c == '^'||c == '/' || c=='*'||c == '+' || c == '-') 
	    	{
			    while(!wskStos -> empty() && prec(intext[i]) <= prec(wskStos -> top())) 
			    {
			    	outtext += wskStos -> top();
			    	wskStos -> get();
			    }
			    wskStos -> put(c);
		    }
        }
        if (c == ' ')
        {
            outtext =outtext + ' ';
        }
    }
    
    // Pop all the remaining elements from the stack
	while(!wskStos -> empty()) {
		outtext += wskStos -> top();
		wskStos -> get();
	}
    
    string outtext2 = "";
    int i = 0;
    
    while (i<outtext.length())
    {
        cout << outtext[i]<< endl;
        if (czyliczba(outtext[i]) == 1 && (outtext[i+1] == '+' || outtext[i+1] == '-' || outtext[i+1] == '*' || outtext[i+1] == '/' || outtext[i+1] == '^'))
        {
            outtext2 = outtext2 + outtext[i] + ' ';
            i = i + 1;
        }
        else if ((outtext[i] == '+' || outtext[i] == '-' || outtext[i] == '*' || outtext[i] == '/' || outtext[i] == '^') && (outtext[i+1] == '+' || outtext[i+1] == '-' || outtext[i+1] == '*' || outtext[i+1] == '/' || outtext[i+1] == '^'))
        {
            outtext2 = outtext2 + outtext[i] + ' ';
            i = i + 1;
        }
        else if (outtext[i] == ' ' && outtext[i+1] == ' ' && outtext[i+2] == ' ')
        {
            outtext2 = outtext2 + outtext[i];
            i = i + 3;
        }
        else if (outtext[i] == ' ' && outtext[i+1] == ' ' && outtext[i+2] != ' ')
        {
            outtext2 = outtext2 + outtext[i];
            i = i + 2;
        }
        else if(i == 0 && outtext[i] == ' ')
        {
            outtext2 == outtext2;
            i = i + 1;
        }
        else
        {
            outtext2 = outtext2 + outtext[i];
            i = i + 1;
        }
        /*
        if (outtext[i] != ' ')
        {
            cout << "Bramka1" <<endl;
            outtext2 = outtext2 + outtext[i];
            i = i + 1;
        }
        if (outtext[i] == ' ' && outtext[i+1] == ' ')
        {
            cout << "Bramka2" <<endl;
            outtext2 = outtext2 + outtext[i];
            i = i + 2;
        }
        if (outtext[i] == ' ' && outtext[i+1] == ' ' && outtext[i+2] == ' ')
        {
            cout << "Bramka3" <<endl;
            outtext2 = outtext2 + outtext[i];
            i = i + 3;
        }
        if (outtext[i] == ' ' && outtext[i+1] != ' ')
        {
            cout << "Bramka4" <<endl;
            outtext2 = outtext2 + outtext[i];
            i = i + 1;
        }
        if (czyliczba(outtext[i]) == 1 && (outtext[i+1] == '+' || outtext[i+1] == '-' || outtext[i+1] == '*' || outtext[i+1] == '/' || outtext[i+1] == '^'))
        {
            cout << "Bramka5" <<endl;
            outtext2 = outtext2 + outtext[i] + ' ';
            i = i + 1;
        }
        if ((outtext[i] == '+' || outtext[i] == '-' || outtext[i] == '*' || outtext[i] == '/' || outtext[i] == '^') && (outtext[i+1] == '+' || outtext[i+1] == '-' || outtext[i+1] == '*' || outtext[i+1] == '/' || outtext[i+1] == '^'))
        {
            cout << "Bramka6" <<endl;
            outtext2 = outtext2 + outtext[i] + ' ';
            i = i + 1;
        }
        */
    }
    
    cout << "outtext:"<< outtext << endl;
    cout << "outtext2:"<< outtext2 << endl;
    return outtext;
}

int main() {
    
    //infixToPostfix("2 + 2 + 2 * 2 / 2");
    string exp2 = infixToPostfix("-2 * 2 - 3 * 4 + 2 - 3 * 3");
    //RPNcalcualtion(exp2);
}
