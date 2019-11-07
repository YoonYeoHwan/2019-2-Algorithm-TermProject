#include <ncurses.h>
#include "PushBoxGame.h"
#include "map.h"

int (*PushBoxGame::getMap())[10]{
    return map_arr;
}

void PushBoxGame::setMap(int level){
    if(level==1) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
    else if(level==2) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
    else if(level==3) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
    else if(level==4) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
    else if(level==5) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
    else if(level==6) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
    else if(level==7) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
    else if(level==8) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
    else if(level==9) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
    else if(level==10) {
        m.set_map(map_arr,level,a,b,goalCount);
        mvwprintw(win_level,2,3,"%d",level);
        wrefresh(win_level);
    }
}

void PushBoxGame::newGame(int map[][10]){
    game_map=newwin(12,14,10,7);
    wborder(game_map,'|','|','-','-','+','+','+','+');
    for(int i=0;i<=9;i++){
        for(int j=0;j<=9;j++){
            if(map[i][j]==1){
                wattron(game_map,COLOR_PAIR(1));
                mvwprintw(game_map,i+1,j+3,"#");
                wattroff(game_map,COLOR_PAIR(1));
            }
            else if(map[i][j]==2) mvwprintw(game_map,i+1,j+3,"*");
            else if(map[i][j]==3) mvwprintw(game_map,i+1,j+3,"@");
            else mvwprintw(game_map,i+1,j+3," ");
        }
    }
    mvwprintw(game_map,a,b,"O");
    wrefresh(game_map);
}

void PushBoxGame::moveUP(int map[][10]){
    int up=a-2; 
    int up2=a-3; 
    if(map[up][b-3]==Wall) return;
    else if(map[up][b-3]==Box){ 
        if(map[up2][b-3]==Wall) return; 
        else if(map[up2][b-3]==Box || map[up2][b-3]==BoxOnGoal) return; 
        else{
            if(map[up2][b-3]==Goal) {
                s.pushUp();
                mvwprintw(game_map,a-2,b,"*");
                map[up2][b-3]=BoxOnGoal; 
                map[up][b-3]=Space;
            }
            else {
                s.pushUp(); 
                mvwprintw(game_map,a-2,b,"*");
                map[up2][b-3]=Box;
                map[up][b-3]=Space;
            }
        }
    }
    else if(map[up][b-3]==BoxOnGoal) {
        if(map[up2][b-3]==Wall) return; 
        else if(map[up2][b-3]==Box || map[up2][b-3]==BoxOnGoal) return; 
        else {
            if(map[up2][b-3]==Goal) {
                s.pushUp(); 
                mvwprintw(game_map,a-2,b,"*");
                map[up2][b-3]=BoxOnGoal; 
                map[up][b-3]=Goal;
            }

            else {
                s.pushUp();
                mvwprintw(game_map,a-2,b,"*");
                map[up2][b-3]=Box;
                map[up][b-3]=Goal;
            }
        }

    }
    if(map[a-1][b-3]==Goal) mvwprintw(game_map,a,b,"@");
    else if(map[a-1][b-3]==Space) mvwprintw(game_map,a,b," ");
    a--;
    s.stepUp();
    mvwprintw(game_map,a,b,"O");
    stepRefresh(win_step,s.getStep());
    pushRefresh(win_push,s.getPush());
    wrefresh(game_map);
}
void PushBoxGame::moveDOWN(int map[][10]){
    int down=a; 
    int down2=a+1; 
    if(map[down][b-3]==Wall) return; 
    else if(map[down][b-3]==Box){ 
        if(map[down2][b-3]==Wall) return; 
        else if(map[down2][b-3]==Box || map[down2][b-3]==BoxOnGoal) return;  
        else{
            if(map[down2][b-3]==Goal) { 
                s.pushUp();
                mvwprintw(game_map,a+2,b,"*");
                map[down2][b-3]=BoxOnGoal; 
                map[down][b-3]=Space;
            }
            else { 
                s.pushUp();
                mvwprintw(game_map,a+2,b,"*");
                map[down2][b-3]=Box;
                map[down][b-3]=Space;
            }
        }
    }
    else if(map[down][b-3]==BoxOnGoal) {
        if(map[down2][b-3]==Wall) return; 
        else if(map[down2][b-3]==Box || map[down2][b-3]==BoxOnGoal) return; 
        else {
            if(map[down2][b-3]==Goal) { 
                s.pushUp();
                mvwprintw(game_map,a+2,b,"*");
                map[down2][b-3]=BoxOnGoal; 
                map[down][b-3]=Goal;
            }
            else {
                s.pushUp();
                mvwprintw(game_map,a+2,b,"*");
                map[down2][b-3]=Box;
                map[down][b-3]=Goal;
            }
        }

    }

    if(map[a-1][b-3]==Goal) mvwprintw(game_map,a,b,"@");
    else if(map[a-1][b-3]==Space) mvwprintw(game_map,a,b," ");
    a++;
    s.stepUp();
    mvwprintw(game_map,a,b,"O");
    stepRefresh(win_step,s.getStep());
    pushRefresh(win_push,s.getPush());
    wrefresh(game_map);
}

