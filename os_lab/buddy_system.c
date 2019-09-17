  #include <stdio.h>

typedef struct X 
{
    unsigned int address;
    int empty;
    int id_req;//id_req
    int allow;
} Block;

typedef struct Y  
{
    int enz;
    int id_req;//req_id
    int ok;
} Defer;

unsigned int block_sizes[8] = {0};
unsigned int memSize;
unsigned int allcSize;

Block blocks[8][128];
int num_blocks[8];

int defer_pointer = 0;
Defer defers[100];

int main(int argc, char **argv)
{
    int x, y, z; 

    for(x = 0;x < 100;x++)
        defers[x].ok = 1;

    for(x = 0;x < 8;x++)
        for(y = 0;y < 128;y++)
            blocks[x][y].empty = blocks[x][y].allow = 0;

    scanf("%u", &memSize);
    scanf("%u", &allcSize);

    block_sizes[0] = allcSize;
    for(x = 0;x+1 < 8;x++)
        if(block_sizes[x] == memSize)
            break;
        else
            block_sizes[x+1] = block_sizes[x]*2;

    blocks[x][0].address = 0;
    blocks[x][0].empty = 1;
    num_blocks[x] = 1;
    for(;x > 0;x--)
    {
        num_blocks[x-1] = num_blocks[x]*2;

        for(y=0;y < num_blocks[x];y++)
        {
            blocks[x-1][2*y].address = blocks[x][y].address;
            blocks[x-1][2*y+1].address = blocks[x][y].address + block_sizes[x-1];
        }
    }

    while(scanf("%d", &z) != EOF)
    {
        char op = getchar();
        while(op != '-' && op != '+') op = getchar();

        if(op == '+')
        {
            unsigned int size;
            scanf("%u", &size);
            printf("Request ID %d: allocates %u byte%s.\n", z, size, size == 1 ? "" : "s");

            int enz = 0;
            while(block_sizes[enz] < size)
                enz++;

            unsigned int address;
            if(allocate(enz, z, &address)) 
            {
                printf("\tSuccess; addr = 0x%08x.\n", address);
            }
            else
            {
                printf("\tRequest deferred.\n");
                defers[defer_pointer].ok = 0;
                defers[defer_pointer].enz = enz;
                defers[defer_pointer].id_req = z;
                defer_pointer++;
            }
        }
        else
        {
            printf("Request ID %d: deallocate.\n", z);

            int success = 0;
            for(x = 0;x < 8 && block_sizes[x] != 0 && success != 1;x++)
                for(y = 0;y < num_blocks[x] && success != 1;y++)
                    if(blocks[x][y].allow)

                        if (blocks[x][y].id_req == z)
                        {
                            blocks[x][y].allow = 0;
                            blocks[x][y].empty = 1;
                            success = 1;
                        }

            x--;y--;

            if(success)
                printf("\tSuccess.\n");
            else
                continue;
            // the buddy system

            while(x < 8 && num_blocks[x] > 1)
            {
                int buddy = (blocks[x][y].address / block_sizes[x]) %2 == 0 ? (y+1) : (y-    1);

                if(blocks[x][buddy].empty)
                {
                    blocks[x][y].empty = 0;
                    blocks[x][buddy].empty = 0;

                    blocks[x+1][y/2].empty = 1;
                    x++;
                    y /= 2;
                }
                else
                {
                    break;
                }
            }

            for(x = 0;x < defer_pointer;x++)
                if(!defers[x].ok)
                {
                    unsigned int address;
                    if(allocate(defers[x].enz, defers[x].id_req, &address))
                    {
                        defers[x].ok = 1;
                        printf("\tDeferred request %d allocated; addr = 0x%08x\n", defers[x].id_req, address);
                    }
                }
        }
    }

    return 0;
}

int allocate(int enz, int id_req, unsigned int *address)
{
    int x, y, ret = 0;
    for(x = enz;x < 8 && block_sizes[x] != 0 && ret == 0;x++)
        for(y = 0;y < num_blocks[x] && ret == 0;y++)
            if(blocks[x][y].empty)
                ret = 1;
    x--;y--;
    if(ret == 0)
        return 0;

    while(x != enz)
    {
        blocks[x][y].empty = 0;

        blocks[x-1][2*y].empty = 1;
        blocks[x-1][2*y+1].empty = 1;

        x = x-1;
        y = 2*y;
    }

    blocks[x][y].empty = 0;
    blocks[x][y].id_req = id_req;
    blocks[x][y].allow = 1;
    *address = blocks[x][y].address;
}