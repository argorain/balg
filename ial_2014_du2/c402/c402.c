
/* c402.c: ********************************************************************}
{* T�ma: Nerekurzivn� implementace operac� nad BVS 
**                                     Implementace: Petr P�ikryl, prosinec 1994
**                                           �pravy: Petr P�ikryl, listopad 1997
**                                                     Petr P�ikryl, kv�ten 1998
**			  	                        P�evod do jazyka C: Martin Tu�ek, srpen 2005
**                                         �pravy: Bohuslav K�ena, listopad 2009
**                                         �pravy: Karel Masa��k, ��jen 2013
**                                         �pravy: Radek Hranick�, ��jen 2014
**
** S vyu�it�m dynamick�ho p�id�lov�n� pam�ti, implementujte NEREKURZIVN�
** n�sleduj�c� operace nad bin�rn�m vyhled�vac�m stromem (p�edpona BT znamen�
** Binary Tree a je u identifik�tor� uvedena kv�li mo�n� kolizi s ostatn�mi
** p��klady):
**
**     BTInit .......... inicializace stromu
**     BTInsert ........ nerekurzivn� vlo�en� nov�ho uzlu do stromu
**     BTPreorder ...... nerekurzivn� pr�chod typu pre-order
**     BTInorder ....... nerekurzivn� pr�chod typu in-order
**     BTPostorder ..... nerekurzivn� pr�chod typu post-order
**     BTDisposeTree ... zru� v�echny uzly stromu
**
** U v�ech funkc�, kter� vyu��vaj� n�kter� z pr�chod� stromem, implementujte
** pomocnou funkci pro nalezen� nejlev�j��ho uzlu v podstromu.
**
** P�esn� definice typ� naleznete v souboru c402.h. Uzel stromu je typu tBTNode,
** ukazatel na n�j je typu tBTNodePtr. Jeden uzel obsahuje polo�ku int Cont,
** kter� sou�asn� slou�� jako u�ite�n� obsah i jako vyhled�vac� kl�� 
** a ukazatele na lev� a prav� podstrom (LPtr a RPtr).
**
** P��klad slou�� zejm�na k procvi�en� nerekurzivn�ch z�pis� algoritm�
** nad stromy. Ne� za�nete tento p��klad �e�it, prostudujte si d�kladn�
** principy p�evodu rekurzivn�ch algoritm� na nerekurzivn�. Programov�n�
** je p�edev��m in�en�rsk� discipl�na, kde op�tn� objevov�n� Ameriky nem�
** m�sto. Pokud se V�m zd�, �e by n�co �lo zapsat optim�ln�ji, promyslete
** si v�echny detaily Va�eho �e�en�. Pov�imn�te si typick�ho um�st�n� akc�
** pro r�zn� typy pr�chod�. Zamyslete se nad modifikac� �e�en�ch algoritm�
** nap��klad pro v�po�et po�tu uzl� stromu, po�tu list� stromu, v��ky stromu
** nebo pro vytvo�en� zrcadlov�ho obrazu stromu (pouze pop�ehazov�n� ukazatel�
** bez vytv��en� nov�ch uzl� a ru�en� star�ch).
**
** P�i pr�chodech stromem pou�ijte ke zpracov�n� uzlu funkci BTWorkOut().
** Pro zjednodu�en� pr�ce m�te p�edem p�ipraveny z�sobn�ky pro hodnoty typu
** bool a tBTNodePtr. Pomocnou funkci BTWorkOut ani funkce pro pr�ci
** s pomocn�mi z�sobn�ky neupravujte 
** Pozor! Je t�eba spr�vn� rozli�ovat, kdy pou��t dereferen�n� oper�tor *
** (typicky p�i modifikaci) a kdy budeme pracovat pouze se samotn�m ukazatelem 
** (nap�. p�i vyhled�v�n�). V tomto p��kladu v�m napov� prototypy funkc�.
** Pokud pracujeme s ukazatelem na ukazatel, pou�ijeme dereferenci.
**/

#include "c402.h"
int solved;

void BTWorkOut (tBTNodePtr Ptr)		{
/*   ---------
** Pomocn� funkce, kterou budete volat p�i pr�chodech stromem pro zpracov�n�
** uzlu ur�en�ho ukazatelem Ptr. Tuto funkci neupravujte.
**/
			
	if (Ptr==NULL) 
    printf("Chyba: Funkce BTWorkOut byla vol�na s NULL argumentem!\n");
  else 
    printf("V�pis hodnoty dan�ho uzlu> %d\n",Ptr->Cont);
}
	
