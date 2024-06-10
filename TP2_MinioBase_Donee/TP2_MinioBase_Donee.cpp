
// Projet2-Algo.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

/*I - CRÉATION DES STRUCTURE DE STOCKAGE*/
//1-	Créez le type T_CLIENT permettant de stocker les informations d’un client

typedef struct T_DATE {
	int jour;
	int mois;
	int annee;
};

typedef struct T_CLIENT {
	int numeroClt;
	string nomClt;
	string prenomClt;
	char genreClt;//F=Femme, H=Homme
	string adresseClt;
	T_DATE dnClt;
	int nbEnfantClt;
	int volumeAchats;
};

//2 - créez le type T_PRODUIT permettant de stocker les informations d’un produit
//3-	Modifier l’un des types précédents pour prendre en considération le fait qu’un client a acheté un produit.
typedef struct T_PRODUIT {
	int refPdt;
	string desPdt;
	double puPdt;
	int numeroClt;//Numero du client qui a acheter ce produit
};

//4-	créez un type tableau TAB_CLIENTS permettant de stocker les informations de tous les clients de l’entreprise. On utilisera une constante MAXCLIENT qui représentera le nombre maximum des clients.
int const MAXCLT = 10;
typedef T_CLIENT TAB_CLIENTS[MAXCLT];

//5 - créez le type tableau TAB_PRODUITS permettant de stocker les informations de tous les produits achetés ou non de l’entreprise.On supposera que leur nombre ne peut pas dépasse MAXPRODUIT.
int const MAXPDT = 10;
typedef T_PRODUIT TAB_PRODUITS[MAXPDT];

//6-	Créez un type T_BDD qui permettra de stocker toutes les informations de la base de données, on veillera à créer un compteur permettant de connaitre le nombre de clients actuellement stocké dans le tableau, ainsi qu’un compteur des produit actuellement dans le tableau.
typedef struct T_BDD {
	TAB_CLIENTS client;
	TAB_PRODUITS produit;
	int nbClt = 0;
	int nbPdt = 0;
};

//Créons enfin une base de données
T_BDD bdd;


void initBdd(T_BDD& pBdd) {
	pBdd.client[0] = { 1111, "Rivard", "Claudine", 'F', "3615 rue des crevettes", 27, 12, 1975, 0 };
	pBdd.client[1] = { 2222, "Leguy", "Yann", 'M', "3616 rue des crevettes", 28, 11, 1976, 1 };
	pBdd.client[2] = { 3333, "William", "Papson", 'M', "3617 rue des crevettes", 29, 10, 1977, 2 };
	pBdd.client[3] = { 4444, "Rayan", "Nord", 'M', "3618 rue des crevettes", 11, 9, 1978, 3 };
	pBdd.client[4] = { 5555, "Nathan", "Dubois", 'M', "3619 rue des crevettes", 27, 8, 1979, 4 };
	pBdd.client[5] = { 1111, "Rivard", "Claudine", 'F', "3615 rue des crevettes", 27, 12, 1975, 0 };
	pBdd.nbClt = 5;

	pBdd.produit[0] = { 9001, "CLAVIER", 25,0 };
	pBdd.produit[1] = { 9002, "SOURIS", 10,0 };
	pBdd.produit[2] = { 9003, "ORDINATEUR", 1200,0 };
	pBdd.produit[3] = { 9004, "ORDINATEUR", 850,0 };
	pBdd.produit[4] = { 9005, "WINDOWS 10", 1000,0 };
	pBdd.produit[5] = { 9006, "ECRAN", 250, 0 };
	pBdd.produit[6] = { 9007, "TELEPHONE", 180,0 };
	pBdd.nbPdt = 7;

	pBdd.produit[0].numeroClt = 1111;
	pBdd.produit[1].numeroClt = 2222;
	pBdd.produit[3].numeroClt = 4444;
	pBdd.produit[4].numeroClt = 4444;
	pBdd.produit[5].numeroClt = 5555;

}
//7 Ajouter client
void ajouterClient(T_BDD& pBdd, int numeroClt, string nomClt, string prenomClt, char genreClt, string adresseClt, int jour, int mois, int annee, int nbEnfantClt) {


	if (pBdd.nbClt < MAXCLT) { // Vérifier si la capacité maximale n'est pas atteinte
		// Ajouter le client à la base de données
		pBdd.client[pBdd.nbClt] = { numeroClt, nomClt, prenomClt, genreClt, adresseClt, {jour, mois, annee}, nbEnfantClt };
		// Incrémenter le nombre de clients dans la base de données
		pBdd.nbClt++;
		cout << "Client ajoute avec succes!" << endl;
	}
	else {
		cout << "La capacite maximale de clients est atteinte. Impossible d'ajouter un nouveau client." << endl;
	}
}
//8 - Ajouter produit
void ajouterProduit(T_BDD& pBdd, int refPdt, string desPdt, double puPdt, int numeroClt) {
	if (pBdd.nbPdt < MAXPDT) { // Vérifier si la capacité maximale n'est pas atteinte
		// Ajouter le produit à la base de données
		pBdd.produit[pBdd.nbPdt] = { refPdt, desPdt, puPdt, numeroClt };
		// Incrémenter le nombre de produits dans la base de données
		pBdd.nbPdt++;
		cout << "Produit ajoute avec succes!" << endl;
	}
	else {
		cout << "La capacite maximale de produits est atteinte. Impossible d'ajouter un nouveau produit." << endl;
	}
}
//9 - Donner la procédure acheter qui prend en paramètre le numéro d’un client et le numéro d’un produit et met à jour le fait que ce client a acheté ce produit

