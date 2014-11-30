
/* c402.c: ********************************************************************}
{* Téma: Nerekurzivní implementace operací nad BVS 
**                                     Implementace: Petr Pøikryl, prosinec 1994
**                                           Úpravy: Petr Pøikryl, listopad 1997
**                                                     Petr Pøikryl, kvìten 1998
**			  	                        Pøevod do jazyka C: Martin Tuèek, srpen 2005
**                                         Úpravy: Bohuslav Køena, listopad 2009
**                                         Úpravy: Karel Masaøík, øíjen 2013
**                                         Úpravy: Radek Hranický, øíjen 2014
**
** S vyu¾itím dynamického pøidìlování pamìti, implementujte NEREKURZIVNÌ
** následující operace nad binárním vyhledávacím stromem (pøedpona BT znamená
** Binary Tree a je u identifikátorù uvedena kvùli mo¾né kolizi s ostatními
** pøíklady):
**
**     BTInit .......... inicializace stromu
**     BTInsert ........ nerekurzivní vlo¾ení nového uzlu do stromu
**     BTPreorder ...... nerekurzivní prùchod typu pre-order
**     BTInorder ....... nerekurzivní prùchod typu in-order
**     BTPostorder ..... nerekurzivní prùchod typu post-order
**     BTDisposeTree ... zru¹ v¹echny uzly stromu
**
** U v¹ech funkcí, které vyu¾ívají nìkterý z prùchodù stromem, implementujte
** pomocnou funkci pro nalezení nejlevìj¹ího uzlu v podstromu.
**
** Pøesné definice typù naleznete v souboru c402.h. Uzel stromu je typu tBTNode,
** ukazatel na nìj je typu tBTNodePtr. Jeden uzel obsahuje polo¾ku int Cont,
** která souèasnì slou¾í jako u¾iteèný obsah i jako vyhledávací klíè 
** a ukazatele na levý a pravý podstrom (LPtr a RPtr).
**
** Pøíklad slou¾í zejména k procvièení nerekurzivních zápisù algoritmù
** nad stromy. Ne¾ zaènete tento pøíklad øe¹it, prostudujte si dùkladnì
** principy pøevodu rekurzivních algoritmù na nerekurzivní. Programování
** je pøedev¹ím in¾enýrská disciplína, kde opìtné objevování Ameriky nemá
** místo. Pokud se Vám zdá, ¾e by nìco ¹lo zapsat optimálnìji, promyslete
** si v¹echny detaily Va¹eho øe¹ení. Pov¹imnìte si typického umístìní akcí
** pro rùzné typy prùchodù. Zamyslete se nad modifikací øe¹ených algoritmù
** napøíklad pro výpoèet poètu uzlù stromu, poètu listù stromu, vý¹ky stromu
** nebo pro vytvoøení zrcadlového obrazu stromu (pouze popøehazování ukazatelù
** bez vytváøení nových uzlù a ru¹ení starých).
**
** Pøi prùchodech stromem pou¾ijte ke zpracování uzlu funkci BTWorkOut().
** Pro zjednodu¹ení práce máte pøedem pøipraveny zásobníky pro hodnoty typu
** bool a tBTNodePtr. Pomocnou funkci BTWorkOut ani funkce pro práci
** s pomocnými zásobníky neupravujte 
** Pozor! Je tøeba správnì rozli¹ovat, kdy pou¾ít dereferenèní operátor *
** (typicky pøi modifikaci) a kdy budeme pracovat pouze se samotným ukazatelem 
** (napø. pøi vyhledávání). V tomto pøíkladu vám napoví prototypy funkcí.
** Pokud pracujeme s ukazatelem na ukazatel, pou¾ijeme dereferenci.
**/

#include "c402.h"
int solved;

void BTWorkOut (tBTNodePtr Ptr)		{
/*   ---------
** Pomocná funkce, kterou budete volat pøi prùchodech stromem pro zpracování
** uzlu urèeného ukazatelem Ptr. Tuto funkci neupravujte.
**/
			
	if (Ptr==NULL) 
    printf("Chyba: Funkce BTWorkOut byla volána s NULL argumentem!\n");
  else 
    printf("Výpis hodnoty daného uzlu> %d\n",Ptr->Cont);
}
	
