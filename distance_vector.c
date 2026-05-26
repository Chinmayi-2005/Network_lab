#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define max_node 10
#define INFINITY INT_MAX

struct Node
{
	int dist[max_node];
	int next_hop[max_node];
};
void initialize(struct Node nodes[],int num_node)
{
	int i,j;
	for(i=0;i<num_node;i++)
	{
		for(j=0;j<num_node;j++)
		{
			if(i==j)
			{
				nodes[i].dist[j]=0;
				nodes[i].next_hop[j]=j;
			}
			else
			{
				nodes[i].dist[j]=INFINITY;
				nodes[i].next_hop[j]=-1;
			}
		}
	}
}
void printing_routingtable(struct Node nodes[],int num_node)
{
	int i,j,k;
	for(i=0;i<num_node;i++)
	{
		printf("routing table for %d\n",i);
		printf("dest\tdist\tnext hop\n");
		for(j=0;j<num_node;j++)
		{
			printf("%d\t\t",j);
			if(nodes[i].dist[j]==INFINITY)
			{
				printf("INF\t\t");
			}
			else
			{
				printf("%d\t\t",nodes[i].dist[j]);
			}
			printf("%d\n",nodes[i].next_hop[j]);
		}//printf("\n");
	}
}
void update_routingtable(struct Node nodes[],int num_node,int adj_matrix[][max_node])
{
	int updated,i,j,k;
	int iteration=0;
	do
	{
		updated=0;
		iteration++;
		for(i=0;i<num_node;i++)
		{
			for(j=0;j<num_node;j++)
			{
				if(i!=j&&adj_matrix[i][j]!=INFINITY)
				{
					for(k=0;k<num_node;k++)
					{
						if(nodes[j].dist[k]==INFINITY)
						{
							continue;
						}
						if(nodes[i].dist[k]>nodes[j].dist[k]+adj_matrix[i][j])
						{
							nodes[i].dist[k]=nodes[j].dist[k]+adj_matrix[i][j];
							nodes[i].next_hop[k]=j;
							updated=1;
						}
					}
				}
			}
		}
		printf("\nAfter iteration %d\n",iteration);
		printing_routingtable(nodes,num_node);
		
	}while(updated);
}
int main()
{
	struct Node nodes[max_node];
	int num_node,i,j,k;
	int adj_matrix[max_node][max_node];
	printf("enter the num of maximum nodes : ");
	scanf("%d",&num_node);
	printf("enter the adj matrix (use %d for infinity)\n",INFINITY);
	for(i=0;i<num_node;i++)
	{
		for(j=0;j<num_node;j++)
		{
			scanf("%d",&adj_matrix[i][j]);
			if(i==j)
			{
				adj_matrix[i][j]=0;
			}
		}
	}
	initialize(nodes,num_node);
	for(i=0;i<num_node;i++)
	{
		for(j=0;j<num_node;j++)
		{
			//scanf("%d",adj_matrix[i][j]);
			if(adj_matrix[i][j]!=INFINITY && i!=j)
			{
				nodes[i].dist[j]=adj_matrix[i][j];
				nodes[i].next_hop[j]=j;
			}
		}
	}
	printf("initial routing tables\n");
	printing_routingtable(nodes,num_node);
	update_routingtable(nodes,num_node,adj_matrix);
	printf("final routing tables\n");
	printing_routingtable(nodes,num_node);
}
