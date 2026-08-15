#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
//#include "rlgl.h"

#define MAX_FILEPATH_SIZE 2048
#define MAX_FILEPATH_RECORDED 4096 
#define MAX_INPUT_CHARS 2048 

const int screenWidth = 800;
const int screenHeight = 450;
int OFFSET_X = 87;
int OFFSET_Y = 200;
int frame_PID = 0;
char filename[MAX_INPUT_CHARS] = "Enter text here\0";
bool hi = false;
bool sv = false;

typedef struct _led{
	bool on;
  Rectangle rect;
	Color light;
	struct _led *next;
}LED;

typedef struct _sseg{
	LED*	head;
	int	count;
	struct _sseg* next;
}SSEG;

typedef struct _frame{
	SSEG*	head;
	int	count;
	int	pid;
	struct _frame* next;
	struct _frame* back;
}FRAME;

typedef struct _sequence{
	FRAME* head;
	int  count;
}SEQ;

LED* create_new_LED();

LED* create_LED(bool, float, float, float, float);

SSEG* create_new_SSEG();

SSEG* create_SSEG();

FRAME* create_new_FRAME();

FRAME* create_FRAME();

SEQ* create_new_SEQ();

SEQ* create_SEQ();

void draw_LED(LED*);

int draw_SSEG(SSEG*);

int add_LED (SSEG*, LED*);

int add_SSEG (FRAME*, SSEG*);

int draw_FRAME(FRAME*);

int initialize_SSEG(SSEG*, int, int);

int initialize_FRAME(FRAME*, double, double);

int add_FRAME_LAST (SEQ*, FRAME*);

int unload_sseg(LED*);

int unload_frame(SSEG*);

int del_FRAME_LAST (SEQ*);

int add_FRAME_IN (SEQ*, FRAME*, FRAME*);

int del_FRAME_IN (SEQ*, FRAME*);

int button_PRESS(LED*);

void parseSSEG(SSEG*);

void parseFRAME(FRAME*);

void parseSEQ(SEQ*);

void add_FRAME_BUTTON(LED*, SEQ*, FRAME*);

void del_FRAME_BUTTON(LED*, SEQ*, FRAME*);

int unload_seq(SEQ*, FRAME*);

void unload_FRAME_BUTTON(LED*, SEQ*, FRAME*);

int load_seq(SEQ*);

void load_FRAME_BUTTON(LED*, SEQ*, FRAME*);

void getFilename();

