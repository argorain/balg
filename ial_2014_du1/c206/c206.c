	
/* c206.c **********************************************************}
{* Téma: Dvousmìrnì vázaný lineární seznam
**
**                   Návrh a referenèní implementace: Bohuslav Køena, øíjen 2001
**                            Pøepracované do jazyka C: Martin Tuèek, øíjen 2004
**                                            Úpravy: Bohuslav Køena, øíjen 2014
**
** Implementujte abstraktní datový typ dvousmìrnì vázaný lineární seznam.
** U¾iteèným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován promìnnou
** typu tDLList (DL znamená Double-Linked a slou¾í pro odli¹ení
** jmen konstant, typù a funkcí od jmen u jednosmìrnì vázaného lineárního
** seznamu). Definici konstant a typù naleznete v hlavièkovém souboru c206.h.
**
** Va¹ím úkolem je implementovat následující operace, které spolu
** s vý¹e uvedenou datovou èástí abstrakce tvoøí abstraktní datový typ
** obousmìrnì vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu pøed prvním pou¾itím,
**      DLDisposeList ... zru¹ení v¹ech prvkù seznamu,
**      DLInsertFirst ... vlo¾ení prvku na zaèátek seznamu,
**      DLInsertLast .... vlo¾ení prvku na konec seznamu, 
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek, 
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku, 
**      DLDeleteFirst ... zru¹í první prvek seznamu,
**      DLDeleteLast .... zru¹í poslední prvek seznamu, 
**      DLPostDelete .... ru¹í prvek za aktivním prvkem,
**      DLPreDelete ..... ru¹í prvek pøed aktivním prvkem, 
**      DLPostInsert .... vlo¾í nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vlo¾í nový prvek pøed aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... pøepí¹e obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal¹í prvek seznamu,
**      DLPred .......... posune aktivitu na pøedchozí prvek seznamu, 
**      DLActive ........ zji¹»uje aktivitu seznamu.
**
** Pøi implementaci jednotlivých funkcí nevolejte ¾ádnou z funkcí
** implementovaných v rámci tohoto pøíkladu, není-li u funkce
** explicitnì uvedeno nìco jiného.
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

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornìní na to, ¾e do¹lo k chybì.
** Tato funkce bude volána z nìkterých dále implementovaných operací.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální promìnná -- pøíznak o¹etøení chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L pøed jeho prvním pou¾itím (tzn. ¾ádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádìt nad ji¾ inicializovaným
** seznamem, a proto tuto mo¾nost neo¹etøujte. V¾dy pøedpokládejte,
** ¾e neinicializované promìnné mají nedefinovanou hodnotu.
**/
    
	L->Act=NULL;
    L->First=NULL;
    L->Last=NULL;
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLDisposeList (tDLList *L) {
/*
** Zru¹í v¹echny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Ru¹ené prvky seznamu budou korektnì
** uvolnìny voláním operace free. 
**/
	tDLElemPtr elementPtr;
    L->Act=L->First;            //nastavíme aktuální prvek na první
	while(L->Act!=NULL)         //ma¾eme dokud je co
    {
        elementPtr = L->Act;    //ulo¾íme si ukazatel na aktuální
        L->Act=L->Act->rptr;    //posuneme se na dal¹í prvek
        free(elementPtr);       //a ulo¾ený prvek uvolníme
    }
    L->Last=NULL;               //na konci by mìlo být v¹echno null
    L->First=NULL;
    L->Act=NULL;
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vlo¾í nový prvek na zaèátek seznamu L.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
	struct tDLElem *element;
    if((element= malloc(sizeof(struct tDLElem)))==NULL) //pro pøípad, ¾e by selhala alokace pamìti
        DLError();
    else
    {
        element -> data = val;              //ulo¾íme do nového prvku data
        element -> rptr = L -> First;       //a taky pointer na souèasný první
        element -> lptr = NULL;             //vlevo od nìj nebude nic (je první)
        if(L -> First != NULL)              //jestli¾e je sám ve frontì, tak první a poslední je toté¾, jiank souèasný první (a za chvíli druhý) ukazuje na nový první prvek
            L -> First -> lptr = element;
        else
            L -> Last = L -> First = element;
        L -> First = element;               //vlo¾íme nový první do seznamu
    }
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vlo¾í nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    struct tDLElem *element;
    if((element= malloc(sizeof(struct tDLElem)))==NULL) //kontrola na chyby alokace
        DLError();
    else
    {
        element -> data = val;                  //ulo¾íme hodnotu
        element -> lptr = L -> Last;            //vlevo je souèasný poslední
        element -> rptr = NULL;                 //vpravo nic
        if(L -> Last != NULL)                   //kdy¾ je ve frontì sám, první a poslední je toté¾, kdy¾ není sám, vpravo od posledního bude nový prvek
            L -> Last -> rptr = element;
        else
            L -> First = L -> Last = element;
        L -> Last = element;                    //a vlo¾íme na poslední místo
    }
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/
	L->Act=L->First;

 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný pøíkaz (nepoèítáme-li return),
** ani¾ byste testovali, zda je seznam L prázdný.
**/
	L->Act=L->Last;
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/
    if(L->First==NULL)  //kontrola prázdnosti
        DLError();
    else
    {
        *val = L->First->data;  //vrácení hodnoty
    }
	
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    if(L->Last==NULL)   //kontroloa prázdnosti
        DLError();
    else
    {
        *val = L->Last->data;       //vrácení hodnoty
    }
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** Zru¹í první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/
	if(L->First==NULL)              //kontrola prázdnosti
        return;
    if(L->First==L->Act)            //kontrola první=aktivní
        L->Act=NULL;
    tDLElemPtr firstPtr = L->First; //ulo¾ení prvního
    L->First=L->First->rptr;        //pøesmìrování prvního
    L->First->lptr=NULL;            //umazání poimteru na bývalý první
    free(firstPtr);                 //a jeho uvolnìní
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}	

