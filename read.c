#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main (int argc, char **argv) {
	FILE *fp;
	unsigned char buf[1024];
	int i;

	if(argc<=1) {
		printf("Usage: %s <plot filename>\n", argv[0]);
		exit(0);
	}
	
	fp=fopen(argv[1],"r");
	if(!fp) {
		printf("Cannot open input file for reading.\n");
		exit(1);
	}
	
	bzero(buf,1024);
	fread(buf,19,1,fp);
	printf("File type: %s\n",buf);

	fread(buf,32,1,fp);
	printf("PlotID: ");
	for(i=0;i<32;i++) printf("%02x",buf[i]);
	printf("\n");

	fread(buf,1,1,fp);
	printf("k size: %d\n",buf[0]);

	fread(buf,2,1,fp);
	i=buf[1];

	bzero(buf,1024);
	fread(buf,i,1,fp);
	printf("Version: %s\n",buf);

	fread(buf,2,1,fp);
	if(buf[1]!=128) {
		printf("Unsupported memo size.\n");
		exit(1);
	}

	fread(buf,128,1,fp);
	printf("Pool public key: ");
	for(i=0;i<128;i++) {
		if(i==48)printf("\nFarmer public key: ");
		if(i==96)printf("\nLocal sk: ");
		printf("%02x",buf[i]);
	}
	printf("\n");
	fclose(fp);
}