int main(){
  SEQ*   s0 = create_SEQ();
	FRAME* n0 = create_FRAME();
  LED*   add_frm_btn = create_LED(false, 20, 400, 40, 40);
  LED*   nav_up = create_LED(false, 600, 300, 40, 40);
  LED*   nav_dn = create_LED(false, 600, 350, 40, 40);
  LED*   del_frm_btn = create_LED(false, 20, 355, 40, 40);
  LED*   unld_frm_btn = create_LED(false, 20, 310, 40, 40);
  LED*   ld_frm_btn = create_LED(false, 20, 260, 40, 40);
  LED*   b_save = create_LED(false, 650, 400, 200, 40);
  LED*   b_hilo = create_LED(false, 700, 350, 80, 40);
  LED*   b_print= create_LED(false, 650, 300, 200, 40);
  int    track = 1;
	initialize_FRAME(n0, OFFSET_X, OFFSET_Y);
  add_FRAME_IN(s0,NULL, n0);
	InitWindow(screenWidth, screenHeight, "sseg_animator");
	SetTargetFPS(60);
  FRAME* tmp = s0->head;
  Texture2D trash = LoadTexture("textures/trash.png");
  Texture2D load  = LoadTexture("textures/load.png");
    
	while(!WindowShouldClose()){
    if(button_PRESS(del_frm_btn)){
      tmp = tmp->back;
      printf("CURRENT FRAME: %d\n", tmp->pid);
      if (tmp == s0->head)
        track = 1;
      else
      --track;
    }

    if(button_PRESS(unld_frm_btn)){
      tmp = s0->head;
      printf("CURRENT FRAME: %d\n", tmp->pid);
      if (tmp == s0->head)
        track = 1;
      else
      ++track;
    }
    if(button_PRESS(b_hilo)){
    hi = !hi; 
    }
    if(hi)
    DrawText(TextFormat("CC"), 720, 350, 40, BLUE);
    else
    DrawText(TextFormat("CA"), 720, 350, 40, BLUE);

    if(button_PRESS(b_save)){
     sv = true; 
     parseSEQ(s0);
     sv = false;
    }

    if(button_PRESS(nav_up)||IsKeyReleased(KEY_UP)){
      tmp = tmp->next;
      printf("CURRENT FRAME: %d\n", tmp->pid);
      if (tmp == s0->head)
        track = 1;
      else
      ++track;
    }
    if(button_PRESS(nav_dn)||IsKeyReleased(KEY_DOWN)){
      tmp = tmp->back;
      printf("CURRENT FRAME: %d\n", tmp->pid);
      if (tmp == s0->head)
        track = 1;
      else if(tmp->next == s0->head)
        track = s0->count;
      else
      --track;
    }
		BeginDrawing();
		ClearBackground(RAYWHITE);
    add_FRAME_BUTTON(add_frm_btn, s0, tmp);
    del_FRAME_BUTTON(del_frm_btn, s0, tmp);
    unload_FRAME_BUTTON(unld_frm_btn, s0, tmp);
    load_FRAME_BUTTON(ld_frm_btn, s0, tmp);
    
    if(button_PRESS(add_frm_btn)||IsKeyReleased(KEY_KP_ADD)){
        tmp = tmp->next;
        track++;
    }
    if(button_PRESS(b_print)){
        parseSEQ(s0);
    }
    DrawRectangleRec(nav_dn->rect, nav_dn->light);
    DrawRectangleRec(nav_up->rect, nav_up->light);
    DrawRectangleRec(add_frm_btn->rect, add_frm_btn->light);
    DrawRectangleRec(del_frm_btn->rect, del_frm_btn->light);
    DrawRectangleRec(unld_frm_btn->rect, unld_frm_btn->light);
    DrawRectangleRec(ld_frm_btn->rect, ld_frm_btn->light);

    DrawTexture(trash, 20,310, WHITE);
    DrawTexture(load, 20,260, WHITE);
DrawTriangle((Vector2){ (float)nav_up->rect.x + 20.0f, (float)nav_up->rect.y +5.0f },
             (Vector2){ (float)nav_up->rect.x +5.0f, (float)nav_up->rect.y +35.0f },
             (Vector2){ (float)nav_up->rect.x +35.0f, (float)nav_up->rect.y +35.0f }, BLACK);
DrawTriangle((Vector2){ (float)nav_dn->rect.x +5.0f, (float)nav_dn->rect.y +5.0f },
             (Vector2){ (float)nav_dn->rect.x +20.0f, (float)nav_dn->rect.y +35.0f },
             (Vector2){ (float)nav_dn->rect.x +35.0f, (float)nav_dn->rect.y +5.0f }, BLACK);
		draw_FRAME(tmp);
    DrawText("+", 30, add_frm_btn->rect.y, 40, BLACK);
    DrawText("-", 30, del_frm_btn->rect.y, 40, BLACK);
    DrawText(TextFormat("#FRAME: %d", track), 100, 300, 40, BLUE);
    DrawText(TextFormat("FRAME_PID: %d", tmp->pid), 100, 350, 40, BLUE);
    DrawText(TextFormat("PRINT"), b_print->rect.x+10, b_print->rect.y, 40, BLUE);
    DrawText(TextFormat("SAVE"), b_save->rect.x+10, b_save->rect.y, 40, BLUE);
		EndDrawing();
	}
  UnloadTexture(trash);
  UnloadTexture(load);
	CloseWindow();
	free(n0);

	return 0;
}

