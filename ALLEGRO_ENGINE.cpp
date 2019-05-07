#include <allegro.h>

// DECLARACOES INICIAIS //
int sair=0; void sair_allegro() {sair=1;}; 
int timer=0; void tempo() {timer++;};
int Ctrl_FPS=60; float delay=0;

// INICIALIZACAO ALLEGRO //
int main()
{
  allegro_init();
  install_timer();
  install_keyboard();
  install_mouse(); 
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  install_int_ex(tempo, BPS_TO_TIMER(60)); //60fps
  set_window_title("ALLEGRO MINIMAL");
  set_close_button_callback( sair_allegro );
  install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
  BITMAP *buffer = create_bitmap(640,480);
  int line1_x1=50;
	int line1_y1=50;
	int line1_x2=200;
	int line1_y2=50;
	int line2_x1=160;
	int line2_y1=120;
	int line2_x2=480;
	int line2_y2=360;
	int PontoInterseccao_x=-99;
	int PontoInterseccao_y=-99;
	double s;
	double t;
  
  // LOOP DE JOGO //
  while (sair==0)
  {
  delay=timer; 
	if (key[KEY_ESC]) {sair=1;}; 
	clear_to_color(buffer,makecol(255,255,255));
	
	/* < SEU CODIGO AQUI! > */

	//ajusta posicao da linha
  if (mouse_b & 1) { line1_x1=mouse_x; line1_y1=mouse_y; };
  if (mouse_b & 2) { line1_x2=mouse_x; line1_y2=mouse_y; };
  
  //calcula a instersecção de linhas
  double det;
	int colisao=0;
	det = (line2_x2 - line2_x1) * (line1_y2 - line1_y1)  -  (line2_y2 - line2_y1) * (line1_x2 - line1_x1);
	if (det == 0.0)	{ colisao=0; PontoInterseccao_x=-99; PontoInterseccao_y=-99; } // não há intersecção
	s = ((line2_x2 - line2_x1) * (line2_y1 - line1_y1) - (line2_y2 - line2_y1) * (line2_x1 - line1_x1))/ det ;
	t = ((line1_x2 - line1_x1) * (line2_y1 - line1_y1) - (line1_y2 - line1_y1) * (line2_x1 - line1_x1))/ det ;
	if (s>=0 and s<=1 and t>=0 and t<=1) { colisao=1; } //existe insterseccao
	
	//calcula Ponto de Interseccao
	if(colisao==1){
		PontoInterseccao_x = line1_x1 + (line1_x2-line1_x1)*s;
		PontoInterseccao_y = line1_y1 + (line1_y2-line1_y1)*s;
		circle(buffer, PontoInterseccao_x, PontoInterseccao_y, 5, makecol(0,0,0));
	}
					
	//desenha linhas
	line(buffer, line1_x1, line1_y1, line1_x2, line1_y2, makecol(255, 0, 0));
	line(buffer, line2_x1, line2_y1, line2_x2, line2_y2, makecol(0, 0, 255));
	
	//mouse
	line(buffer, mouse_x-20, mouse_y, mouse_x+20, mouse_y, makecol(000, 000, 000));
	line(buffer, mouse_x, mouse_y-20, mouse_x, mouse_y+20, makecol(000, 000, 000));
	circlefill(buffer, mouse_x, mouse_y, 2, makecol(0,0,0));
	
	//desenha na tela
  textprintf_ex(buffer, font, 5, 5, makecol(000,000,000), -1, "Use o botao esquerdo e direito do mouse para desenhar a linha1");
  if (colisao==1) { textprintf_ex(buffer, font, mouse_x-30, mouse_y-30, makecol(000,000,000), -1, "colisao!!!"); };
	draw_sprite(screen, buffer, 0, 0);
		
  // FINALIZACOES //
	while(timer==delay){};	
	clear(buffer);
  }; 
  destroy_bitmap(buffer);
  return 0;
};
END_OF_MAIN();
