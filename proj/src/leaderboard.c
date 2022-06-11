#include "leaderboard.h"
#include "pause.h"

extern enum STATE GameState;
extern uint8_t *BoardMenu;
extern xpm_image_t imgBoard;

int leaderboard(SnakeBody snake) {

    FILE *fptr;
    char * buffer = 0;
    long length;
    size_t size;
    int scores[5];

    fptr = fopen("/home/lcom/labs/g04/proj/src/leaderboard.txt","r");

   if (fptr)
        {
        fseek (fptr, 0, SEEK_END);
        length = ftell (fptr);
        fseek (fptr, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread (buffer, 1, length, fptr);
        }
            fclose(fptr);
        }

        if (buffer)
        {
            int i = 0;
            char* auxStr =  malloc(65536);
            char *p1, *p2;
            while(1) {
                p1 = strstr(buffer, "-");
                if (p1) {
                    p2 = strstr(buffer, "\n");
                    if (p2){
                        size = p2-p1;
                        memset(auxStr,0,65536);
                        memcpy(auxStr,(p1+2),size-2);
                        scores[i] = atoi(auxStr);
                        buffer = p2+1;
                        i++;
                    } else {
                        size = strlen(p1) - 1;
                        memset(auxStr,0,65536);
                        memcpy(auxStr,(p1+2),size);
                        scores[i] = atoi(auxStr);
                        break;
                    }
                }
                else {
                    break;
                }
            }
        }

    fptr = fopen("/home/lcom/labs/g04/proj/src/leaderboard.txt","w");
    int j = 0;
    int vsize = 5;
    for(int i = 0; i < vsize; i++) {
        if(snake.bodySize > scores[i]) {
            fprintf(fptr,"%d - %d\n",j+1,snake.bodySize);
            snake.bodySize = 0;
            i--;
            j++;
            vsize--;
        } else {
            fprintf(fptr,"%d - %d\n",j+1,scores[i]);
            j++;
        }
    }

    //printf com o resultado do jogador

    fclose(fptr);
    return 0;
}


void BoardTimerHandler() {
}

void BoardHandlerKBC(enum KEY k) {
  switch (k)
  {
  case ESC:
    GameState = MENU;
    break;
  default:
    break;
  }
}

void drawDefBoard() {
  draw_pix_map(0,0,BoardMenu,imgBoard);
}

void drawBoard() {
}
