
/* HlaviÄkovĂ˝ soubor pro c016.h - Tabulka s RozptĂ˝lenĂ˝mi PoloĹžkami,
**  obsahuje jednak nutnĂŠ includes a externovanĂŠ promÄnnĂŠ,
**  ale rovneĹž definici datovĂ˝ch typĹŻ. Tento soubor neupravujte!
**  TĂŠma:  Tabulka s explicitnÄ zĹetÄzenĂ˝mi synonymy
**                      PrvnĂ­ implementace: Petr PĹikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      Ăpravy: Karel MasaĹĂ­k, ĹĂ­jen 2013
**                      Ăpravy: Radek HranickĂ˝, ĹĂ­jen 2014
**
***/


#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>

extern int solved;			/* externi promenna pouzivana v testeru */

/* MaximĂĄlnĂ­ velikost pole pro implementaci
   vyhledĂĄvacĂ­ tabulky. ĹeĹĄenĂŠ procedury vĹĄak
   vyuĹžĂ­vajĂ­ pouze HTSIZE prvkĹŻ pole (viz deklarace tĂŠto promÄnnĂŠ).
*/
#define MAX_HTSIZE 101

/* typ klĂ­Äe (napĹĂ­klad identifikace zboĹžĂ­) */
typedef char* tKey;

/* typ obsahu (napĹĂ­klad cena zboĹžĂ­) */
typedef float tData;

/*DatovĂĄ poloĹžka TRP s explicitnÄ ĹetÄzenĂ˝mi synonymy*/
 typedef struct tHTItem{
	tKey key;				/* klĂ­Ä  */
	tData data;				/* obsah */
	struct tHTItem* ptrnext;	/* ukazatel na dalĹĄĂ­ synonymum */
} tHTItem;

/* TRP s explicitnÄ zĹetÄzenĂ˝mi synonymy. */
typedef tHTItem* tHTable[MAX_HTSIZE];

/* Pro ĂşÄely testovĂĄnĂ­ je vhodnĂŠ mĂ­t moĹžnost volby velikosti pole,
   kterĂ˝m je vyhledĂĄvacĂ­ tabulka implementovĂĄna. Fyzicky je deklarovĂĄno
   pole o rozmÄru MAX_HTSIZE, ale pĹi implementaci vaĹĄich procedur uvaĹžujte
   velikost HTSIZE.  Ve skriptu se pĹed volĂĄnĂ­m ĹeĹĄenĂ˝ch procedur musĂ­
   objevit pĹĂ­kaz HTSIZE N, kde N je velikost poĹžadovanĂŠho prostoru.
   
   POZOR! Pro sprĂĄvnou funkci TRP musĂ­ bĂ˝t hodnota tĂŠto promÄnnĂŠ prvoÄĂ­slem.
*/
extern int HTSIZE;

/* HlaviÄky ĹeĹĄenĂ˝ch procedur a funkcĂ­. */

int hashCode ( tKey key );

void htInit ( tHTable* ptrht );

tHTItem* htSearch ( tHTable* ptrht, tKey key );

void htInsert ( tHTable* ptrht, tKey key, tData data );

tData* htRead ( tHTable* ptrht, tKey key );

void htDelete ( tHTable* ptrht, tKey key );

void htClearAll ( tHTable* ptrht );

#endif