void acheter(T_BDD& bdd) {
	int numeroClt, numeroPdt;

	cout << "Entrez le numero du client: ";
	cin >> numeroClt;

	cout << "Entrez le numero du produit: ";
	cin >> numeroPdt;


	// Vérifie si le client et le produit existent dans la base de données
	bool clientTrouve = false;
	bool produitTrouve = false;
	int indiceClient = -1;
	int indiceProduit = -1;

	// Recherche du client dans la base de données
	for (int i = 0; i < bdd.nbClt; i++) {
		if (bdd.client[i].numeroClt == numeroClt) {
			clientTrouve = true;
			indiceClient = i;
			break;
		}
	}

	// Recherche du produit dans la base de données
	for (int i = 0; i < bdd.nbPdt; i++) {
		if (bdd.produit[i].refPdt == numeroPdt) {
			produitTrouve = true;
			indiceProduit = i;
			break;
		}
	}

	// Si le client et le produit sont trouvés, met à jour les informations dans la base de données
	if (clientTrouve && produitTrouve) {
		bdd.produit[indiceProduit].numeroClt = numeroClt;

	}
	else {
		cout << "Client ou produit non trouve dans la base de donnees." << endl;
	}
}


//11- procedure achat client
void afficherProduit(T_PRODUIT pProduit) {
	cout << "\n " << setw(12) << left << pProduit.refPdt;
	cout << "| " << setw(12) << left << pProduit.desPdt;
	cout << "| " << setw(12) << left << pProduit.puPdt;
}

//12 - écrire la procédure afficheClient qui prend en paramètre le numéro d’un client et la base de données puis affiche les informations de ce client.

void afficherClient(T_CLIENT pClient) {
	cout << "\n" << setw(12) << left << pClient.numeroClt;
	cout << "| " << setw(12) << left << pClient.nomClt;
	cout << "| " << setw(12) << left << pClient.prenomClt;
	cout << "| " << setw(6) << left << pClient.genreClt;
	cout << "| " << setw(20) << left << pClient.adresseClt;
	cout << "| " << setw(2) << pClient.dnClt.jour << "/" << setw(3) << left << pClient.dnClt.mois << "/" << setw(2) << left << pClient.dnClt.annee;
	cout << "| " << setw(10) << left << pClient.nbEnfantClt;
}
void afficherClients(T_BDD pBdd) {
	cout << "Liste des clients :\n";
	cout << "\n" << setw(12) << left << "Numero";
	cout << "| " << setw(12) << left << "Nom";
	cout << "| " << setw(12) << left << "Prenom";
	cout << "| " << setw(6) << left << "Genre";
	cout << "| " << setw(22) << left << "Adresse";
	cout << "| " << setw(8) << left << "Date Naiss";
	cout << "| " << setw(10) << left << "Nb Enfants";

	cout << "\n" << setw(56) << setfill('.') << left << "" << setfill(' ');
	for (int i = 0; i < pBdd.nbClt; i++) {
		afficherClient(pBdd.client[i]);
	}
}

