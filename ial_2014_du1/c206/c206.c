	
/* c206.c **********************************************************}
{* T�ma: Dvousm�rn� v�zan� line�rn� seznam
**
**                   N�vrh a referen�n� implementace: Bohuslav K�ena, ��jen 2001
**                            P�epracovan� do jazyka C: Martin Tu�ek, ��jen 2004
**                                            �pravy: Bohuslav K�ena, ��jen 2014
**
** Implementujte abstraktn� datov� typ dvousm�rn� v�zan� line�rn� seznam.
** U�ite�n�m obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom�nnou
** typu tDLList (DL znamen� Double-Linked a slou�� pro odli�en�
** jmen konstant, typ� a funkc� od jmen u jednosm�rn� v�zan�ho line�rn�ho
** seznamu). Definici konstant a typ� naleznete v hlavi�kov�m souboru c206.h.
**
** Va��m �kolem je implementovat n�sleduj�c� operace, kter� spolu
** s v��e uvedenou datovou ��st� abstrakce tvo�� abstraktn� datov� typ
** obousm�rn� v�zan� line�rn� seznam:
**
**      DLInitList ...... inicializace seznamu p�ed prvn�m pou�it�m,
**      DLDisposeList ... zru�en� v�ech prvk� seznamu,
**      DLInsertFirst ... vlo�en� prvku na za��tek seznamu,
**      DLInsertLast .... vlo�en� prvku na konec seznamu, 
**      DLFirst ......... nastaven� aktivity na prvn� prvek,
**      DLLast .......... nastaven� aktivity na posledn� prvek, 
**      DLCopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DLCopyLast ...... vrac� hodnotu posledn�ho prvku, 
**      DLDeleteFirst ... zru�� prvn� prvek seznamu,
**      DLDeleteLast .... zru�� posledn� prvek seznamu, 
**      DLPostDelete .... ru�� prvek za aktivn�m prvkem,
**      DLPreDelete ..... ru�� prvek p�ed aktivn�m prvkem, 
**      DLPostInsert .... vlo�� nov� prvek za aktivn� prvek seznamu,
**      DLPreInsert ..... vlo�� nov� prvek p�ed aktivn� prvek seznamu,
**      DLCopy .......... vrac� hodnotu aktivn�ho prvku,
**      DLActualize ..... p�ep�e obsah aktivn�ho prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal�� prvek seznamu,
**      DLPred .......... posune aktivitu na p�edchoz� prvek seznamu, 
**      DLActive ........ zji��uje aktivitu seznamu.
**
** P�i implementaci jednotliv�ch funkc� nevolejte ��dnou z funkc�
** implementovan�ch v r�mci tohoto p��kladu, nen�-li u funkce
** explicitn� uvedeno n�co jin�ho.
**
** Nemus�te o�et�ovat situaci, kdy m�sto leg�ln�ho ukazatele na seznam 
** p�ed� n�kdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn� komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepou��v� pojem procedura.
** Proto zde pou��v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozorn�n� na to, �e do�lo k chyb�.
** Tato funkce bude vol�na z n�kter�ch d�le implementovan�ch operac�.
**/	
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* glob�ln� prom�nn� -- p��znak o�et�en� chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L p�ed jeho prvn�m pou�it�m (tzn. ��dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d�t nad ji� inicializovan�m
** seznamem, a proto tuto mo�nost neo�et�ujte. V�dy p�edpokl�dejte,
** �e neinicializovan� prom�nn� maj� nedefinovanou hodnotu.
**/
    
	L->Act=NULL;
    L->First=NULL;
    L->Last=NULL;
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLDisposeList (tDLList *L) {
/*
** Zru�� v�echny prvky seznamu L a uvede seznam do stavu, v jak�m
** se nach�zel po inicializaci. Ru�en� prvky seznamu budou korektn�
** uvoln�ny vol�n�m operace free. 
**/
	tDLElemPtr elementPtr;
    L->Act=L->First;            //nastav�me aktu�ln� prvek na prvn�
	while(L->Act!=NULL)         //ma�eme dokud je co
    {
        elementPtr = L->Act;    //ulo��me si ukazatel na aktu�ln�
        L->Act=L->Act->rptr;    //posuneme se na dal�� prvek
        free(elementPtr);       //a ulo�en� prvek uvoln�me
    }
    L->Last=NULL;               //na konci by m�lo b�t v�echno null
    L->First=NULL;
    L->Act=NULL;
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vlo�� nov� prvek na za��tek seznamu L.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
	struct tDLElem *element;
    if((element= malloc(sizeof(struct tDLElem)))==NULL) //pro p��pad, �e by selhala alokace pam�ti
        DLError();
    else
    {
        element -> data = val;              //ulo��me do nov�ho prvku data
        element -> rptr = L -> First;       //a taky pointer na sou�asn� prvn�
        element -> lptr = NULL;             //vlevo od n�j nebude nic (je prvn�)
        if(L -> First != NULL)              //jestli�e je s�m ve front�, tak prvn� a posledn� je tot�, jiank sou�asn� prvn� (a za chv�li druh�) ukazuje na nov� prvn� prvek
            L -> First -> lptr = element;
        else
            L -> Last = L -> First = element;
        L -> First = element;               //vlo��me nov� prvn� do seznamu
    }
	
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vlo�� nov� prvek na konec seznamu L (symetrick� operace k DLInsertFirst).
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
    struct tDLElem *element;
    if((element= malloc(sizeof(struct tDLElem)))==NULL) //kontrola na chyby alokace
        DLError();
    else
    {
        element -> data = val;                  //ulo��me hodnotu
        element -> lptr = L -> Last;            //vlevo je sou�asn� posledn�
        element -> rptr = NULL;                 //vpravo nic
        if(L -> Last != NULL)                   //kdy� je ve front� s�m, prvn� a posledn� je tot�, kdy� nen� s�m, vpravo od posledn�ho bude nov� prvek
            L -> Last -> rptr = element;
        else
            L -> First = L -> Last = element;
        L -> Last = element;                    //a vlo��me na posledn� m�sto
    }
	
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLFirst (tDLList *L) {
/*
** Nastav� aktivitu na prvn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
	L->Act=L->First;

 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLLast (tDLList *L) {
/*
** Nastav� aktivitu na posledn� prvek seznamu L.
** Funkci implementujte jako jedin� p��kaz (nepo��t�me-li return),
** ani� byste testovali, zda je seznam L pr�zdn�.
**/
	L->Act=L->Last;
	
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/
    if(L->First==NULL)  //kontrola pr�zdnosti
        DLError();
    else
    {
        *val = L->First->data;  //vr�cen� hodnoty
    }
	
	
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu posledn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
**/

    if(L->Last==NULL)   //kontroloa pr�zdnosti
        DLError();
    else
    {
        *val = L->Last->data;       //vr�cen� hodnoty
    }
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** Zru�� prvn� prvek seznamu L. Pokud byl prvn� prvek aktivn�, aktivita 
** se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
**/
	if(L->First==NULL)              //kontrola pr�zdnosti
        return;
    if(L->First==L->Act)            //kontrola prvn�=aktivn�
        L->Act=NULL;
    tDLElemPtr firstPtr = L->First; //ulo�en� prvn�ho
    L->First=L->First->rptr;        //p�esm�rov�n� prvn�ho
    L->First->lptr=NULL;            //umaz�n� poimteru na b�val� prvn�
    free(firstPtr);                 //a jeho uvoln�n�
	
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}	

void DLDeleteLast (tDLList *L) {
/*
** Zru�� posledn� prvek seznamu L. Pokud byl posledn� prvek aktivn�,
** aktivita seznamu se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned�je.
**/
    if(L->First==NULL)              //kontrola pr�zdnosti
        return;
    if(L->Last==L->Act)             //kontrola aktivity
        L->Act=NULL;
	tDLElemPtr lastPtr = L->Last;
    L->Last = L->Last->lptr;        //p�esm�rov�n� posledn�ho
    L->Last->rptr=NULL;             //smaz�n� pointeru na star� posledn�
    free(lastPtr);                  //a jeho uvoln�n�
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPostDelete (tDLList *L) {
/*
** Zru�� prvek seznamu L za aktivn�m prvkem.
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** posledn�m prvkem seznamu, nic se ned�je.
**/
    if(L -> Act != NULL && L -> Act -> rptr != NULL)    //kontrola aktivity a poslednosti
    {
        tDLElemPtr element;
        element = L -> Act -> rptr;                     //z�sk�n� n�sleduj�c�ho prvku
        L -> Act -> rptr = element -> rptr;             //p�epojen� seznamu
        if(element -> rptr == NULL)                     //o�et�en� posledn�ho prvku
            L -> Last= L -> Act;                        //posledn� se st�v� akut�ln�m
        else
            element -> rptr -> lptr = L -> Act;         //nebo p�epojen� aktu�ln�ho prvku
        free(element);                                  //a uvoln�n�
    }
		
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPreDelete (tDLList *L) {
/*
** Zru�� prvek p�ed aktivn�m prvkem seznamu L .
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** prvn�m prvkem seznamu, nic se ned�je.
**/
    if(L -> Act != NULL && L -> Act -> lptr != NULL)    //kontrola aktivity a prvosti
    {
        tDLElemPtr element;
        element = L -> Act -> lptr;                     //z�sk�n� p�edchoz�ho prvku
        L -> Act -> lptr = element -> lptr;             //p�epojen� seznamu
        if(element -> lptr == NULL)                     //pokud p�ed uvolnovan�m prvkem nic nen�, tak se prvn� rovn� aktu�ln�mu
            L -> First= L -> Act;
        else
            element -> lptr -> rptr = L -> Act;         //jinak se seznam prov�e
        free(element);                                  //a uvoln�n�
    }

 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlo�� prvek za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
	if(L->Act==NULL)        //kontrola aktivity
        return;
    struct tDLElem *element;
    if((element= malloc(sizeof(struct tDLElem)))!=NULL) //kontrola alokace
    {
        element->rptr=L->Act->rptr;         //nav�z�n� zprava do nov�ho
        element->rptr->lptr=element;        //nav�z�n� zprava do seznamu
        L->Act->rptr=element;               //nav�z�n� zleva do seznamu
        element->lptr=L->Act;               //nav�z�n� zleva do nov�ho
        element->data=val;                  //ulo�en� hodnoty do nov�ho
    }
	
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vlo�� prvek p�ed aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned�je.
** V p��pad�, �e nen� dostatek pam�ti pro nov� prvek p�i operaci malloc,
** vol� funkci DLError().
**/
    if(L->Act==NULL)    //kontrola aktivity
        return;
    struct tDLElem *element;
    if((element= malloc(sizeof(struct tDLElem)))!=NULL) //kontrola alokace
    {
        element->lptr=L->Act->lptr;     //nav�z�n� zleva do nov�ho
        element->lptr->rptr=element;    //nav�z�n� zleva do seznamu
        L->Act->lptr=element;           //nav�z�n� zprava do seznamu
        element->rptr=L->Act;           //nav�z�n� zprava do nov�ho
        element->data=val;              //ulo�en� hodnoty do nov�ho
    }
	
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** Prost�ednictv�m parametru val vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, vol� funkci DLError ().
**/
    if(L->Act==NULL)    //kontrola aktivity
        DLError();
    else
        *val=L->Act->data;  //z�sk�n� hodnoty

	
// solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLActualize (tDLList *L, int val) {
/*
** P�ep�e obsah aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, ned�l� nic.
**/
	if(L->Act==NULL)        //kontrola aktivity
        DLError();
    else
        L->Act->data=val;      //vlo�en� nov� hodnoty
	
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na posledn�m prvku se seznam stane neaktivn�m.
**/
	if(L->Act!=NULL)        //kontrola aktivity
	    L->Act=L->Act->rptr;    //p�esunut� aktivity vpravo
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na p�edchoz� prvek seznamu L.
** Nen�-li seznam aktivn�, ned�l� nic.
** V�imn�te si, �e p�i aktivit� na prvn�m prvku se seznam stane neaktivn�m.
**/

    if(L->Act!=NULL)        //kontrola aktivity
        L->Act=L->Act->lptr;    //p�esunut� aktivity vlevo
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam aktivn�, vrac� true. V opa�n�m p��pad� vrac� false.
** Funkci implementujte jako jedin� p��kaz.
**/
    return L->Act!=NULL;    //je aktivn�?
	
 //solved = FALSE;                   /* V p��pad� �e�en�, sma�te tento ��dek! */
}

/* Konec c206.c*/
