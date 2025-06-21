/*
 * Dexter’s License v-1.0
 *
 * Curiosity is the zero-day of the soul.
 *
 * Use at your own risk: no docs, no warranty, just raw source.
 * Break things. Patch them. Share exploits.
 *
 * © Dexter — segfaulting reality since boot.
 *
 * P.S. Trust was never in the protocol.
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>


// Maze dimensions/settings
#define WIDTH  41
#define HEIGHT 21
#define DELAY  100
#define NUM_ITEMS 5
#define NUM_ENEMIES 3
#define NUM_TELEPORTS (16/2) // 8 pairs

// --- Vulnerability & Teleport array ---
int maze_escape[16]; // holds x,y coords pairs for 8 teleporters

static const int DX[4] = {0,1,0,-1};
static const int DY[4] = {-1,0,1,0};

typedef struct {int x,y;} Position;
typedef struct {Position pos;int alive;} Enemy;

static int maze[HEIGHT][WIDTH];
static Position items[NUM_ITEMS];
static Enemy enemies[NUM_ENEMIES];
static Position player, goal;
static int score=0, steps=0;
static time_t start_time;

// prototypes
void init_ncurses();
void cleanup();
void generate_maze(int cx,int cy);
void place_items_goal_and_teleports();
void init_enemies();
void draw();
void handle_input(int ch);
void update_enemies();
int is_valid(int x,int y);
void game_loop();

int main() {
    printf("The maze begins at this location, your journey starts here @ %p\n",&main);
    int coordinates, slot;
    setbuf(stdin,NULL);
    setbuf(stdout,NULL);
    alarm(0x20);
    printf("Configure coordinates (0 >=) : ");
    scanf("%d", &coordinates);
    printf("Set slot value (10 >=) : ");
    scanf("%d", &slot);
    maze_escape[coordinates] = slot; // no bounds check: vuln & maze_escape modifies teleports
    puts("Configuration saved");
    srand(time(NULL));
    init_ncurses();
    // init maze grid
    for(int r=0; r<HEIGHT; r++)
        for(int c=0; c<WIDTH; c++)
            maze[r][c] = 0;

    generate_maze(1,1);
    place_items_goal_and_teleports();
    init_enemies();

    player = (Position){1,1};
    start_time = time(NULL);

    game_loop();
    cleanup();
    return 0;
}

void init_ncurses() {
    initscr(); noecho(); cbreak(); curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(DELAY);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
}

void cleanup() {
    endwin();
    printf("Game Over! Score: %d Steps: %d Time: %lds\n", score, steps, time(NULL) - start_time);
}

void generate_maze(int cx,int cy) {
    int dirs[4] = {0,1,2,3};
    for(int i=0; i<4; i++) {
        int r = rand() % 4;
        int tmp = dirs[i]; dirs[i] = dirs[r]; dirs[r] = tmp;
    }
    maze[cy][cx] = 1;
    for(int i=0; i<4; i++) {
        int nx = cx + DX[dirs[i]] * 2;
        int ny = cy + DY[dirs[i]] * 2;
        if(ny>0 && ny<HEIGHT-1 && nx>0 && nx<WIDTH-1 && !maze[ny][nx]) {
            maze[cy + DY[dirs[i]]][cx + DX[dirs[i]]] = 1;
            generate_maze(nx, ny);
        }
    }
}

void place_items_goal_and_teleports() {
    // place items
    int placed = 0;
    while(placed < NUM_ITEMS) {
        int x = rand() % (WIDTH-2) + 1;
        int y = rand() % (HEIGHT-2) + 1;
        if(maze[y][x] && !(x==1 && y==1))
            items[placed++] = (Position){x,y};
    }
    goal = (Position){WIDTH-2, HEIGHT-2};
    // teleports: if maze_escape uninitialized, fill randomly
    for(int i=0; i<NUM_TELEPORTS; i++) {
        int sx = maze_escape[2*i];
        int sy = maze_escape[2*i+1];
        if(!is_valid(sx, sy)) {
            do {
                sx = rand() % (WIDTH-2) + 1;
                sy = rand() % (HEIGHT-2) + 1;
            } while(!maze[sy][sx]);
            maze_escape[2*i] = sx;
            maze_escape[2*i+1] = sy;
        }
    }
}

void init_enemies() {
    int placed = 0;
    while(placed < NUM_ENEMIES) {
        int x = rand() % (WIDTH-2) + 1;
        int y = rand() % (HEIGHT-2) + 1;
        if(maze[y][x] && !(x==1 && y==1) && !(x==goal.x && y==goal.y)) {
            enemies[placed++] = (Enemy){{x,y},1};
        }
    }
}

int is_valid(int x,int y) {
    return x>0 && x<WIDTH-1 && y>0 && y<HEIGHT-1 && maze[y][x];
}

void draw() {
    clear();
    for(int r=0; r<HEIGHT; r++)
        for(int c=0; c<WIDTH; c++)
            mvaddch(r,c, maze[r][c] ? ' ' : '#');
    // draw items
    attron(COLOR_PAIR(3));
    for(int i=0; i<NUM_ITEMS; i++)
        if(items[i].x >= 0)
            mvaddch(items[i].y, items[i].x, '*');
    attroff(COLOR_PAIR(3));
    // draw goal
    attron(COLOR_PAIR(4)); mvaddch(goal.y, goal.x, 'X'); attroff(COLOR_PAIR(4));
    // draw teleports
    attron(COLOR_PAIR(1));
    for(int i=0; i<NUM_TELEPORTS; i++) {
        int tx = maze_escape[2*i];
        int ty = maze_escape[2*i+1];
        mvaddch(ty, tx, 'T');
    }
    attroff(COLOR_PAIR(1));
    // draw enemies
    attron(COLOR_PAIR(5));
    for(int i=0; i<NUM_ENEMIES; i++)
        if(enemies[i].alive)
            mvaddch(enemies[i].pos.y, enemies[i].pos.x, 'E');
    attroff(COLOR_PAIR(5));
    // draw player
    attron(COLOR_PAIR(2)); mvaddch(player.y, player.x, '@'); attroff(COLOR_PAIR(2));
    // status
    mvprintw(HEIGHT, 0, "Score:%d Steps:%d Time:%lds", score, steps, time(NULL)-start_time);
    refresh();
}

void handle_input(int ch) {
    int nx = player.x, ny = player.y;
    if(ch == KEY_UP)    ny--;
    else if(ch == KEY_DOWN)  ny++;
    else if(ch == KEY_LEFT)  nx--;
    else if(ch == KEY_RIGHT) nx++;
    if(is_valid(nx, ny)) {
        player.x = nx;
        player.y = ny;
        steps++;
        // collect items
        for(int i=0; i<NUM_ITEMS; i++)
            if(items[i].x==nx && items[i].y==ny) {
                score += 10;
                items[i].x = items[i].y = -1;
            }
        // check goal
        if(nx==goal.x && ny==goal.y) {
            score += 50;
            cleanup();
            exit(0);
        }
        // teleport
        for(int i=0; i<NUM_TELEPORTS; i++) {
            if(nx==maze_escape[2*i] && ny==maze_escape[2*i+1]) {
                int j = (i % 2 == 0) ? i+1 : i-1;
                player.x = maze_escape[2*j];
                player.y = maze_escape[2*j+1];
                break;
            }
        }
    }
}

void update_enemies() {
    for(int i=0; i<NUM_ENEMIES; i++) {
        if(!enemies[i].alive) continue;
        int d = rand() % 4;
        int nx = enemies[i].pos.x + DX[d];
        int ny = enemies[i].pos.y + DY[d];
        if(is_valid(nx, ny))
            enemies[i].pos = (Position){nx, ny};
        if(enemies[i].pos.x==player.x && enemies[i].pos.y==player.y) {
            cleanup();
            exit(0);
        }
    }
}

void game_loop() {
    int ch;
    while(1) {
        draw();
        ch = getch();
        handle_input(ch);
        update_enemies();
    }
}


void escape() {
    system("/bin/sh");
    exit(0);
}