/* -------------------------------------------------------------------------- */
/*
** Funkce pro zásobník hotnot typu tBTNodePtr. Tyto funkce neupravujte.
**/

void SInitP (tStackP *S)  
/*   ------
** Inicializace zásobníku.
**/
{
	S->top = 0;  
}	

void SPushP (tStackP *S, tBTNodePtr ptr)
/*   ------
** Vlo¾í hodnotu na vrchol zásobníku.
**/
{ 
                 /* Pøi implementaci v poli mù¾e dojít k pøeteèení zásobníku. */
  if (S->top==MAXSTACK) 
    printf("Chyba: Do¹lo k pøeteèení zásobníku s ukazateli!\n");
  else {  
		S->top++;  
		S->a[S->top]=ptr;
	}
}	

tBTNodePtr STopPopP (tStackP *S)
/*         --------
** Odstraní prvek z vrcholu zásobníku a souèasnì vrátí jeho hodnotu.
**/
{
                            /* Operace nad prázdným zásobníkem zpùsobí chybu. */
	if (S->top==0)  {
		printf("Chyba: Do¹lo k podteèení zásobníku s ukazateli!\n");
		return(NULL);	
	}	
	else {
		return (S->a[S->top--]);
	}	
}

bool SEmptyP (tStackP *S)
/*   -------
** Je-li zásobník prázdný, vrátí hodnotu true.
**/
{
  return(S->top==0);
}	

/* -------------------------------------------------------------------------- */
/*
** Funkce pro zásobník hotnot typu bool. Tyto funkce neupravujte.
*/

void SInitB (tStackB *S) {
/*   ------
** Inicializace zásobníku.
**/

	S->top = 0;  
}	

void SPushB (tStackB *S,bool val) {
/*   ------
** Vlo¾í hodnotu na vrchol zásobníku.
**/
                 /* Pøi implementaci v poli mù¾e dojít k pøeteèení zásobníku. */
	if (S->top==MAXSTACK) 
		printf("Chyba: Do¹lo k pøeteèení zásobníku pro boolean!\n");
	else {
		S->top++;  
		S->a[S->top]=val;
	}	
}

bool STopPopB (tStackB *S) {
/*   --------
** Odstraní prvek z vrcholu zásobníku a souèasnì vrátí jeho hodnotu.
**/
                            /* Operace nad prázdným zásobníkem zpùsobí chybu. */
	if (S->top==0) {
		printf("Chyba: Do¹lo k podteèení zásobníku pro boolean!\n");
		return(NULL);	
	}	
	else {  
		return(S->a[S->top--]); 
	}	
}

bool SEmptyB (tStackB *S) {
/*   -------
** Je-li zásobník prázdný, vrátí hodnotu true.
**/
  return(S->top==0);
}

/* -------------------------------------------------------------------------- */
/*
** Následuje jádro domácí úlohy - funkce, které máte implementovat. 
*/

void BTInit (tBTNodePtr *RootPtr)	{
/*   ------
** Provede inicializaci binárního vyhledávacího stromu.
**
** Inicializaci smí programátor volat pouze pøed prvním pou¾itím binárního
** stromu, proto¾e neuvolòuje uzly neprázdného stromu (a ani to dìlat nemù¾e,
** proto¾e pøed inicializací jsou hodnoty nedefinované, tedy libovolné).
** Ke zru¹ení binárního stromu slou¾í procedura BTDisposeTree.
**	
** V¹imnìte si, ¾e zde se poprvé v hlavièce objevuje typ ukazatel na ukazatel,	
** proto je tøeba pøi práci s RootPtr pou¾ít dereferenèní operátor *.
**/
	
    (*RootPtr)=NULL;
	 //solved = FALSE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */
}

