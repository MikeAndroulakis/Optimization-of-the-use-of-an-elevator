#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#ifdef REC
int solve(int nrid,int nst,int *dests){
	int b;
	int floor;//metablhth gia to megisto orofo
	int cost=0;
	int i;
	int nfl;//max orofos
	taksinomisi(dests,nrid);//taksinomeitai o pinakas twn stasewn
	nfl=*(dests+nrid-1);//o max orofos
	//printf("%d",*(dests+nrid-1));
	if(nst==0){//ean apo thn eisodo dothikan 0 staseis
		cost=fw(0,200000,dests,nrid);
	}
	else{//an yparxoyn j staseis diafores toy 0
		for(i=0;i<=nfl;i++){//gia kathe i apo mhden mexri nfl
			b=M(i,nst,dests,nrid,nst);//kaleitai h M kai h timh ths apothikeyetai sth b
			if((b<cost)||(i==0)){//an to kostos einai mikrotero apo to prohgoymeno h an to i=1
				floor=i;//o neos max orofos ginetai o i
				cost=b;//to neo kostos ginetai to b
			}
		}
	}
	if(nst==0){//an den yparxoyn staseis
		printf("No elevator stops\n");
	}
	else{
		printf("Last stop at floor  %d\n",floor);
	}
	return cost;//epestrepse to elaxisto kostos
}




int M(int i,int j,int *dests,int nrid,int nst){
	int g,k,num;
	int f1,f2,f3;
	int currentlesscost;
	if(j>=1){
		for(k=0;k<=i;k++){//gia kathe k apo 0 mexri i
			num=M(k,j-1,dests,nrid,nst);//kaleitai pali h M
			f1=fw(k,200000,dests,nrid);//(otan kaleitai h fw me 2o orisma 200000 thewreitai symbolika apeiro)
			f2=fw(k,i,dests,nrid);
			f3=fw(i,200000,dests,nrid);//(otan kaleitai h fw me 2o orisma 200000 thewreitai symbolika apeiro)
			g=num-f1+f2+f3;//ypologizetai to g
			if((g<currentlesscost)||(k==0)){//an to neo g einai megalytero apo to prohgoymeno kostos h to k=0
				currentlesscost=g;
			}
		}
	}
	else{//an to j ginetai 0 den exoyme allh anadromh
		return fw(0,200000,dests,nrid);
	}
	return currentlesscost;//epistrefetai to elaxisto kostos gia ayto to i
}

#endif

#ifdef MEM

int solve(int nrid,int nst,int *dests){
	int b;
	int cost;
	int maxfloor;
	int i,j;
	int nfl;
	taksinomisi(dests,nrid);//taksinomeitai o pinakas twn stasewn
	nfl=*(dests+nrid-1);//max orofos
	int **values;
	values=(int **)malloc((nfl+1)*sizeof(int *));//dhmioyrgeitai pinakas deiktwn se deiktes
	for(i=0;i<=nfl;i++){
		values[i]=(int *)malloc((nst+1)*sizeof(int ));//dhmioyrgeitai dysdiastatos pinakas
	}

	for(i=0;i<=nfl;i++){//gemizoyn oles oi times twn values me -1
		for(j=0;j<=nst;j++){
			values[i][j]=-1;
		}
	}
	
	if(nst==0){//an de kanei kamia stash
		cost=fw(0,200000,dests,nrid);	
	}
	else{
		for(i=0;i<=nfl;i++){//gia ola ta dynata i
			b=M(i,nst,dests,nrid,nst,values);//kaleitai h M
			if((b<cost)||(i==0)){//ean to b einai mikrotero apo to proigoymeno mikrotero kostos h to i=0 tote ginetai to neo kostos
				maxfloor=i;//kai o maxfloor einai to i
				cost=b;
			}
		}
	}
	if(nst==0){
		printf("No elevator stops\n");
	}
	else{
		printf("Last stop at floor %d\n",maxfloor);
	}
	
	for(i=0;i<=nfl;i++){
		free(values[i]);
	}
	return cost;
}