//13 - 	écrire la procédure depenseClient qui prend en paramètre le numéro d’un client et la base de données puis affiche le montant total dépensé par ce client

void depenseClient(T_BDD& bdd) {
	int numeroClt;
	double totalDepense = 0;

	cout << "Entrez le numero du client: ";
	cin >> numeroClt;


	// Parcours tous les produits pour calculer la dépense totale du client
	for (int i = 0; i < bdd.nbPdt; i++) {
		if (bdd.produit[i].numeroClt == numeroClt) {
			totalDepense += bdd.produit[i].puPdt;
		}
	}

	// Affiche le montant total dépensé par le client
	cout << "\nLe client " << numeroClt << " a depense un total de " << totalDepense << " dollars." << endl;
}

//14 - écrire la procédure infoClientProduit qui prend en paramètre le numéro d’un produit et la base de données puis affiche toutes les informations du client qui a acheté ce produit.

void infoClientProduit(T_BDD& bdd) {
	int numeroPdt;
	cout << "Entrez le numero du produit : ";
	cin >> numeroPdt;

	bool produitTrouve = false;

	// Parcourt tous les produits dans la base de données
	for (int i = 0; i < bdd.nbPdt; i++) {
		// Vérifie si le numéro de produit correspond au numéro passé en paramètre
		if (bdd.produit[i].refPdt == numeroPdt) {
			produitTrouve = true;
			int numeroClt = bdd.produit[i].numeroClt;

			// Recherche le client associé au produit dans la base de données
			for (int j = 0; j < bdd.nbClt; j++) {
				if (bdd.client[j].numeroClt == numeroClt) {
					// Si le client est trouvé, affiche ses informations
					cout << "Nom du Produit : " << bdd.produit[i].desPdt << endl << endl;
					cout << "Informations du Client qui a achete le produit :\n";
					cout << "Numero du Client : " << bdd.client[j].numeroClt << endl;
					cout << "Nom : " << bdd.client[j].nomClt << endl;
					cout << "Prenom : " << bdd.client[j].prenomClt << endl;
					cout << "Genre : " << bdd.client[j].genreClt << endl;
					cout << "Adresse : " << bdd.client[j].adresseClt << endl;
					cout << "Date de Naissance : " << bdd.client[j].dnClt.jour << "/" << bdd.client[j].dnClt.mois << "/" << bdd.client[j].dnClt.annee << endl;
					cout << "Nombre d'Enfants : " << bdd.client[j].nbEnfantClt << endl;
					cout << "-----------------------------------\n";
					break;  // Sort du boucle dès que le client est trouvé
				}
			}
		}
	}

	// Si le produit n'est pas trouvé dans la base de données
	if (!produitTrouve) {
		cout << "Produit non trouve dans la base de donnees.\n";
	}
}

// 15-	écrire la procédure listeClient qui affiche la liste de tous les clients par ordre alphabétique

// Fonction pour comparer deux clients pour un tri alphabétique par nom
bool compararClientes(const T_CLIENT& cliente1, const T_CLIENT& cliente2) {
	return cliente1.nomClt < cliente2.nomClt;
}

// Fonction pour afficher la liste de tous les clients par ordre alphabétique
void listeClient(T_BDD& bdd) {
	// Trie les clients par ordre alphabétique par nom
	sort(bdd.client, bdd.client + bdd.nbClt, compararClientes);

	cout << "Liste de tous les clients par ordre alphabetique :\n";
	cout << "\n" << setw(12) << left << "Numero";
	cout << "| " << setw(12) << left << "Nom";
	cout << "| " << setw(12) << left << "Prenom";
	cout << "| " << setw(6) << left << "Genre";
	cout << "| " << setw(22) << left << "Adresse";
	cout << "| " << setw(8) << left << "Date Naiss";
	cout << "| " << setw(10) << left << "Nb Enfants";

	cout << "\n" << setw(56) << setfill('.') << left << "" << setfill(' ');
	// Affiche les clients triés
	for (int i = 0; i < bdd.nbClt; i++) {
		afficherClient(bdd.client[i]);
	}
}

//16-	écrire la procédure listeClient qui affiche la liste de tous les clients par ordre du chiffre d’affaire effectué

 
//17-	Ecrire la procédure  qui affiche la liste de tous les produits dont le prix est inférieur à un prix passé en paramètre

