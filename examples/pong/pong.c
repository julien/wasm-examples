#define W 500
#define H 400

extern int setInterval(int (*callback)());
extern int fillRect(int x, int y, int w, int h);
extern int clearRect(int x, int y, int w, int h);
extern float rand(float min, float max);

int runCallback(int (*callback)()) {
  return callback();
}

typedef struct Vec2 {
  float x;
  float y;
} Vec2;

typedef struct Rect {
  float x;
  float y;
  float w;
  float h;
} Rect;

typedef enum Type {
  WALL,
  BALL
} Type;

typedef struct Object {
  Type t;
  Rect r;
  Vec2 v;
} Object;

const float startx = (W - 5) * 0.5;
const float starty = (H - 5) * 0.5;

Object world[] = {
  /* walls */
  {.r = {0, 0, W, 16},      .t = WALL},
  {.r = {0, H - 16, W, 16}, .t = WALL},
  {.r = {0, 0, 16, H},      .t = WALL},
  {.r = {W - 16, 0, 16, H}, .t = WALL},

  /* paddles */
  {
    .r = {20, (H - 50) * 0.5, 10, 50},
    .v = {0.0f, 1.5f}
  },
  {
    .r = {W - (10 + 20), (H - 50) * 0.5, 10, 50},
    .v = {0.0f, 1.5f}
  },

  /* ball */
  {
    .t = BALL,
    .r = {startx, starty, 5, 5},
    .v = {2.5f, 1.25f}
  }
};

int drawWorld() {
  int c = sizeof(world) / sizeof(Object);
  for (int i = 0; i < c; i++) {
    Rect r = world[i].r;
    fillRect(r.x, r.y, r.w, r.h);
  }
  return 0;
}

int inRange(float val, float min, float max) {
  return (val >= min) && (val <= max);
}

int overlap(Rect *a, Rect *b) {
  int x = inRange(a->x, b->x, b->x + b->w) ||
    inRange(b->x, a->x, a->x + a->w);

  int y = inRange(a->y, b->y, b->y + b->h) ||
    inRange(b->y, a->y, a->y + a->h);

  return x && y;
}

void move(Object *o) {
  int c = sizeof(world) / sizeof(Object);

  Rect n = o->r;
  n.x += o->v.x;
  n.y += o->v.y;

  for (int i = 0; i < c; i++) {
    Rect r = world[i].r;

    if (world[i].t == o->t) {
      continue;
    }

    if (o != &world[i] && overlap(&n, &r)) {
      n = o->r;
      n.x += o->v.x;

      if (overlap(&n, &r)) {
        o->v.x *= -1;
      }

      n.y += o->v.y;

      if (overlap(&n, &r)) {
        o->v.y *= -1;
      }
    }
  }
  o->r = n;
}

void moveBall(Object *o) {
  Rect n = o->r;
  n.x += o->v.x;
  n.y += o->v.y;
}

void movePaddle(Object *o) {
  Rect n = o->r;
  n.y += o->v.y;

  int top = 10;
  int bottom = H - (n.h + 10);

  if (n.y <= top || n.y >= bottom) {
    o->v.y *= -1;
  }
  o->r = n;
}

int tick() {
  clearRect(0, 0, W, H);
  drawWorld();
  movePaddle(&world[4]);
  movePaddle(&world[5]);
  move(&world[6]);
  return 0;
}

void randomizeVelocity(Object *o) {
  Vec2 v = o->v;
  v.y = rand(-3.5f, 2.5f);
  o->v = v;
}

int main() {
  randomizeVelocity(&world[4]);
  randomizeVelocity(&world[5]);

  setInterval(tick);
  return 0;
}

