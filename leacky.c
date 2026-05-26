#include<stdio.h>
int main()
{
	int bucket_size,incoming_pkt,store=0,outgoing_rate,input,i,j;
	printf("enter the bucket_size : ");
	scanf("%d",&bucket_size);
	printf("enter the outgoing rate : ");
	scanf("%d",&outgoing_rate);
	printf("enter the inputs : ");
	scanf("%d",&input);
	for(i=1;i<=input;i++)
	{
		printf("input %d\n",i);
		int dropped=0;
		printf("enter the pkt : ");
		scanf("%d",&incoming_pkt);
		for(j=0;j<incoming_pkt;j++)
		{
			if(store<bucket_size)
			{
				store++;
				printf("Bucket occupancy is %d,%d\n",store,bucket_size);
			}
			else
			{
				dropped++;
				printf("dropped 1 pkt \n");
			}
		}
		int transmitted=(store<outgoing_rate)?store:outgoing_rate;
		store-=transmitted;
		printf("Transmitted pkt from bucket : %d\n",transmitted);
		printf("Bucket occupancy is %d,%d\n",store,bucket_size);
		printf("pkts dropped : %d\n",dropped);
		
	}
	printf("simulation complete\n");
	printf("final state\n");
	printf("Bucket occupancy is %d,%d",store,bucket_size);
}