/* -------------------------------------------------------------------------- */
/*
** Funkce pro z�sobn�k hotnot typu tBTNodePtr. Tyto funkce neupravujte.
**/

void SInitP (tStackP *S)  
/*   ------
** Inicializace z�sobn�ku.
**/
{
	S->top = 0;  
}	

void SPushP (tStackP *S, tBTNodePtr ptr)
/*   ------
** Vlo�� hodnotu na vrchol z�sobn�ku.
**/
{ 
                 /* P�i implementaci v poli m��e doj�t k p�ete�en� z�sobn�ku. */
  if (S->top==MAXSTACK) 
    printf("Chyba: Do�lo k p�ete�en� z�sobn�ku s ukazateli!\n");
  else {  
		S->top++;  
		S->a[S->top]=ptr;
	}
}	

tBTNodePtr STopPopP (tStackP *S)
/*         --------
** Odstran� prvek z vrcholu z�sobn�ku a sou�asn� vr�t� jeho hodnotu.
**/
{
                            /* Operace nad pr�zdn�m z�sobn�kem zp�sob� chybu. */
	if (S->top==0)  {
		printf("Chyba: Do�lo k podte�en� z�sobn�ku s ukazateli!\n");
		return(NULL);	
	}	
	else {
		return (S->a[S->top--]);
	}	
}

bool SEmptyP (tStackP *S)
/*   -------
** Je-li z�sobn�k pr�zdn�, vr�t� hodnotu true.
**/
{
  return(S->top==0);
}	

/* -------------------------------------------------------------------------- */
/*
** Funkce pro z�sobn�k hotnot typu bool. Tyto funkce neupravujte.
*/

void SInitB (tStackB *S) {
/*   ------
** Inicializace z�sobn�ku.
**/

	S->top = 0;  
}	

void SPushB (tStackB *S,bool val) {
/*   ------
** Vlo�� hodnotu na vrchol z�sobn�ku.
**/
                 /* P�i implementaci v poli m��e doj�t k p�ete�en� z�sobn�ku. */
	if (S->top==MAXSTACK) 
		printf("Chyba: Do�lo k p�ete�en� z�sobn�ku pro boolean!\n");
	else {
		S->top++;  
		S->a[S->top]=val;
	}	
}

bool STopPopB (tStackB *S) {
/*   --------
** Odstran� prvek z vrcholu z�sobn�ku a sou�asn� vr�t� jeho hodnotu.
**/
                            /* Operace nad pr�zdn�m z�sobn�kem zp�sob� chybu. */
	if (S->top==0) {
		printf("Chyba: Do�lo k podte�en� z�sobn�ku pro boolean!\n");
		return(NULL);	
	}	
	else {  
		return(S->a[S->top--]); 
	}	
}

bool SEmptyB (tStackB *S) {
/*   -------
** Je-li z�sobn�k pr�zdn�, vr�t� hodnotu true.
**/
  return(S->top==0);
}

/* -------------------------------------------------------------------------- */
/*
** N�sleduje j�dro dom�c� �lohy - funkce, kter� m�te implementovat. 
*/

void BTInit (tBTNodePtr *RootPtr)	{
/*   ------
** Provede inicializaci bin�rn�ho vyhled�vac�ho stromu.
**
** Inicializaci sm� program�tor volat pouze p�ed prvn�m pou�it�m bin�rn�ho
** stromu, proto�e neuvol�uje uzly nepr�zdn�ho stromu (a ani to d�lat nem��e,
** proto�e p�ed inicializac� jsou hodnoty nedefinovan�, tedy libovoln�).
** Ke zru�en� bin�rn�ho stromu slou�� procedura BTDisposeTree.
**	
** V�imn�te si, �e zde se poprv� v hlavi�ce objevuje typ ukazatel na ukazatel,	
** proto je t�eba p�i pr�ci s RootPtr pou��t dereferen�n� oper�tor *.
**/
	
    (*RootPtr)=NULL;
	 //solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */
}