// Fonction pour afficher la liste de tous les produits dont le prix est inférieur à un prix passé en paramètre
void prixInferieur(T_BDD& bdd) {
	double prixMax;
	cout << "Entrez le prix maximum : ";
	cin >> prixMax;

	cout << "Liste de tous les produits dont le prix est inferieur a " << prixMax << " :\n";
	cout << "\n" << setw(12) << left << "Reference";
	cout << "| " << setw(12) << left << "Nom";
	cout << "| " << setw(12) << left << "Pu";

	cout << "\n" << setw(36) << setfill('.') << left << "" << setfill(' ');
	// Parcours tous les produits pour afficher ceux dont le prix est inférieur à prixMax
	for (int i = 0; i < bdd.nbPdt; i++) {
		if (bdd.produit[i].puPdt < prixMax) {
			afficherProduit(bdd.produit[i]);
		}
	}
}

// 18-	Écrire la procédure qui affiche la liste de tous les clients suivis des produits acheté




// 19- Écrire la procédure qui affiche la liste des clients classés par chiffre d’affaire et par genre

void affiCheClientDeGenre(T_BDD& bdd) {
	// Vecteurs pour stocker les clients masculins et féminins
	vector<T_CLIENT> masculins;
	vector<T_CLIENT> feminins;

	// Calcule le volume d'achats de chaque client et les stocke dans les vecteurs appropriés
	for (int i = 0; i < bdd.nbClt; i++) {
		double volumeAchats = 0;
		for (int j = 0; j < bdd.nbPdt; j++) {
			if (bdd.produit[j].numeroClt == bdd.client[i].numeroClt) {
				volumeAchats += bdd.produit[j].puPdt;
			}
		}
		bdd.client[i].volumeAchats = volumeAchats; // Stocke le volume d'achats dans le client

		// Ajoute le client au vecteur selon le genre
		if (bdd.client[i].genreClt == 'M') {
			masculins.push_back(bdd.client[i]);
		}
		else {
			feminins.push_back(bdd.client[i]);
		}
	}

	// Trie les vecteurs par volume d'achats (du plus grand au plus petit)
	sort(masculins.begin(), masculins.end(), [](const T_CLIENT& a, const T_CLIENT& b) {
		return a.volumeAchats > b.volumeAchats;
		});
	sort(feminins.begin(), feminins.end(), [](const T_CLIENT& a, const T_CLIENT& b) {
		return a.volumeAchats > b.volumeAchats;
		});

	// Affiche la liste des clients masculins
	cout << "Clients masculins :\n";
	for (const auto& client : masculins) {
		afficherClient(client);
		cout << "Volume d'achats : " << client.volumeAchats << " $" << endl;
		cout << "-----------------------------------\n";
	}

	// Affiche la liste des clients féminins
	cout << "\nClients feminins :\n";
	for (const auto& client : feminins) {
		afficherClient(client);
		cout << "Volume d'achats : " << client.volumeAchats << " $" << endl;
		cout << "-----------------------------------\n";
	}
}



//20- écrire une procédure qui affiche la liste des clients de sexe féminin, nées avant 1978 ayant fait au moins un achat

void femAvant1978(T_BDD& bdd) {
	cout << "Liste des clientes feminins nees avant 1978 ayant effectue au moins un achat :" << endl;
	cout << "-------------------------------------------------------------------------" << endl;

	bool clientsTrouves = false;

	for (int i = 0; i < bdd.nbClt; i++) {
		if (bdd.client[i].genreClt == 'F' && bdd.client[i].dnClt.annee < 2100) {
			bool aAchete = false;
			// Vérifie si le client a effectué au moins un achat
			for (int j = 0; j < bdd.nbPdt; j++) {
				if (bdd.produit[j].numeroClt == bdd.client[i].numeroClt) {
					aAchete = true;
					break;
				}
			}
			// Affiche les informations du client s'il a effectué au moins un achat
			if (aAchete) {
				clientsTrouves = true;
				cout << "Nom: " << bdd.client[i].nomClt << ", Prenom: " << bdd.client[i].prenomClt << ", Date de naissance: " << bdd.client[i].dnClt.jour << "/" << bdd.client[i].dnClt.mois << "/" << bdd.client[i].dnClt.annee << endl;
			}
		}
	}

	if (!clientsTrouves) {
		cout << "Aucune cliente ne correspond aux criteres specifies." << endl;
	}
}