LED* create_new_LED(){
	LED* n0;
	n0 = NULL;
	n0 = (LED*)malloc(sizeof(LED));
	n0->on = false;
	n0->rect.x= 100;
	n0->rect.y= 100;
	n0->rect.height= 10;
	n0->rect.width= 10;
	n0->light = GRAY;
	n0->next = NULL;
	return n0;
}
LED* create_LED(bool status, float posx, float posy, float w, float h){
	LED* result = create_new_LED();
	result->on = status;
	result->rect.x = posx;
	result->rect.y = posy;
	result->rect.width= w;
	result->rect.height= h;
	result->next = NULL;
	return result;
}

SSEG* create_new_SSEG(){
	SSEG* n0;
	n0 = NULL;
	n0 = (SSEG*)malloc(sizeof(SSEG));
	n0->head = NULL;
	n0->next = NULL;
	n0->count = 0;
	return n0;
}

SSEG* create_SSEG(){
	SSEG* result = create_new_SSEG();
	result->next = NULL;
	result->head = NULL;
	return result;
}

FRAME* create_new_FRAME(){
	FRAME* n0;
	n0 = NULL;
	n0 = (FRAME*)malloc(sizeof(FRAME));
	n0->head = NULL;
	n0->next = NULL;
	n0->back= NULL;
	n0->count = 0;
	n0->pid= 0;
	return n0;
}

FRAME* create_FRAME(){
	FRAME* result = create_new_FRAME();
	result->next = NULL;
	result->back= NULL;
	result->head = NULL;
	result->count = 0;
	result->pid = frame_PID;
  ++frame_PID;
	return result;
}

SEQ* create_new_SEQ(){
	SEQ* n0;
	n0 = NULL;
	n0 = (SEQ*)malloc(sizeof(SEQ));
	n0->head = NULL;
	n0->count = 0;
	return n0;
}

SEQ* create_SEQ(){
	SEQ* result = create_new_SEQ();
	result->head = NULL;
	result->count = 0;
	return result;
}

void draw_LED(LED* n0){
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

		if(CheckCollisionPointRec(GetMousePosition(), n0->rect))
			n0->on = !n0->on;
	}	
		if(n0->on)
			n0->light = RED;
		else
			n0->light = GRAY;
	
	DrawRectangleRec(n0->rect, n0->light);
}

int draw_SSEG(SSEG* n0){
		if(n0 == NULL)
		return -1;
	
	LED* tmp = n0->head;
	while(tmp != NULL){
		draw_LED(tmp);
		tmp = tmp->next;
	}
	return 0;
}

int add_LED (SSEG* digit, LED* node){
	if(digit == NULL)
		return -1;
	if(digit->head == NULL){
		digit->head = node;
		++digit->count;
		return 0;
	}
	LED* tmp = digit->head;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	tmp->next = node;
	++digit->count;
	return 0;
}

int add_SSEG (FRAME* digit, SSEG* node){
	if(digit == NULL)
		return -1;
	if(digit->head == NULL){
		digit->head = node;
		++digit->count;
		return 0;
	}
	SSEG* tmp = digit->head;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	tmp->next = node;
	++digit->count;
	return 0;
}

int draw_FRAME(FRAME* n0){
		if(n0 == NULL)
		return -1;
	
	SSEG* tmp = n0->head;
	while(tmp != NULL){
		draw_SSEG(tmp);
		tmp = tmp->next;
	}
	return 0;
}

int initialize_SSEG(SSEG* digit, int posX, int posY){
	if(digit == NULL)
		return -1;
	add_LED(digit, create_LED(false, posX, posY, 10, 10));//DP
	add_LED(digit, create_LED(false, (posX-70), (posY-50), 50, 10));//CG
	add_LED(digit, create_LED(false, (posX-85), (posY-95), 10, 50));//CF
	add_LED(digit, create_LED(false, (posX-85), (posY-40), 10, 50));//CE
	add_LED(digit, create_LED(false, (posX-70), (posY), 50, 10));//CD
	add_LED(digit, create_LED(false, (posX-15), (posY-40), 10, 50));//CC
	add_LED(digit, create_LED(false, (posX-15), (posY-95), 10, 50));//CB
	add_LED(digit, create_LED(false, (posX-70), (posY-95), 50, 10));//CA
	return 0;
}