void BTInsert (tBTNodePtr *RootPtr, int Content) {
/*   --------
** Vlo�� do stromu nov� uzel s hodnotou Content.
**
** Z pohledu vkl�d�n� ch�pejte vytv��en� strom jako bin�rn� vyhled�vac� strom,
** kde uzly s hodnotou men�� ne� m� otec le�� v lev�m podstromu a uzly v�t��
** le�� vpravo. Pokud vkl�dan� uzel ji� existuje, neprov�d� se nic (dan� hodnota
** se ve stromu m��e vyskytnout nejv��e jednou). Pokud se vytv��� nov� uzel,
** vznik� v�dy jako list stromu. Funkci implementujte nerekurzivn�.
**/
    tBTNodePtr temp,pass;

    if((*RootPtr)==NULL){                                   //Strom je pr�zdn�, vlo��me uzel na za��tek
        temp=malloc(sizeof(struct tBTNode));
        temp->Cont=Content;
        temp->LPtr= NULL;
        temp->RPtr=NULL;
        (*RootPtr)=temp;
    }else{
        pass=(*RootPtr);
        while(pass!=NULL){                                  //dokud je ukazatel pln�, hled�me m�sto
            if(Content<pass->Cont){ //levy                  //n� obsah je men��, jdeme vlevo
                if(pass->LPtr!=NULL)                        //vlevo je kam? jdeme vlevo
                    pass=pass->LPtr;
                else{                                       //nen� kam pokra�ovat, vlo��me uzel sem
                    temp=malloc(sizeof(struct tBTNode));
                    temp->Cont=Content;
                    temp->LPtr= NULL;
                    temp->RPtr=NULL;
                    pass->LPtr=temp;
                    return;
                }
            }else if(Content>pass->Cont) { //pravy          //n� obsah je v�t��, jdeme vpravo a vice versa
                if(pass->RPtr!=NULL)
                    pass=pass->RPtr;
                else{
                    temp=malloc(sizeof(struct tBTNode));
                    temp->Cont=Content;
                    temp->LPtr= NULL;
                    temp->RPtr=NULL;
                    pass->RPtr=temp;
                    return;
                }
            }else{
                return;
            }
        }
    }
		
	// solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */
}

/*                                  PREORDER                                  */

void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack)	{
/*   -----------------
** Jde po lev� v�tvi podstromu, dokud nenaraz� na jeho nejlev�j�� uzel.
**
** P�i pr�chodu Preorder nav�t�ven� uzly zpracujeme vol�n�m funkce BTWorkOut()
** a ukazatele na n� is ulo��me do z�sobn�ku.
**/

    while(ptr != NULL){         //dokud je kam, jdeme vlevo
        SPushP(Stack, ptr);     //ulo��me si nav�t�ven� prvek
        BTWorkOut(ptr);         //zavol�me workout
        ptr = ptr-> LPtr;       //a postoup�me vlevo
    }
}

void BTPreorder (tBTNodePtr RootPtr)	{
/*   ----------
** Pr�chod stromem typu preorder implementovan� nerekurzivn� s vyu�it�m funkce
** Leftmost_Preorder a z�sobn�ku ukazatel�. Zpracov�n� jednoho uzlu stromu
** realizujte jako vol�n� funkce BTWorkOut(). 
**/

    if((RootPtr)==NULL)                             //nen�-li kam j�t, jdeme pry�.
        return;
    else{
        tBTNodePtr tmp;

        tStackP stack;                              //vyrob�me si z�sobn�k
        SInitP(&stack);

        Leftmost_Preorder(RootPtr,&stack);          //dojdeme upln� vlevo
        while(!SEmptyP(&stack)){                    //a dokud nevypr�zdn�me z�sobn�k, proch�z�me v�echny prav� v�tve
            tmp = STopPopP(&stack);
            Leftmost_Preorder(tmp -> RPtr,&stack);
        }
    }
}


/*                                  INORDER                                   */ 

void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack)		{
/*   ----------------
** Jde po lev� v�tvi podstromu, dokud nenaraz� na jeho nejlev�j�� uzel.
**
** P�i pr�chodu Inorder ukl�d�me ukazatele na v�echny nav�t�ven� uzly do
** z�sobn�ku. 
**/

    while(ptr != NULL) {            //dokud to jde, jdeme d�le
        SPushP(Stack, ptr);         //ukl�d�me si nav�t�ven� uzly
        ptr = ptr-> LPtr;           //a jdeme vlevo
    }
	
	// solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */
	
}

