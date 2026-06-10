#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int r = 25;
int c = 80;

char pic[25][80];

typedef struct {
    int id, type, rad;
    int x1, y1;
    int x2, y2;
    int x3, y3;
} shape;

shape data[100];
int total = 0;

void clear_canvas() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            pic[i][j] = '_';
        }
    }
}

void draw_line(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int steps = (dx > dy) ? dx : dy;
    float xin = (float)(x2 - x1) / steps;
    float yin = (float)(y2 - y1) / steps;
    float x = x1, y = y1;

    for (int i = 0; i <= steps; i++) {
        if ((int)x >= 0 && (int)x < 80 && (int)y >= 0 && (int)y < 25) {
            pic[(int)y][(int)x] = '*';
        }
        x += xin;
        y += yin;
    }
}

void draw_rectangle(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; i++) {
        if (y1 >= 0 && y1 < 25 && i >= 0 && i < 80) pic[y1][i] = '*';
        if (y2 >= 0 && y2 < 25 && i >= 0 && i < 80) pic[y2][i] = '*';
    }
    for (int i = y1; i <= y2; i++) {
        if (i >= 0 && i < 25 && x1 >= 0 && x1 < 80) pic[i][x1] = '*';
        if (i >= 0 && i < 25 && x2 >= 0 && x2 < 80) pic[i][x2] = '*';
    }
}

void draw_circle(int cx, int cy, int rad) {
    int rr = rad * rad;
    for (int y = 0; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            int d = (x - cx) * (x - cx) + (y - cy) * (y - cy);
            if (abs(d - rr) <= rad) pic[y][x] = '*';
        }
    }
}

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(x1, y1, x2, y2);
    draw_line(x2, y2, x3, y3);
    draw_line(x3, y3, x1, y1);
}

void render_all() {
    clear_canvas();
    for (int i = 0; i < total; i++) {
        if (data[i].type == 1) draw_line(data[i].x1, data[i].y1, data[i].x2, data[i].y2);
        else if (data[i].type == 2) draw_rectangle(data[i].x1, data[i].y1, data[i].x2, data[i].y2);
        else if (data[i].type == 3) draw_circle(data[i].x1, data[i].y1, data[i].rad);
        else if (data[i].type == 4) draw_triangle(data[i].x1, data[i].y1, data[i].x2, data[i].y2, data[i].x3, data[i].y3);
    }
}

void display_canvas() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            printf("%c", pic[i][j]);
        }
        printf("\n");
    }
}

void add_shape() {
    shape s;
    printf("\n1. Line\n2. Rectangle\n3. Circle\n4. Triangle\nEnter type: ");
    scanf("%d", &s.type);
    s.id = total + 1;

    if (s.type == 1 || s.type == 2) printf("Enter x1 y1 x2 y2: "), scanf("%d%d%d%d", &s.x1, &s.y1, &s.x2, &s.y2);
    else if (s.type == 3) printf("Enter center x center y radius: "), scanf("%d%d%d", &s.x1, &s.y1, &s.rad);
    else if (s.type == 4) printf("Enter x1 y1 x2 y2 x3 y3: "), scanf("%d%d%d%d%d%d", &s.x1, &s.y1, &s.x2, &s.y2, &s.x3, &s.y3);
    else { printf("Invalid Type\n"); return; }

    data[total++] = s;
    render_all();
}

void delete_shape() {
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < total; i++) {
        if (data[i].id == id) {
            found = 1;
            for (int j = i; j < total - 1; j++) data[j] = data[j + 1];
            total--;
            break;
        }
    }
    if (found) { render_all(); printf("Deleted Successfully\n"); }
    else printf("ID Not Found\n");
}

void update_shape() {
    int id, found = 0;
    printf("Enter ID to modify: ");
    scanf("%d", &id);
    for (int i = 0; i < total; i++) {
        if (data[i].id == id) {
            found = 1;
            if (data[i].type == 1 || data[i].type == 2) printf("Enter new x1 y1 x2 y2: "), scanf("%d%d%d%d", &data[i].x1, &data[i].y1, &data[i].x2, &data[i].y2);
            else if (data[i].type == 3) printf("Enter new center x center y radius: "), scanf("%d%d%d", &data[i].x1, &data[i].y1, &data[i].rad);
            else if (data[i].type == 4) printf("Enter new x1 y1 x2 y2 x3 y3: "), scanf("%d%d%d%d%d%d", &data[i].x1, &data[i].y1, &data[i].x2, &data[i].y2, &data[i].x3, &data[i].y3);
            render_all();
            printf("Modified Successfully\n");
            break;
        }
    }
    if (!found) printf("ID Not Found\n");
}

int main() {
    int ch;
    clear_canvas();
    do {
        printf("\n1. Add Shape\n2. Delete Shape\n3. Modify Shape\n4. Display Picture\n5. Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: add_shape(); break;
            case 2: delete_shape(); break;
            case 3: update_shape(); break;
            case 4: display_canvas(); break;
            case 5: printf("Program Ended\n"); break;
            default: printf("Wrong Choice\n");
        }
    } while (ch != 5);
    return 0;
}