void DLDeleteLast (tDLList *L) {
/*
** Zru¹í poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se nedìje.
**/
    if(L->First==NULL)              //kontrola prázdnosti
        return;
    if(L->Last==L->Act)             //kontrola aktivity
        L->Act=NULL;
	tDLElemPtr lastPtr = L->Last;
    L->Last = L->Last->lptr;        //pøesmìrování posledního
    L->Last->rptr=NULL;             //smazání pointeru na starý poslední
    free(lastPtr);                  //a jeho uvolnìní
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPostDelete (tDLList *L) {
/*
** Zru¹í prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se nedìje.
**/
    if(L -> Act != NULL && L -> Act -> rptr != NULL)    //kontrola aktivity a poslednosti
    {
        tDLElemPtr element;
        element = L -> Act -> rptr;                     //získání následujícího prvku
        L -> Act -> rptr = element -> rptr;             //pøepojení seznamu
        if(element -> rptr == NULL)                     //o¹etøení posledního prvku
            L -> Last= L -> Act;                        //poslední se stává akutálním
        else
            element -> rptr -> lptr = L -> Act;         //nebo pøepojení aktuálního prvku
        free(element);                                  //a uvolnìní
    }
		
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPreDelete (tDLList *L) {
/*
** Zru¹í prvek pøed aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se nedìje.
**/
    if(L -> Act != NULL && L -> Act -> lptr != NULL)    //kontrola aktivity a prvosti
    {
        tDLElemPtr element;
        element = L -> Act -> lptr;                     //získání pøedchozího prvku
        L -> Act -> lptr = element -> lptr;             //pøepojení seznamu
        if(element -> lptr == NULL)                     //pokud pøed uvolnovaným prvkem nic není, tak se první rovná aktuálnímu
            L -> First= L -> Act;
        else
            element -> lptr -> rptr = L -> Act;         //jinak se seznam prová¾e
        free(element);                                  //a uvolnìní
    }

 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo¾í prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
	if(L->Act==NULL)        //kontrola aktivity
        return;
    struct tDLElem *element;
    if((element= malloc(sizeof(struct tDLElem)))!=NULL) //kontrola alokace
    {
        element->rptr=L->Act->rptr;         //navázání zprava do nového
        element->rptr->lptr=element;        //navázání zprava do seznamu
        L->Act->rptr=element;               //navázání zleva do seznamu
        element->lptr=L->Act;               //navázání zleva do nového
        element->data=val;                  //ulo¾ení hodnoty do nového
    }
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vlo¾í prvek pøed aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se nedìje.
** V pøípadì, ¾e není dostatek pamìti pro nový prvek pøi operaci malloc,
** volá funkci DLError().
**/
    if(L->Act==NULL)    //kontrola aktivity
        return;
    struct tDLElem *element;
    if((element= malloc(sizeof(struct tDLElem)))!=NULL) //kontrola alokace
    {
        element->lptr=L->Act->lptr;     //navázání zleva do nového
        element->lptr->rptr=element;    //navázání zleva do seznamu
        L->Act->lptr=element;           //navázání zprava do seznamu
        element->rptr=L->Act;           //navázání zprava do nového
        element->data=val;              //ulo¾ení hodnoty do nového
    }
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostøednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/
    if(L->Act==NULL)    //kontrola aktivity
        DLError();
    else
        *val=L->Act->data;  //získání hodnoty

	
// solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLActualize (tDLList *L, int val) {
/*
** Pøepí¹e obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedìlá nic.
**/
	if(L->Act==NULL)        //kontrola aktivity
        DLError();
    else
        L->Act->data=val;      //vlo¾ení nové hodnoty
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na posledním prvku se seznam stane neaktivním.
**/
	if(L->Act!=NULL)        //kontrola aktivity
	    L->Act=L->Act->rptr;    //pøesunutí aktivity vpravo
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na pøedchozí prvek seznamu L.
** Není-li seznam aktivní, nedìlá nic.
** V¹imnìte si, ¾e pøi aktivitì na prvním prvku se seznam stane neaktivním.
**/

    if(L->Act!=NULL)        //kontrola aktivity
        L->Act=L->Act->lptr;    //pøesunutí aktivity vlevo
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam aktivní, vrací true. V opaèném pøípadì vrací false.
** Funkci implementujte jako jediný pøíkaz.
**/
    return L->Act!=NULL;    //je aktivní?
	
 //solved = FALSE;                   /* V pøípadì øe¹ení, sma¾te tento øádek! */
}

/* Konec c206.c*/
