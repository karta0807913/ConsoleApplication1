int gcd(int n,int m){
	if(m == 0)
		return n;
	gcd(m,n%m);
}