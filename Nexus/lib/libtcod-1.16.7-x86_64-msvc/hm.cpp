#include <libtcod.h>
// size of the heightmap
#define HM_WIDTH 100
#define HM_HEIGHT 80
TCODRandom *rnd=new TCODRandom(3735928559U);
TCODNoise *noise=new TCODNoise(2,rnd);
// 3x3 kernel for smoothing operations
int smoothKernelSize=9;
int smoothKernelDx[9]={-1,0,1,-1,0,1,-1,0,1};
int smoothKernelDy[9]={-1,-1,-1,0,0,0,1,1,1};
float smoothKernelWeight[9]={1,2,1,2,20,2,1,2,1};
// function building the heightmap
void buildMap(TCODHeightMap *hm) {
	hm->normalize(0,1);
	hm->scaleFbm(noise,1,1,0,0,6,0.5,1);
	scaleFbmDelta += HM_WIDTH;
	smoothKernelWeight[4] = 20;
	for (int i=2; i>= 0; i--) {
		hm->kernelTransform(smoothKernelSize,smoothKernelDx,smoothKernelDy,smoothKernelWeight,0,0);
	}
	{
		TCODHeightMap tmp(HM_WIDTH,HM_HEIGHT);
		tmp.addFbm(noise,1,1,0,0,6,1,1);
		hm->lerp(hm,&tmp,0);
	}
}
// test code to print the heightmap
// to compile this file on Linux :
//  g++ hm.cpp -o hm -I include/ -L . -ltcod -ltcod++
// to compile this file on Windows/mingw32 :
//  g++ hm.cpp -o hm.exe -I include/ -L lib -ltcod-mingw
int main(int argc, char *argv[]) {
	TCODHeightMap hm(HM_WIDTH,HM_HEIGHT);
	buildMap(&hm);
	TCODConsole::initRoot(HM_WIDTH,HM_HEIGHT,"height map test",false);
	for (int x=0; x < HM_WIDTH; x ++ ) {
		for (int y=0;y < HM_HEIGHT; y++ ) {
			float z = hm.getValue(x,y);
			uint8_t val=(uint8_t)(z*255);
			TCODColor c(val,val,val);
			TCODConsole::root->setCharBackground(x,y,c);
		}
	}
	TCODConsole::root->flush();
	TCODConsole::waitForKeypress(true);
	return 0;
}