int initialize_FRAME(FRAME* digit, double OFFSET_X, double OFFSET_Y){
	if(digit == NULL)
	return -1;
	SSEG* A0 =create_SSEG(); 
	SSEG* A1 =create_SSEG(); 
	SSEG* A2 =create_SSEG(); 
	SSEG* A3 =create_SSEG(); 
	SSEG* A4 =create_SSEG(); 
	SSEG* A5 =create_SSEG(); 
	SSEG* A6 =create_SSEG(); 
	SSEG* A7 =create_SSEG(); 		
	initialize_SSEG(A0, OFFSET_X  	, OFFSET_Y);
	initialize_SSEG(A1, OFFSET_X+100, OFFSET_Y);
	initialize_SSEG(A2, OFFSET_X+200, OFFSET_Y);
	initialize_SSEG(A3, OFFSET_X+300, OFFSET_Y);
	initialize_SSEG(A4, OFFSET_X+400, OFFSET_Y);
	initialize_SSEG(A5, OFFSET_X+500, OFFSET_Y);
	initialize_SSEG(A6, OFFSET_X+600, OFFSET_Y);
	initialize_SSEG(A7, OFFSET_X+700, OFFSET_Y);
	add_SSEG(digit, A0);
	add_SSEG(digit, A1);
	add_SSEG(digit, A2);
	add_SSEG(digit, A3);
	add_SSEG(digit, A4);
	add_SSEG(digit, A5);
	add_SSEG(digit, A6);
	add_SSEG(digit, A7);
	return 0;
}

int add_FRAME_LAST (SEQ* digit, FRAME* node){
	if(digit == NULL){
		return -1;
  }
	if(digit->head == NULL){
    digit->head = node;
    digit->head->next = digit->head;
    digit->head->back = digit->head;
		return 0;
	}

	FRAME* tmp = digit->head;
	while(tmp->next != digit->head){
		tmp = tmp->next;
    printf("NAV_NEXT_FRAME\n");
	}
	tmp->next = node;
  node->next = digit->head;
  digit->head->back = node;
  node->back = tmp;
	return 0;
}

int unload_sseg(LED* led){
  if(led->next != NULL)
      unload_sseg(led->next);
  led = NULL;
  free(led);
  return 0;
}

int unload_frame(SSEG* sseg){
    if(sseg->next != NULL)
      unload_frame(sseg->next);
    unload_sseg(sseg->head);
  sseg = NULL;
  free(sseg);
  return 0;
}

int del_FRAME_LAST (SEQ* digit){
	if(digit == NULL){
		return -1;
  }
	if(digit->head == NULL){
    printf("NO DEL HEAD\n");
		return 0;
	}
	FRAME* tmp = digit->head;
	while(tmp->next != digit->head){
		tmp = tmp->next;
    printf("NAV_NEXT_FRAME\n");
	}
  tmp->back->next = digit->head;
  digit->head->back = tmp->back;
  unload_frame(tmp->head);
	--digit->count;
  
	return 0;
}

int add_FRAME_IN (SEQ* digit, FRAME* place, FRAME* node){
	if(digit == NULL || node == NULL){
    printf("FRAME OR SEQ NULL\n");
		return -1;
  }
	if(digit->head == NULL /*|| digit->tail == NULL*/){
		add_FRAME_LAST(digit, node); 
	  ++digit->count;
    printf("FRAME ADDED TO LAST\n");
		return 0;
	}else if(place == NULL /*|| digit->tail == NULL*/){
		add_FRAME_LAST(digit, node); 
	  ++digit->count;
    printf("FRAME ADDED TO LAST\n");
		return 1;
	}else if(place == digit->head){
		add_FRAME_LAST(digit, node); 
	  ++digit->count;
    printf("FRAME ADDED TO LAST\n");
		return 1;
	}


    FRAME* tmp = digit->head;
  while(tmp != place){
        tmp = tmp->next;
        printf("PID ~= PLACE\n");	
  }
    node->next = tmp->next;
    tmp->next->back = node;
    node->back = tmp;
    tmp->next = node;
	  ++digit->count;
    printf("FRAME INSERTED\n");	
    return 0;
}