void BTInorder (tBTNodePtr RootPtr)	{
/*   ---------
** Pr�chod stromem typu inorder implementovan� nerekurzivn� s vyu�it�m funkce
** Leftmost_Inorder a z�sobn�ku ukazatel�. Zpracov�n� jednoho uzlu stromu
** realizujte jako vol�n� funkce BTWorkOut(). 
**/

    if((RootPtr)==NULL)                             //kde nic nen�, ani inorder nebere
        return;
    else{
        tBTNodePtr tmp;

        tStackP stack;
        SInitP(&stack);                             //vyrob�me si z�sobn�k

        Leftmost_Inorder(RootPtr, &stack);          //projdeme upln� vlevo
        while(!SEmptyP(&stack)) {                   //dokud nen� pr�zdn� z�sobn�k, proch�z�me prav� v�tve a nav�t�ven� vypisujeme je workoutem
            tmp = STopPopP(&stack);
            BTWorkOut(tmp);
            Leftmost_Inorder(tmp->RPtr, &stack);
        }

    }
}

/*                                 POSTORDER                                  */ 

void Leftmost_Postorder (tBTNodePtr ptr, tStackP *StackP, tStackB *StackB) {
/*           --------
** Jde po lev� v�tvi podstromu, dokud nenaraz� na jeho nejlev�j�� uzel.
**
** P�i pr�chodu Postorder ukl�d�me ukazatele na nav�t�ven� uzly do z�sobn�ku
** a sou�asn� do z�sobn�ku bool hodnot ukl�d�me informaci, zda byl uzel
** nav�t�ven poprv� a �e se tedy je�t� nem� zpracov�vat. 
**/
    while(ptr != NULL){
        SPushP(StackP, ptr);            //ulo��me si nav�t�ven� uzel
        SPushB(StackB, TRUE);           //nastav�me p��znak na TRUE
        ptr = ptr -> LPtr;              //jdeme vlevo
    }
}

void BTPostorder (tBTNodePtr RootPtr)	{
/*           -----------
** Pr�chod stromem typu postorder implementovan� nerekurzivn� s vyu�it�m funkce
** Leftmost_Postorder, z�sobn�ku ukazatel� a z�sobn�ku hotdnot typu bool.
** Zpracov�n� jednoho uzlu stromu realizujte jako vol�n� funkce BTWorkOut(). 
**/

    if((RootPtr)==NULL)
        return;
    else{
        tStackP stackP;
        tStackB stackB;
        SInitP(&stackP);
        SInitB(&stackB);                                        //vyrob�me z�sobn�ky
        tBTNodePtr tmp;

        Leftmost_Postorder(RootPtr, &stackP, &stackB);          //projdeme upln� vlevo

        while(!SEmptyP(&stackP)){                               //a vyprazd�ujeme z�sobn�k
            tmp = STopPopP(&stackP);
            SPushP(&stackP, tmp);                               //vyjmut� prvek vlo��me zp�t (chceme se na n�j jen pod�vat zat�m)
            if(STopPopB(&stackB) == TRUE){                      //vyjmeme p��znak
                SPushB(&stackB, FALSE);                         //je-li true, zm�n�me ho na false a pokra�ujeme v hled�n� vpravo
                Leftmost_Postorder(tmp -> RPtr, &stackP, &stackB);
            } else {                                            //je li false, vyjmeme prvek ze z�sobn�ku a zavol�me workout
                tmp = STopPopP(&stackP);
                BTWorkOut(tmp);
            }
        }
    }

}


void BTDisposeTree (tBTNodePtr *RootPtr)	{
/*   -------------
** Zru�� v�echny uzly stromu a korektn� uvoln� jimi zabranou pam�.
**
** Funkci implementujte nerekurzivn� s vyu�it�m z�sobn�ku ukazatel�.
**/
    tBTNodePtr temp;
    tStackP stack;


	if((*RootPtr)==NULL)
        return;
    else{
        SInitP(&stack);
        while(!SEmptyP(&stack) || (*RootPtr) != NULL)    //dokud nen� z�sobn�k pr�zdn� nebo strom u� nen� smazan�
        {
            if((*RootPtr) == NULL)                      //kdy� je strom pr�zdn�, vyjmeme posledn� vlo�en� uzel ze z�sobn�ku
                *RootPtr = STopPopP(&stack);
            else                                        //nen� li pr�zdn�, zkusme j�t vlevo
            {
                if((*RootPtr) -> LPtr != NULL)
                    SPushP(&stack,(*RootPtr) -> LPtr);  //poda�� li se j�t vlevo, ulo��me si lev� uzel
                temp = (*RootPtr);
                (*RootPtr) = (*RootPtr) -> RPtr;        //p�epoj�me prav� uzel
                free(temp);                             //uvoln�me sou�asn� uzel
            }
        }
    }
	
	 //solved = FALSE;		  /* V p��pad� �e�en� sma�te tento ��dek! */
}

/* konec c402.c */