void BTInsert (tBTNodePtr *RootPtr, int Content) {
/*   --------
** Vlo¾í do stromu nový uzel s hodnotou Content.
**
** Z pohledu vkládání chápejte vytváøený strom jako binární vyhledávací strom,
** kde uzly s hodnotou men¹í ne¾ má otec le¾í v levém podstromu a uzly vìt¹í
** le¾í vpravo. Pokud vkládaný uzel ji¾ existuje, neprovádí se nic (daná hodnota
** se ve stromu mù¾e vyskytnout nejvý¹e jednou). Pokud se vytváøí nový uzel,
** vzniká v¾dy jako list stromu. Funkci implementujte nerekurzivnì.
**/
    tBTNodePtr temp,pass;

    if((*RootPtr)==NULL){                                   //Strom je prázdný, vlo¾íme uzel na zaèátek
        temp=malloc(sizeof(struct tBTNode));
        temp->Cont=Content;
        temp->LPtr= NULL;
        temp->RPtr=NULL;
        (*RootPtr)=temp;
    }else{
        pass=(*RootPtr);
        while(pass!=NULL){                                  //dokud je ukazatel plný, hledáme místo
            if(Content<pass->Cont){ //levy                  //ná¹ obsah je men¹í, jdeme vlevo
                if(pass->LPtr!=NULL)                        //vlevo je kam? jdeme vlevo
                    pass=pass->LPtr;
                else{                                       //není kam pokraèovat, vlo¾íme uzel sem
                    temp=malloc(sizeof(struct tBTNode));
                    temp->Cont=Content;
                    temp->LPtr= NULL;
                    temp->RPtr=NULL;
                    pass->LPtr=temp;
                    return;
                }
            }else if(Content>pass->Cont) { //pravy          //ná¹ obsah je vìt¹í, jdeme vpravo a vice versa
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
		
	// solved = FALSE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */
}

/*                                  PREORDER                                  */

void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack)	{
/*   -----------------
** Jde po levì vìtvi podstromu, dokud nenarazí na jeho nejlevìj¹í uzel.
**
** Pøi prùchodu Preorder nav¹tívené uzly zpracujeme voláním funkce BTWorkOut()
** a ukazatele na nì is ulo¾íme do zásobníku.
**/

    while(ptr != NULL){         //dokud je kam, jdeme vlevo
        SPushP(Stack, ptr);     //ulo¾íme si nav¹tívený prvek
        BTWorkOut(ptr);         //zavoláme workout
        ptr = ptr-> LPtr;       //a postoupíme vlevo
    }
}

void BTPreorder (tBTNodePtr RootPtr)	{
/*   ----------
** Prùchod stromem typu preorder implementovaný nerekurzivnì s vyu¾itím funkce
** Leftmost_Preorder a zásobníku ukazatelù. Zpracování jednoho uzlu stromu
** realizujte jako volání funkce BTWorkOut(). 
**/

    if((RootPtr)==NULL)                             //není-li kam jít, jdeme pryè.
        return;
    else{
        tBTNodePtr tmp;

        tStackP stack;                              //vyrobíme si zásobník
        SInitP(&stack);

        Leftmost_Preorder(RootPtr,&stack);          //dojdeme uplnì vlevo
        while(!SEmptyP(&stack)){                    //a dokud nevyprázdníme zásobník, procházíme v¹echny pravé vìtve
            tmp = STopPopP(&stack);
            Leftmost_Preorder(tmp -> RPtr,&stack);
        }
    }
}


/*                                  INORDER                                   */ 

void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack)		{
/*   ----------------
** Jde po levì vìtvi podstromu, dokud nenarazí na jeho nejlevìj¹í uzel.
**
** Pøi prùchodu Inorder ukládáme ukazatele na v¹echny nav¹tívené uzly do
** zásobníku. 
**/

    while(ptr != NULL) {            //dokud to jde, jdeme dále
        SPushP(Stack, ptr);         //ukládáme si nav¹tívené uzly
        ptr = ptr-> LPtr;           //a jdeme vlevo
    }
	
	// solved = FALSE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */
	
}

void BTInorder (tBTNodePtr RootPtr)	{
/*   ---------
** Prùchod stromem typu inorder implementovaný nerekurzivnì s vyu¾itím funkce
** Leftmost_Inorder a zásobníku ukazatelù. Zpracování jednoho uzlu stromu
** realizujte jako volání funkce BTWorkOut(). 
**/

    if((RootPtr)==NULL)                             //kde nic není, ani inorder nebere
        return;
    else{
        tBTNodePtr tmp;

        tStackP stack;
        SInitP(&stack);                             //vyrobíme si zásobník

        Leftmost_Inorder(RootPtr, &stack);          //projdeme uplnì vlevo
        while(!SEmptyP(&stack)) {                   //dokud není prázdný zásobník, procházíme pravé vìtve a nav¹tívené vypisujeme je workoutem
            tmp = STopPopP(&stack);
            BTWorkOut(tmp);
            Leftmost_Inorder(tmp->RPtr, &stack);
        }

    }
}

/*                                 POSTORDER                                  */ 

void Leftmost_Postorder (tBTNodePtr ptr, tStackP *StackP, tStackB *StackB) {
/*           --------
** Jde po levì vìtvi podstromu, dokud nenarazí na jeho nejlevìj¹í uzel.
**
** Pøi prùchodu Postorder ukládáme ukazatele na nav¹tívené uzly do zásobníku
** a souèasnì do zásobníku bool hodnot ukládáme informaci, zda byl uzel
** nav¹tíven poprvé a ¾e se tedy je¹tì nemá zpracovávat. 
**/
    while(ptr != NULL){
        SPushP(StackP, ptr);            //ulo¾íme si nav¹tívený uzel
        SPushB(StackB, TRUE);           //nastavíme pøíznak na TRUE
        ptr = ptr -> LPtr;              //jdeme vlevo
    }
}

void BTPostorder (tBTNodePtr RootPtr)	{
/*           -----------
** Prùchod stromem typu postorder implementovaný nerekurzivnì s vyu¾itím funkce
** Leftmost_Postorder, zásobníku ukazatelù a zásobníku hotdnot typu bool.
** Zpracování jednoho uzlu stromu realizujte jako volání funkce BTWorkOut(). 
**/

    if((RootPtr)==NULL)
        return;
    else{
        tStackP stackP;
        tStackB stackB;
        SInitP(&stackP);
        SInitB(&stackB);                                        //vyrobíme zásobníky
        tBTNodePtr tmp;

        Leftmost_Postorder(RootPtr, &stackP, &stackB);          //projdeme uplnì vlevo

        while(!SEmptyP(&stackP)){                               //a vyprazdòujeme zásobník
            tmp = STopPopP(&stackP);
            SPushP(&stackP, tmp);                               //vyjmutý prvek vlo¾íme zpìt (chceme se na nìj jen podívat zatím)
            if(STopPopB(&stackB) == TRUE){                      //vyjmeme pøíznak
                SPushB(&stackB, FALSE);                         //je-li true, zmìníme ho na false a pokraèujeme v hledání vpravo
                Leftmost_Postorder(tmp -> RPtr, &stackP, &stackB);
            } else {                                            //je li false, vyjmeme prvek ze zásobníku a zavoláme workout
                tmp = STopPopP(&stackP);
                BTWorkOut(tmp);
            }
        }
    }

}


void BTDisposeTree (tBTNodePtr *RootPtr)	{
/*   -------------
** Zru¹í v¹echny uzly stromu a korektnì uvolní jimi zabranou pamì».
**
** Funkci implementujte nerekurzivnì s vyu¾itím zásobníku ukazatelù.
**/
    tBTNodePtr temp;
    tStackP stack;


	if((*RootPtr)==NULL)
        return;
    else{
        SInitP(&stack);
        while(!SEmptyP(&stack) || (*RootPtr) != NULL)    //dokud není zásobník prázdný nebo strom u¾ není smazaný
        {
            if((*RootPtr) == NULL)                      //kdy¾ je strom prázdný, vyjmeme poslední vlo¾ený uzel ze zásobníku
                *RootPtr = STopPopP(&stack);
            else                                        //není li prázdný, zkusme jít vlevo
            {
                if((*RootPtr) -> LPtr != NULL)
                    SPushP(&stack,(*RootPtr) -> LPtr);  //podaøí li se jít vlevo, ulo¾íme si levý uzel
                temp = (*RootPtr);
                (*RootPtr) = (*RootPtr) -> RPtr;        //pøepojíme pravý uzel
                free(temp);                             //uvolníme souèasný uzel
            }
        }
    }
	
	 //solved = FALSE;		  /* V pøípadì øe¹ení sma¾te tento øádek! */
}

/* konec c402.c */