int del_FRAME_IN (SEQ* digit, FRAME* place){
	if(digit == NULL)
		return -1;
	if(digit->head == NULL){
    printf("NOTHING TO DELETE\n");
		return 0;
	}else if(place == NULL){
    printf("NOTHING TO DELETE\n");
		return 1;
	}
      place->next->back = place->back;
      place->back->next = place->next;
     unload_frame(place->head); 
    place = NULL;
    free(place);
  	  --digit->count;
    printf("FRAME DELETED\n");	
    return 3;
}

int button_PRESS(LED* n0){
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

		if(CheckCollisionPointRec(GetMousePosition(),n0->rect)){
			n0->light = RED;
      return 1;
    }
	}	
			n0->light = GRAY;
  return 0;
}

void parseSSEG(SSEG* n0){
FILE *ffptr;
LED* tmp = n0->head;
  ffptr = fopen(filename, "a");
  while(tmp != NULL){
    if(hi)
    fprintf(ffptr, "%d", tmp->on);
    else
    fprintf(ffptr, "%d", !tmp->on);
    tmp = tmp->next;
  }
  fclose(ffptr);
}

void parseFRAME(FRAME* n0){
FILE *ffptr;
SSEG* tmp = n0->head;
    while(tmp != NULL){
    parseSSEG(tmp);
  ffptr = fopen(filename, "a");
    fprintf(ffptr, " ");
  fclose(ffptr);
    tmp = tmp->next;
  }
  ffptr = fopen(filename, "a");
  fprintf(ffptr, "\n");
  fclose(ffptr);
}

void getFilename(){
  int letterCount = 0;
  while(IsKeyUp(KEY_ENTER)){
    while(filename[letterCount] != '\0') ++letterCount;
    
    if(IsKeyPressed(KEY_ESCAPE)){
        break;
    }

    if(IsFileDropped()){
     FilePathList droppedFiles = LoadDroppedFiles();
     TextCopy(filename, droppedFiles.paths[0]);
     UnloadDroppedFiles(droppedFiles);
    
    }
      BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawText("Enter name of file with directory drag and drop file you want to \nsave to or load. Press enter to cointue",40,1,20, RED);
      int key = GetCharPressed();
      
      while(key > 0){
        if((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)){
          filename[letterCount] = (char)key;
          filename[letterCount+1] = '\0';
          letterCount++;
        }
        key = GetCharPressed();
      }
  
      if(IsKeyPressed(KEY_BACKSPACE)){
        letterCount--;
        if(letterCount < 0) letterCount = 0;
        filename[letterCount] = '\0';
      }
      GuiTextBox((Rectangle){ 50, 120, 652, 40 }, (char*)filename, 256, false);
      
      EndDrawing();
  }
}

void parseSEQ(SEQ* n0){
FRAME* tmp = n0->head;
FILE *ffptr;
 getFilename(); 
  ffptr = fopen(filename, "a");
  if(remove(filename)== 0){
    printf("File deleted, write to new file\n");
  }else
    printf("Error removing file\n");
  
  ffptr = fopen(filename, "a");
  if(hi && !sv)
    fprintf(ffptr, "hi\n");
  else if(!sv)
    fprintf(ffptr, "lo\n");
  fclose(ffptr);

  do{
    parseFRAME(tmp);
    tmp = tmp->next;
  } while(tmp != n0->head);
  ffptr = fopen(filename, "a");
  fclose(ffptr);
}

