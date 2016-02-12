int three_n_plass_one(int input){
	int output = 1;
	while(input != 1){
		if(input %2 == 0)
			input /=2;
		else
			input = input*3+1;
		output ++;
	}
	return output;
}