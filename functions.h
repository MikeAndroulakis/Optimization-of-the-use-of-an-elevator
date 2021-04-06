void taksinomisi(int *dests,int nrid);
int fw(int a,int b,int *dests,int nrid);//synarthseis poy isxyoun kai stis 3 periptwseis
int solve(int nrid,int nst,int *dests);
#ifdef REC
int M(int i,int j,int *dests,int nrid,int nst);//synarthsh M gia to REC
#endif

#ifdef MEM
int M(int i,int j,int *dests,int nrid,int nst,int **values);//synarthsh M gia to MEM
#endif

#ifdef BF
int brute(int i,int j,int nrid,int *dests,int *floor,int staseis);
#endif