void PushBoxGame::moveLEFT(int map[][10]){
    int left=b-4; 
    int left2=b-5; 
    if(map[a-1][left]==Wall) return; 
    else if(map[a-1][left]==Box){ 
        if(map[a-1][left2]==Wall) return; 
        else if(map[a-1][left2]==Box || map[a-1][left2]==BoxOnGoal) return; 
        else{
            if(map[a-1][left2]==Goal) {
                s.pushUp(); 
                mvwprintw(game_map,a,b-2,"*");
                map[a-1][left2]=BoxOnGoal; 
                map[a-1][left]=Space;
            }
            else { 
                s.pushUp();
                mvwprintw(game_map,a,b-2,"*");
                map[a-1][left2]=Box;
                map[a-1][left]=Space;
            }
        }
    }
    else if(map[a-1][left]==BoxOnGoal) {
        if(map[a-1][left2]==Wall) return; 
        else if(map[a-1][left2]==Box || map[a-1][left2]==BoxOnGoal) return;
        else {
            if(map[a-1][left2]==Goal) { 
                s.pushUp();
                mvwprintw(game_map,a,b-2,"*");
                map[a-1][left2]=BoxOnGoal; 
                map[a-1][left]=Goal;
            }

            else {
                s.pushUp();
                mvwprintw(game_map,a,b-2,"*");
                map[a-1][left2]=Box;
                map[a-1][left]=Goal;
            }
        }

    }
    if(map[a-1][b-3]==Goal) mvwprintw(game_map,a,b,"@");
    else if(map[a-1][b-3]==Space) mvwprintw(game_map,a,b," ");
    b--;
    s.stepUp();
    mvwprintw(game_map,a,b,"O");
    stepRefresh(win_step,s.getStep());
    pushRefresh(win_push,s.getPush());
    wrefresh(game_map);
}

void PushBoxGame::moveRIGHT(int map[][10]){
    int right=b-2; 
    int right2=b-1;
    if(map[a-1][right]==Wall) return;
    else if(map[a-1][right]==Box){ 
        if(map[a-1][right2]==Wall) return; 
        else if(map[a-1][right2]==Box || map[a-1][right2]==BoxOnGoal) return; 
        else{
            if(map[a-1][right2]==Goal) { 
                s.pushUp();
                mvwprintw(game_map,a,b+2,"*");
                map[a-1][right2]=BoxOnGoal; 
                map[a-1][right]=Space;
            }
            else { 
                s.pushUp();
                mvwprintw(game_map,a,b+2,"*");
                map[a-1][right2]=Box;
                map[a-1][right]=Space;
            }
        }
    }
    else if(map[a-1][right]==BoxOnGoal) {
        if(map[a-1][right2]==Wall) return; 
        else if(map[a-1][right2]==Box || map[a-1][right2]==BoxOnGoal) return;
        else {
            if(map[a-1][right2]==Goal) {
                s.pushUp();
                mvwprintw(game_map,a,b+2,"*");
                map[a-1][right2]=BoxOnGoal;
                map[a-1][right]=Goal;
            }

            else { 
                s.pushUp();
                mvwprintw(game_map,a,b+2,"*");
                map[a-1][right2]=Box;
                map[a-1][right]=Goal;
            }
        }

    }
    if(map[a-1][b-3]==Goal) mvwprintw(game_map,a,b,"@");
    else if(map[a-1][b-3]==Space) mvwprintw(game_map,a,b," ");
    b++;
    s.stepUp();
    mvwprintw(game_map,a,b,"O");
    stepRefresh(win_step,s.getStep());
    pushRefresh(win_push,s.getPush());
    wrefresh(game_map);
}

