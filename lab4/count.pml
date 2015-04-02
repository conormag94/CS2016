int n = 0;
int finished = 0;

proctype P() {

	int temp = 0;
	int i = 0;
	for(i : 1..10){
		temp = n;
		n = temp + 1;
	}

	finished = finished + 1;

}

proctype Q() {

	int temp = 0;
	int i = 0;
	for(i:1..10){
		temp = n;
		n = temp + 1;
	}
	finished = finished + 1;
}

init {
	printf("Starting again\n");
	n = 0;
	run P();
	run Q();
	(finished == 2);
	assert(n!=2);					
}
