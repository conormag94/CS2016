int n = 0;
bool finished = false;

proctype P() {

	finished = false;
	int temp = 0;
	int i = 0;
	for(i : 1..10){
		temp = n;
		n = temp + 1;
	}

	finished = true;

}

proctype Q() {

	finished = false;
	int temp = 0;
	int i = 0;
	for(i:1..10){
		temp = n;
		n = temp + 1;
	}
	finished = true;
}

init {
	do
	:: n!=2 ->
		printf("Starting again\n");
		n = 0;
		run P();
		run Q();
		if
		:: finished == true -> assert(n!=2);
		fi
	od
		
	printf("result = %d\n", n);
}