bool PushBoxGame::finishGame(){
    int cnt=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(map_arr[i][j]==5) cnt++;
        }
    }
    if(goalCount==cnt) return true;
    else return false;
}
void PushBoxGame::stepRefresh(WINDOW *win,int step){
    mvwprintw(win,2,3,"%d",step);
    wrefresh(win_step);
}
void PushBoxGame::pushRefresh(WINDOW *win,int push){
    mvwprintw(win,2,3,"%d",push);
    wrefresh(win_push);
}

void PushBoxGame::lifeRefresh(){
    s.lifeDown();
    mvwprintw(win_life,2,3,"%d",s.getLife());
    wrefresh(win_life);
}
int PushBoxGame::getlife(){
    return s.getLife();
}

void PushBoxGame::clearMap(int level) {
    int nowScore = (level * 200 + s.getLife() * 200) - (s.getPush() * 5 + s.getStep() * 3);
    win_clear=newwin(27,27,0,0);
    wattron(win_clear,COLOR_PAIR(2));
    wborder(win_clear,'*','*','*','*','*','*','*','*');
    mvwprintw(win_clear, 5, 6, "CONGRATULATIONS!");
    mvwprintw(win_clear, 12, 7, "YOUR SCORE IS");
    mvwprintw(win_clear, 14, 9, "%d POINT", nowScore);
    mvwprintw(win_clear, 20, 7, "PRESS ANY KEY");
    mvwprintw(win_clear, 22, 5, "TO PLAY NEXT LEVEL");
    wattroff(win_clear,COLOR_PAIR(2));        
    refresh();
    wrefresh(win_clear);
    delwin(win_clear);
    getch();
}

void PushBoxGame::reloadMap() {
    resize_term(27,27);
    attron(COLOR_PAIR(2));
    border('*','*','*','*','*','*','*','*');
    mvprintw(2,7,"push box game");
    attroff(COLOR_PAIR(2));
    win_level=newwin(4,7,4,2);
    wborder(win_level,'|','|','-','-','+','+','+','+');
    mvwprintw(win_level,1,1,"Level");
    win_push=newwin(4,7,4,10);
    wborder(win_push,'|','|','-','-','+','+','+','+');
    mvwprintw(win_push,1,1,"Push");
    mvwprintw(win_push,2,3,"%d",s.getPush());
    win_step=newwin(4,7,4,18);
    wborder(win_step,'|','|','-','-','+','+','+','+');
    mvwprintw(win_step,1,1,"Step");
    mvwprintw(win_step,2,3,"%d",s.getStep());
    win_life=newwin(4,7,22,10);
    wborder(win_life,'|','|','-','-','+','+','+','+');
    mvwprintw(win_life,1,1,"Life");
    mvwprintw(win_life,2,3,"%d",s.getLife());
    refresh();
    wrefresh(win_life);
    wrefresh(win_push);
    wrefresh(win_step);
}

void PushBoxGame::ending(int level) {
    int nowScore = (level * 200 + s.getLife() * 200) - (s.getPush() * 5 + s.getStep() * 3);
    win_end=newwin(27,27,0,0);
    wattron(win_end,COLOR_PAIR(2));
    wborder(win_end,'*','*','*','*','*','*','*','*');
    mvwprintw(win_end, 5, 6, "CONGRATULATIONS!");
    mvwprintw(win_end, 6, 4, "YOU CLEAR ALL LEVEL!");
    mvwprintw(win_end, 12, 7, "YOUR SCORE IS");
    mvwprintw(win_end, 14, 9, "%d POINT", nowScore);
    mvwprintw(win_end, 20, 7, "PRESS ANY KEY");
    mvwprintw(win_end, 22, 8, "TO EXIT GAME");
    wattroff(win_end,COLOR_PAIR(2));        
    refresh();
    wrefresh(win_end);
    getch();
}

void PushBoxGame::gameover(int level) {
    int nowScore = (level * 200 + s.getLife() * 200) - (s.getPush() * 5 + s.getStep() * 3);
    win_over=newwin(27,27,0,0);
    wattron(win_over,COLOR_PAIR(2));
    wborder(win_over,'*','*','*','*','*','*','*','*');
    mvwprintw(win_over, 5, 9, "GAME OVER!");
    mvwprintw(win_over, 12, 4, "YOUR TOTAL SCORE IS");
    mvwprintw(win_over, 14, 9, "%d POINT", nowScore);
    mvwprintw(win_over, 20, 7, "PRESS ANY KEY");
    mvwprintw(win_over, 22, 8, "TO EXIT GAME");
    wattroff(win_over,COLOR_PAIR(2));        
    refresh();
    wrefresh(win_over);
    getch();
}