int M(int i,int j,int *dests,int nrid,int nst,int **values){//h M kaleitai me ton pinaka twn values
	int k;
	int a;
	int number;
	int cost;
	if(values[i][j]!=-1){//ean exei ypologistei pio prin ayth h timh toy value
		return values[i][j];//kane apla return
	}
	else if(j==0){//alliws an oi staseis einai 0
		a=fw(0,200000,dests,nrid);
		values[i][j]=a;
		return a;
	}
	else{
		for(k=0;k<=i;k++){
			number=M(k,j-1,dests,nrid,nst,values)-fw(k,200000,dests,nrid)+fw(k,i,dests,nrid)+fw(i,200000,dests,nrid);//kaleitai h M
			if((number<cost)||(k==0)){//an to number einai mikrotero apo to proigoymeno kostos ginetai to neo kostos
				cost=number;
			}
		}
		values[i][j]=cost;//arxikopeiitai ayth h thesh
		return cost;//epistrefo elaxistoy kostoys gia ayto to i
	}
}
#endif

#ifdef DP
int solve(int nrid,int nst,int *dests){
	int j,i,k;
	int **values;//pinakas gia ta values
	int cost=20000;
	int *floor;
	int cost2;
	int cost3;
	int nfl;
	int number;
	floor=(int *)malloc((nst+1)*sizeof(int));
	taksinomisi(dests,nrid);//taksinomisi pinaka
	nfl=*(dests+nrid-1);
	values=(int **)malloc((nfl+1)*sizeof(int *));//desmeyetai disdyastatos pinakas gia ta values sto heap
	int *current;//pinakas gia metafora timwn apo th floor
	current=(int *)malloc((nst+1)*sizeof(int));
	for(i=0;i<=nfl;i++){
		values[i]=(int *)malloc((nst+1)*sizeof(int));
	}
	for(i=0;i<=nfl;i++){
		for(j=0;j<=nst;j++){
			values[i][j]=0;
		}
	}
	for(j=0;j<=nst;j++){
		for(i=0;i<=nfl;i++){//gia kathe dynato max orofo 
			if(j==0){
				cost3=fw(0,200000,dests,nrid);//an to j einai 0 apla kaleitai h fw
				values[i][j]=cost3;//gemizoyme to pinaka twn values
				printf("%3d ",cost3);
			}
			else{
				for(k=0;k<=i;k++){//gia kathe dynato k
					number=values[k][j-1]-fw(k,200000,dests,nrid)+fw(k,i,dests,nrid)+fw(i,200000,dests,nrid);
					if((number<cost)||(k==0)){//gia ena sygkekrimeno j kai i,metaksy twn k briskoyme to mikrotero
						cost=number;
					}
				}
				values[i][j]=cost;
				printf("%3d ",cost);
			}
			if((i==0)||(cost<cost3)){//gia ena sygkekrimeno j metaksy twn i briskoyme to mikrotero kostos
				cost3=cost;
			}
		}
		if((cost3<cost2)||(j==0)){//metaksy twn j briskoyme to mikrotero
			cost2=cost3;
		}
		printf("\n");
	}
	int max;
	int max2;
	if(nst==0){//ean oi staseis einai 0
		printf("No elevator stops\n");
	}
	else{
		printf("Elevator stops are: ");
		for(i=0;i<=nfl;i++){//gia ola ta i
			if(((values[i][nst])<cost3)||(i==0)){//briskoyme to mikrotero value gia th teleytaia  stash
				cost3=values[i][nst];//kai to apothikeyoume sto cost3
				floor[nst]=i;//apothikeyetai o teleytaios orofos sto pinaka
			}
		}
		max=floor[nst];//to max exei to teleytaio orofo
		j=nst;
		int mini=0;
		while(j!=0){
			j-=1;
			for(k=0;k<=max;k++){//gia j-1 psaxnoyme to mikrotero k poy exei timh isi me cost3
				number=values[k][j]-fw(k,200000,dests,nrid)+fw(k,max,dests,nrid)+fw(max,200000,dests,nrid);
				if(number==cost3){//otan to broyme apothikeyoume ton epomeno orofo apo to telos
					max2=k;
					floor[j]=k;
					break;
				}
			}
			max=max2;//to max einai o proigoymenos orofos poy brikame
			for(i=0;i<=max;i++){//gia ola ta i psaxnoyme to mikrotero kostos
				number=values[i][j];
				if((i==0)||(number<cost3)){
					cost3=number;
					mini=i;//apothikeyetai h timh toy i
				}
			}
			max=mini;//to max ginetai h timh toy proigoymenoy orofoy poy brethike to elaxisto
		}
		int elegxos=0;
		
		for(i=0;i<=nst;i++){
			current[i]=0;//gemizoyn me 0 oles oi theseis
		}
		for(j=1;j<=nst;j++){//se ayth th for etaferontai oi times toy pinaka ths floor,sthn current,wste an yparxoyn koines staseis 
			for(i=0;i<=nst;i++){//na mh typwthoyn polles fores
				if((current[i]==floor[j])&&(current[i]!=0)){//an yparxei koinh stash
					elegxos=1;//o elegxos ginetai 1
				}
			}
			if((elegxos==0)&&(floor[j]!=0)){//an de brethike koinh stash gia ayto to j tote ginetai arxikopoihsh toy current
				current[j]=floor[j];
				printf("%d ",floor[j]);
			}
			if(j==nst){
				printf("\n");
			}
			elegxos=0;//o elegxos mhdenizetai gia thn epomenh epanalipsi
		}
	}
	for(i=0;i<=nst;i++){
		free(values[i]);//ginetai free toy dysdiastatou pinaka
	}
	free (floor);
	free(current);
	return cost2;
}

