
/* c016.c: **********************************************************}
{* TĂŠma:  Tabulka s RozptĂ˝lenĂ˝mi PoloĹžkami
**                      PrvnĂ­ implementace: Petr PĹikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      Ăpravy: Karel MasaĹĂ­k, ĹĂ­jen 2014
**                      Ăpravy: Radek HranickĂ˝, ĹĂ­jen 2014
**
** VytvoĹete abstraktnĂ­ datovĂ˝ typ
** TRP (Tabulka s RozptĂ˝lenĂ˝mi PoloĹžkami = Hash table)
** s explicitnÄ ĹetÄzenĂ˝mi synonymy. Tabulka je implementovĂĄna polem
** lineĂĄrnĂ­ch seznamĹŻ synonym.
**
** Implementujte nĂĄsledujĂ­cĂ­ procedury a funkce.
**
**  HTInit ....... inicializuje tabulku pĹed prvnĂ­m pouĹžitĂ­m
**  HTInsert ..... vloĹženĂ­ prvku
**  HTSearch ..... zjiĹĄtÄnĂ­ pĹĂ­tomnosti prvku v tabulce
**  HTDelete ..... zruĹĄenĂ­ prvku
**  HTRead ....... pĹeÄtenĂ­ hodnoty prvku
**  HTClearAll ... zruĹĄenĂ­ obsahu celĂŠ tabulky (inicializace tabulky
**                 potĂŠ, co jiĹž byla pouĹžita)
**
** Definici typĹŻ naleznete v souboru c016.h.
**
** Tabulka je reprezentovĂĄna datovou strukturou typu tHTable,
** kterĂĄ se sklĂĄdĂĄ z ukazatelĹŻ na poloĹžky, jeĹž obsahujĂ­ sloĹžky
** klĂ­Äe 'key', obsahu 'data' (pro jednoduchost typu float), a
** ukazatele na dalĹĄĂ­ synonymum 'ptrnext'. PĹi implementaci funkcĂ­
** uvaĹžujte maximĂĄlnĂ­ rozmÄr pole HTSIZE.
**
** U vĹĄech procedur vyuĹžĂ­vejte rozptylovou funkci hashCode.  PovĹĄimnÄte si
** zpĹŻsobu pĹedĂĄvĂĄnĂ­ parametrĹŻ a zamyslete se nad tĂ­m, zda je moĹžnĂŠ parametry
** pĹedĂĄvat jinĂ˝m zpĹŻsobem (hodnotou/odkazem) a v pĹĂ­padÄ, Ĺže jsou obÄ
** moĹžnosti funkÄnÄ pĹĂ­pustnĂŠ, jakĂŠ jsou vĂ˝hody Äi nevĂ˝hody toho Äi onoho
** zpĹŻsobu.
**
** V pĹĂ­kladech jsou pouĹžity poloĹžky, kde klĂ­Äem je ĹetÄzec, ke kterĂŠmu
** je pĹidĂĄn obsah - reĂĄlnĂŠ ÄĂ­slo.
*/

#include "c016.h"

int HTSIZE = MAX_HTSIZE;
int solved;

/*          -------
** RozptylovacĂ­ funkce - jejĂ­m Ăşkolem je zpracovat zadanĂ˝ klĂ­Ä a pĹidÄlit
** mu index v rozmezĂ­ 0..HTSize-1.  V ideĂĄlnĂ­m pĹĂ­padÄ by mÄlo dojĂ­t
** k rovnomÄrnĂŠmu rozptĂ˝lenĂ­ tÄchto klĂ­ÄĹŻ po celĂŠ tabulce.  V rĂĄmci
** pokusĹŻ se mĹŻĹžete zamyslet nad kvalitou tĂŠto funkce.  (Funkce nebyla
** volena s ohledem na maximĂĄlnĂ­ kvalitu vĂ˝sledku). }
*/

