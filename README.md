# cpp09

Ex00 : map (ou multimap)

Ex01 : stack

Ex02 : list / vector

# Utilisation des stream

```cpp
#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>

int main()
{
	//TEST 1
	std::ostream_iterator<double> it(std::cout, "\n");

	*it = 3.14;
	*it = 2.71828;

	//TEST 2
	std::ifstream fichier("data.csv");

	std::istream_iterator<std::string> jt(fichier);
	std::istream_iterator<std::string> end;

	int h = 0;
	while (jt != end)
	{
		std::cout << *jt << std::endl;
		++jt;
		h++;
	}

	std::cout << h << std::endl;

	return 0;
}
```

TEST 1 : ?????

TEST 2 : 

1. Instanciation d’un objet ifstream
2. Instanciation de l’iterateur de début
3. Instanciation de l’iterateur de fin
4. Boucle pour parcourir l’objet ifstream

## back_insert_iterator

Le back_insert_iterator fonctionne comme un iterator à la difference que son déréferencement ajoute un élément au vecteur alors qu’un iterateur habituel modifie une case déjà créée.

```cpp
#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <vector>

class Display
{
	public :
		template <typename T>
		void operator()(T & a)
		{
			std::cout << a << " ";
		}
};

int main()
{
	std::vector<std::string> tab;

	std::ifstream file("data.csv");
	std::istream_iterator<std::string> it(file);
	std::istream_iterator<std::string> end;
	std::back_insert_iterator<std::vector<std::string> > it2(tab);

	copy(it, end, it2);

	for_each(tab.begin(), tab.end(), Display());

	return 0;
}
```

## ostringstream

Objet permettant de créer un flux sortant. On peut ajouter à ce flux un contenu à l’aide de l’opérateur <<

```cpp
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

int main()
{
	std::ostringstream flux;

	flux << "Hello ";
	flux << 18.42;
	flux << " !";

	std::string const chaine = flux.str();

	std::cout << chaine << std::endl;

	return 0;
}
```

## istringstream

Objet permettant de créer un flux entrant. L’opérateur >> permet de passer le contenu du lux à une variable.

```cpp
std::istringstream str_f(date);

	std::cout << str_f << std::endl;

	int n;

	while (str_f )
	{
		str_f >> n;

		if (str_f)
		{
			std::cout << "sucess " << n <<std::endl;
		}
		else
		{
			std::cout << "No sucess" <<std::endl;
		}
	}
```

L'objet std::istringstream peut également être utilisé comme un booléen pour déterminer si la dernière opération d'extraction a échoué. Cela se produit s'il n'y a plus de chaîne dans le flux. Par exemple, si le flux contient encore des caractères, nous pouvons à nouveau extraire la chaîne. L'opérateur d'extraction >> écrit le flux dans la variable à droite de l'opérateur et renvoie l'objet std::istringstream. Ainsi, l'expression complète my_stream >> n est un objet std::istringstream qui renvoie un booléen, c'est-à-dire true si le flux est possible, sinon false.

# Structure tm

Il faut importer <ctime> pour l’utiliser. Elles est aussi disponible en C dans “time.h”.

```cpp
#include <iostream>
#include <ctime>

int main()
{
	time_t now = time(0);

	std::cout << now << std::endl;

	std::string dt = ctime(&now);

	std::cout << dt << std::endl;

	tm *gmtm = gmtime(&now);

	dt = asctime(gmtm);

	std::cout << dt << std::endl;

	return 0;
}
```

# Algorithme de Ford-Johnson

## Tri par fusion = Merge sort

![Merge-sort-example-300px.gif](cpp09%20ddce651aba91441cbdde2065251060a7/Merge-sort-example-300px.gif)

## Tri par insertion = Insertion sort

![Insertion-sort-example-300px.gif](cpp09%20ddce651aba91441cbdde2065251060a7/Insertion-sort-example-300px.gif)

[https://www.youtube.com/watch?v=w1QXGe295sI](https://www.youtube.com/watch?v=w1QXGe295sI)

# ex00

Attention ce code ne fonctionne pas !

```cpp
MultimapInput mp_in("input.txt");

std::multimap<std::string, float>::iterator itr2;

for (itr2 = mp_in.get_mp_input().begin(); itr2 != mp_in.get_mp_input().end(); ++itr2)
{
    std::cout << itr2->first << " => " << itr2->second << std::endl;
}
```

Cela fait une segmentation fault au run time car chaque fois que l’on appelle get_mp_input, on obtient une nouvelle copie !!!!

# ex01

Comment lire une stack efficacement :

```cpp
// C++ program for the above approach
#include <bits/stdc++.h>
using namespace std;

// Function to print stack elements
// from top to bottom with the
// order of elements unaltered
void PrintStack(stack<int> s)
{
	// If stack is empty
	if (s.empty())
		return;

// Extract top of the stack
	int x = s.top();

	// Pop the top element
	s.pop();

	// Print the current top
	// of the stack i.e., x
	cout << x << ' ';

	// Proceed to print
// remaining stack
	PrintStack(s);

	// Push the element back
	s.push(x);
}

// Driver Code
int main()
{
	stack<int> s;

	// Given stack s
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);

	// Function Call
	PrintStack(s);

	return 0;
}
```

Extrait de la table ASCII :

| Caractère | Valeur en décimal |
| --- | --- |
| + | 42 |
| - | 47 |
| / | 45 |
| * | 43 |

# Sources

[https://github.com/decidedlyso/merge-insertion-sort/blob/master/README.md](https://github.com/decidedlyso/merge-insertion-sort/blob/master/README.md)

[Comma-separated values](https://en.wikipedia.org/wiki/Comma-separated_values)

[How to use std::getline() in C++?  | DigitalOcean](https://www.digitalocean.com/community/tutorials/getline-in-c-plus-plus)

[Processing strings using std::istringstream - GeeksforGeeks](https://www.geeksforgeeks.org/processing-strings-using-stdistringstream/)

[Tri fusion](https://fr.wikipedia.org/wiki/Tri_fusion)

[Insertion sort](https://en.wikipedia.org/wiki/Insertion_sort)

[Suite de Jacobsthal](https://fr.wikipedia.org/wiki/Suite_de_Jacobsthal)

[Binary search algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)

[Merge-insertion sort](https://en.wikipedia.org/wiki/Merge-insertion_sort)

[](https://seriouscomputerist.atariverse.com/media/pdf/book/Art%20of%20Computer%20Programming%20-%20Volume%203%20(Sorting%20&%20Searching).pdf)

[Using C++ containers efficiently](https://blog.quasar.ai/using-c-containers-efficiently)