#endif

#ifdef BF
int solve(int nrid,int nst,int *dests){
	int i;
	int cost=0;
	int *floor;
	floor=(int *)malloc((nst+1)*sizeof(int));//desmeyetai pinakas gia ta floors
	taksinomisi(dests,nrid);//taksinomeitai o pinakas twn stasewn
	/*int *current;
	current=(int *)malloc((nst+1)*sizeof(int));//desmeyetai  pinakas gia  sto heap
	int *best;
	best=(int *)malloc((nst+1)*sizeof(int));*/
	if(nst==0){//ean den exoyme staseis
		for(i=0;i<nrid;i++){
			cost+=*(dests+i);//ypologizetai to kostos poy prepei n perpatisoyn oloi oi epibates
		}
		printf("No elevator stops\n");
	}
	else{
		cost=brute(1,nst,nrid,dests,floor,nst);//kaleitai h brute
		printf("Elevator stops are: ");
		printf("\n");
	}
	free(floor);
	return cost;
}


int brute(int i,int j,int nrid,int *dests,int *floor,int staseis){
	int k,l,p;
	int cost=0;
	int cost2=0;
	int cost3;
	int number;
	int nfl=*(dests+nrid-1);//maxfloor twn epibatwn
	if(j!=0){
		j=j-1;
		for(k=i;k<=nfl;k++){//apo i(poy kalesthke h brute) mexri nfl briskoyme to elaxisto kostos
			floor[j]=k;//apothikeyetai h timh ths trexoysas epanalipsis
			number=brute(k,j,nrid,dests,floor,staseis);//kaleitai h brute pali wste na elegxthoyn oles oi periptwseis
			if((k==i)||(number<cost3)){//briskoyme to elaxisto sygkrinontas ta me tis proigoymenes times poy gyrise h brute
				cost3=number;
				/*current[j+1]=k;
				for(p=0;p<=(j+1);p++){
					best[p]=current[p];
				}*/
			}
		}
		return cost3;
	}
	else{//an eimaste gia j=0
		for(k=i;k<=nfl;k++){//apo i(poy kalesthke h brute) mexri nfl briskoyme to elaxisto kostos
			floor[j]=k;//apothikeytai h timh toy k
			for(l=(staseis-1);l>=0;l--){//ginetai epanalipsi gia na perastei olos o pinakas ths floor
				for(p=0;p<nrid;p++){//gia ola ta atoma
					if((l==(staseis-1))&&(*(dests+p)<floor[staseis-1])){//an eimaste sth prwth stash toy asanser kai h stash aytoy toy epibath brisketai katw apo th prwth stash toy asanser
						if(*(dests+p)<((floor[staseis-1])-*(dests+p))){//an brisketai kontitera sto 0
							cost+=*(dests+p);//paei me ta podia
						}
						else{//alliws
							cost+=floor[staseis-1]-*(dests+p);//paei apo th prwth stash sto proorismo toy
						}
					}
					else if((l==0)&&(*(dests+p)>(floor[0]))){//an eimaste sth teleytaia stash kai h stash aytoy toy epibath brisketai psilotera
						cost+=*(dests+p)-floor[0];//tote to kostos ayksanetai toso oso einai h metakinhsh toy apo to teleytaio orofo sth stash toy
					}
					else{//alliws an eimaste se endiameses staseis
						if((*(dests+p)>floor[l])&&(*(dests+p)<=floor[l-1])){//an h stash toy epibath brisketai metaksy twn dyo aytwn stasewn toy anelkysthra
							if((*(dests+p)-floor[l])<(floor[l-1]-*(dests+p))){//an brisketai pio konta sth katw stash
								cost+=*(dests+p)-floor[l];
							}
							else{//alliws an brisketai pio konta sth panw stash
								cost+=floor[l-1]-*(dests+p);
							}
						}
					}
				}
			}
			if((k==i)||(cost<cost2)){//ean exoyme prwth epanalipsi h brethike mikrotero kostos tote
				cost2=cost;//to kostos allazei
				//current[0]=k;
			}
		}
		return cost2;//epistrofh toy elaxistoy kostoys
	}
}