int hashCode ( tKey key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

/*
** Inicializace tabulky s explicitnÄ zĹetÄzenĂ˝mi synonymy.  Tato procedura
** se volĂĄ pouze pĹed prvnĂ­m pouĹžitĂ­m tabulky.
*/

void htInit ( tHTable* ptrht ) {
    for(int i=0; i< MAX_HTSIZE; i++){
        (*ptrht)[i]=NULL;
    }
}

/* TRP s explicitnÄ zĹetÄzenĂ˝mi synonymy.
** VyhledĂĄnĂ­ prvku v TRP ptrht podle zadanĂŠho klĂ­Äe key.  Pokud je
** danĂ˝ prvek nalezen, vracĂ­ se ukazatel na danĂ˝ prvek. Pokud prvek nalezen nenĂ­, 
** vracĂ­ se hodnota NULL.
**
*/

tHTItem* htSearch ( tHTable* ptrht, tKey key ) {
    tHTItem *tmp;
    for(int i=0; i< MAX_HTSIZE; i++){
        tmp=(*ptrht)[i];
        while(tmp!=NULL){
            if(tmp->key==key)
                return tmp;
            tmp=tmp->ptrnext;
        }
    }
 //solved = 0; /*v pripade reseni, smazte tento radek!*/
}

/* 
** TRP s explicitnÄ zĹetÄzenĂ˝mi synonymy.
** Tato procedura vklĂĄdĂĄ do tabulky ptrht poloĹžku s klĂ­Äem key a s daty
** data.  ProtoĹže jde o vyhledĂĄvacĂ­ tabulku, nemĹŻĹže bĂ˝t prvek se stejnĂ˝m
** klĂ­Äem uloĹžen v tabulce vĂ­ce neĹž jedenkrĂĄt.  Pokud se vklĂĄdĂĄ prvek,
** jehoĹž klĂ­Ä se jiĹž v tabulce nachĂĄzĂ­, aktualizujte jeho datovou ÄĂĄst.
**
** VyuĹžijte dĹĂ­ve vytvoĹenou funkci htSearch.  PĹi vklĂĄdĂĄnĂ­ novĂŠho
** prvku do seznamu synonym pouĹžijte co nejefektivnÄjĹĄĂ­ zpĹŻsob,
** tedy proveÄte.vloĹženĂ­ prvku na zaÄĂĄtek seznamu.
**/

void htInsert ( tHTable* ptrht, tKey key, tData data ) {
    tHTItem *tmp;
    if((tmp=htSearch(ptrht, key))==NULL) {
        int hash = hashCode(key);
        int line = hash % (MAX_HTSIZE + 1);
        tmp = malloc(sizeof(tHTItem));
        tmp->ptrnext = (*ptrht)[line];
        tmp->key = key;
        tmp->data = data;
        (*ptrht)[line] = tmp;
    }else{
        tmp->data=data;
    }

 //solved = 0; /*v pripade reseni, smazte tento radek!*/
}

/*
** TRP s explicitnÄ zĹetÄzenĂ˝mi synonymy.
** Tato funkce zjiĹĄĹĽuje hodnotu datovĂŠ ÄĂĄsti poloĹžky zadanĂŠ klĂ­Äem.
** Pokud je poloĹžka nalezena, vracĂ­ funkce ukazatel na poloĹžku
** Pokud poloĹžka nalezena nebyla, vracĂ­ se funkÄnĂ­ hodnota NULL
**
** VyuĹžijte dĹĂ­ve vytvoĹenou funkci HTSearch.
*/

tData* htRead ( tHTable* ptrht, tKey key ) {
    return &(htSearch(ptrht, key)->data);
 //solved = 0; /*v pripade reseni, smazte tento radek!*/
}

/*
** TRP s explicitnÄ zĹetÄzenĂ˝mi synonymy.
** Tato procedura vyjme poloĹžku s klĂ­Äem key z tabulky
** ptrht.  UvolnÄnou poloĹžku korektnÄ zruĹĄte.  Pokud poloĹžka s uvedenĂ˝m
** klĂ­Äem neexistuje, dÄlejte, jako kdyby se nic nestalo (tj. nedÄlejte
** nic).
**
** V tomto pĹĂ­padÄ NEVYUĹ˝ĂVEJTE dĹĂ­ve vytvoĹenou funkci HTSearch.
*/

void htDelete ( tHTable* ptrht, tKey key ) {
    int hash = hashCode(key);
    int line = hash % (MAX_HTSIZE + 1);
    tHTItem *tmp = (*ptrht)[line];
    (*ptrht)[line]=tmp->ptrnext;
    free(tmp);
 //solved = 0; /*v pripade reseni, smazte tento radek!*/
}

/* TRP s explicitnÄ zĹetÄzenĂ˝mi synonymy.
** Tato procedura zruĹĄĂ­ vĹĄechny poloĹžky tabulky, korektnÄ uvolnĂ­ prostor,
** kterĂ˝ tyto poloĹžky zabĂ­raly, a uvede tabulku do poÄĂĄteÄnĂ­ho stavu.
*/

void htClearAll ( tHTable* ptrht ) {
    tHTItem *tmp, *next;
    for(int i=0; i< MAX_HTSIZE; i++){
        while((*ptrht)[i]!=NULL) {
            tmp = (*ptrht)[i];
            (*ptrht)[i] = tmp->ptrnext;
            free(tmp);
        }
    }
//solved = 0; /*v pripade reseni, smazte tento radek!*/
}
