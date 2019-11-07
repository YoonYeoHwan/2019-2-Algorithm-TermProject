#include "PushBoxGame.h"

int main(){
    PushBoxGame g;
    int level=1;
    while(1){
        bool checkF1 = false;

        if(level==10){
            g.ending(level);
            getch();
            endwin();
            break;
        }
        g.setMap(level++);
        g.newGame(g.getMap());
        while(true){
            int inputKey=getch();
            if(inputKey==KEY_F(1)){
                g.lifeRefresh();
                g.setMap(--level);
                g.newGame(g.getMap());
                checkF1 = true;
                break;
            }
            if(inputKey==KEY_UP){
                g.moveUP(g.getMap());
                if(g.finishGame()) {
                    checkF1 = false;
                    break;
                }
            }
            else if(inputKey==KEY_DOWN){
                g.moveDOWN(g.getMap());
                if(g.finishGame()) {
                    checkF1 = false;
                    break;
                }
            }
            else if(inputKey==KEY_RIGHT){
                g.moveRIGHT(g.getMap());
                if(g.finishGame()) {
                    checkF1 = false;
                    break;
                }
            }
            else if(inputKey==KEY_LEFT){
                g.moveLEFT(g.getMap());
                if(g.finishGame()) {
                    checkF1 = false;
                    break;
                }
            }
        }
        if(level!=10 && checkF1==false) {
            g.clearMap(level);
            g.reloadMap();
        }
        if(g.getlife()==0){
            g.gameover(level);            
            getch();
            break;
        }
    }
    return 0;
}
