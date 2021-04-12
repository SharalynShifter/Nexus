#include <stdlib.h>
#include <libtcod.h>
// size of the heightmap
#define HM_WIDTH 100
#define HM_HEIGHT 80
TCOD_random_t rnd=NULL;
TCOD_noise_t noise=NULL;
// 3x3 kernel for smoothing operations
int smoothKernelSize=9;
int smoothKernelDx[9]={-1,0,1,-1,0,1,-1,0,1};
int smoothKernelDy[9]={-1,-1,-1,0,0,0,1,1,1};
float smoothKernelWeight[9]={1,2,1,2,20,2,1,2,1};
// function building the heightmap
void buildMap(TCOD_heightmap_t *hm) {
	TCOD_heightmap_normalize(hm,0,1);
	TCOD_heightmap_scale_fbm(hm,noise,1,1,0,0,6,0.5,1);
	scaleFbmDelta += HM_WIDTH;
	smoothKernelWeight[4] = 20;
	{
		int i;
		for (i=2; i>= 0; i--) {
			TCOD_heightmap_kernel_transform(hm,smoothKernelSize,smoothKernelDx,smoothKernelDy,smoothKernelWeight,0,0);
		}
	}
	{
		TCOD_heightmap_t *tmp=TCOD_heightmap_new(HM_WIDTH,HM_HEIGHT);
		TCOD_heightmap_add_fbm(tmp,noise,1,1,0,0,6,1,1);
		TCOD_heightmap_lerp(hm,tmp,hm,0);
		TCOD_heightmap_delete(tmp);
	}
}
// test code to print the heightmap
// to compile this file on Linux :
//  gcc hm.c -o hm -I include/ -L . -ltcod
// to compile this file on Windows/mingw32 :
//  gcc hm.c -o hm.exe -I include/ -L lib -ltcod-mingw
int main(int argc, char *argv[]) {
	int x,y;
	TCOD_heightmap_t *hm=TCOD_heightmap_new(HM_WIDTH,HM_HEIGHT);
	rnd=TCOD_random_new_from_seed(3735928559U);
	noise=TCOD_noise_new(2,TCOD_NOISE_DEFAULT_HURST,TCOD_NOISE_DEFAULT_LACUNARITY,rnd);
	buildMap(hm);
	TCOD_console_init_root(HM_WIDTH,HM_HEIGHT,"height map test",false);
	for (x=0; x < HM_WIDTH; x ++ ) {
		for (y=0;y < HM_HEIGHT; y++ ) {
			float z = TCOD_heightmap_get_value(hm,x,y);
			uint8_t val=(uint8_t)(z*255);
			TCOD_color_t c={val,val,val};
			TCOD_console_set_char_background(NULL,x,y,c,TCOD_BKGND_SET);
		}
	}
	TCOD_console_flush();
	TCOD_console_wait_for_keypress(true);
	return 0;
}
