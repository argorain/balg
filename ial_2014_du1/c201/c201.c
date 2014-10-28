
/* c201.c *********************************************************************}
{* Téma: Jednosmìrný lineární seznam
**
**                     Návrh a referenèní implementace: Petr Pøikryl, øíjen 1994
**                                          Úpravy: Andrea Nìmcová listopad 1996
**                                                   Petr Pøikryl, listopad 1997
**                                Pøepracované zadání: Petr Pøikryl, bøezen 1998
**                                  Pøepis do jazyka C: Martin Tuèek, øíjen 2004
**	                                      Úpravy: Bohuslav Køena, øíjen 2014
**
** Implementujte abstraktní datový typ jednosmìrný lineární seznam.
** U¾iteèným obsahem prvku seznamu je celé èíslo typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou typu tList.
** Definici konstant a typù naleznete v hlavièkovém souboru c201.h.
** 
** Va¹ím úkolem je implementovat následující operace, které spolu s vý¹e
** uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ tList:
**
**      InitList ...... inicializace seznamu pøed prvním pou¾itím,
**      DisposeList ... zru¹ení v¹ech prvkù seznamu,
**      InsertFirst ... vlo¾ení prvku na zaèátek seznamu,
**      First ......... nastavení aktivity na první prvek,
**      CopyFirst ..... vrací hodnotu prvního prvku,
**      DeleteFirst ... zru¹í první prvek seznamu,
**      PostDelete .... ru¹í prvek za aktivním prvkem,
**      PostInsert .... vlo¾í nový prvek za aktivní prvek seznamu,
**      Copy .......... vrací hodnotu aktivního prvku,
**      Actualize ..... pøepí¹e obsah aktivního prvku novou hodnotou,
**      Succ .......... posune aktivitu na dal¹í prvek seznamu,
**      Active ........ zji¹»uje aktivitu seznamu.
**
** Pøi implementaci funkcí nevolejte ¾ádnou z funkcí implementovaných v rámci
** tohoto pøíkladu, není-li u dané funkce explicitnì uvedeno nìco jiného.
**
** Nemusíte o¹etøovat situaci, kdy místo legálního ukazatele na seznam 
** pøedá nìkdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodnì komentujte!
**
** Terminologická poznámka: Jazyk C nepou¾ívá pojem procedura.
** Proto zde pou¾íváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c201.h"

int solved;
int errflg;

void Error() {
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tato funkce bude volána z nìkterých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;                      /* globální promìnná -- pøíznak chyby */
}

void InitList (tList *L) {
/*
** Provede inicializaci seznamu L pøed jeho prvním pou¾itím (tzn. ¾ádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad ji¾ inicializovaným
** seznamem, a proto tuto mo¾nost neo¹etøujte. V¾dy pøedpokládejte,
** ¾e neinicializované promìnné mají nedefinovanou hodnotu.
**/
    L->Act= NULL;
    L->First = NULL;
}

void DisposeList (tList *L) {
/*
** Zru¹í v¹echny prvky seznamu L a uvede seznam L do stavu, v jakém se nacházel
** po inicializaci. Ve¹kerá pamì» pou¾ívaná prvky seznamu L bude korektnì
** uvolnìna voláním operace free.
***/
	tElemPtr first;
    L->Act=NULL;            //aktivní vynulujeme
    while(L->First!=NULL)   //ma¾eme, dokud je co
    {
        first=L->First;     //vezmeme první prvek
        L->First=L->First->ptr; //nastavíme nový první prvek jako starý následující
        free(first);        //starý první prvek uvolníme
    }
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void InsertFirst (tList *L, int val) {
/*
** Vlo¾í prvek s hodnotou val na zaèátek seznamu L.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci Error().
**/
    struct tElem *element;
    if ((element = malloc(sizeof(struct tElem)))!=NULL) //kontrola alokace
    {
        element->data = val;        //nastavíme data
        element->ptr = L->First;    //nastavíme ptr na starý první
        L->First=element;           //vlo¾íme do seznamu
    }
    else
    {
        Error();
    }
    //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void First (tList *L) {
/*
** Nastaví aktivitu seznamu L na jeho první prvek.
** Funkci implementujte jako jediný pøíkaz, ani¾ byste testovali,
** zda je seznam L prázdný.
**/
	
    L->Act=L->First;
// solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void CopyFirst (tList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci Error().
**/
	if(L->First==NULL)  //kontrola
        Error();
    else
        *val = L->First->data;  //vrácení dat

 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DeleteFirst (tList *L) {
/*
** Zru¹í první prvek seznamu L a uvolní jím pou¾ívanou pamì».
** Pokud byl ru¹ený prvek aktivní, aktivita seznamu se ztrácí.
** Pokud byl seznam L prázdný, nic se nedìje.
**/
	if(L->First==NULL)  //kontrola
        return;
    else
    {
        if(L->First==L->Act)        //pokud aktuální = první, aktuální se ztrácí
            L->Act=NULL;
        tElemPtr first = L->First;  //ptr na uvolnovany prvek
        L->First=L->First->ptr;     //pøesunutí nového prvního prvku
        free(first);                //a uvolnìní
    }

 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}	

void PostDelete (tList *L) {
/* 
** Zru¹í prvek seznamu L za aktivním prvkem a uvolní jím pou¾ívanou pamì».
** Pokud není seznam L aktivní nebo pokud je aktivní poslední prvek seznamu L,
** nic se nedìje.
**/
	if(L->Act==NULL || L->Act->ptr==NULL)   //kontrola prvosti a aktivnosti
        return;
    tElemPtr erase = L->Act->ptr;   //vezmeme prvek ke smazání
    L->Act->ptr=L->Act->ptr->ptr;   //pøepojíme seznam
    free(erase);                    //sma¾eme
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void PostInsert (tList *L, int val) {
/*
** Vlo¾í prvek s hodnotou val za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje!
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** zavolá funkci Error().
**/
	if(L->Act == NULL)  //kontrola aktivity
        return;
    struct tElem *newone;
    if((newone = malloc(sizeof(struct tElem)))!=NULL) //kontrola alokace
    {
        tElemPtr next = L->Act->ptr;    //ptr na následující prvek
        L->Act->ptr=newone;             //vlo¾ení nového prvku
        newone->ptr=next;               //navázání seznamu
        newone->data=val;               //a jeho data
    }
    else
    {
        Error();
        return;
    }
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void Copy (tList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam není aktivní, zavolá funkci Error().
**/
    if(L->Act==NULL)        //kontrola
        Error();
    else
        *val = L->Act->data;    //vzetí jeho dat
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void Actualize (tList *L, int val) {
/*
** Pøepí¹e data aktivního prvku seznamu L hodnotou val.
** Pokud seznam L není aktivní, nedìlá nic!
**/
    if(L->Act==NULL)        //kontrola
        Error();
    else
        L->Act->data=val;   //nastavení dat
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void Succ (tList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** V¹imnìte si, ¾e touto operací se mù¾e aktivní seznam stát neaktivním.
** Pokud seznam L není aktivní, nedìlá nic.
**/
	
	if(L->Act!=NULL)        //kontrola
        L->Act=L->Act->ptr; //pøesunutí ptr na dal¹í
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

int Active (tList *L) {		
/*
** Je-li seznam L aktivní, vrací TRUE. V opaèném pøípadì vrací FALSE.
** Tuto funkci implementujte jako jediný pøíkaz return. 
**/
	
	return L->Act != NULL;
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

/* Konec c201.c */