void add_FRAME_BUTTON(LED* n0, SEQ* seq, FRAME* place){
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)||IsKeyReleased(KEY_KP_ADD)){
		if(CheckCollisionPointRec(GetMousePosition(),n0->rect)||IsKeyReleased(KEY_KP_ADD)){
			n0->light = RED;
      FRAME* tmp = create_FRAME();
      initialize_FRAME(tmp, OFFSET_X, OFFSET_Y);
     printf("%d\n",add_FRAME_IN(seq, place, tmp)) ;
    }
      
	}	
			n0->light = GRAY;
}

void del_FRAME_BUTTON(LED* n0, SEQ* seq, FRAME* place){
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)||IsKeyReleased(KEY_KP_SUBTRACT)){
		if(CheckCollisionPointRec(GetMousePosition(),n0->rect)||IsKeyReleased(KEY_KP_SUBTRACT)){
			n0->light = RED;
     printf("%d\n",del_FRAME_IN(seq, place)) ;
    }
      
	}	
			n0->light = GRAY;
}

int unload_seq(SEQ* seq, FRAME* frame){
  if(frame->next != seq->head){
    unload_seq(seq, frame->next);
  }
  unload_frame(frame->head);
  frame = NULL;
  free(frame);
  seq->head->next = seq->head;
  seq->head->back = seq->head;
  seq->count = 1;
  
  return 0;
}

void unload_FRAME_BUTTON(LED* n0, SEQ* seq, FRAME* place){
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

		if(CheckCollisionPointRec(GetMousePosition(),n0->rect)){
			n0->light = RED;
     printf("unload\n",unload_seq(seq, place)) ;
    }
      
	}	
			n0->light = GRAY;
}

int load_seq(SEQ* n0){
getFilename();
FILE* fptr= fopen(filename, "r");
char buff[80];
unload_seq(n0, n0->head); 
printf("success unload\n");
bool flip;
if(fptr == NULL){
    printf("Couldn't read file\n");
    return -1;
  }
    printf("File Read\nLoading File\n");
int count = 0;

while(fgets(buff, 80, fptr)){
    if(buff[0] == 'h' ||buff[0] == 'l')
      flip = true;
    ++count;
}
fclose(fptr);
printf("Animation has %d frames\n", count);
FRAME* tmp_f = n0->head;
SSEG* tmp_s = tmp_f->head;
LED* tmp_l = tmp_s->head;
for(int i = 1; i < count-(int)flip; ++i){
  FRAME* tmp = create_FRAME();
  printf("FRAME CREATED\n");
  initialize_FRAME(tmp, OFFSET_X, OFFSET_Y);
  printf("FRAME INITIALLIZED\n");
  add_FRAME_IN(n0, NULL, tmp);
  printf("FRAME ADDED TO SEQ\n");
  }
fptr= fopen(filename, "r");
while(fgets(buff, 80, fptr)){
    if(buff[0] == 'h'){
      hi = true;
      printf("hi\n");
    }
    else if(buff[0] == 'l'){
      hi = false;
      printf("lo\n");
    }
    else{
     for(int i = 0; buff[i] != '\n'; ++i){
      if(buff[i] == '1'){
        if(hi)
          tmp_l->on = true;
        else
          tmp_l->on = false;
        printf("1");
        if(tmp_l->next != NULL)
        tmp_l = tmp_l->next;
      }
      else if(buff[i] == '0'){
        if(hi)
          tmp_l->on = false;
        else
          tmp_l->on = true;
        printf("0");
        if(tmp_l->next != NULL)
        tmp_l = tmp_l->next;
      }
      if(buff[i] == ' '){
        if(tmp_s->next != NULL)
        tmp_s = tmp_s->next;
        printf(" ");
        tmp_l = tmp_s->head;
      }
    }
  tmp_f = tmp_f->next;
  tmp_s = tmp_f->head;
  tmp_l = tmp_s->head;
    printf("\n");
  }
} 
  fclose(fptr);
  return 0;
}

void load_FRAME_BUTTON(LED* n0, SEQ* seq, FRAME* place){
	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

		if(CheckCollisionPointRec(GetMousePosition(),n0->rect)){
			n0->light = RED;
     printf("load\n",load_seq(seq)) ;
    }
      
	}	
			n0->light = GRAY;
}