void achatClient(T_BDD pBdd) {
	int pNumeroClt;
	cout << "Entre le numero de client: ";
	cin >> pNumeroClt;
	cout << "\nListe de produits achete' par le client Numero: " << pNumeroClt << "\n";
	cout << "\n " << setw(12) << left << "Reference";
	cout << "| " << setw(12) << left << "Nom";
	cout << "| " << setw(12) << left << "Pu";

	cout << "\n" << setw(36) << setfill('.') << left << "" << setfill(' ');
	for (int i = 0; i < pBdd.nbPdt; i++) {
		if (pBdd.produit[i].numeroClt == pNumeroClt) afficherProduit(pBdd.produit[i]);
	}
}

//Fonction main
int main()
{
	int numeroClt = 0;
	string nomClt, prenomClt, adresseClt;
	char genreClt;
	int jour, mois, annee, nbEnfantClt;

	T_BDD pBdd;
	int refPdt;
	string desPdt;
	double puPdt;


	int option;
	initBdd(bdd);
	cout << "\n";
	//char car = _getch();

	cout << "\n\nTP 2 - ALGORITHMIQUE\n";

	do {
		cout << "\nBase Donnee Algorithmique.";
		cout << "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n";
		cout << "Menu des Options:" << endl;
		cout << "7. Ajouter client." << endl;
		cout << "8. Ajouter produit." << endl;
		cout << "9. Acheter Produit." << endl;
		cout << "11. Achat Client." << endl;
		cout << "12. Affiche client." << endl;
		cout << "13. Depense client." << endl;
		cout << "14. Info Client Produit." << endl;
		cout << "15. Liste Client ordre alphabetique." << endl;
		cout << "16. " << endl;
		cout << "17. Prix Inferieur." << endl;
		cout << "18. " << endl;
		cout << "19. Comparer les Chiffres et Affaires." << endl;
		cout << "20. Afficher Femme < 1978." << endl;
		cout << "0. Quitter." << endl;

		cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-";

		cout << "\nEntrez le numero de l'option souhaitee: ";
		cin >> option;
		cout << "\n";

		system("cls");

		switch (option) {

		case 7:


			cout << "Entrez le numero du client: ";
			cin >> numeroClt;
			cout << "Entrez le prenomClt du client: ";
			cin >> prenomClt;
			cout << "Entrez le nom du client: ";
			cin >> nomClt;
			cout << "Entrez le genre du client: ";
			cin >> genreClt;
			cout << "Entrez le adress du client: ";
			getline(cin, adresseClt);
			getline(cin, adresseClt);
			cout << "Entrez le anniversaire du client: ";
			cin >> jour >> mois >> annee;
			cout << "Entrez le nombre d'enfant du client: ";
			cin >> nbEnfantClt;

			ajouterClient(bdd, numeroClt, nomClt, prenomClt, genreClt, adresseClt, jour, mois, annee, nbEnfantClt);

			break;
		case 8:
			cout << "Entrez le numero du produit: ";
			cin >> refPdt;

			cout << "Entrez la description du produit: ";
			getline(cin, desPdt);
			getline(cin, desPdt);

			cout << "Entrez le prix du produit: ";
			cin >> puPdt;


			ajouterProduit(pBdd, refPdt, desPdt, puPdt, numeroClt);
			break;
		case 9:
			acheter(bdd); // Le client (numero) a acheté le produit 9003

			break;
		case 11:
			achatClient(bdd);
			break;
		case 12:
			afficherClients(bdd);
			break;

		case 13:
			depenseClient(bdd); // Affiche le montant total dépensé par le client 
			break;

		case 14:
			infoClientProduit(bdd);
			break;

		case 15:
			listeClient(bdd);
			break;

		case 16:
			break;

		case 17:
			prixInferieur(bdd);
			break;

		case18:
			
			break;

		case 19:
			affiCheClientDeGenre(bdd);
			break;

		case 20:
			femAvant1978(bdd);
			break;

		case 0:
			cout << "\nQuitter le programme\n";
			cout << "\nMerci pour utiliser notre programme\n\n";

			cout << "Devs responsables: Mouhamed Aziz, Alexei Zubakin, Marcus Santos\n\n";
			break;


		}

	} while (option != 0);
}