#endif



int fw(int a,int b,int *dests,int nrid){
	int i;
	int cost=0;
	if(a<b){//ean exei nohma h fw dld to a<b
		for(i=0;i<nrid;i++){//elegxontai oles oi staseis twn epibatwn
			if(b!=200000){//an to deytero orisma den einai apeiro(symbolika)
				if((*(dests+i)>a)&&(*(dests+i)<=b)){//elegxetai an brisketai panw apo to a kai mexri kai to b
					if((*(dests+i)-a)<(b-*(dests+i))){//an brisketai pio konta sto a
						cost+=*(dests+i)-a;//tote ypologizetai to kostos ths metakinisis toy epibath apo th stash toy sto a
				
					}
					else{//alliws ypoligizetai to kostos metakinisis apo th stash toy sto b
						cost+=b-*(dests+i);
					}
				}
			}
			else if(b==200000){//an to b einai apeiro
				for(i=0;i<nrid;i++){//gia olous toys epibates
					if((*(dests+i))>a){//elegxetai an h stash toys brisketai panw apo thn a
						cost+=*(dests+i)-a;//kai an briskete ypologizetai to kostos metakinishs apo th stash toys sthn a
					}
				}
			}
		}
	}
	return cost;
}
void taksinomisi(int *dests,int nrid){
	int metritis=0;
	int elegxos=0;
	int i,a,b;
	while(metritis!=(nrid-1)){//oso den exei taksinomithei o pinakas
		for(i=0;(i<nrid-1);i++){//kanoyme (atoma-1) epanalipseis
			if(*(dests+i)<=(*(dests+(i+1)))){//an o orofos poy thelei na katebei o i epibatis einai mikroteros apo ton orofo toy i+1
				if(elegxos==0){//kai an o elegxos den einai mhden
					metritis++;//ayksise to metriti
				}
			}
			else{//alliws o elegxos ginetai 1 wste na mhn ksanayksithei o metritis
				elegxos=1;
				metritis=0;//o metritis mhdenizetai gia thn epomenh epanalipsi
				a=*(dests+i);//oi dyo orofoi allazoyn seires wste na prohgeitai o mikroteros
				b=*(dests+(i+1));
				*(dests+i)=b;
				*(dests+(i+1))=a;
			}
		}
		elegxos=0;//o elegxos ginetai mhden gia thn epomenh epanalipsi
	}
}



